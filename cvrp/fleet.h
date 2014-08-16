#ifndef VRPSOLVER_FLEET_H
#define VRPSOLVER_FLEET_H

#include <algorithm>
#include <bitset>
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
        typedef typename std::vector<vehicle_type>::iterator iterator;
        typedef typename std::vector<vehicle_type>::const_iterator const_iterator;

        // iterator support
        iterator begin()
        { return fleet_.begin(); }

        const_iterator begin() const
        { return fleet_.begin(); }

        iterator end()
        { return fleet_.end(); }

        const_iterator end() const
        { return fleet_.end(); }

        Fleet(size_t size, unsigned int max_capacity)
            : size_(size), max_capacity_(max_capacity),
              fleet_()
        {
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

        bool is_visit(size_t id) const
        { return is_visit_.test(id); }

        bool is_visit(const customer_type& c) const
        { return is_visit_.test(c.id()); }

        bool is_feasible(size_t dimension)
        { return is_visit_.count() == dimension; }

        void add(vehicle_type v) {
            fleet_.push_back(v);
        }

        void erase(const vehicle_type& v) {
            auto i = std::find(std::begin(fleet_), std::end(fleet_), v);
            fleet_.erase(i);
        }

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
