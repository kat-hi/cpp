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
    treemap<K, T>::treemap() = default;

    template<typename K, typename T>
    void treemap<K, T>::clear() {
        treeroot_ = nullptr;
        treesize_ = 0;
    }

// random read-only access to value by key
    template<typename K, typename T>
    T treemap<K, T>::operator[](const K &key) const {
        return find(key)->second;
    }

// random write access to value by key
    template<typename K, typename T>
    T &treemap<K, T>::operator[](const K &key) {
        if (treeroot_ == nullptr) {
            treeroot_ = std::make_shared<node>(std::make_pair(key, T())); // providing space for type T()
            treesize_++;
            return treeroot_->data_.second; // returning data_.second so that lvalue can get it
        } else {
            auto node = find(key);
            if (node.nodeObserver_.lock() != nullptr) {
                return node->second;
            } else {
                std::pair<treemap<K, T>::iterator, bool> n = insert(key, T());
                return n.first->second;
            }
        }
    }

// number of elements in map (nodes in tree)
    template<typename K, typename T>
    size_t treemap<K, T>::size() const {
        return treesize_;
    }

// move ctor
    template<typename K, typename T>
    treemap<K, T>::treemap(treemap<K, T> &&treemap) {
        swap(*this, treemap);
    }

// deep copy ctor
    template<typename K, typename T>
    treemap<K, T>::treemap(const treemap<K, T> &treemap) {
        for(auto node : treemap) {
            this->insert(node.first, node.second);
        }
    }

// assignment (move & copy)
    template<typename K, typename T>
    treemap<K, T> &treemap<K, T>::operator=(treemap<K, T> rhs) {
        treemap<K, T> map(rhs);
        swap(*this, map);
        return *this;
    }


// iterator referencing first element (node) in map
    template<typename K, typename T>
    typename treemap<K, T>::iterator treemap<K, T>::begin() const {
        if (treeroot_ != nullptr) {
            node_ref smallest_node = treeroot_->get_smallest_node();
            return iterator(smallest_node, treeroot_);
        }
        // if no node exists, return iterator nullptr
        return iterator(nullptr, treeroot_);
    }

// iterator referencing no element (node) in map
    template<typename K, typename T>
    typename treemap<K, T>::iterator treemap<K, T>::end() const {
        return iterator(nullptr, treeroot_);
    }

// add a new element into the tree
// returns:
// - iterator to element
// - true if element was inserted; false if key already has been in map
    template<typename K, typename T>
    std::pair<typename treemap<K, T>::iterator, bool>
    treemap<K, T>::insertOrOverwrite(const K &key, const T &value, bool overwrite) {
        std::pair<K, T> data = std::make_pair(key, value);
        if (treeroot_ == nullptr) {
            treeroot_ = std::make_shared<node>(data);
            treesize_++;
            return std::make_pair(iterator(treeroot_, treeroot_), true);
        } else {
            std::pair<node_ref, bool> n = treeroot_->insert(data, overwrite);
            if (n.second) {
                treesize_++;
            }
            return std::make_pair(iterator(n.first, treeroot_), n.second);
        }
    }

    template<typename K, typename T>
    std::pair<typename treemap<K, T>::iterator, bool> treemap<K, T>::insert(const K &key, const T &value) {
        return insertOrOverwrite(key, value, false);
    }

// add a new element into the tree, or overwrite existing element if key already in map
// returns:
// - iterator to element
// - true if element was newly created; false if value for existing key was overwritten
    template<typename K, typename T>
    std::pair<typename treemap<K, T>::iterator, bool> treemap<K, T>::insert_or_assign(const K &k, const T &v) {
        return insertOrOverwrite(k, v, true);
    }

// find element with specific key. returns end() if not found.
    template<typename K, typename T>
    typename treemap<K, T>::iterator treemap<K, T>::find(const K &key) const {
        std::pair<node_ref, bool> node = treeroot_->find(key);
        if (node.second == false) return end();
        else return iterator(node.first, treeroot_);
    }

    template<typename K, typename T>
    size_t treemap<K, T>::count(const K &key) const {
        if (treeroot_->find(key).second) return 1;
        return 0;
    }

// swap is overloaded in global namespace
// see https://stackoverflow.com/questions/11562/how-to-overload-stdswap
// (answer by Attention Mozza314)
    template<typename K, typename T>
    void treemap<K, T>::swap(treemap<K, T> &lhs, treemap<K, T> &rhs) {
        std::swap(lhs.treeroot_, rhs.treeroot_);
        std::swap(lhs.treesize_, rhs.treesize_);
    }

} // my::
