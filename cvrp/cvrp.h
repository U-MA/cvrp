#ifndef VRPSOLVER_CVRP_H
#define VRPSOLVER_CVRP_H

#include <utility>
#include <string>
#include <vector>

namespace VrpSolver {

    struct Problem {
        Problem() : name_(""), dimension_(0), capacity_(0), demands_(0),
                 distances_(0), coords_(0) {}

        std::string name_;
        unsigned int dimension_;
        unsigned int capacity_;
        unsigned int depot_;
        std::vector<unsigned int> demands_;
        std::vector<int> distances_;
        std::vector<std::pair<int,int>> coords_;
    };

    class Cvrp {
    public:
        Cvrp() { problem_ = new Problem(); }

        void read_vrp(const std::string &infile);

        std::string name() const;
        unsigned int dimension() const;
        unsigned int capacity() const;
        unsigned int demand(unsigned int node_id) const;
        int distance(unsigned int from, unsigned int to) const;

    private:
        Problem *problem_;
    };

    // cvrp intialize by infile
    void read_vrp(Problem *problem, const std::string &infile);

} // namespace VrpSolver

#endif // VRPSOLVER_CVRP_H
