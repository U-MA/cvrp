#include <cvrp/fleet.h>

namespace VrpSolver {

    int Vehicle::distance(const customer_type& c1, const customer_type& c2) const {
        const int from = c1.id();
        const int to   = c2.id();
        const int index = (to > from) ? ((to-1)*(to)/2+(from)) :
                                        ((from-1)*(from)/2+(to));
        return distance_[index];
    }

    void Vehicle::visit(const customer_type& c) {
        if (!can_visit(c))
            throw std::runtime_error("vehicle overloaded");
        capacity_ += c.demand();
        mileage_  += distance(current_, c);
        route_.push_back(c);
        current_ = c;
        if (fleet_ != nullptr)
            fleet_->is_visit_.set(c.id());
    }

} // namespace VrpSolver
