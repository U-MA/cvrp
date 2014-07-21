#ifndef VRPSOLVER_VEHICLE_TRAITS_H
#define VRPSOLVER_VEHICLE_TRAITS_H

namespace VrpSolver {

    template <class VehicleT>
    struct vehicle_traits
    {
        typedef VehicleT vehicle_type;
        typedef typename VehicleT::customer_type customer_type;

        static std::size_t capacity(const vehicle_type& v)
        { return v.capacity(); }

        static std::size_t distance(const vehicle_type& v, const DistanceList& dlist)
        { return 0; }

        static bool can_visit(const vehicle_type& v, const customer_type& c)
        { return v.can_visit(c); }

        static void visit(vehicle_type& v, const customer_type& c)
        { v.visit(c); }
    };

    // free function
    template <class VehicleT>
    size_t capacity(const VehicleT& v)
    {
        return vehicle_traits<VehicleT>::capacity(v);
    }

    template <class VehicleT>
    size_t distance(const VehicleT& v, const DistanceList& dlist)
    {
        return vehicle_traits<VehicleT>::distance(v, dlist);
    }

    template <class VehicleT>
    bool can_visit(const VehicleT& v, const typename VehicleT::customer_type& c)
    {
        return vehicle_traits<VehicleT>::can_visit(v, c);
    }

    template <class VehicleT>
    void visit(VehicleT& v, typename VehicleT::customer_type& c)
    {
        vehicle_traits<VehicleT>::visit(v, c);
    }

} // namespace VrpSolver

#endif // VRPSOLVER_VEHICLE_TRAITS_H
