#ifndef VRPSOLVER_DETAIL_SAVINGS_LIST_H
#define VRPSOLVER_DETAIL_SAVINGS_LIST_H

#include <algorithm>

#include <cvrp/cvrp.h>

namespace VrpSolver {

    namespace detail {

        int calc_saving(const Cvrp &cvrp, std::size_t i, std::size_t j) {
            constexpr int depot = 0;
            return cvrp.distance(depot, i) + cvrp.distance(depot, j) - cvrp.distance(i, j);
        }

        class SavingsList {
            public:

                typedef typename std::vector<std::pair<
                    int, std::pair<std::size_t, std::size_t>>>::iterator
                    iterator;
                typedef typename std::vector<std::pair<
                    int, std::pair<std::size_t, std::size_t>>>::const_iterator
                    const_iterator;

                // iterator support
                iterator begin() {
                    return savings_list_.begin();
                }

                const_iterator begin() const {
                    return savings_list_.begin();
                }

                iterator end() {
                    return savings_list_.end();
                }

                const_iterator end() const {
                    return savings_list_.end();
                }

                SavingsList(const Cvrp &cvrp)
                    : list_pointer_(0)
                {
                    for (std::size_t i=1; i < cvrp.dimension(); ++i) {
                        for (std::size_t j=1; j < i; ++j) {
                            savings_list_.push_back(std::make_pair(calc_saving(cvrp, i, j),
                                        std::make_pair(i, j)));
                        }
                    }
                    std::sort(savings_list_.rbegin(), savings_list_.rend());
                }

                // 今指しているsaving pairを返す
                std::pair<std::size_t, std::size_t> top() const {
                    return savings_list_[list_pointer_].second;
                }

                std::size_t size() const {
                    return savings_list_.size();
                }

                // 今指しているsaving pairを次に進める
                void next() {
                    ++list_pointer_;
                }

            private:
                std::vector<std::pair<
                    int, std::pair<std::size_t, std::size_t>>
                    > savings_list_;
                std::size_t list_pointer_;
        };

    } // namespace detail

} // namespace VrpSolver

#endif // VRPSOLVER_DETAIL_SAVINGS_LIST_H
