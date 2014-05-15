#include <iostream>
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

    // infileから情報を読み取りCvrpクラスをセットアップする
    void read_vrp(Cvrp& cvrp, const std::string &infile) {
        std::ifstream ifs(infile.c_str());
        if (!ifs) {
            throw std::runtime_error("can't open file "+infile);
        }

        while (!ifs.eof()) {
            std::string tag;
            ifs >> tag;
            trim(tag, " ");
            if (tag == "NAME") {
                std::string name;
                ifs >> name;
                while (name == ":") ifs >> name; // ':'は読み飛ばす
                cvrp.name_ = name;
            }
        }
    }
}
