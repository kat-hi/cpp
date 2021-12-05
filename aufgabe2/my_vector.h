//
// Created by Katharina Sachs on 09.11.21.
//

#ifndef AUFGABE2_MY_VECTOR_H
#define AUFGABE2_MY_VECTOR_H

using namespace std;

namespace my {
    template<typename T>
    class vector {
    public:
        vector() { n_ = new T[0]; }

        vector(int number_intial_elements, T t) {
            n_ = new T[number_intial_elements];
            for (int i = 0; i < number_intial_elements; i++) {
                n_[i] = t;
                size_++;
            }
        }

        explicit vector(int number_intial_elements) {
            n_ = new T[number_intial_elements];
            for (int i = 0; i < number_intial_elements; i++) {
                n_[i] = nullptr;
                size_++;
            }
        }

        bool empty() const { return size_ == 0; };

        size_t size() const { return size_; }

        ~vector() {
            delete[] n_;
            size_ = 0;
        }

        void clear() {
            delete[] n_;
            size_ = 0;
        }

        void push_back(const T &);

        T pop_back();

        T &operator[](size_t) const;

        T &at(size_t) const;

        vector(vector<T> const &) = delete;

        vector<T> &operator=(vector<T> const &) = delete;

    private:
        T *n_;
        size_t size_ = 0;
    };

    template<typename T>
    inline void vector<T>::push_back(const T &value) {
        T *tmp_arr = new T[size_ + 1];
        for (int i = 0; i < size_; i++) {
            tmp_arr[i] = n_[i];
        }
        delete[] n_;
        tmp_arr[size_] = value;
        size_++;
        n_ = tmp_arr;
    }

    template<typename T>
    T vector<T>::pop_back() {
        T *tmp_arr = new T[size_ - 1];
        for (int i = 0; i < size_ - 1; i++) {
            tmp_arr[i] = n_[i];
        }
        T removed_element = n_[size_ - 1];
        delete[] n_;
        n_ = tmp_arr;
        size_--;
        return removed_element;
    }

    template<typename T>
    T &vector<T>::operator[](size_t index) const {
        return n_[index];
    }


    template<typename T>
    T &vector<T>::at(size_t index) const {
        cout << index << endl;
        cout << size_ << endl;
        if (index >= 0 && index < size_) {
            return n_[index];
        } else {
            throw out_of_range("Index is out of range.");
        }
    }
}

#endif //AUFGABE2_MY_vector_H
