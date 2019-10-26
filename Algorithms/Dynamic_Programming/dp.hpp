#include <map>
#include <vector>
#include <functional>

class DynamicProgramming
{
    private:
    std::function<bool(long long, long long)> cmp;

    public:
    DynamicProgramming(const std::map<long long, long long>& SOLUTION_VALUE_TABLE, const long long PROBLEM, const long long LIMIT);
    ~DynamicProgramming(){};

    std::vector<long long> optimal_value;
    std::vector<long long> optimal_choice; // default 0, no solution
    std::map<long long, long long> optimal_solution;
    bool has_solution = false;
};

DynamicProgramming::DynamicProgramming(const std::map<long long, long long>& SOLUTION_VALUE_TABLE, const long long PROBLEM, const long long LIMIT):
optimal_value(PROBLEM + 1, LIMIT), optimal_choice(PROBLEM + 1, 0)
{
    if (LIMIT < 0)
        cmp = std::less<long long>();
    else
        cmp = std::greater<long long>();
    
    optimal_value[0] = 0;
    for (auto &&choice : SOLUTION_VALUE_TABLE)
        optimal_solution[choice.first] = 0;  // each solution has used 0 times yet
    
    for (long long problem = 1; problem <= PROBLEM; ++problem)
    {
        for (auto &&choice : SOLUTION_VALUE_TABLE)  // solve optimal solution of this problem
        {
            if (choice.first <= problem)    // chosed solution will not over solve this problem
            {
                auto sub_optimal_value = optimal_value[problem - choice.first];
                if (sub_optimal_value != LIMIT)     // subproblem has optimal solution
                {                
                    auto value = choice.second + sub_optimal_value;
                    if (cmp(optimal_value[problem], value))
                    {
                        optimal_value[problem] = value;
                        optimal_choice[problem] = choice.first;
                    }
                }
            }
            else
                break;
        }
    }

    if (optimal_choice[PROBLEM] != 0)
    {
        has_solution = true;
        for (auto problem = PROBLEM; 0 < problem; problem-=optimal_choice[problem])
        {
            ++optimal_solution[optimal_choice[problem]];
        }
    }
}
