#ifndef VRPSOLVER_CUSTOMER_H
#define VRPSOLVER_CUSTOMER_H

namespace VrpSolver {

    class Customer {
    public:
        Customer(unsigned int id, std::size_t demand)
            : id_(id), demand_(demand) {}

        unsigned int id() const {
            return id_;
        }

        std::size_t demand() const {
            return demand_;
        }

    private:
        Customer();
        unsigned int id_;
        std::size_t demand_;
    };

} // namespace VrpSolver

#endif // VRPSOLVER_CUSTOMER_H
