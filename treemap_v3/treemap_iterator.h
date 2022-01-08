// C++ Aufgabe tree_map von Hartmut Schirmacher, BHT Berlin

#pragma once

// class definitions
#include "treemap_class.h"

namespace my {

    // iterator: references a node within the tree
    template<typename K, typename T>
    class treemap<K, T>::iterator {
    protected:

        // treemap is a friend, can call protected constructor
        friend class treemap;

        // construct iterator referencing a specific node
        // - only treemap shall be allowed to do so
        iterator(const std::shared_ptr<node> &value, const std::shared_ptr<node> &treeroot) : nodeObserver_(
                std::weak_ptr<node>(value)), treeroot_ptr_(std::weak_ptr<node>(treeroot)) {}

        // non-owning reference to the actual node
        std::weak_ptr<node> nodeObserver_;
        std::weak_ptr<node> treeroot_ptr_;

    public:

        // access data of referenced map element (node)
        value_type &operator*() {
            return nodeObserver_.lock()->data_;
        }

        value_type *operator->() {
            auto node = nodeObserver_.lock();
            return &node->data_;
        }

        // two iterators are equal if they point to the same node
        bool operator==(const iterator &) const {
            /* todo */ return false;
        }

        bool operator!=(const iterator &) const {
            /* todo */ return false;
        }

        // next element in map, pre-increment
        // note: must modify self!
        iterator &operator++() {
            auto access = nodeObserver_.lock();
            if (access->right_child_ == nullptr) {
                std::shared_ptr<node> tmp = access->parentnode_.lock();

                while (tmp != nullptr && access == tmp->right_child_) {
                    access = tmp;
                    tmp = tmp->parentnode_.lock();
                }
                access = tmp;
            } else { // if current iterator not nullptr
                access = access->right_child_;

                while (access->left_child_ != nullptr) {
                    access = access->left_child_;
                }
            }

            *this = iterator(access, treeroot_ptr_.lock());
            return *this;
        }

        // prev element in map, pre-decrement
        // note: must modify self!
        iterator &operator--() {
            /* todo */ static iterator dummy;
            return dummy;
        }

    }; // class iterator

} // my::

