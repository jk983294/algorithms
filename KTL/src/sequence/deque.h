#ifndef _DEQUE_H_
#define _DEQUE_H_

#include <initializer_list>
#include "../algorithm/algorithm.h"
#include "../allocator/allocator.h"
#include "../allocator/construct.h"
#include "../allocator/uninitialized.h"

namespace ktl {

template <class T, class Ref, class Ptr, size_t BufSize>
struct _deque_iterator {
    typedef _deque_iterator<T, T&, T*, BufSize> iterator;
    typedef _deque_iterator<const T, const T&, const T*, BufSize> const_iterator;
    typedef _deque_iterator self;

    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef ptrdiff_t difference_type;

    typedef size_t size_type;
    typedef T** map_pointer;

    // count of T to be contained in one buffer
    static size_t buffer_size() { return _deque_buf_size(BufSize, sizeof(T)); }

    T* cur;              // current element of buffer
    T* first;            // head of buffer
    T* last;             // tail of buffer
    map_pointer buffer;  // map[x], map is control center of deque

    // if user define buf size, use it
    // otherwise, if size of T > 512, use 1
    // otherwise, it is the count of T which a 512 buffer can contain
    static size_t _deque_buf_size(size_t bs, size_t sz) {
        return bs != 0 ? bs : (sz < 512 ? size_t(512 / sz) : size_t(1));
    }

    // move this iterator to the first position of next buffer
    void set_buffer(map_pointer new_buffer) {
        buffer = new_buffer;
        first = *new_buffer;
        last = first + difference_type(buffer_size());
    }

    reference operator*() const { return *cur; }
    pointer operator->() const { return &(operator*()); }
    difference_type operator-(const self& x) const {
        return difference_type(buffer_size()) * (buffer - x.buffer - 1) /* count of buffer * count of T */
               + (cur - first)                                          /* count of this buffer be used */
               + (x.last - x.cur);                                      /* count of buffer x be used */
    }

    self& operator++() {  // ++i
        ++cur;
        if (cur == last) {
            set_buffer(buffer + 1);
            cur = first;
        }
        return *this;
    }

    self operator++(int) {  // i++
        self tmp = *this;
        ++*this;
        return tmp;
    }

    self& operator--() {  // --i
        if (cur == first) {
            set_buffer(buffer - 1);
            cur = last;
        }
        --cur;
        return *this;
    }

    self operator--(int) {  // i--
        self tmp = *this;
        --*this;
        return tmp;
    }

    self& operator+=(difference_type n) {
        difference_type offset = n + cur - first;
        if (offset >= 0 && offset < difference_type(buffer_size())) {
            cur += n;  // in the same buffer
        } else {       // in different buffer
            difference_type buffer_offset = 0;
            if (offset > 0) {
                buffer_offset = offset / difference_type(buffer_size());
            } else {
                buffer_offset = -difference_type((-offset - 1) / difference_type(buffer_size())) - 1;
            }
            set_buffer(buffer + buffer_offset);
            cur = first + (offset - buffer_offset * difference_type(buffer_size()));
        }
        return *this;
    }

    self operator+(difference_type n) const {
        self tmp = *this;
        return tmp += n;
    }

    self& operator-=(difference_type n) { return *this += -n; }

    self operator-(difference_type n) const {
        self tmp = *this;
        return tmp -= n;
    }

    reference operator[](difference_type n) const { return *(*this + n); }

    bool operator==(const self& x) const { return cur == x.cur; }
    bool operator!=(const self& x) const { return cur != x.cur; }
    bool operator<(const self& x) const { return (buffer == x.buffer) ? (cur < x.cur) : (buffer < x.buffer); }
};

template <class T, class Alloc = alloc, size_t BufSize = 0>
class deque {
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

public:
    typedef _deque_iterator<T, T&, T*, BufSize> iterator;

protected:
    typedef pointer* map_pointer;
    typedef simple_alloc<value_type, Alloc> data_allocator;
    typedef simple_alloc<pointer, Alloc> map_allocator;

    pointer allocate_buffer() { return data_allocator::allocate(buffer_size()); }

    void deallocate_buffer(pointer x) { data_allocator::deallocate(x, buffer_size()); }

    static size_t buffer_size() { return _deque_buf_size(BufSize, sizeof(T)); }

