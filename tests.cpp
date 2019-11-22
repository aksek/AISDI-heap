#include <stdexcept>
#include <iostream>
#include <cassert>
#include "heap.h"

void unit_test() 
{
    Heap4<int,int> heap;

    // pusty kopiec
    assert(heap.empty());
    assert(heap.size() == 0);

    bool exception_thrown = false;
    try 
	{
        heap.peek();
    } 
	catch(const std::logic_error&) 
	{
        exception_thrown = true;
    }
    assert(exception_thrown);

    // dodawanie elementów
    heap.insert(10, 10);	// [10]
    assert(heap.peek().first == 10);

    heap.insert(50, 50);	// [10, 50]
    heap.insert(100, 100);  // [10, 50, 100]
    heap.insert(40, 40);	// [10, 40, 50, 100]
    heap.insert(20, 20);	// [10, 20, 40, 50, 100]
    assert(heap.peek().first == 100);

    heap.insert(5, 5);		// [5, 10, 20, 40, 50, 100]
    assert(heap.peek().first == 100);

	heap.print(std::cout);

    assert(!heap.empty());
    assert(heap.size() == 6);

    // pobieranie elementów
    heap.pop();				// [10, 20, 40, 50, 5]
    assert(heap.peek().first == 50);
    assert(heap.size() == 5);

    heap.pop();				// [20, 40, 10, 5]
    heap.print(std::cout);
    assert(heap.peek().first == 40);

    heap.pop();				// [5, 10, 20]
    assert(heap.peek().first == 20);

    heap.pop();				// [5, 10]
    assert(heap.peek().first == 10);

    heap.pop();				// [5]
    assert(heap.peek().first == 5);

    heap.pop();
    assert(heap.empty());
    heap.print(std::cout);

    int random;
    for (int i = 0; i < 30; ++i) {
        random = rand() % 200;
        heap.insert(random, random);
        if (i % 10 == 0) {
            heap.print(std::cout);
            std::cout << '\n';
        }
    }
    
    for (int i = 0; i < 30; ++i) {
        heap.pop();
        if (i % 10 == 0) {
            heap.print(std::cout);
            std::cout << '\n';
        }
    }
}

int main()
{
	unit_test();
}
