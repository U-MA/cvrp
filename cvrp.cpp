#include <sstream>
#include <fstream>
#include <stdexcept>
#include <cmath>

#include "cvrp.h"
#include "tsplib_format.h"

namespace VrpSolver {

    unsigned int Cvrp::demand(unsigned int node_id) const {
        if ((1 > node_id) || (node_id > dimension_))
            throw std::out_of_range("error: in Cvrp::demand");
        return demands_[node_id];
    }

    int Cvrp::distance(unsigned int from, unsigned int to) const {
        if ((1 > from) || (from > dimension_) ||
            (1 > to) || (to > dimension_))
            throw std::out_of_range("error: in Cvrp::distance");

        const int index = (to > from) ? ((to-2)*(to-1)/2+(from-1)) :
                                        ((from-2)*(from-1)/2+(to-1));
        return distances_[index];
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

    // infileから情報を読み取りCvrpクラスをセットアップする
    void read_vrp(Cvrp& cvrp, const std::string &infile) {
        std::ifstream ifs(infile.c_str());
        if (!ifs)
            throw std::runtime_error("error: can't open file " + infile);

        std::string edge_weight_type,
                    edge_weight_format,
                    display_data_type;

        while (!ifs.eof()) {
            std::string tsp_keyword;
            ifs >> tsp_keyword;
            trim(tsp_keyword, " :");
            if (tsp_keyword == Tsplib::NAME) {
                cvrp.name_ = get_parameter(ifs);
            }
            else if (tsp_keyword == Tsplib::DIMENSION) {
                cvrp.dimension_ = stoi(get_parameter(ifs));
            }
            else if (tsp_keyword == Tsplib::CAPACITY) {
                cvrp.capacity_ = stoi(get_parameter(ifs));
            }
            else if (tsp_keyword == Tsplib::DEMAND_SECTION) {
                cvrp.demands_.push_back(0); // 0要素目は0にしておく
                for (int i=1; i <= cvrp.dimension_; i++) {
                    unsigned int node_id, demand;
                    ifs >> node_id >> demand;
                    if (node_id != i)
                        throw std::runtime_error("error:"
                              "DEMAND_SECTION format may be different");
                    cvrp.demands_.push_back(demand);
                }
            }
            else if (tsp_keyword == Tsplib::EDGE_WEIGHT_TYPE) {
                edge_weight_type = get_parameter(ifs);
            }
            else if (tsp_keyword == Tsplib::EDGE_WEIGHT_FORMAT) {
                edge_weight_format = get_parameter(ifs);
            }
            else if (tsp_keyword == Tsplib::DISPLAY_DATA_TYPE) {
                display_data_type = get_parameter(ifs);
            }
            else if (tsp_keyword == Tsplib::EDGE_WEIGHT_SECTION) {
                if (edge_weight_format == Tsplib::EdgeWeightFormat::LOWER_ROW) {
                    int num=0;
                    for (int i=0; i < cvrp.dimension_; i++) {
                        for (int j=0; j < i; j++) {
                            int weight;
                            ifs >> weight;
                            cvrp.distances_.push_back(weight);
                            num++;
                        }
                    }
                    // n点からなる完全グラフの枝数はn * (n-1) / 2
                    const int num_edges = cvrp.dimension_ * (cvrp.dimension_-1) / 2;
                    if (num != num_edges)
                        throw std::runtime_error("error:"
                              "EDGE_WEIGHT_SECTION may be differnt");
                }
            }
            else if (tsp_keyword == Tsplib::NODE_COORD_SECTION) {
                int n=1, m, x, y;
                while (n != cvrp.dimension_) {
                    ifs >> n >> x >> y;
                    std::pair<int,int> c(x,y);
                    cvrp.coords_.push_back(c);
                    n++;
                }
            }
            else if (tsp_keyword == Tsplib::DEPOT_SECTION) {
                cvrp.depot_ = stoi(get_parameter(ifs));
                if (stoi(get_parameter(ifs)) != -1)
                    throw std::runtime_error("error:"
                          "can't handle multiple depots");
            }
        }
        // distancesの設定
        if (edge_weight_type != Tsplib::EdgeWeightType::EXPLICIT) {
            auto& distances = cvrp.distances_;
            auto& coords    = cvrp.coords_;
            for (int i=0; i < cvrp.dimension_; i++) {
                for (int j=0; j < i; j++) {
                    int dx = coords[j].first  - coords[i].first;
                    int dy = coords[j].second - coords[i].second;
                    distances.push_back(floor(sqrt(dx*dx + dy*dy)+0.5));
                }
            }
        }
    }
} // namespace VrpSolver
