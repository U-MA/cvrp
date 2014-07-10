#ifndef VRPSOLVER_FLEET_H
#define VRPSOLVER_FLEET_H

#include <bitset>
#include <iterator>
#include <stdexcept>
#include <vector>

#include <cvrp/cvrp.h>

namespace VrpSolver {

    class Fleet;

    class Vehicle {
    public:

        typedef Customer customer_type;

        Vehicle(std::size_t max_capacity, const DistanceList &distance,
                Fleet* fleet = nullptr) :
            route_(), current_(Customer(0,0)), mileage_(0), capacity_(0),
            max_capacity_(max_capacity), distance_(distance), fleet_(fleet) {}

        unsigned int capacity() const {
            return capacity_;
        }

        // 走行距離を返す
        unsigned int mileage() const;

        // 顧客cを訪問する
        void visit(const Customer& c);

        // 顧客cを訪問可能か
        bool can_visit(const Customer& c) const;

    private:
        int distance(const Customer &from, const Customer &to) const;

        std::vector<Customer> route_;
        Customer current_;             // 最後に訪問した顧客
        unsigned int mileage_;
        unsigned int capacity_;
        std::size_t max_capacity_;    // 最大容量
        const DistanceList &distance_;
        Fleet* fleet_;                 // 所属している車団

        // Vehicleが保持しているroute_を出力する
        friend std::ostream& operator<<(std::ostream& ost, const Vehicle& v);
    };


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
        size_t size_;
        unsigned int max_capacity_;
        std::vector<Vehicle> fleet_;
        const Graph& graph_;

    public:
        Fleet() = delete;
    };

} // namespace VrpSolver

#endif // VRPSOLVER_FLEET_H
