#include <iostream>
#include <cmath>
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>

#include "cvrp.h"
#include <cvrp/tsplib_keyword.h>

namespace VrpSolver {

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

    void Cvrp::read_vrp(const std::string &infile) {
        std::ifstream ifs(infile.c_str());
        if (!ifs)
            throw std::runtime_error("error: can't open file " + infile);

        EdgeWeightType   edge_weight_type   = EXPLICIT;
        EdgeWeightFormat edge_weight_format = LOWER_ROW;

        while (ifs) {
            keyword tsp_keyword;
            ifs >> tsp_keyword;
            if (ifs.eof()) break;
            trim(tsp_keyword, " :");
            switch (keyword_map[tsp_keyword]) {

                // The specification part
                case NAME :
                    name_ = get_parameter(ifs);
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
                    dimension_ = stoi(get_parameter(ifs));
                    break;
                case CAPACITY :
                    capacity_ = stoi(get_parameter(ifs));
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
                        for (std::size_t i=0; i != dimension_; i++) {
                            ifs >> m >> x >> y;
                            cinfo_.push_back(Customer(i, 0, x, y));
                        }
                    }
                    break;
                case DEPOT_SECTION :
                    {
                        depot_ = stoi(get_parameter(ifs));
                        if (stoi(get_parameter(ifs)) != -1)
                            throw std::runtime_error("error:"
                                    "can't handle multiple depots");
                    }
                    break;
                case DEMAND_SECTION :
                    {
                        unsigned int node_id, demand;
                        ifs >> node_id >> demand;
                        for (std::size_t i=0; i < dimension_; i++) {
                            ifs >> node_id >> demand;
                            cinfo_[i].demand(demand);
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
                        for (std::size_t i=0; i < dimension_; i++) {
                            for (std::size_t j=0; j < i; j++) {
                                int distance;
                                ifs >> distance;
                                dlist_.push_back(distance);
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
            for (std::size_t i=0; i < dimension_; i++) {
                for (std::size_t j=0; j < i; j++) {
                    int dx = cinfo_[j].x() - cinfo_[i].x();
                    int dy = cinfo_[j].y() - cinfo_[i].y();
                    dlist_.push_back(floor(sqrt(dx*dx + dy*dy)+0.5));
                }
            }
        }

        // 車体数の設定(TSPLIB formatでは明示的に示されていないので
        // ファイル名から読み取る
        size_t i = infile.rfind('k');
        size_t j = infile.rfind('.');
        std::istringstream iss(infile.substr(i+1, j));
        iss >> num_vehicles_;
        if (!iss)
            throw std::runtime_error("error: can not read number of vehicles");
    }

    std::size_t Cvrp::demand(unsigned int node_id) const {
        if (node_id > dimension_)
            throw std::out_of_range("error: in Cvrp::demand");
        return cinfo_[node_id].demand();
    }

    std::size_t Cvrp::distance(unsigned int from, unsigned int to) const {
        if (from > dimension_ || to > dimension_)
            throw std::out_of_range("error: in Cvrp::distance");

        const int index = (to > from) ? ((to-1)*(to)/2+(from)) :
                                        ((from-1)*(from)/2+(to));
        return dlist_[index];
    }

} // namespace VrpSolver
