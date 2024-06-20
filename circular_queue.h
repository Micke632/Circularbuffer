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
      size_t index(size_type value) const noexcept
      {
         return value & m_max_items_minus_one;
      }
      static_assert(!(s  & (s - 1)));     //must be power of 2
      static constexpr size_type max_items = s;
   };

   struct modulo
   {
      size_t index(size_type value) const noexcept
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

   typedef typename PolicySelector<moduloPolicy>::type policy_type;

   policy_type policy;

   template <bool isconst = false>
   struct Iiterator
   {
      using iterator_category = std::random_access_iterator_tag;
      using difference_type = long long;
      using reference = typename std::conditional_t< isconst, T const &, T & >;
      using pointer = typename std::conditional_t< isconst, T const *, T * >;

      Container *ptrToBuffer;
      size_type offset;
      size_type index;
      policy_type *m_policy;

   public:
      Iiterator() : ptrToBuffer(nullptr), offset(0), index(0) {} 

      reference operator*() {
         return  ptrToBuffer->operator[](m_policy->index(offset + index));
      }

      reference operator[](size_type index) {
         Iiterator iter = *this;
         iter.index += index;
         return *iter;
      }
    //  pointer operator->() { return &(operator *()); }

      Iiterator& operator++ ()
      {
         ++index;
         return *this;
      };
      Iiterator operator ++(int)
      {
         Iiterator iter = *this;
         ++index;
         return iter;
      }
      Iiterator& operator --()
      {
         --index;
         return *this;
      }
      Iiterator operator --(int) {
         Iiterator iter = *this;
         --index;
         return iter;
      }
      friend  Iiterator operator+(Iiterator lhs, int rhs) {
         lhs.index += rhs;
         return lhs;
      }
      friend  Iiterator operator+(int lhs, Iiterator rhs) {
         rhs.index += lhs;
         return rhs;
      }
      Iiterator& operator+=(int n) {
         index += n;
         return *this;
      }
      friend  Iiterator operator-(Iiterator lhs, int rhs) {
         lhs.index -= rhs;
         return lhs;
      }
      friend difference_type operator-(const  Iiterator& lhs, const  Iiterator& rhs) {
         lhs.index -= rhs;
         return lhs.index - rhs.index;
      }
      Iiterator& operator-=(int n) {
         index -= n;
         return *this;
      }
      bool operator==(const  Iiterator &other)
      {
         return (index + offset == other.index + other.offset);
      }
      bool operator!=(const  Iiterator &other)
      {
         return !this->operator==(other);

      }
      bool operator<(const  Iiterator &other)
      {
         return (index + offset < other.index + other.offset);
      }
      bool operator<=(const  Iiterator &other)
      {
         return (index + offset <= other.index + other.offset);
      }
      bool operator >(const  Iiterator &other)
      {
         return !this->operator<=(other);
      }
      bool operator>=(const  Iiterator &other)
      {
         return !this->operator<(other);
      }
   };

public:

   using iterator = Iiterator<false>;
   using const_iterator = Iiterator<true>;

   iterator begin()
   {
      iterator iter;
      iter.ptrToBuffer = &m_v;
      iter.m_policy = &policy;
      iter.offset = m_head;
      iter.index = 0;
      return iter;
   }

   const_iterator begin() const
   {
      const_iterator iter;
      iter.ptrToBuffer = &m_v;
      iter.m_policy = &policy;
      iter.offset = m_head;
      iter.index = 0;
      return iter;
   }

   const_iterator cbegin() const
   {
      const_iterator iter;
      iter.ptrToBuffer = &m_v;
      iter.m_policy = &policy;
      iter.offset = m_head;
      iter.index = 0;
      return iter;
   }
   
   iterator end()
   {
      iterator iter;
      iter.ptrToBuffer = &m_v;
      iter.m_policy = &policy;
      iter.offset = m_head;
      iter.index = size();
      return iter;
   }
   const_iterator end() const
   {
      const_iterator iter;
      iter.ptrToBuffer = &m_v;
      iter.m_policy = &policy;
      iter.offset = m_head;
      iter.index = size();
      return iter;
   }
   const_iterator cend() const
   {
      const_iterator iter;
      iter.ptrToBuffer = &m_v;
      iter.m_policy = &policy;
      iter.offset = m_head;
      iter.index = size();
      return iter;

   }


   constexpr circular_queue()
      :m_v(m_max_items)
   {}

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

   const T &at(size_type i) const
   {
      return m_v[i];
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