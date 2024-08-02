#ifndef CONCEPT_H
#define CONCEPT_H

#include <concepts>

template<typename T>
concept Comparable = requires(T a, T b) {
    a < b
    a > b
    a == b
}


#endif