#ifndef VRPSOLVER_ALGORITHM_VISIT_RAMDOMLY
#define VRPSOLVER_ALGORITHM_VISIT_RAMDOMLY

#include <iostream>

#include <cvrp/cvrp.h>
#include <cvrp/fleet.h>

namespace VrpSolver {

    void visit_randomly(const Cvrp& cvrp, Fleet& fleet, unsigned int seed = 2014) {
        srand(seed);
        const CustomerList& customer_list = cvrp.customer_list();
        for (auto& v : fleet) {
            while (1) {
                CustomerList candidates;
                for (auto c : customer_list) {
                    if (!fleet.is_visit(c.id()) && v.can_visit(c))
                        candidates.push_back(c);
                }

                if (candidates.empty()) break;

                v.visit(candidates[rand() % candidates.size()]);
            }
        }
    }

} // namespace VrpSolver

#endif // VRPSOLVER_ALGORITHM_VISIT_RAMDOMLY
