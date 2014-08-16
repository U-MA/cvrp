#ifndef VRPSOLVER_CLARKE_AND_WRIGHT_SAVINGS_METHOD_H
#define VRPSOLVER_CLARKE_AND_WRIGHT_SAVINGS_METHOD_H

#include <algorithm>
#include <vector>
#include <utility>

#include <cvrp/cvrp.h>
#include <cvrp/customer.h>
#include <cvrp/vehicle.h>
#include <cvrp/fleet.h>
#include <cvrp/vehicle_traits.h>

#include <cvrp/detail/savings_list.h>

namespace VrpSolver {

    // fleetに属する車両を調べ
    // cidの顧客が属している車両へのイテレータを返す
    // なければイテレータendを返す
    template <class vehicleT>
    typename Fleet<vehicleT>::iterator find_vehicle_including(std::size_t cid, Fleet<vehicleT> &fleet){
        return find_if(std::begin(fleet), std::end(fleet),
                       [cid](vehicleT v){ return is_include(v, cid); });
    }

    // cidがvの内部であればtrue, そうでなければfalseを返す
    // 前提条件: cidはvに属していることを想定している
    template <class vehicleT>
    bool is_interior(std::size_t cid, vehicleT &v) {
        return (std::begin(v)->id() != cid) && (v.rbegin()->id() != cid);
    }

    template <class vehicleT>
    void clarke_wright_savings(const Cvrp& cvrp, Fleet<vehicleT>& fleet) {

        // 顧客の数だけ車両を作成する
        std::vector<Customer> cinfo = cvrp.customer_information();
        for (std::size_t i=1; i < cvrp.dimension(); ++i) {
            Vehicle<Customer> v(cvrp.capacity());
            v.visit(cinfo[i]);
            fleet.add(v);
        }

        // Savings listを作成する
        detail::SavingsList sl(cvrp);

        // Savings listを上から処理していく
        for (auto sit = std::begin(sl); sit != std::end(sl); ++sit) {
            std::pair<std::size_t, std::size_t> pair = sit->second; // 現在指しているSavingsを得る

            // iterator to vehicle
            // fleetは全ての顧客を含んでいるため
            // findVehicleIncluding()はend(fleet)を返さない
            auto vit1 = find_vehicle_including(pair.first,  fleet);
            auto vit2 = find_vehicle_including(pair.second, fleet);

            // 同じ車両の場合は何もしない
            if (vit1 == vit2)
                continue;

            // merge(*vit1, *vit2)と出来るように*vit1, *vit2を操作
            if ((vit1->size() == 1) && (vit2->size() == 1)) {
                // どちらの顧客もルートに含まれていない場合
                // FALLTHROUGH
            } else if (!is_interior(pair.first, *vit1) && vit2->size() == 1) {
                // pair.firstのみが構成されたルートに含まれていて
                // pair.firstは属するルートの内部で無い
                if (std::begin(*vit1)->id() == pair.first)
                    reverse(*vit1);
            } else if (!is_interior(pair.second, *vit2)  && vit1->size() == 1) {
                // pair.secondのみが構成されたルートに含まれていて
                // pair.secondは属するルートの内部でない
                if (std::begin(*vit2)->id() != pair.second)
                    reverse(*vit2);
            } else if (!is_interior(pair.first, *vit1) && !is_interior(pair.second, *vit2)) {
                // pair.firstもpair.secondもどちらもルートの内部で無い
                if (std::begin(*vit1)->id() == pair.first && std::begin(*vit2)->id() == pair.second) {
                    reverse(*vit1);
                } else if (std::begin(*vit1)->id() == pair.first && vit2->rbegin()->id() == pair.second) {
                    reverse(*vit1);
                    reverse(*vit2);
                } else if (vit1->rbegin()->id() == pair.first && std::begin(*vit2)->id() == pair.second) {
                    // FALLTHROUGH
                } else {
                    reverse(*vit2);
                }
            }

            if (vit1->capacity() + vit2->capacity() <= cvrp.capacity()) {
                merge(*vit1, *vit2);
                fleet.erase(*vit2);
            }
        }
    }

} // namespace VrpSolver

#endif // VRPSOLVER_CLARKE_AND_WRIGHT_SAVINGS_METHOD_H
