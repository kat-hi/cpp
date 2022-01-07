// C++ Aufgabe tree_map von Hartmut Schirmacher, BHT Berlin

#pragma once

// other includes
#include <memory>
#include <iostream>
#include <utility>
#include <tuple>
#include <cassert>


// class definitions
#include "treemap_class.h"
#include "treemap_iterator.h"
#include "treemap_node.h"

namespace my {

    template<typename K, typename T>
    treemap<K, T>::treemap() {
    }

    template<typename K, typename T>
    void treemap<K, T>::clear() {
        treeroot_ = nullptr;
        treesize_ = 0;
    }

// random read-only access to value by key
    template<typename K, typename T>
    T
    treemap<K, T>::operator[](const K &) const {
        /* todo */ return T();
    }

// random write access to value by key
    template<typename K, typename T>
    T &
    treemap<K, T>::operator[](const K &) {
        /* todo */ static T dummy;
        return dummy;
    }

// number of elements in map (nodes in tree)
    template<typename K, typename T>
    size_t treemap<K, T>::size() const {
        return treesize_;
    }

// move ctor
    template<typename K, typename T>
    treemap<K, T>::treemap(treemap<K, T> &&map) {
        swap(*this, map);
    }

// deep copy ctor
    template<typename K, typename T>
    treemap<K, T>::treemap(const treemap<K, T> &map) {
        /* todo */
    }

// assignment (move & copy)
    template<typename K, typename T>
    treemap<K, T> &
    treemap<K, T>::operator=(treemap<K, T>) {
        /* todo, use copy&swap */
        return *this;
    }


// iterator referencing first element (node) in map
    template<typename K, typename T>
    typename treemap<K, T>::iterator
    treemap<K, T>::begin() {
        /* todo */ return iterator();
    }

// iterator referencing no element (node) in map
    template<typename K, typename T>
    typename treemap<K, T>::iterator
    treemap<K, T>::end() const {
        /* todo */ return iterator();
    }

// add a new element into the tree
// returns:
// - iterator to element
// - true if element was inserted; false if key was already in map

    template<typename K, typename T>
    std::pair<typename treemap<K, T>::iterator, bool> treemap<K, T>::insertOrAssign(const K &key, const T &value, bool assign) {
        std::pair<K, T> data = std::make_pair(key, value);
        if (treeroot_ == nullptr) {
            treeroot_ = std::make_shared<node>(data);
            treesize_++;
            return std::make_pair(iterator(treeroot_), true);
        } else {
            std::pair<std::shared_ptr<node>, bool> n = treeroot_->insert(data, assign);
            if (n.second) {
                treesize_++;
            }
            return std::make_pair(iterator(n.first), n.second);
        }
    }

    template<typename K, typename T>
    std::pair<typename treemap<K, T>::iterator, bool> treemap<K, T>::insert(const K &key, const T &value) {
        return insertOrAssign(key, value, false);
    }

// add a new element into the tree, or overwrite existing element if key already in map
// returns:
// - iterator to element
// - true if element was newly created; false if value for existing key was overwritten
    template<typename K, typename T>
    std::pair<typename treemap<K, T>::iterator, bool>
    treemap<K, T>::insert_or_assign(const K &key, const T &value) {
        return insertOrAssign(key, value, true);
    }

// find element with specific key. returns end() if not found.
    template<typename K, typename T>
    typename treemap<K, T>::iterator
    treemap<K, T>::find(const K &) const {
        /* todo */ return iterator();
    }

// how often is the element contained in the map?
    template<typename K, typename T>
    size_t
    treemap<K, T>::count(const K &) const {
        /* todo */ return 666;
    }

// swap is overloaded in global namespace
// see https://stackoverflow.com/questions/11562/how-to-overload-stdswap
// (answer by Attention Mozza314)
    template<typename K, typename T>
    void
    treemap<K, T>::swap(treemap<K, T> &, treemap<K, T> &) {
    }

} // my::
