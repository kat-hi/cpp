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
        iterator(const std::shared_ptr<node> &node_ref, const std::shared_ptr<node> &treeroot) : nodeObserver_(
                std::weak_ptr<node>(node_ref)), treeroot_ptr_(std::weak_ptr<node>(treeroot)) {}

//        iterator(const std::shared_ptr<node> &val, const std::shared_ptr<node> &root) : nodeObserver_(
//                std::weak_ptr<node>(val)), root_(std::weak_ptr<node>(root)) {}

        // non-owning reference to the actual node
        // node can be deleted even if an iterator points to it
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
        bool operator==(const iterator &iter) const {
            return nodeObserver_.lock() == iter.nodeObserver_.lock();
        }

        bool operator!=(const iterator &iter) const {
            return !(*this == iter);
        }

        // next element in map, pre-increment
        // note: must modify self!
        iterator &operator++() {
            std::shared_ptr<node> access_current_node = nodeObserver_.lock();
            if (access_current_node->right_child_ == nullptr) {
                std::shared_ptr<node> tmp = access_current_node->parentnode_.lock();

                // stop if root or right child exists
                while (tmp != nullptr && access_current_node == tmp->right_child_) {
                    access_current_node = tmp;
                    tmp = tmp->parentnode_.lock();
                }
                access_current_node = tmp;
            } else { // if current iterator not nullptr
                access_current_node = access_current_node->right_child_;

                // if right child has left children -> they are smaller!
                while (access_current_node->left_child_ != nullptr) {
                    access_current_node = access_current_node->left_child_;
                }
            }

            *this = iterator(access_current_node, treeroot_ptr_.lock());
            return *this;
        }

        // prev element in map, pre-decrement
        // note: must modify self!
        iterator &operator--() {
            std::shared_ptr<node> access_current_node = nodeObserver_.lock();
            if (access_current_node == nullptr) {
                // case: node.end()
                // get root and search for the biggest node to start with (right children)
                std::shared_ptr<node> access_root = treeroot_ptr_.lock();
                access_current_node = access_root->right_child_;
                while (access_current_node->right_child_ != nullptr) {
                    access_current_node = access_current_node->right_child_;
                }
            } else if (access_current_node->left_child_ != nullptr) {
                // if left child exists -> search for the smallest left one
                access_current_node = access_current_node->left_child_;
                while (access_current_node->left_child_ != nullptr) {
                    access_current_node = access_current_node->left_child_;
                }
            } else {
                // if left child is nullptr, get parents as long as parent is not nullptr (root arrived) and
                // parent has got a left child that is not the current child
                std::shared_ptr<node> access_parent = access_current_node->parentnode_.lock();
                while (access_parent != nullptr && access_current_node == access_parent->left_child_) {
                    access_current_node = access_parent;
                    access_parent = access_parent->parentnode_.lock();
                }
                access_current_node = access_parent;
            }
            std::shared_ptr<node> treerootnode = treeroot_ptr_.lock();
            *this = iterator(access_current_node, treerootnode);
            return *this;
        }

    }; // class iterator

} // my::

