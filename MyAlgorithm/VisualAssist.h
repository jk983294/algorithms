#ifndef MYALGORITHM_VISUALASSIST_H
#define MYALGORITHM_VISUALASSIST_H

#include <iostream>
#include <set>
using namespace std;

template<typename Type>
inline std::ostream& operator << (std::ostream& os, const set<Type>& _set) {
    for(auto itr = _set.begin(); itr != _set.end(); itr++)
        os<<*itr<<" ";
    return os;
}

template<typename Type>
inline std::ostream& operator << (std::ostream& os, const vector<Type>& v) {
    for(auto itr = v.begin(); itr != v.end(); itr++)
        os<<*itr<<" ";
    return os;
}
template<typename Type>
inline std::ostream& operator << (std::ostream& os, const vector< vector<Type> >& v) {
    for(auto itr = v.begin(); itr != v.end(); itr++)
        os<<*itr<<endl;
    return os;
}

#endif //MYALGORITHM_VISUALASSIST_H
