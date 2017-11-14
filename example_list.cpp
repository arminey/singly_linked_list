#include <iostream>
#include "a_list.h"

int main(){
    a::list<int> l;
    a::list<int> l1;
    l1.push_back(5);
    l1.print();
    l.reverse();
    l.print();
    if(l == l1)
        std::cout << "true" << std::endl;
    std::cout << l.size() << std::endl;
}
