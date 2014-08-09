#ifndef VRPSOLVER_ALGORITHM_NEAREST_NEIGHBOR_INSERTION
#define VRPSOLVER_ALGORITHM_NEAREST_NEIGHBOR_INSERTION

#include <cvrp/cvrp.h>
#include <cvrp/fleet.h>
#include <cvrp/vehicle_traits.h>

namespace VrpSolver {

    template <class vehicleT>
    void nearest_neighbor_insertion(const Cvrp& cvrp, Fleet<vehicleT>& fleet) {
        const CustomerList cinfo = cvrp.customer_information();
        for (auto& v : fleet) {
            Customer current(0, 0); // depot
            while (1) {
                CustomerList candidates;
                for (auto c : cinfo) {
                    if (!fleet.is_visit(c) && can_visit(v, c))
                        candidates.push_back(c);
                }

                if (candidates.empty()) break;

                VrpSolver::Customer next(0, 0);
                unsigned int min = 1000000;
                for (auto c : candidates) {
                    unsigned int dist = distance(cvrp.distance_list(), current, c);
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

} // namespace VrpSolver

#endif // VRPSOLVER_ALGORITHM_NEAREST_NEIGHBOR_INSERTION
