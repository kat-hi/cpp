// C++ Aufgabe treemap von Hartmut Schirmacher, BHT Berlin

#pragma once

// class definitions
#include "treemap_class.h"
#include <memory>
#include "treemap_node.h"

namespace my {

    // this is an inner class of class my::tree_map
    template<typename K, typename T>
    class treemap<K, T>::node
            : public std::enable_shared_from_this<node> {

    public:
        std::weak_ptr<node> parentnode_ = std::weak_ptr<node>();
        std::shared_ptr<node> left_child = nullptr;
        std::shared_ptr<node> right_child = nullptr;
        std::pair<K, T> data_ = std::pair<K, T>();

        node() = default;

        node(const std::pair<K, T> &data) : data_(data) {}

        std::pair<std::shared_ptr<node>, bool> insert(const std::pair<K, T> &data, bool overwrite) {
            bool inserted = false;
            if (data_.first > data.first) {
                if (left_child == nullptr) {
                    left_child = std::make_shared<node>(data);
                    left_child->parentnode_ = node::weak_from_this();
                    inserted = true;
                    return std::make_pair(left_child, inserted);
                } else {
                    // again call insert, until it returns
                    return left_child->insert(data, overwrite);
                }
            } else if (data_.first < data.first) {
                if (right_child == nullptr) {
                    right_child = std::make_shared<node>(data);
                    right_child->parentnode_ = node::weak_from_this();
                    inserted = true;
                    return std::make_pair(right_child, inserted);
                } else {
                    // again call insert, until it returns
                    return right_child->insert(data, overwrite);
                }
            } else { // wenn key gleich ist, gibt den node zurück
                if (overwrite) data_ = data;
                return std::make_pair(node::shared_from_this(), inserted);
            }
        }

        std::pair<std::shared_ptr<node>, bool> find(const K &key) {
            bool found = false;
            if (key < data_.first) {
                if (left_child == nullptr) {
                    return std::make_pair(nullptr, found);
                } else {
                    return left_child->find(key);
                }
            } else if (key > data_.first) {
                if (right_child == nullptr) {
                    return std::make_pair(nullptr, found);
                } else {
                    return right_child->find(key);
                }
            } else { // if key == data_.first
                found = true;
                return std::make_pair(node::shared_from_this(), found);
            }
        }


        std::shared_ptr<node> get_smallest_node() {
            if (left_child == nullptr) {
                return node::shared_from_this();
            } else {
                return right_child->get_smallest_node();
            }
        }
    };


} // my::