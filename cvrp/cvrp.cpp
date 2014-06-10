#include <iostream>
#include <cmath>
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>

#include "cvrp.h"

namespace VrpSolver {

    void read_vrp(Problem *, const std::string &infile);

    void Cvrp::read_vrp(const std::string &infile) {
        VrpSolver::read_vrp(problem_, infile);

        // 車体数の設定(TSPLIB formatでは明示的に示されていないので
        // ファイル名から読み取る
        size_t i = infile.rfind('k');
        size_t j = infile.rfind('.');
        std::istringstream iss(infile.substr(i+1, j));
        iss >> num_vehicles_;
        if (!iss)
            throw std::runtime_error("error: can not read number of vehicles");
    }

    std::string Cvrp::name() const {
        return problem_->name_;
    }

    unsigned int Cvrp::dimension() const {
        return problem_->dimension_;
    }

    unsigned int Cvrp::capacity() const {
        return problem_->capacity_;
    }

    unsigned int Cvrp::demand(unsigned int node_id) const {
        if ((1 > node_id) || (node_id > problem_->dimension_))
            throw std::out_of_range("error: in Cvrp::demand");
        return problem_->customers_[node_id].demand();
    }

    unsigned int Cvrp::num_vehicles() const {
        return num_vehicles_;
    }

    unsigned int Cvrp::distance(unsigned int from, unsigned int to) const {
        if ((0 > from) || (from > problem_->dimension_) ||
            (0 > to) || (to > problem_->dimension_))
            throw std::out_of_range("error: in Cvrp::distance");

        const int index = (to > from) ? ((to-1)*(to)/2+(from)) :
                                        ((from-1)*(from)/2+(to));
        return problem_->distances_[index];
    }

    const DistanceList &Cvrp::distance_list() const {
        return problem_->distances_;
    }

    const CustomerList &Cvrp::customer_list() const {
        return problem_->customers_;
    }

    unsigned int distance(const DistanceList& dlist, 
                          const Customer& c1, const Customer& c2) {
        const int from = c1.id();
        const int to   = c2.id();
        const int index = (to > from) ? ((to-2)*(to-1)/2+(from-1)) :
                                        ((from-2)*(from-1)/2+(to-1));
        return dlist[index];
    }

    // 文字列strからtrim_char文字列に含まれている文字を削除
    void trim(std::string& str, const std::string& trim_char) {
        size_t pos;
        while ((pos = str.find_first_of(trim_char)) != std::string::npos)
            str.erase(pos, 1);
    }

    // セミコロン以後の文字列(空白の直前まで)を読み取る
    std::string get_parameter(std::ifstream& ifs) {
        std::string param;
        ifs >> param;
        while (param == ":") ifs >> param; // ":"は読み飛ばす
        return param;
    }

    typedef std::string keyword;

    enum TsplibKeyword {
        // The specification part
        NAME, TYPE, COMMENT, DIMENSION, CAPACITY,
        EDGE_WEIGHT_TYPE, EDGE_WEIGHT_FORMAT, EDGE_DATA_FORMAT,
        NODE_COORD_TYPE, DISPLAY_DATA_TYPE, END_OF_FILE,

        // The data part
        NODE_COORD_SECTION, DEPOT_SECTION, DEMAND_SECTION,
        EDGE_DATA_SECTION, EDGE_WEIGHT_SECTION,
    };

    std::map<keyword, TsplibKeyword> keyword_map = {
        // The specification part
        { "NAME",                NAME },
        { "TYPE",                TYPE },
        { "COMMENT",             COMMENT },
        { "DIMENSION",           DIMENSION },
        { "CAPACITY",            CAPACITY },
        { "EDGE_WEIGHT_TYPE",    EDGE_WEIGHT_TYPE },
        { "EDGE_WEIGHT_FORMAT",  EDGE_WEIGHT_FORMAT },
        { "EDGE_DATA_FORMAT",    EDGE_DATA_FORMAT },
        { "NODE_COORD_TYPE",     NODE_COORD_TYPE },
        { "DISPLAY_DATA_TYPE",   DISPLAY_DATA_TYPE },
        { "EOF",                 END_OF_FILE },

        // The data part
        { "NODE_COORD_SECTION",  NODE_COORD_SECTION },
        { "DEPOT_SECTION",       DEPOT_SECTION },
        { "DEMAND_SECTION",      DEMAND_SECTION },
        { "EDGE_DATA_SECTION",   EDGE_DATA_SECTION },
        { "EDGE_WEIGHT_SECTION", EDGE_WEIGHT_SECTION }
    };

    enum EdgeWeightType {
        EXPLICIT, EUC_2D
    };

    std::map<keyword, EdgeWeightType> ew_type_map = {
        { "EXPLICIT", EXPLICIT },
        { "EUC_2D",   EUC_2D }
    };

