#ifndef VRPSOLVER_VEHICLE_H
#define VRPSOLVER_VEHICLE_H

#include <iostream>
#include <vector>

namespace VrpSolver {

    class Fleet;

    class Vehicle {
    public:

        typedef Customer customer_type;

        Vehicle(std::size_t max_capacity, const DistanceList& distance,
                Fleet* fleet = nullptr) :
            route_(), current_(Customer(0,0)), mileage_(0), capacity_(0),
            max_capacity_(max_capacity), distance_(distance), fleet_(fleet) {}

        std::size_t capacity() const {
            return capacity_;
        }

        // 走行距離を返す
        std::size_t mileage() const {
            if (route_.empty()) return 0;
            Customer depot(0, 0);
            return mileage_ + distance(current_, depot);
        }

        // 顧客cを訪問する
        void visit(const customer_type& c);

        // 顧客cを訪問可能か
        bool can_visit(const customer_type& c) const {
            return capacity_ + c.demand() <= max_capacity_;
        }

    private:
        int distance(const customer_type& from, const customer_type& to) const;

        std::vector<customer_type> route_;
        customer_type              current_;       // 最後に訪問した顧客
        std::size_t                mileage_;
        std::size_t                capacity_;
        std::size_t                max_capacity_;  // 最大容量
        const DistanceList&        distance_;
        Fleet*                     fleet_;         // 所属している車団

        // Vehicleが保持しているroute_を出力する
        friend std::ostream& operator<<(std::ostream& ost, const Vehicle& v) {
            auto route = v.route_;
            for (int i=0; i < static_cast<int>(route.size()); i++)
                ost << route[i].id() << " ";
            return ost;
        }

    };

} // namespace VrpSolver

#endif // VRPSOLVER_VEHICLE_H
