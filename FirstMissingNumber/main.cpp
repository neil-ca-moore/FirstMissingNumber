//
//  main.cpp
//  FirstMissingNumber
//
//  Created by Neil Moore on 19/02/2017.
//  Copyright © 2017 Neil Moore. All rights reserved.
//


#include <algorithm>
#include <iostream>
#include <vector>

//  Problem is to take in an unsorted vector of non-repeated numbers in the
//  range 1..n and find the first missing number
int firstMissingBySort(std::vector<unsigned> numbers) {
    std::sort(numbers.begin(), numbers.end());
    unsigned expected = 1;
    for(auto const& number : numbers) {
        if(number != expected) {
            break;
        } else {
            ++expected;
        }
    }
    return expected;
}


//Postcondition: recurse on a smaller range
int firstMissingByPartitionRecursive(std::vector<unsigned>::iterator begin,
                                     std::vector<unsigned>::iterator end,
                                     unsigned minExpected) {
    if(begin == end) {
        return minExpected;
    }
    auto partitionValue = begin;
    auto secondPartition = std::partition(begin, end, [=](unsigned num) { return num < *partitionValue; });
    unsigned partitionValueIfNothingMissingInLowerHalf = minExpected + (unsigned)std::distance(begin, secondPartition);
    if(partitionValueIfNothingMissingInLowerHalf == *secondPartition) {
        return firstMissingByPartitionRecursive(secondPartition, end, partitionValueIfNothingMissingInLowerHalf);
    } else {
        return firstMissingByPartitionRecursive(begin, secondPartition, minExpected);
    }
}

//  Problem is to take in an unsorted vector of non-repeated numbers in the
//  range 1..n and find the first missing number
int firstMissingByPartition(std::vector<unsigned> numbers) {
    return firstMissingByPartitionRecursive(numbers.begin(), numbers.end(), 1);
}

int main(int argc, const char * argv[]) {
    for(auto const& fn : {firstMissingBySort, firstMissingByPartition}) {
        
        std::cout << fn({}) << std::endl;
        std::cout << fn({2}) << std::endl;
        std::cout << fn({1}) << std::endl;
        std::cout << fn({1,3,4}) << std::endl;
        std::cout << fn({1,2,3,4}) << std::endl;
        std::cout << fn({4,3,1}) << std::endl;
        std::cout << fn({5,4,3,2,1}) << std::endl;
        std::cout << fn({5,4,3,1}) << std::endl;
        std::cout << fn({4,3,2,1,5,7,8}) << std::endl;
        std::cout << fn({4,3,6,2,1,5,8}) << std::endl;
        std::cout << std::endl;
    }
    return 0;
}
