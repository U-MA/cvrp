#ifndef VRPSOLVER_ALGORITHM_VISIT_RAMDOMLY
#define VRPSOLVER_ALGORITHM_VISIT_RAMDOMLY

#include <iostream>

#include <cvrp/cvrp.h>
#include <cvrp/fleet.h>
#include <cvrp/vehicle_traits.h>

namespace VrpSolver {

    // Cvrp::num_vehicles()が設定されていることを想定している
    template <class vehicleT>
    void visit_randomly(const Cvrp& cvrp, Fleet<vehicleT>& fleet,
                        unsigned int seed = 2014) {
        srand(seed);
        const auto cinfo = cvrp.customer_information();
        for (std::size_t i=0; i < cvrp.num_vehicles(); ++i) {
            vehicleT v(cvrp.capacity());
            while (1) {
                std::vector<Customer> candidates;
                for (auto c : cinfo) {
                    if (!fleet.is_visit(c) && can_visit(v, c))
                        candidates.push_back(c);
                }

                if (candidates.empty()) break;

                Customer next = candidates[rand() % candidates.size()];
                visit(v, next);
                fleet.is_visit_[next.id()] = true;
            }
            fleet.add(v);
        }
    }

} // namespace VrpSolver

#endif // VRPSOLVER_ALGORITHM_VISIT_RAMDOMLY
