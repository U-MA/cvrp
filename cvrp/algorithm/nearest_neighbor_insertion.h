#ifndef VRPSOLVER_ALGORITHM_NEAREST_NEIGHBOR_INSERTION
#define VRPSOLVER_ALGORITHM_NEAREST_NEIGHBOR_INSERTION

#include <cvrp/cvrp.h>
#include <cvrp/fleet.h>

namespace VrpSolver {

    void nearest_neighbor_insertion(const Cvrp& cvrp, Fleet& fleet) {
        const CustomerList customer_list = cvrp.customer_list();
        for (auto& v : fleet) {
            Customer current(0, 0); // depot
            while (1) {
                CustomerList candidates;
                for (auto c : customer_list) {
                    if (!fleet.is_visit(c) && v.can_visit(c))
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
                v.visit(next);
            }
        }
    }

} // namespace VrpSolver

#endif // VRPSOLVER_ALGORITHM_NEAREST_NEIGHBOR_INSERTION