    static size_t _deque_buf_size(size_t n, size_t sz) {
        return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
    }

    size_t initial_map_size() { return 8; }

    void fill_initialize(size_type n, const value_type& value) {
        create_map_and_buffers(n);
        map_pointer cur;
        for (cur = start.buffer; cur < finish.buffer; ++cur) uninitialized_fill(*cur, *cur + buffer_size(), value);
        uninitialized_fill(finish.first, finish.cur, value);
    }

    void push_back_aux(const value_type& t) {
        value_type t_copy = t;
        reserve_map_at_back();
        *(finish.buffer + 1) = allocate_buffer();

        construct(finish.cur, t_copy);  // fulfill last element in current buffer, then move to new buffer
        finish.set_buffer(finish.buffer + 1);
        finish.cur = finish.first;
    }

    void push_front_aux(const value_type& t) {
        value_type t_copy = t;
        reserve_map_at_front();
        *(start.buffer - 1) = allocate_buffer();

        start.set_buffer(start.buffer - 1);  // move to new buffer, fulfill last element of that buffer
        start.cur = start.last - 1;
        construct(start.cur, t_copy);
    }

    /**
     * init map, reserve at least buffer can fit num_elements of T
     */
    void create_map_and_buffers(size_type num_elements) {
        size_type num_buffers = num_elements / buffer_size() + 1;
        map_size = max(initial_map_size(), num_buffers + 2);
        map = map_allocator::allocate(map_size);

        // first buffer sit in the middle of buffer array, spare two side for enlargement
        map_pointer nstart = map + (map_size - num_buffers) / 2;
        map_pointer nfinish = nstart + num_buffers - 1;
        map_pointer cur;

        for (cur = nstart; cur <= nfinish; cur++) {
            *cur = allocate_buffer();
        }
        start.set_buffer(nstart);
        finish.set_buffer(nfinish);
        start.cur = start.first;
        finish.cur = finish.first + num_elements % buffer_size();
    }

    void reserve_map_at_back(size_type buffer_to_add = 1) {
        if (buffer_to_add > map_size - (finish.buffer - map + 1)) reallocate_map(buffer_to_add, false);
    }
    void reserve_map_at_front(size_type buffer_to_add = 1) {
        if (buffer_to_add > size_type(start.buffer - map)) reallocate_map(buffer_to_add, true);
    }
    void reallocate_map(size_type buffer_to_add, bool add_at_front) {
        size_type old_num_buffers = finish.buffer - start.buffer + 1;
        size_type new_num_buffers = old_num_buffers + buffer_to_add;

        map_pointer new_nstart;
        if (map_size > 2 * new_num_buffers) {
            // no need to allocate more buffers, just shift used buffers into middle area
            new_nstart = map + (map_size - new_num_buffers) / 2 + (add_at_front ? buffer_to_add : 0);
            if (new_nstart < start.buffer)
                copy(start.buffer, finish.buffer + 1, new_nstart);
            else
                copy_backward(start.buffer, finish.buffer + 1, new_nstart + old_num_buffers);
        } else {
            size_type new_map_size = map_size + max(map_size, buffer_to_add) + 2;
            map_pointer new_map = map_allocator::allocate(new_map_size);
            new_nstart = new_map + (new_map_size - new_num_buffers) / 2 + (add_at_front ? buffer_to_add : 0);
            copy(start.buffer, finish.buffer + 1, new_nstart);
            map_allocator::deallocate(map, map_size);
            map = new_map;
            map_size = new_map_size;
        }

        start.set_buffer(new_nstart);
        finish.set_buffer(new_nstart + old_num_buffers - 1);
    }

    void pop_back_aux() {  // finish.cur == finish.first release this buffer
        deallocate_buffer(finish.first);
        finish.set_buffer(finish.buffer - 1);
        finish.cur = finish.last - 1;
        destroy(finish.cur);
    }

    void pop_front_aux() {  // start.cur == start.last - 1
        destroy(start.cur);
        deallocate_buffer(start.first);
        start.set_buffer(start.buffer + 1);
        start.cur = start.first;
    }

