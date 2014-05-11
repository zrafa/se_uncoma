/**
 * @file MyroIO.h
 *
 * This header file contains helper functions, to make it easier/faster to 
 * output things. Currently, it only contains overloaded << operators for
 * list and vector. In the future it may contain other things of the same
 * idea.
 */

#ifndef __MYRO_IO_H__
#define __MYRO_IO_H__

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>

/** @defgroup myro_io MyroIO.h Commands
 * These features are only available if you \#include<MyroIO.h> in your source. 
 * This functions only serve as convienience functions and are strictly 
 * optional and up to the student to use if they feel it will make their life 
 * easier.
 * @{
 */

/**
 * Pretty Printing vector
 * Will print each element in the vector in the format of: 
 * {element_one, element_two, element_three, ..., element_n}
 */
template <typename T> std::ostream& operator << (std::ostream& os, std::vector<T> & Vref) {
    typename std::vector<T>::const_iterator Vi;
    os << "{";
    for (Vi = Vref.begin(); Vi != Vref.end(); Vi++) {
        os << *Vi;
        if (Vi+1 != Vref.end()) os << ", ";
    }
    os << "}";
    return os;
}

/**
 * Pretty Printing list
 * Will print each element in the list in the format of: 
 * [element_one, element_two, element_three, ..., element_n]
 */
template <typename T> std::ostream& operator << (std::ostream& os, std::list<T> Lref) {
    int i = 0;
    typename std::list<T>::const_iterator Li;
    os << "[";
    for (Li = Lref.begin(); Li != Lref.end(); Li++) {
        os << *Li;
        if (++i < (int) Lref.size()) os << ", ";
    }
    os << "]";
    return os;
}

///@}

#endif //__MYRO_IO_H__
