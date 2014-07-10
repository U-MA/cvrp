#ifndef VRPSOLVER_CVRP_H
#define VRPSOLVER_CVRP_H

#include <string>
#include <utility>
#include <vector>

#include <cvrp/customer.h>

namespace VrpSolver {

    typedef std::vector<std::size_t> DistanceList;
    typedef std::vector<Customer>     CustomerList;
    typedef std::pair<int, int>       Point;

    struct Graph {
        DistanceList distance_list_;
        CustomerList customer_list_;
    };

    struct Problem {
        Problem() : name_(""), dimension_(0), capacity_(0), depot_(0),
                    coords_(0)
        { }

        std::string        name_;
        std::size_t        dimension_;
        std::size_t        capacity_;
        std::size_t        depot_;
        std::vector<Point> coords_;
        Graph              graph_;
    };

    class Cvrp {
    public:
        Cvrp() { problem_ = new Problem(); }
        ~Cvrp() { delete problem_; }

        // cvrp intialize by infile
        void read_vrp(const std::string &infile);

        std::string name() const;
        std::size_t dimension() const;
        std::size_t capacity() const;
        std::size_t demand(unsigned int node_id) const;
        size_t num_vehicles() const;
        std::size_t distance(unsigned int from, unsigned int to) const;
        const DistanceList &distance_list() const;
        const CustomerList &customer_list() const;
        const Graph &graph() const
        { return problem_->graph_; }

    private:
        Problem *problem_;
        size_t num_vehicles_;
    };

    std::size_t distance(const DistanceList& dlist,
                          const Customer& from, const Customer& to);

} // namespace VrpSolver

#endif // VRPSOLVER_CVRP_H