    iterator insert_aux(iterator pos, const value_type& x) {
        size_type index = size_type(pos - start);
        value_type x_copy = x;
        if (index < size() / 2) {
            push_front(front());
            __copy(start + 2, start + index, start + 1, _false_type());
        } else {
            push_back(back());
            __copy_backward(pos, finish - 2, finish - 1, _false_type());
        }
        *pos = x_copy;
        return pos;
    }

public:
    deque() : start(), finish(), map(0), map_size(0) { create_map_and_buffers(0); }
    deque(int n, const value_type& value) : start(), finish(), map(0), map_size(0) { fill_initialize(n, value); }
    ~deque() {
        clear();
        deallocate_buffer(start.first);
        map_allocator::deallocate(map, map_size);
    }

    void push_back(const value_type& t) {
        if (finish.cur != finish.last - 1) {
            construct(finish.cur, t);
            ++finish.cur;
        } else {  // only one element left in current buffer, need a new empty buffer
            push_back_aux(t);
        }
    }

    void push_front(const value_type& t) {
        if (start.cur != start.first) {
            construct(start.cur - 1, t);
            --start.cur;
        } else {  // need new buffer
            push_front_aux(t);
        }
    }

    void pop_back() {
        if (finish.cur != finish.first) {  // at least one element in finish buffer
            --finish.cur;
            destroy(finish.cur);
        } else {
            pop_back_aux();
        }
    }

    void pop_front() {
        if (start.cur != start.last - 1) {  // at least one element in start buffer
            destroy(start.cur);
            ++start.cur;
        } else {
            pop_front_aux();
        }
    }

    // left only one empty buffer
    void clear() {
        for (map_pointer buffer = start.buffer + 1; buffer < finish.buffer; ++buffer) {
            destroy(*buffer, *buffer + buffer_size());
            data_allocator::deallocate(*buffer, buffer_size());
        }

        if (start.buffer != finish.buffer) {
            destroy(start.cur, start.last);
            destroy(finish.first, finish.cur);
            data_allocator::deallocate(finish.first, buffer_size());  // keep first buffer
        } else {
            destroy(start.cur, finish.cur);
        }
        finish = start;
    }

    iterator erase(iterator pos) {
        iterator next = pos;
        ++next;
        size_type index = size_type(pos - start);
        // check which side element less, [start, pos) against [pos + 1, finish)
        // because it is not continous space, so need to use non-pod version copy algorithm
        // even though its value_type is pod
        if (index < (size() >> 1)) {
            __copy_backward(start, pos, next, _false_type());
            pop_front();
        } else {
            __copy(next, finish, pos, _false_type());
            pop_back();
        }
        return start + index;
    }

    iterator erase(iterator first, iterator last) {
        if (first == start && last == finish) {
            clear();
            return finish;
        } else {
            difference_type n = last - first;
            difference_type element_before = first - start;
            if (element_before < (size() - n) / 2) {  // left has less elements
                __copy_backward(start, first, last, _false_type());
                iterator new_start = start + n;
                destroy(start, new_start);  // call destructor
                for (map_pointer i = start.buffer; i < new_start.buffer; ++i) {
                    data_allocator::deallocate(*i, buffer_size());
                }
                start = new_start;
            } else {  // right has less elements
                __copy(last, finish, first, _false_type());
                iterator new_finish = finish - n;
                destroy(new_finish, finish);
                for (map_pointer i = new_finish.buffer + 1; i <= finish.buffer; ++i) {
                    data_allocator::deallocate(*i, buffer_size());
                }
                finish = new_finish;
            }
            return start + element_before;
        }
    }

    iterator insert(iterator position, const value_type& x) {
        if (position.cur == start.cur) {
            push_front(x);
            return start;
        } else if (position.cur == finish.cur) {
            push_back(x);
            return finish - 1;
        } else {
            return insert_aux(position, x);
        }
    }

protected:
    iterator start;   // first buffer first element
    iterator finish;  // last buffer last element

    map_pointer map;     // map is array of pointer, point to actual buffer space, type is T**
    size_type map_size;  // buffer count, every buffer is the same size

public:
    iterator begin() { return start; }
    iterator end() { return finish; }
    reference operator[](size_type n) { return *(start + n); }

    reference front() { return *start; }
    reference back() { return *(finish - 1); }

    size_type size() const { return finish - start; }

    size_type max_size() const { return size_type(-1); }
    bool empty() const { return finish == start; }
};
}

#endif
