#ifndef VRPSOLVER_FLEET_H
#define VRPSOLVER_FLEET_H

#include <bitset>
#include <iterator>
#include <stdexcept>
#include <vector>

#include <cvrp/cvrp.h>
#include <cvrp/vehicle_traits.h>

namespace VrpSolver {

    template <class vehicleT>
    class Fleet {
    public:

        typedef vehicleT vehicle_type;
        typedef typename vehicleT::customer_type customer_type;

        Fleet(size_t size, unsigned int max_capacity)
            : size_(size), max_capacity_(max_capacity),
              fleet_()
        {
            for (size_t i=0; i < size; i++)
                fleet_.push_back(vehicle_type(max_capacity));
            is_visit_.set(0);
        }

        std::size_t distance(const DistanceList& dlist) const
        {
            std::size_t sum_distance = 0;
            for (auto v : fleet_)
                sum_distance += VrpSolver::distance(v, dlist);
            return sum_distance;
        }

        vehicle_type& get(size_t i)
        { return fleet_[i]; }

        typename std::vector<vehicle_type>::iterator begin()
        { return fleet_.begin(); }

        typename std::vector<vehicle_type>::iterator end()
        { return fleet_.end(); }

        bool is_visit(size_t id) const
        { return is_visit_.test(id); }

        bool is_visit(const customer_type& c) const
        { return is_visit_.test(c.id()); }

        bool is_feasible(size_t dimension)
        { return is_visit_.count() == dimension; }

        std::bitset<101> is_visit_;

    private:
        size_t               size_;
        unsigned int         max_capacity_;
        std::vector<vehicle_type> fleet_;

    public:
        Fleet() = delete;
    };

} // namespace VrpSolver

#endif // VRPSOLVER_FLEET_H
