#ifndef VRPSOLVER_VEHICLE_H
#define VRPSOLVER_VEHICLE_H

#include <iostream>
#include <stdexcept>
#include <vector>

namespace VrpSolver {

    template <class customerT>
    class Vehicle {
    public:

        typedef customerT                                           customer_type;
        typedef typename std::vector<customer_type>::iterator       iterator;
        typedef typename std::vector<customer_type>::const_iterator const_iterator;
        typedef typename std::vector<customer_type>::reverse_iterator reverse_iterator;

        // iterator support
        iterator begin() {
            return route_.begin();
        }

        const_iterator begin() const {
            return route_.begin();
        }

        iterator end() {
            return route_.end();
        }

        const_iterator end() const {
            return route_.end();
        }

        // reverse iterator support
        reverse_iterator rbegin() {
            return route_.rbegin();
        }

        reverse_iterator rend() {
            return route_.rend();
        }

        Vehicle(std::size_t max_capacity) :
            route_(), capacity_(0),
            max_capacity_(max_capacity) {}

        std::size_t capacity() const {
            return capacity_;
        }

        // 顧客cを訪問する
        void visit(const customer_type& c) {
            if (!can_visit(c))
                throw std::runtime_error("vehicle overloaded");
            capacity_ += c.demand();
            route_.push_back(c);
        }

        // 顧客cを訪問可能か
        bool can_visit(const customer_type& c) const {
            return capacity_ + c.demand() <= max_capacity_;
        }

        std::size_t size() const {
            return route_.size();
        }

        bool operator==(const Vehicle<customer_type> &v) const {
            return route_ == v.route_;
        }

        bool operator!=(const Vehicle<customer_type> &v) const {
            return !(*this == v);
        }

    private:

        std::vector<customer_type> route_;
        std::size_t                capacity_;
        std::size_t                max_capacity_;  // 最大容量

        // Vehicleが保持しているroute_を出力する
        friend std::ostream& operator<<(std::ostream& ost, const Vehicle<customer_type>& v) {
            auto route = v.route_;
            for (int i=0; i < static_cast<int>(route.size()); i++)
                ost << route[i].id() << " ";
            return ost;
        }

    };

} // namespace VrpSolver

#endif // VRPSOLVER_VEHICLE_H
