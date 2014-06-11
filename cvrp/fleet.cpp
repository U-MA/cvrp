#include <cvrp/fleet.h>

namespace VrpSolver {

    unsigned int Fleet::distance() const
    {
        unsigned int sum_distance = 0;
        for (auto v : fleet_)
            sum_distance += v.mileage();
        return sum_distance;
    }

} // namespace VrpSolver
