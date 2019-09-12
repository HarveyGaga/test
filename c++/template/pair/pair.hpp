#include <iostream>
#include <string>
using namespace std;
template <class T1,class T2>
class Pair
{
public:
    T1 key;  //关键字
    T2 value;  //值
    Pair(T1 k,T2 v):key(k),value(v) { };
    bool operator < (const Pair<T1,T2> & p) const;
};
template<class T1,class T2>
bool Pair<T1,T2>::operator < (const Pair<T1,T2> & p) const
//Pair的成员函数 operator <
{ //"小"的意思就是关键字小
    return key < p.key;
}
