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

    struct Graph {
        DistanceList distance_list_;
        CustomerList customer_list_;
    };

    struct Problem {
        Problem() : name_(""), dimension_(0), capacity_(0), depot_(0),
                    coords_(0) {}

        std::string name_;
        unsigned int dimension_;
        unsigned int capacity_;
        unsigned int depot_;
        std::vector<Point> coords_;
        Graph graph_;
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
        size_t num_vehicles() const;
        unsigned int distance(unsigned int from, unsigned int to) const;
        const DistanceList &distance_list() const;
        const CustomerList &customer_list() const;
        const Graph &graph() const
        { return problem_->graph_; }

    private:
        Problem *problem_;
        size_t num_vehicles_;
    };

    unsigned int distance(const DistanceList& dlist,
                          const Customer& from, const Customer& to);

} // namespace VrpSolver

#endif // VRPSOLVER_CVRP_H
