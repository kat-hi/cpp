// C++ Aufgabe treemap von Hartmut Schirmacher, BHT Berlin

#pragma once

// class definitions
#include "treemap_class.h"
#include <memory>


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
        node(const std::pair<K,T>& data) : data_(data) {}
    };


} // my::