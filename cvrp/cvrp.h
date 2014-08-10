#ifndef VRPSOLVER_CVRP_H
#define VRPSOLVER_CVRP_H

#include <string>
#include <utility>
#include <vector>

#include <cvrp/customer.h>

namespace VrpSolver {

    typedef std::vector<std::size_t>  DistanceList;
    typedef std::vector<Customer>     CustomerList;
    typedef std::pair<int, int>       Point;

    struct Graph {
        DistanceList distance_list_;
        CustomerList customer_list_;
    };

    class Cvrp {
    public:
        Cvrp() : name_("UNKNOWN"), num_vehicles_(0)
        { }

        std::string name() const {
            return name_;
        }

        std::size_t dimension() const {
            return dimension_;
        }

        std::size_t capacity() const {
            return capacity_;
        }

        // deprecated
        const DistanceList& distance_list() const {
            return dlist_;
        }

        std::size_t num_vehicles() const {
            return num_vehicles_;
        }

        std::size_t demand(unsigned int node_id) const;

        std::size_t distance(unsigned int from, unsigned int to) const;

        std::pair<int, int> coordinate(std::size_t cid) const {
            return std::make_pair(cinfo_[cid].x(), cinfo_[cid].y());
        }

        const std::vector<Customer>& customer_information() const {
            return cinfo_;
        }

        // cvrp intialize by infile
        void read_vrp(const std::string &infile);

    private:
        std::string              name_;
        std::size_t              dimension_;
        std::size_t              capacity_;
        std::size_t              depot_;
        std::size_t              num_vehicles_;
        std::vector<Customer>    cinfo_; // customer info
        std::vector<std::size_t> dlist_;
    };

    std::size_t distance(const DistanceList& dlist,
                         const Customer& from, const Customer& to);

} // namespace VrpSolver

#endif // VRPSOLVER_CVRP_H
