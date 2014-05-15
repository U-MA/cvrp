#include <sstream>
#include <fstream>
#include <stdexcept>

#include "cvrp.h"

namespace VrpSolver {

    inline unsigned int Cvrp::demand(unsigned int node_id) {
        return demands_[node_id];
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

    // 文字列を整数に変換する
    int stoi(std::string str) {
        std::istringstream iss(str);
        int i;
        iss >> i;
        return i;
    }

    // infileから情報を読み取りCvrpクラスをセットアップする
    void read_vrp(Cvrp& cvrp, const std::string &infile) {
        std::ifstream ifs(infile.c_str());
        if (!ifs) {
            throw std::runtime_error("can't open file " + infile);
        }

        std::string edge_weight_type,
                    edge_weight_format,
                    display_data_type;

        while (!ifs.eof()) {
            std::string tag;
            ifs >> tag;
            trim(tag, " :");
            if (tag == "NAME") {
                cvrp.name_ = get_parameter(ifs);
            }
            else if (tag == "DIMENSION") {
                cvrp.dimension_ = VrpSolver::stoi(get_parameter(ifs));
            }
            else if (tag == "CAPACITY") {
                cvrp.capacity_ = VrpSolver::stoi(get_parameter(ifs));
            }
            else if (tag == "DEMAND_SECTION") {
                for (int i=0; i < cvrp.dimension_; i++) {
                    unsigned int node_id, demand;
                    ifs >> node_id >> demand;
                    if (node_id != i+1)
                        throw std::runtime_error("error:"
                              "DEMAND_SECTION format may be different");
                    cvrp.demands_.push_back(demand);
                }
            }
            else if (tag == "EDGE_WEIGHT_TYPE") {
                edge_weight_type = get_parameter(ifs);
            }
            else if (tag == "EDGE_WEIGHT_FORMAT") {
                edge_weight_format = get_parameter(ifs);
            }
            else if (tag == "DISPLAY_DATA_TYPE") {
                display_data_type = get_parameter(ifs);
            }
            else if (tag == "DEPOT_SECTION") {
                cvrp.depot_ = VrpSolver::stoi(get_parameter(ifs));
                if (VrpSolver::stoi(get_parameter(ifs)) != -1)
                    throw std::runtime_error("error:"
                          "can't handle multiple depots");
            }
            // 車体数を読み込むのは最後
        }
    }
}
