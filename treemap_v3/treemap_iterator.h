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
        iterator(const std::shared_ptr <node> &val, const std::shared_ptr <node> &root)
        : nodeObserver_(std::weak_ptr<node>(val)), root_(std::weak_ptr<node>(root)) {}

        // non-owning reference to the actual node
        /* todo */

    public:

        // access data of referenced map element (node)
        value_type &operator*() {
            /* todo */ static value_type dummy;
            return dummy;
        }

        value_type *operator->() {
            /* todo */ static value_type dummy;
            return &dummy;
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
            /* todo */ static iterator dummy;
            return dummy;
        }

        // prev element in map, pre-decrement
        // note: must modify self!
        iterator &operator--() {
            /* todo */ static iterator dummy;
            return dummy;
        }

    }; // class iterator

} // my::

