#ifndef VRPSOLVER_VEHICLE_H
#define VRPSOLVER_VEHICLE_H

#include <iostream>
#include <vector>

#include <cvrp/customer.h>
#include <cvrp/cvrp.h> // for Distance type

namespace VrpSolver {

    class Vehicle {
    public:
        Vehicle(unsigned int max_capacity,
                const Distance *distance) :
            route_(), current_(Customer(1,0)), mileage_(0),
            capacity_(0), max_capacity_(max_capacity), distance_(distance) {}

        unsigned int capacity() const {
            return capacity_;
        }

        // 走行距離を返す
        unsigned int mileage() const;

        // 顧客cを訪問する
        void visit(const Customer& c);

    private:
        int distance(const Customer &from, const Customer &to) const;

        std::vector<Customer> route_;
        Customer current_;          // 最後に訪問した顧客
        unsigned int mileage_;
        unsigned int capacity_;
        unsigned int max_capacity_; // 最大容量
        const Distance *distance_;

        // Vehicleが保持しているroute_を出力する
        friend std::ostream& operator<<(std::ostream& ost, const Vehicle& v);
    };

} // namespace VrpSolver

#endif // VRPSOLVER_VEHICLE_H
