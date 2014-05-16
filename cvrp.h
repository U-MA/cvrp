#ifndef VRPSOLVER_CVRP_H

#include <utility>
#include <string>
#include <vector>

namespace VrpSolver {

    class Cvrp {
    public:
        Cvrp() : name_(), dimension_(0), capacity_(0), demands_(0) {}

        // accessor
        // 範囲外は無視する
        unsigned int demand(unsigned int node_id) const {
            return demands_[node_id];
        }

        // 範囲外は無視する
        int distance(unsigned int from, unsigned int to) const {
            const int index = (to > from) ? ((to-2)*(to-1)/2+(from-1)) :
                ((from-2)*(from-1)/2+(to-1));
            return distances_[index];
        }


        // member variable
        std::string name_;
        unsigned int dimension_;
        unsigned int capacity_;
        unsigned int depot_;
        std::vector<unsigned int> demands_;
        std::vector<int> distances_;
        std::vector<std::pair<int,int>> coords_;
    };

    // cvrp intialize by infile
    void read_vrp(Cvrp& cvrp, const std::string &infile);
}

#endif // VRPSOLVER_CVRP_H
