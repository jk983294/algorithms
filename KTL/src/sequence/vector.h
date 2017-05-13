#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <initializer_list>

#include "../algorithm/algorithm.h"
#include "../allocator/allocator.h"
#include "../allocator/uninitialized.h"
#include "../iterator/iterator.h"

namespace ktl {

template <class T, class Alloc = alloc>
class vector {
public:
    typedef T value_type;
    typedef T* pointer;
    typedef T* iterator;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef reverse_iterator_<iterator> reverse_iterator;

protected:
    typedef simple_alloc<value_type, Alloc> data_allocator;

    iterator start_;
    iterator finish_;
    iterator end_of_storage_;

    void insert_aux(iterator position, const T& x);

    void deallocate() {
        if (start_) {
            data_allocator::deallocate(start_, end_of_storage_ - start_);
        }
    }

    void fill_initialize(size_type n, const T& value) {
        start_ = allocate_and_fill(n, value);
        finish_ = start_ + n;
        end_of_storage_ = finish_;
    }

    iterator allocate_and_fill(size_type n, const T& x) {
        iterator result = data_allocator::allocate(n);
        uninitialized_fill_n(result, n, x);
        return result;
    }

public:
    iterator begin() const { return start_; }
    iterator end() const { return finish_; }
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }

    size_type size() const { return size_type(end() - begin()); }
    size_type capacity() const { return size_type(end_of_storage_ - begin()); }
    bool empty() const { return begin() == end(); }
    reference operator[](size_type n) { return *(begin() + n); }
    bool operator==(const vector& other) const {
        auto first1 = begin(), last1 = end();
        auto first2 = other.begin(), last2 = other.end();
        for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
            if (*first1 != *first2) return false;
        }
        return (first1 == last1 && first2 == last2);
    }

    vector() : start_(0), finish_(0), end_of_storage_(0) {}
    vector(size_type n, const T& value) { fill_initialize(n, value); }
    vector(int n, const T& value) { fill_initialize(n, value); }
    vector(long n, const T& value) { fill_initialize(n, value); }
    vector(const std::initializer_list<T> v) {
        auto start_v = v.begin();
        auto end_v = v.end();
        size_type n = v.size();
        fill_initialize(n, T());  // also works for POD, int() == 0
        finish_ = ktl::copy(start_v, end_v, start_);
    }
    explicit vector(size_type n) { fill_initialize(n, T()); }

    template <class InputIterator>
    vector(InputIterator first, InputIterator last) {
        fill_initialize(last - first, T());  // also works for POD, int() == 0
        finish_ = ktl::copy(first, last, start_);
    }

    ~vector() {
        destroy(start_, finish_);  // call destructor of each object for non-POD
        deallocate();              // return space to allocator
    }

    reference front() { return *begin(); }
    reference back() { return *(end() - 1); }
    void push_back(const T& x) {
        if (finish_ != end_of_storage_) {
            construct(finish_, x);
            finish_++;
        } else {
            insert_aux(end(), x);
        }
    }

    void pop_back() {
        --finish_;
        destroy(finish_);
    }

    void insert(iterator position, size_type n, const T& x);

    // erase one element
    iterator erase(iterator position) {
        if (position + 1 != end()) copy(position + 1, finish_, position);
        finish_--;
        destroy(finish_);
        return position;
    }

    // erase elements in range
    iterator erase(iterator start_earse, iterator end_earse) {
        auto i = copy(end_earse, finish_, start_earse);
        destroy(i, finish_);
        finish_ = finish_ - (finish_ - start_earse);
        return start_earse;
    }

    // if new size < old size, then erase redudent. else insert at tail
    void resize(size_type new_size, const T& x) {
        if (new_size < size())
            erase(begin() + new_size, end());
        else
            insert(end(), new_size - size(), x);
    }

    void resize(size_type new_size) { resize(new_size, T()); }
    void clear() { erase(begin(), end()); }
};

template <class T, class Alloc>
void vector<T, Alloc>::insert(iterator position, size_type n, const T& x) {
    T x_copy = x;
    if (n != 0) {
        if (size_type(end_of_storage_ - finish_) >= n) {
            // spare space can hold n elements, so no need to allocate more space
            const size_type elems_after = finish_ - position;
            iterator old_finish = finish_;

            if (elems_after > n) {
                // enough space for copy_backward
                uninitialized_copy(finish_ - n, finish_, finish_);
                finish_ += n;
                copy_backward(position, old_finish - n, old_finish);
                fill(position, position + n, x_copy);
            } else {
                uninitialized_fill_n(finish_, n, x_copy);
                finish_ += n - elems_after;
                uninitialized_copy(position, old_finish, finish_);
                finish_ += elems_after;
                fill(position, old_finish, x_copy);
            }
        } else {
            // not enough space, then increase space
            const size_type old_size = size();
            const size_type new_size = old_size + max(old_size, n);

            iterator new_start = data_allocator::allocate(new_size);
            iterator new_finish = new_start;
            try {
                new_finish = uninitialized_copy(start_, position, new_start);
                new_finish = uninitialized_fill_n(new_finish, n, x_copy);
                new_finish = uninitialized_copy(position, finish_, new_finish);
            } catch (...) {
                destroy(new_start, new_finish);
                data_allocator::deallocate(new_start, new_size);
                throw;
            }
            destroy(start_, finish_);
            deallocate();
            start_ = new_start;
            finish_ = new_finish;
            end_of_storage_ = new_start + new_size;
        }
    }
}

template <class T, class Alloc>
void vector<T, Alloc>::insert_aux(iterator position, const T& x) {
    if (finish_ != end_of_storage_) {
        // still have space, construct in finish_ with previous postion's value
        construct(finish_, *(finish_ - 1));
        ++finish_;
        T x_copy = x;
        copy_backward(position, finish_ - 2, finish_ - 1);
        *position = x_copy;
    } else {
        // no space, then double old size
        const size_type old_size = size();
        const size_type new_size = old_size != 0 ? 2 * old_size : 1;

        iterator new_start = data_allocator::allocate(new_size);
        iterator new_finish = new_start;

        // three phase construction
        try {
            new_finish = ktl::uninitialized_copy(start_, position, new_start);  // phase 1
            construct(new_finish, x);                                           // phase 2
            new_finish++;
            new_finish = ktl::uninitialized_copy(position, finish_, new_finish);  // phase 3
        } catch (...) {
            // commit or rollback semantics
            destroy(new_start, new_finish);
            data_allocator::deallocate(new_start, new_size);
            throw;
        }

        // release old space
        destroy(begin(), end());
        deallocate();

        // adjust pointer to new space
        start_ = new_start;
        finish_ = new_finish;
        end_of_storage_ = new_start + new_size;
    }
}
}

#endif
