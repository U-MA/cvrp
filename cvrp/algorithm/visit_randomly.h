#ifndef VRPSOLVER_ALGORITHM_VISIT_RAMDOMLY
#define VRPSOLVER_ALGORITHM_VISIT_RAMDOMLY

#include <iostream>

#include <cvrp/cvrp.h>
#include <cvrp/fleet.h>
#include <cvrp/vehicle_traits.h>

namespace VrpSolver {

    void visit_randomly(const Cvrp& cvrp, Fleet& fleet,
                        unsigned int seed = 2014) {
        srand(seed);
        const CustomerList& customer_list = cvrp.customer_list();
        for (auto& v : fleet) {
            while (1) {
                CustomerList candidates;
                for (auto c : customer_list) {
                    if (!fleet.is_visit(c) && can_visit(v, c))
                        candidates.push_back(c);
                }

                if (candidates.empty()) break;

                visit(v, candidates[rand() % candidates.size()]);
            }
        }
    }

    void visit_randomly(Fleet& fleet,
                        unsigned int seed = 2014) {
        srand(seed);
        const CustomerList& customer_list = fleet.graph().customer_list_;
        for (auto& v : fleet) {
            while (1) {
                CustomerList candidates;
                for (auto c : customer_list) {
                    if (!fleet.is_visit(c) && can_visit(v, c))
                        candidates.push_back(c);
                }

                if (candidates.empty()) break;

                visit(v, candidates[rand() % candidates.size()]);
            }
        }
    }

} // namespace VrpSolver

#endif // VRPSOLVER_ALGORITHM_VISIT_RAMDOMLY
