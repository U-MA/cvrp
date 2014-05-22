#ifndef VRPSOLVER_CUSTOMER_H
#define VRPSOLVER_CUSTOMER_H

#include <utility>

namespace VrpSolver {

    class Customer {
    public:
        Customer(unsigned int id, unsigned int demand) :
            id_(id), demand_(demand), coord_(), distances_(0) {}

        unsigned int id() const {
            return id_;
        }

        unsigned int demand() const {
            return demand_;
        }

    private:
        unsigned int id_;
        unsigned int demand_;
        std::pair<int,int> coord_; // 自分の座標
        std::vector<unsigned int> distances_; // 他の顧客との距離
    };

} // namespace VrpSolver

#endif // VRPSOLVER_CUSTOMER_H
