#include <cmath>
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>

#include "cvrp.h"
#include "tsplib_format.h"

namespace VrpSolver {

    void Cvrp::read_vrp(const std::string &infile) {
        VrpSolver::read_vrp(problem_, infile);
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
        return problem_->demands_[node_id];
    }

    int Cvrp::distance(unsigned int from, unsigned int to) const {
        if ((1 > from) || (from > problem_->dimension_) ||
            (1 > to) || (to > problem_->dimension_))
            throw std::out_of_range("error: in Cvrp::distance");

        const int index = (to > from) ? ((to-2)*(to-1)/2+(from-1)) :
                                        ((from-2)*(from-1)/2+(to-1));
        return problem_->distances_[index];
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

        EdgeWeightType   edge_weight_type;
        EdgeWeightFormat edge_weight_format;

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
                        int n=0, m, x, y; // m do not use
                        for (int i=0; i != problem->dimension_; i++) {
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
                        problem->demands_.push_back(0); // 0要素目は0にしておく
                        for (int i=1; i <= problem->dimension_; i++) {
                            unsigned int node_id, demand;
                            ifs >> node_id >> demand;
                            if (node_id != i)
                                throw std::runtime_error("error:"
                                        "DEMAND_SECTION format may be different");
                            problem->demands_.push_back(demand);
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
                        for (int i=0; i < problem->dimension_; i++) {
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
            for (int i=0; i < problem->dimension_; i++) {
                for (int j=0; j < i; j++) {
                    int dx = coords[j].first  - coords[i].first;
                    int dy = coords[j].second - coords[i].second;
                    distances.push_back(floor(sqrt(dx*dx + dy*dy)+0.5));
                }
            }
        }
    }

} // namespace VrpSolver