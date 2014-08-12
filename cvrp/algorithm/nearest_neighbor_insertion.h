#ifndef VRPSOLVER_ALGORITHM_NEAREST_NEIGHBOR_INSERTION
#define VRPSOLVER_ALGORITHM_NEAREST_NEIGHBOR_INSERTION

#include <cvrp/cvrp.h>
#include <cvrp/fleet.h>
#include <cvrp/vehicle_traits.h>

namespace VrpSolver {

    /*
    template <class vehicleT>
    void nearest_neighbor_insertion(const Cvrp& cvrp, Fleet<vehicleT>& fleet) {
        const auto cinfo = cvrp.customer_information();
        for (auto& v : fleet) {
            Customer current(0, 0); // depot
            while (1) {
                std::vector<Customer> candidates;
                for (auto c : cinfo) {
                    if (!fleet.is_visit(c) && can_visit(v, c))
                        candidates.push_back(c);
                }

                if (candidates.empty()) break;

                VrpSolver::Customer next(0, 0);
                unsigned int min = 1000000;
                for (auto c : candidates) {
                    unsigned int dist = cvrp.distance(current.id(), c.id());
                    if (dist < min) {
                        min  = dist;
                        next = c;
                    }
                }
                visit(v, next);
                fleet.is_visit_[next.id()] = true;
            }
        }
    }
    */

    template <class vehicleT>
    void nearest_neighbor_insertion(const Cvrp& cvrp, Fleet<vehicleT>& fleet) {
        const auto cinfo = cvrp.customer_information();
        for (std::size_t i=0; i < cvrp.num_vehicles(); ++i) {
            vehicleT v(cvrp.capacity());
            Customer current(0, 0);
            while (1) {
                std::vector<Customer> candidates;
                for (auto c : cinfo) {
                    if (!fleet.is_visit(c) && can_visit(v, c))
                        candidates.push_back(c);
                }

                if (candidates.empty()) break;

                VrpSolver::Customer next(0, 0);
                unsigned int min = 1000000;
                for (auto c : candidates) {
                    unsigned int dist = cvrp.distance(current.id(), c.id());
                    if (dist < min) {
                        min  = dist;
                        next = c;
                    }
                }
                visit(v, next);
                fleet.is_visit_[next.id()] = true;
            }
            fleet.add(v);
        }
    }

} // namespace VrpSolver

#endif // VRPSOLVER_ALGORITHM_NEAREST_NEIGHBOR_INSERTION
