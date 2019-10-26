#include <iostream>
#include <climits>
#include "dp.hpp"

int main(int argc, char const *argv[])
{
    std::map<long long, long long> length_value;
    length_value[1] = 1;
    length_value[2] = 5;
    length_value[3] = 8;
    length_value[4] = 9;
    length_value[5] = 10;
    length_value[6] = 17;
    length_value[7] = 17;
    length_value[8] = 20;
    length_value[9] = 24;
    length_value[10]= 30;
    long long total_length = 17;
    DynamicProgramming dp1(length_value, total_length, LLONG_MIN);
    if (dp1.has_solution)
    {
        std::cout << "max value of cut "<<total_length<<"\nlength\tvalue\tcount\toptimal value"<< std::endl;
        for (int i=1; i <= 10; ++i)
            std::cout<<i<<"\t"<<length_value[i]<<"\t"<<dp1.optimal_solution[i]<<"\t"<<dp1.optimal_value[i]<<std::endl;
    }
    else
        std::cout<<"no solution for cut "<<total_length<<std::endl;
    
    std::map<long long, long long> coin_count;
    coin_count[2] = 1;
    coin_count[5] = 1;
    coin_count[10]= 1;
    
    for (long long change = 32; change < 35; ++change)
    {
        DynamicProgramming dp2(coin_count, change, LLONG_MAX);
        if (dp2.has_solution)
        {
            std::cout <<"\nmin coins to change "<<change<<"\ncoin\tcount\ttotal"<< std::endl;
            std::cout<<"2\t"<<dp2.optimal_solution[2]<<"\t"<<dp2.optimal_value[change]<<std::endl;
            std::cout<<"5\t"<<dp2.optimal_solution[5]<<"\t"<<std::endl;
            std::cout<<"10\t"<<dp2.optimal_solution[10]<<"\t"<<std::endl;
        }
        else
            std::cout<<"\nno solution for change "<<change<<std::endl;
    }

    return 0;
}
