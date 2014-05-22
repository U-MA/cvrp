#ifndef VRPSOLVER_VEHICLE_H
#define VRPSOLVER_VEHICLE_H

#include <iostream>
#include <vector>

#include <cvrp/customer.h>

namespace VrpSolver {

    class Vehicle {
    public:
        Vehicle(unsigned int max_capacity) :
            route_(), last_(Customer(1,0)), capacity_(0), max_capacity_(max_capacity) {}

        unsigned int capacity() const {
            return capacity_;
        }

        // 顧客cを訪問する
        // その際、cの需要の分だけcapacityも増える
        void visit(const Customer& c);

    private:
        Vehicle() {} // CAN NOT USE

        std::vector<Customer> route_;
        unsigned int capacity_;
        unsigned int max_capacity_; // 最大容量

        // Vehicleが保持しているroute_を出力する
        friend std::ostream& operator<<(std::ostream& ost, const Vehicle& v);
    };

} // namespace VrpSolver

#endif // VRPSOLVER_VEHICLE_H
