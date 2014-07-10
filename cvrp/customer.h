#ifndef VRPSOLVER_CUSTOMER_H
#define VRPSOLVER_CUSTOMER_H

namespace VrpSolver {

    class Customer {
    public:
        Customer(std::size_t id, std::size_t demand)
            : id_(id), demand_(demand)
        { }

        std::size_t id() const {
            return id_;
        }

        std::size_t demand() const {
            return demand_;
        }

    private:
        std::size_t id_;
        std::size_t demand_;
    };

} // namespace VrpSolver

#endif // VRPSOLVER_CUSTOMER_H