    enum EdgeWeightFormat {
        LOWER_ROW
    };

    std::map<keyword, EdgeWeightFormat> ew_format_map = {
        { "LOWER_ROW", LOWER_ROW }
    };

    // infileから情報を読み取りCvrpクラスをセットアップする
    void read_vrp(Problem *problem, const std::string &infile) {
        std::ifstream ifs(infile.c_str());
        if (!ifs)
            throw std::runtime_error("error: can't open file " + infile);

        EdgeWeightType   edge_weight_type = EXPLICIT;
        EdgeWeightFormat edge_weight_format = LOWER_ROW;

        while (ifs) {
            keyword tsp_keyword;
            ifs >> tsp_keyword;
            if (ifs.eof()) break;
            trim(tsp_keyword, " :");
            switch (keyword_map[tsp_keyword]) {

                // The specification part
                case NAME :
                    problem->name_ = get_parameter(ifs);
                    break;
                case TYPE :
                    {
                        std::string not_use;
                        getline(ifs, not_use);
                    }
                    break;
                case COMMENT :
                    {
                        std::string not_use;
                        getline(ifs, not_use);
                    }
                    break;
                case DIMENSION :
                    problem->dimension_ = stoi(get_parameter(ifs));
                    break;
                case CAPACITY :
                    problem->capacity_ = stoi(get_parameter(ifs));
                    break;
                case EDGE_WEIGHT_TYPE :
                    edge_weight_type = ew_type_map[get_parameter(ifs)];
                    break;
                case EDGE_WEIGHT_FORMAT :
                    edge_weight_format = ew_format_map[get_parameter(ifs)];
                    break;
                case EDGE_DATA_FORMAT :
                    {
                        std::string not_use;
                        getline(ifs, not_use);
                    }
                    break;
                case NODE_COORD_TYPE :
                    {
                        std::string not_use;
                        getline(ifs, not_use);
                    }
                    break;
                case DISPLAY_DATA_TYPE :
                    {
                        std::string not_use;
                        getline(ifs, not_use);
                    }
                    break;
                case END_OF_FILE :
                    // do nothing
                    break;

                // The data part
                case NODE_COORD_SECTION :
                    {
                        int m, x, y; // m do not use
                        for (int i=0; i != static_cast<int>(problem->dimension_); i++) {
                            ifs >> m >> x >> y;
                            std::pair<int,int> c(x,y);
                            problem->coords_.push_back(c);
                        }
                    }
                    break;
                case DEPOT_SECTION :
                    {
                        problem->depot_ = stoi(get_parameter(ifs));
                        if (stoi(get_parameter(ifs)) != -1)
                            throw std::runtime_error("error:"
                                    "can't handle multiple depots");
                    }
                    break;
                case DEMAND_SECTION :
                    {
                        // demandの番号は1であると仮定
                        // Customerのidは0から開始するためにnode_idから
                        // 2を引いている
                        unsigned int node_id, demand;
                        ifs >> node_id >> demand; // depotの情報は捨てる
                        for (int i=0; i < static_cast<int>(problem->dimension_-1); i++) {
                            ifs >> node_id >> demand;
                            if (static_cast<int>(node_id-2) != i)
                                throw std::runtime_error("error:"
                                        "DEMAND_SECTION format may be different");
                            problem->customers_.push_back(Customer(node_id-1, demand));
                        }
                    }
                    break;
                case EDGE_DATA_SECTION :
                    throw std::runtime_error("Sorry, can not handle 'EDGE_DATA_SECTION'");
                    break;
                case EDGE_WEIGHT_SECTION :
                    {
                        if (edge_weight_format != LOWER_ROW)
                            throw std::runtime_error("Sorry, can not handle except EDGE_WEIGHT_FORMAT == LOWER_ROW");
                        for (int i=0; i < static_cast<int>(problem->dimension_); i++) {
                            for (int j=0; j < i; j++) {
                                int distance;
                                ifs >> distance;
                                problem->distances_.push_back(distance);
                            }
                        }
                    }
                    break;

                default :
                    throw std::runtime_error("error: unknown keyword '" + tsp_keyword + "'");
                    break;
            }
        }

        // distancesの設定
        if (edge_weight_type != EXPLICIT) {
            auto& distances = problem->distances_;
            auto& coords    = problem->coords_;
            for (int i=0; i < static_cast<int>(problem->dimension_); i++) {
                for (int j=0; j < i; j++) {
                    int dx = coords[j].first  - coords[i].first;
                    int dy = coords[j].second - coords[i].second;
                    distances.push_back(floor(sqrt(dx*dx + dy*dy)+0.5));
                }
            }
        }
    }

} // namespace VrpSolver
