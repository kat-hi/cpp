//
// Created by Katharina Sachs on 09.11.21.
//

#ifndef AUFGABE2_MY_VECTOR_H
#define AUFGABE2_MY_VECTOR_H

using namespace std;
#include "payload.h"

namespace my {
    template<typename T>
    class vector {
    public:
        // default constructor
        vector<T>() : n_(nullptr) {};

        // move constructor
        vector<T>(vector<T> &&rhs) : vector<T>() {
            swap(*this, rhs);
        };

        // copy constructor
        vector<T>(const vector<T> &vec) : size_(vec.size_), capacity_(vec.capacity_) {
            n_ = static_cast<T *>(malloc(sizeof(T) * vec.capacity_));
            for (int index = 0; index < vec.size_; index++) {
                new(n_ + index) T(vec[index]);
            }
        }

        vector<T>(const size_t &number_intial_elements) {
            reserve(number_intial_elements);
        }

        vector<T>(const size_t &number_intial_elements, const T &type) {
            size_ = number_intial_elements;
            capacity_ = number_intial_elements;
            n_ = static_cast<T *>(malloc(sizeof(T) * number_intial_elements));
            for (int index = 0; index < number_intial_elements; index++) {
                new(n_ + index) T(type);
            }
        }

        // copy assignment
        vector<T> &operator=(vector<T> rhs);

//        // move assignment // handled by copy assignment
//        vector<T> &operator=(vector<T>&& rhs);

        template<typename TT>
        friend void swap(vector<TT> &lhs, vector<TT> &rhs);

        bool empty() const { return size_ == 0; };

        size_t size() const { return size_; };

        size_t capacity() const { return capacity_; }

        void reserve(size_t new_capacity);

        void shrink_to_fit();

        ~vector();

        void clear();

        void push_back(const T &);

        T pop_back();

        T &operator[](size_t) const;

        T &at(size_t) const;

        bool operator==(const vector<T> rhs);

    private:
        T *n_;
        size_t size_ = 0;
        size_t capacity_ = 0;
    };

    template<typename T>
    vector<T>::~vector() {
        clear();
        free(n_);
        capacity_ = 0;
    }

    template<typename T>
    inline void vector<T>::clear() {
        for (int index = 0; index < size_; index++) {
            (n_+index)->~T();
        }
        size_ = 0;

    }

    template<typename T>
    inline void vector<T>::push_back(const T &value) {
        size_t oldsize = size_;
        size_++;
        if (size_ <= capacity_) {
            T *v = new(n_ + oldsize) T(value);
            assert(v == n_ + oldsize);
        } else {
            vector<T> copy = vector<T>(*this);
            clear();

            size_ = oldsize + 1;
            capacity_ = capacity_ * 2;
            n_ = static_cast<T *>(malloc(sizeof(T) * capacity_));

            for (int i = 0; i <= size_; i++) {
                if (oldsize == i) {
                    T *v = new(n_ + i) T(value);
                    assert(v == n_ + i);
                } else {
                    T *v = new(n_ + i) T(copy[i]);
                    assert(v == n_ + i);
                }
            };
        };
    }

    template<typename T>
    T vector<T>::pop_back() {
        // n_[new_size] ->> object -->> item
        // n_+new_size ->> reference -->> *item
        size_t new_size = size_ - 1;
        T item = n_[new_size];
        n_[new_size].~T();
        size_ = new_size;
        return item;
    }

    template<typename T>
    T &vector<T>::operator[](size_t index) const {
        return n_[index];
    }


    template<typename T>
    T &vector<T>::at(size_t index) const {
        if (index >= 0 && index < size_) {
            return n_[index];
        } else {
            throw out_of_range("Index is out of range.");
        }
    }

    template<typename T>
    void vector<T>::reserve(const size_t new_capacity) {
        size_t old_size = size_;
        if (capacity_ == 0) {
            // only reservation, no data copy
            n_ = static_cast<T *>(malloc(sizeof(T) * capacity_));
        } else {
            // reservation and data copy
            vector<T> copy(*this); // copy constructor
            clear();
            free(n_);
            n_ = static_cast<T *>(malloc(sizeof(T) * capacity_));
            size_t max_index;
            if (new_capacity >= old_size) {
                // mehr Kapazität als Größe -> alles passt rein
                max_index = old_size;
            } else {
                // mehr Items als Kapazität -> Datenverlust!
                max_index = new_capacity;
            }
            for (int i = 0; i < max_index; i++) {
                T *item = new(n_ + i) T(copy[i]);
                assert(item == n_ + i);
            }
        }
        capacity_ = new_capacity;
        size_ = old_size;
    }

    template<typename T>
    void vector<T>::shrink_to_fit() {
        if (capacity_ > size_) {
            reserve(size_);
        }
    }

    // copy assignment and move assigment
    // don't copy your function arguments, instead pass them by value
    // wenn rhs l-value erkannt ist, dann gibt's eine Kopie
    // wenn rhs r-value(temporärer Wert) ist, dann moved compiler
    template<typename T>
    vector<T> &vector<T>::operator=(vector<T> rhs) {
        swap(*this, rhs);
        return *this;
    }

    template<typename TT>
    void swap(vector<TT> &lhs, vector<TT> &rhs) {
        std::swap(lhs.n_, rhs.n_);
        std::swap(lhs.capacity_, rhs.capacity_);
        std::swap(lhs.size_, rhs.size_);
    }

    template<typename T>
    bool vector<T>::operator==(const vector<T> rhs) {
        bool equals = true;
        for (int index = 0; index < size_; index++) {
            if(n_[index] != rhs[index]) {
                return false;
            }
        }
        return equals;
    }
}


#endif //AUFGABE2_MY_vector_H
