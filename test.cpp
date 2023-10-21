#include <iostream>

int main() {
    const int SIZE = 5;
    int* sourceArray[SIZE] = {new int(1), new int(2), new int(3), new int(4), new int(5)};
    int* destinationArray[SIZE];

    destinationArray[0] = sourceArray[SIZE-1];
    for (int i = 1; i < SIZE; i++) {
        destinationArray[i] = sourceArray[i-1];
    }

    // Print the elements of the destination array
    for (int i = 0; i < SIZE; i++) {
        std::cout << *destinationArray[i] << " ";
    }

    // Clean up memory
    for (int i = 0; i < SIZE; i++) {
        delete sourceArray[i];
    }

    return 0;
}
