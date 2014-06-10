#include <iostream>
#include <stdexcept>
#include <vector>

#include <cvrp/customer.h>
#include <cvrp/vehicle.h>

namespace VrpSolver {

    int Vehicle::distance(const Customer &c1, const Customer &c2) const {
        const int from = c1.id();
        const int to   = c2.id();
        const int index = (to > from) ? ((to-2)*(to-1)/2+(from-1)) :
                                        ((from-2)*(from-1)/2+(to-1));
        return distance_[index];
    }

    unsigned int Vehicle::mileage() const {
        Customer depot(1, 0);
        return mileage_ + distance(current_, depot);
    }

    void Vehicle::visit(const Customer& c) {
        if (!can_visit(c))
            throw std::runtime_error("vehicle overloaded");
        capacity_ += c.demand();
        mileage_  += distance(current_, c);
        route_.push_back(c);
        current_ = c;
    }

    bool Vehicle::can_visit(const Customer& c) const {
        return capacity_ + c.demand() <= max_capacity_;
    }

    std::ostream& operator<<(std::ostream& ost, const Vehicle& v) {
        auto route = v.route_;
        for (int i=0; i < static_cast<int>(route.size()); i++)
            ost << route[i].id() << " ";
        return ost;
    }

} // namespace VrpSolver
