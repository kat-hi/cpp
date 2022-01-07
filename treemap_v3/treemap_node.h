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

    };


} // my::