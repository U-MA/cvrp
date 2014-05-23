#ifndef VRPSOLVER_CUSTOMER_H
#define VRPSOLVER_CUSTOMER_H

namespace VrpSolver {

    class Customer {
    public:
        Customer(unsigned int id, unsigned int demand) :
            id_(id), demand_(demand) {}

        unsigned int id() const {
            return id_;
        }

        unsigned int demand() const {
            return demand_;
        }

    private:
        Customer();
        unsigned int id_;
        unsigned int demand_;
    };

} // namespace VrpSolver

#endif // VRPSOLVER_CUSTOMER_H
