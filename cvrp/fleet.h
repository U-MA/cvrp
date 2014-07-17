#ifndef VRPSOLVER_FLEET_H
#define VRPSOLVER_FLEET_H

#include <bitset>
#include <iterator>
#include <stdexcept>
#include <vector>

#include <cvrp/cvrp.h>
#include <cvrp/vehicle.h>

namespace VrpSolver {

    class Fleet {
    public:
        Fleet(size_t size, unsigned int max_capacity,
              const Graph& graph)
            : size_(size), max_capacity_(max_capacity),
              fleet_(), graph_(graph)
        {
            for (size_t i=0; i < size; i++)
                fleet_.push_back(Vehicle(max_capacity, graph.distance_list_, this));
            is_visit_.set(0);
        }

        unsigned int distance() const;

        Vehicle& get(size_t i)
        { return fleet_[i]; }

        std::vector<Vehicle>::iterator begin()
        { return fleet_.begin(); }

        std::vector<Vehicle>::iterator end()
        { return fleet_.end(); }

        bool is_visit(size_t id) const
        { return is_visit_.test(id); }

        bool is_visit(const Customer& c) const
        { return is_visit_.test(c.id()); }

        bool is_feasible(size_t dimension)
        { return is_visit_.count() == dimension; }

        const Graph& graph() const
        { return graph_; }

        std::bitset<101> is_visit_;

    private:
        size_t               size_;
        unsigned int         max_capacity_;
        std::vector<Vehicle> fleet_;
        const Graph&         graph_;

    public:
        Fleet() = delete;
    };

} // namespace VrpSolver

#endif // VRPSOLVER_FLEET_H
