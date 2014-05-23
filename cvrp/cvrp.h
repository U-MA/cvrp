#ifndef VRPSOLVER_CVRP_H
#define VRPSOLVER_CVRP_H

#include <string>
#include <utility>
#include <vector>

#include <cvrp/customer.h>

namespace VrpSolver {

    typedef std::vector<unsigned int> DistanceList;
    typedef std::vector<Customer>     CustomerList;
    typedef std::pair<int, int>       Point;

    struct Problem {
        Problem() : name_(""), dimension_(0), capacity_(0),
                    distances_(0), customers_(), coords_(0) {}

        std::string name_;
        unsigned int dimension_;
        unsigned int capacity_;
        unsigned int depot_;
        DistanceList distances_;
        CustomerList customers_;
        std::vector<Point> coords_;
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
        unsigned int distance(unsigned int from, unsigned int to) const;
        const DistanceList &distance_list() const;
        const CustomerList &customer_list() const;

    private:
        Problem *problem_;
        unsigned int num_vehicles_;
    };

    void read_vrp(Problem *problem, const std::string &infile);

    unsigned int distance(const DistanceList& dlist,
                          const Customer& from, const Customer& to);

} // namespace VrpSolver

#endif // VRPSOLVER_CVRP_H
