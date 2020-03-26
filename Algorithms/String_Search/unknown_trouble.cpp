#include <iostream>
#include "KMP.hpp"
#include "Sunday.hpp"

int main(int argc, char const *argv[])
{
    const std::string str("abcaabbabcabaacbacba");
    std::cout << "kmp_search" << std::endl;
    std::cout << kmp_search(str, "abcabaa") << std::endl;
    std::cout << kmp_search(str, "bcabaa") << std::endl;
    std::cout << "sunday_search" << std::endl;
    std::cout << sunday_search(str, "abcabaa") << std::endl;
    std::cout << sunday_search(str, "bcabaa") << std::endl;
    return 0;
}
