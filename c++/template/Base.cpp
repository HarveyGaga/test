#include "Base.hpp"

template <typename T>
Stack<T>::Stack()
{
    m_iTop = 0;
}

template <typename T>
bool Stack<T>::IsEmpty()
{
    return m_iTop == 0;
}

template <typename T>
bool Stack<T>::IsFull()
{
    return m_iTop == MAX;
}

template <typename T>
bool Stack<T>::Push(const T& item)
{
    if (m_iTop < MAX)
    {
        Items[m_iTop++] = item;
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool Stack<T>::Pop(T& item)
{
    if (m_iTop > 0)
    {
        item = Items[m_iTop--];
        return true;
    }
    else
    {
        return false;
    }
}
