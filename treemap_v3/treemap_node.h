// C++ Aufgabe treemap von Hartmut Schirmacher, BHT Berlin

#pragma once

// class definitions
#include "treemap_class.h"
#include <memory>
#include "treemap_node.h"

namespace my {

    // this is an inner class of class my::tree_map (protected)
    template<typename K, typename T>
    class treemap<K, T>::node: public std::enable_shared_from_this<node> { // Ableitung um shared_ptr von sich selbst zu erstellen

    using node_ref = std::shared_ptr<node>;

    public:
        // nach oben mit weak_ptr, nach unten mit shared_ptr
        std::weak_ptr<node> parentnode_ = std::weak_ptr<node>();
        node_ref left_child_ = nullptr;
        node_ref right_child_ = nullptr;
        std::pair<K, T> data_ = std::pair<K, T>();

        node() = default;

        explicit node(const std::pair<K, T> &data) : data_(data) {}

        // called by treemap.insert()
        std::pair<node_ref, bool> insert(const std::pair<K, T> &data, bool overwrite) {
            bool inserted = false;
            if (data_.first > data.first) {
                if (left_child_ == nullptr) {
                    left_child_ = std::make_shared<node>(data);
                    left_child_->parentnode_ = node::weak_from_this();
                    inserted = true;
                    return std::make_pair(left_child_, inserted);
                } else {
                    // recursion(!): call insert, until it returns
                    return left_child_->insert(data, overwrite);
                }
            } else if (data_.first < data.first) {
                if (right_child_ == nullptr) {
                    right_child_ = std::make_shared<node>(data);
                    right_child_->parentnode_ = node::weak_from_this();
                    inserted = true;
                    return std::make_pair(right_child_, inserted);
                } else {
                    // recursion(!): call insert, until it returns
                    return right_child_->insert(data, overwrite);
                }
            } else { // if key equal, return node
                if (overwrite) data_ = data;
                return std::make_pair(node::shared_from_this(), inserted);
            }
        }

        // called by treemap.find()
        std::pair<node_ref, bool> find(const K &key) {
            bool found = false;
            if (key < data_.first) {
                if (left_child_ == nullptr) {
                    return std::make_pair(nullptr, found);
                } else {
                    return left_child_->find(key);
                }
            } else if (key > data_.first) {
                if (right_child_ == nullptr) {
                    return std::make_pair(nullptr, found);
                } else {
                    return right_child_->find(key);
                }
            } else { // if key == data_.first
                found = true;
                return std::make_pair(node::shared_from_this(), found);
            }
        }

        node_ref get_smallest_node() {
            if (left_child_ == nullptr) {
                return node::shared_from_this();
            } else {
                return left_child_->get_smallest_node();
            }
        }
    };
}