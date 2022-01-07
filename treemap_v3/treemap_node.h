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
        std::weak_ptr<node> parent_ = std::weak_ptr<node>();
        std::shared_ptr<node> child_L_ = nullptr;
        std::shared_ptr<node> child_R_ = nullptr;
        std::pair<K, T> data_ = std::pair<K, T>();

        node() = default;

        node(const std::pair<K, T> &data) : data_(data) {}

        std::pair<std::shared_ptr<node>, bool> insert(const std::pair<K, T> &data, bool assign) {
            bool inserted = false;
            if (data_.first > data.first) {
                if (child_L_ == nullptr) {
                    child_L_ = std::make_shared<node>(data);
                    child_L_->parent_ = node::weak_from_this();
                    inserted = true;
                    return std::make_pair(child_L_, inserted);
                } else {
                    // again insert, until it returns
                    return child_L_->insert(data, assign);
                }
            } else if (data_.first < data.first) {
                if (child_R_ == nullptr) {
                    child_R_ = std::make_shared<node>(data);
                    child_R_->parent_ = node::weak_from_this();
                    inserted = true;
                    return std::make_pair(child_R_, inserted);
                } else {
                    // again insert, until it returns
                    return child_R_->insert(data, assign);
                }
            } else if (data_.first == data.first) { // wenn key gleich ist, gibt den node zurück
                if(assign) {
                    data_ = data;
                }
                return std::make_pair(node::shared_from_this(), inserted);
            }
        }
    };


} // my::