#include <sstream>
#include <fstream>
#include <stdexcept>

#include "cvrp.h"

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

    // infileから情報を読み取りCvrpクラスをセットアップする
    void read_vrp(Cvrp& cvrp, const std::string &infile) {
        std::ifstream ifs(infile.c_str());
        if (!ifs) {
            throw std::runtime_error("can't open file "+infile);
        }

        while (!ifs.eof()) {
            std::string tag;
            ifs >> tag;
            trim(tag, " :");
            if (tag == "NAME") {
                cvrp.name_ = get_parameter(ifs);
            }
            else if (tag == "DIMENSION") {
                std::istringstream iss(get_parameter(ifs));
                iss >> cvrp.dimension_;
            }
            else if (tag == "CAPACITY") {
                std::istringstream iss (get_parameter(ifs));
                iss >> cvrp.capacity_;
            }
            // 車体数を読み込むのは最後
        }
    }
}
