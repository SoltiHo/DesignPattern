#include "lab1_problem_adapter.h"

void main(){
    std::cout << "------ adapter_problem demo ------" << std::endl;
    adapter_problem::demo();
    std::cout << std::endl << std::endl;

    std::cout << "------ adapter_adapter1 demo ------" << std::endl;
    adapter_adapter1::demo();
    std::cout << std::endl << std::endl;

    std::cout << "------ adapter_adapter2 demo ------" << std::endl;
    adapter_adapter2::demo();
    std::cout << std::endl << std::endl;
}