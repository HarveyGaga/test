#ifndef STACKTP_H_
#define STACKTP_H_

template <typename T>
class Stack
{
public:
    Stack();
    bool IsEmpty();
    bool IsFull();
    bool Push(const T& item);
    bool Pop(T& item);
private:
    enum{MAX = 10};
    T Items[MAX];
    int m_iTop;
};

#endif
