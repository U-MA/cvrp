#ifndef VRPSOLVER_CVRP_H

#include <string>
#include <vector>

namespace VrpSolver {
    class Cvrp {
    public:
        Cvrp() : name_(), dimension_(0), capacity_(0), demands_(0) {}

        // accessor
        unsigned int demand(unsigned int node_id) const;
        int distance(unsigned int from, unsigned int to) const;

        // member variable
        std::string name_;
        unsigned int dimension_;
        unsigned int capacity_;
        unsigned int depot_;
        std::vector<unsigned int> demands_;
        std::vector<int> distances_;
    };

    // cvrp intialize by infile
    void read_vrp(Cvrp& cvrp, const std::string &infile);
}

#endif // VRPSOLVER_CVRP_H
