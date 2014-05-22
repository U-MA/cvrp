#ifndef VRPSOLVER_CVRP_H
#define VRPSOLVER_CVRP_H

#include <string>
#include <utility>
#include <vector>

#include <cvrp/customer.h>

namespace VrpSolver {

    struct Problem {
        typedef std::vector<Customer> CustomerList;

        Problem() : name_(""), dimension_(0), capacity_(0),
                 distances_(0), customers_(), coords_(0) {}

        std::string name_;
        unsigned int dimension_;
        unsigned int capacity_;
        unsigned int depot_;
        std::vector<int> distances_;
        std::vector<Customer> customers_;
        std::vector<std::pair<int,int>> coords_;
    };

    class Cvrp {
    public:
        Cvrp() { problem_ = new Problem(); }
        ~Cvrp() { delete problem_; }

        // cvrp intialize by infile
        void read_vrp(const std::string &infile);

        std::string name() const;
        unsigned int dimension() const;
        unsigned int capacity() const;
        unsigned int demand(unsigned int node_id) const;
        unsigned int num_vehicles() const;
        int distance(unsigned int from, unsigned int to) const;

    private:
        Problem *problem_;
        unsigned int num_vehicles_;
    };

    void read_vrp(Problem *problem, const std::string &infile);

} // namespace VrpSolver

#endif // VRPSOLVER_CVRP_H
