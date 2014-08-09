#ifndef VRPSOLVER_CUSTOMER_H
#define VRPSOLVER_CUSTOMER_H

#include <utility>

namespace VrpSolver {

    class Customer {
    public:
        Customer(std::size_t id, std::size_t demand)
            : id_(id), demand_(demand), vertex_(std::make_pair(0, 0))
        { }

        Customer(std::size_t id, std::size_t demand, std::pair<int, int> vertex)
            : id_(id), demand_(demand), vertex_(vertex)
        { }

        Customer(std::size_t id, std::size_t demand, int x, int y)
            : id_(id), demand_(demand), vertex_(std::make_pair(x, y))
        { }

        std::size_t id() const {
            return id_;
        }

        std::size_t demand() const {
            return demand_;
        }

        int x() const {
            return vertex_.first;
        }

        void x(int x) {
            vertex_.first = x;
        }

        int y() const {
            return vertex_.second;
        }

        void y(int y) {
            vertex_.second = y;
        }

    private:
        std::size_t id_;
        std::size_t demand_;
        std::pair<int, int> vertex_;
    };

} // namespace VrpSolver

#endif // VRPSOLVER_CUSTOMER_H
