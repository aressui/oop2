#include <iostream>
#include "include/solution.h"

// Различные конструкторы

int main() {
    Five firstArray{1, 2, 2, 3, 1, 4, 0};
    std::cout << "First array: ";
    firstArray.print(std::cout) << std::endl;

    Five secondArray{1, 4, 3};
    std::cout << "Second array: ";
    secondArray.print(std::cout) << std::endl;

    Five thirdArray{1, 4, 3};
    std::cout << "Third array: ";
    thirdArray.print(std::cout) << std::endl;

    //fill
    Five filledArray(5, 2);
    std::cout << "Filled array (5 elements with value 2): ";
    filledArray.print(std::cout) << std::endl;

    //from String
    Five fromString("1432");
    std::cout << "Array from string: ";
    fromString.print(std::cout) << std::endl;
    
    //move
    Five fourthArray(std::move(thirdArray));
    std::cout << "Fourth array (moved from third): ";
    fourthArray.print(std::cout) << std::endl;

    Five tempArray(Five{2, 1, 1, 0, 4, 4, 2});

    //sum
    Five fifthArray(firstArray.add(secondArray));
    std::cout << "Addition result: ";
    fifthArray.print(std::cout) << std::endl;

    try {
        // Ok
        Five sixthArray = firstArray.remove(secondArray);
        std::cout << "Subtraction result (successful): ";
        sixthArray.print(std::cout) << std::endl;

        // Error
        Five seventhArray = secondArray.remove(fourthArray);
        std::cout << "Subtraction result (should not execute): ";
        seventhArray.print(std::cout) << std::endl;

    } catch (std::exception& exception) {
        std::cerr << "Caught exception: " << exception.what() << std::endl;
    }

    // equals; large; small
    std::cout << "secondArray == thirdArray: " << (secondArray.equals(thirdArray) ? "Yes" : "No") << std::endl;
    std::cout << "firstArray > secondArray : "  << (firstArray.large(secondArray)  ? "Yes" : "No") << std::endl;
    std::cout << "firstArray < secondArray : "  << (firstArray.small(secondArray)  ? "Yes" : "No") << std::endl;
    
    return 0;
}