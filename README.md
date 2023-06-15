# AVLTree Library
This is an implementation of an AVLTree data structure in C++ using templates and a comparator class.
This library was created as part of the Data Structures and Algorithms course at the University of Tehran in Spring 2023.

## Usage
To use the AVLTree library, include the library.h header file in your C++ code. 
The AVLTree class is templated, so you can use it with any data type that supports the comparison operators (<, >, ==, etc.). 
You can also provide a custom comparator class to the AVLTree constructor if you need to use a different comparison function.

Here's an example of how to use the AVLTree class:
```cpp
#include "library.h"
#include "library.cpp"
#include <iostream>

int main() {
    AVLTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);
    std::cout << "Tree height: " << tree.getHeight() << std::endl;
    std::vector<int> sorted = tree.getSorted();
    for (int value : sorted) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    return 0;
}
```

### License
This AVLTree library is released under the MIT License. 
See the LICENSE file for more information.



