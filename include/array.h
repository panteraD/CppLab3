#ifndef ARRAY_ARRAY_H
#define ARRAY_ARRAY_H

#include <cstddef>
#include <iostream>
#include <stdexcept>

template<class T>
class Vector {
public:
    // Member types
    using value_type = T;
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    static value_type invar;

    // Member function
    Vector();

    explicit Vector(size_type count);

    Vector(size_type count, const value_type& value);

    Vector(const Vector &other);

    Vector(Vector&& other) noexcept;

    ~Vector();

    Vector& operator=(const Vector& other);

    Vector& operator=(Vector&& other) noexcept;

    // Element access
    reference operator[](size_type pos) noexcept;

    const_reference operator[](size_type pos) const noexcept;

    // at() checks pos and throws std::out_of_range is pos >= size()
    reference at(size_type pos);

    const_reference at(size_type pos) const;

    reference front() noexcept;

    const_reference front() const noexcept;

    reference back() noexcept;

    const_reference back() const noexcept;

    pointer data() noexcept;

    const_pointer data() const noexcept;

    // Capacity
    bool empty() const noexcept;

    size_type size() const noexcept;

    size_type capacity() const noexcept;

    // Modifiers
    void clear();

    void push_back(const value_type& value);

private:
    //Member
    value_type *data_;
    size_type size_;
    size_type capacity_;

};

template <class T>
T Vector<T>::invar = T();

template <class T>
Vector<T>::Vector() {
    data_ = new value_type[1];
    capacity_ = 1;
    size_ = 0;
}

template <class T>
Vector<T>::Vector(size_type count) {
    data_ = new value_type[2*count];
    capacity_ = 2*count;
    size_ = count;
}

template <class T>
Vector<T>::Vector(size_type count, const value_type& value) {
    data_ = new value_type[2*count];
    capacity_ = 2*count;
    size_ = count;
    for(size_type i = 0; i < count; ++i) {
        *(data_ + i) = value;
    }
}

template <class T>
Vector<T>::Vector(const Vector &other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new value_type[capacity_];
    for(size_type i = 0; i < size_; ++i) {
        *(data_ + i) = *(other.data_ + i);
    }
}

template <class T>
Vector<T>::Vector(Vector&& other) noexcept {
    size_ = other.size_;
    other.size_ = 0;
    capacity_ = other.capacity_;
    other.capacity_ = 0;
    data_ = other.data_;
    other.data_ = &Vector<T>::invar;
}

template <class T>
Vector<T>::~Vector() {
    if (data_ != &Vector::invar) {
        delete[] data_;
    }
}

template <class T>
Vector<T> & Vector<T>::operator=(const Vector& other) {
    if (capacity_ >= other.size_) {
        for(size_type i = 0; i < other.size_; ++i) {
            *(data_ + i) = *(other.data_ + i);
        }
    } else {
        delete [] data_;
        data_ = new value_type[2*other.size_];
        capacity_ = 2*other.size_;
        for(size_type i = 0; i < other.size_; ++i) {
            *(data_ + i) = *(other.data_ + i);
        }
    }
    size_ = other.size_;
}

template <class T>
Vector<T> & Vector<T>::operator=(Vector&& other) noexcept {
    size_ = other.size_;
    capacity_ = other.capacity_;
    delete [] data_;
    data_ = other.data_;
    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = &Vector<T>::invar;
}

template <class T>
T& Vector<T>::operator[](size_type pos) noexcept { /* noexcept? */
    return *(data_ + pos);
}

template <class T>
const T& Vector<T>::operator[](size_type pos) const noexcept { /* noexcept ? */
    return *(data_ + pos);
}

template <class T>
T& Vector<T>::at(size_type pos) {
    if (pos >= size_) { /* capacity */
        throw std::out_of_range("");
    }
    value_type *pt = data_ + pos;
    return *(pt);
}

template <class T>
const T& Vector<T>::at(size_type pos) const {
    if (pos >= size_) { /* capacity */
        throw std::out_of_range("");
    }
    value_type *pt = data_ + pos;
    return *(pt);
}

template <class T>
T& Vector<T>::front() noexcept {
    return *data_;
}

template <class T>
const T& Vector<T>::front() const noexcept {
    return *data_;
}

template <class T>
T& Vector<T>::back() noexcept {
    return *(data_ + size_ - 1);
}

template <class T>
const T& Vector<T>::back() const noexcept {
    return *(data_ + size_ - 1);
}

template <class T>
T* Vector<T>::data() noexcept {
    return data_;
}

template <class T>
const T* Vector<T>::data() const noexcept {
    return data_;
}

template <class T>
bool Vector<T>::empty() const noexcept {
    return size_ != 0 ? false : true;
}

template <class T>
std::size_t Vector<T>::size() const noexcept {
    return size_;
}

template <class T>
std::size_t Vector<T>::capacity() const noexcept {
    return capacity_;
}

template <class T>
void Vector<T>::clear() {
    size_ = 0;
}

template <class T>
void Vector<T>::push_back(const value_type& value) {
    if ((size_ + 1) <= capacity_) {
        *(data_ + size_) = value;
        ++size_;
    } else {
        ++size_;
        capacity_ = 2*size_;
        value_type *tmp = new value_type[capacity_];
        for(size_type i = 0; i < size_ - 1; ++i) {
            *(tmp + i) = *(data_ + i);
        }
        *(tmp + size_ - 1) = value;
        data_ = tmp;
    }
}

#endif //ARRAY_ARRAY_H
