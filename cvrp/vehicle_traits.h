#ifndef VRPSOLVER_VEHICLE_TRAITS_H
#define VRPSOLVER_VEHICLE_TRAITS_H

#include <algorithm>

namespace VrpSolver {

    template <class VehicleT>
    struct vehicle_traits
    {
        typedef VehicleT vehicle_type;
        typedef typename VehicleT::customer_type customer_type;

        static std::size_t capacity(const vehicle_type& v)
        { return v.capacity(); }

        // vehicle_type::customer_typeがid()を持っていることが必要
        // dlistはindexを計算している順に格納されていないといけない
        template <class distance_list>
        static std::size_t distance(const vehicle_type& v, const distance_list& dlist)
        {
            std::size_t cur = 0;
            std::size_t sum = 0;
            for (auto i = std::begin(v); i != std::end(v); ++i) {
                std::size_t next = (*i).id();
                const int index = (next > cur) ? ((next-1)*(next)/2+(cur)) :
                                                 ((cur-1)*(cur)/2+(next));
                sum += dlist[index];
                cur = next;
            }
            const int index = (cur-1)*cur/2;
            return sum + dlist[index];
        }

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

    template <class VehicleT, class distance_list>
    size_t distance(const VehicleT& v, const distance_list& dlist)
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

    template <class vehicleT>
    void reverse(vehicleT &v) {
        std::reverse(std::begin(v), std::end(v));
    }

    template <class vehicleT>
    bool is_include(const vehicleT &v, std::size_t cid) {
        auto i = std::find_if(std::begin(v), std::end(v),
                              [cid](const typename vehicleT::customer_type &c){
                                   return c.id() == cid; });
        return i != std::end(v);
    }

    template <class vehicleT>
    void merge(vehicleT &v1, const vehicleT &v2) {
        for (auto i = std::begin(v2); i != std::end(v2); ++i) {
            typename vehicleT::customer_type c = *i;
            visit(v1, c);
        }
    }

} // namespace VrpSolver

#endif // VRPSOLVER_VEHICLE_TRAITS_H
