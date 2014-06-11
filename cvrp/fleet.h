#ifndef VRPSOLVER_FLEET_H
#define VRPSOLVER_FLEET_H

#include <iterator>
#include <vector>

#include <cvrp/cvrp.h>
#include <cvrp/vehicle.h>

namespace VrpSolver {

    class Fleet {
    public:
        Fleet(size_t size, unsigned int max_capacity,
              const DistanceList& distance_list)
            : size_(size), max_capacity_(max_capacity),
              distance_list_(distance_list), fleet_()
        {
            for (size_t i=0; i < size; i++)
                fleet_.push_back(Vehicle(max_capacity, distance_list));
        }

        unsigned int distance() const;

        Vehicle& get(size_t i)
        { return fleet_[i]; }

        std::vector<Vehicle>::iterator begin()
        { return fleet_.begin(); }

        std::vector<Vehicle>::iterator end()
        { return fleet_.end(); }

    private:
        size_t size_;
        unsigned int max_capacity_;
        const DistanceList& distance_list_;
        std::vector<Vehicle> fleet_;

    public:
        Fleet() = delete;
    };

} // namespace VrpSolver

#endif // VRPSOLVER_FLEET_H
