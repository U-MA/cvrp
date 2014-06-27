#ifndef VRPSOLVER_VEHICLE_TRAITS_H
#define VRPSOLVER_VEHICLE_TRAITS_H

namespace VrpSolver {

    template <VehicleT>
    struct vehicle_traits
    {
        typedef VehicleT vehicle_type;
        typedef typename VehicleT::customer_type customer_type;

        static size_t capacity(const vehicle_type& v)
        { return v.capacity(); }

        static size_t distance(const vehicle_type& v)
        { return v.distance(); }

        static bool can_visit(const vehicle_type& v, const customer_type& c)
        { return v.can_visit(c); }

        static void visit(vehicle_type& v, const customer_type& c)
        { v.visit(c); }
    };

} // namespace VrpSolver
