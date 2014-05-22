#include <iostream>
#include <stdexcept>
#include <vector>

#include <cvrp/customer.h>
#include <cvrp/vehicle.h>

namespace VrpSolver {

    void Vehicle::visit(const Customer& c) {
        if (capacity_ + c.demand() > max_capacity_)
            throw std::runtime_error("vehicle overloaded");
        capacity_ += c.demand();
        route_.push_back(c);
    }

    std::ostream& operator<<(std::ostream& ost, const Vehicle& v) {
        auto route = v.route_;
        for (int i=0; i < route.size(); i++)
            ost << route[i].id() << " ";
        return ost;
    }

} // namespace VrpSolver
