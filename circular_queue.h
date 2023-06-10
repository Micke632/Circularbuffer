#pragma once

#include <vector>

/*
Circularbuffer . Default using modulo operator
circular_queue<T, 50>   q;

Circularbuffer . can be used with fast & operation (power of two).
size -1 can be used internally.
circular_queue<T, 32, false>   q;

*/

template<typename T, size_t s = 32, bool moduloPolicy = true, typename Container = std::vector<T>>
class circular_queue
{
    static constexpr size_t m_max_items = s + 1;
    static constexpr size_t m_max_items_minus_one = s - 1;

    using size_type = typename Container::size_type;

    size_type m_head = 0;
    size_type m_tail = 0;
    size_t m_overrun_counter = 0;
    Container m_v;


    struct power_of_two
    {
        size_t index(size_type value) const
        {
            return value & m_max_items_minus_one;
        }
        static_assert(!(s  & (s - 1)));     //must be power of 2
        static constexpr size_type max_items = s;
    };

    struct modulo
    {
        size_t index(size_type value) const
        {
            return value % max_items;
        }
        
        static constexpr size_type max_items = m_max_items;

        
    };

    template<bool>
    struct PolicySelector;

    template<>
    struct PolicySelector<true>
    {
        typedef modulo type;
    };
    template<>
    struct PolicySelector<false>
    {
      
        typedef power_of_two type;
    };


    typename PolicySelector<moduloPolicy>::type policy;

public:

    circular_queue()
        :m_v(m_max_items)
    {
    }

    circular_queue(const circular_queue &) = default;
    circular_queue &operator=(const circular_queue &) = default;
    circular_queue(circular_queue &&other) = delete;
    circular_queue &operator=(circular_queue &&other) = delete;

    void push_back(T &&item)
    {

        m_v[m_tail] = std::move(item);
        m_tail = policy.index(m_tail + 1);

        if (m_tail == m_head)
        {
            m_head = policy.index(m_head + 1);
            ++m_overrun_counter;
        }

    }

    void push(const T &item)
    {
        push_back(item);
    }

    void push_back(const T &item)
    {
        m_v[m_tail] = item;
        m_tail = policy.index(m_tail + 1);

        if (m_tail == m_head)
        {
            m_head = policy.index(m_head + 1);
            ++m_overrun_counter;
        }
    }

    const T &front() const
    {
        return m_v[m_head];
    }

    T &front()
    {
        return m_v[m_head];
    }


    size_t size() const
    {
        if (m_tail >= m_head)
        {
            return m_tail - m_head;
        }
        else
        {
            return  policy.max_items - (m_head - m_tail);
        }
    }


    void pop_front()
    {
        m_head = policy.index(m_head + 1);
    }

    bool empty() const
    {
        return m_tail == m_head;
    }


    void clear()
    {
        m_tail = m_head = 0;
    }


    bool full() const
    {
        return policy.index(m_tail + 1) == m_head;
    }

    size_t overrun_counter() const
    {
        return m_overrun_counter;
    }

};