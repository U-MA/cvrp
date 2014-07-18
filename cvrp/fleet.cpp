#include <cvrp/fleet.h>

namespace VrpSolver {

    void Vehicle::visit(const customer_type& c) {
        if (!can_visit(c))
            throw std::runtime_error("vehicle overloaded");
        capacity_ += c.demand();
        mileage_  += distance(current_, c);
        route_.push_back(c);
        current_ = c;
    }

} // namespace VrpSolver
