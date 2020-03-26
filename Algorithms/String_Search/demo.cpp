#include <iostream>
#include "KMP.hpp"
#include "Sunday.hpp"

int main(int argc, char const *argv[])
{
    const std::string str(
"Naïve string search"
"A simple and inefficient way to see where one string occurs inside another is to check each place it could be, one by one, "
"to see if it's there. So first we see if there's a copy of the needle in the first character of the haystack; "
"if not, we look to see if there's a copy of the needle starting at the second character of the haystack; "
"if not, we look starting at the third character, and so forth. In the normal case, we only have to look at one or two characters "
"for each wrong position to see that it is a wrong position, so in the average case, this takes O(n + m) steps, "
"where n is the length of the haystack and m is the length of the needle; but in the worst case, "
"searching for a string like \"aaaab\" in a string like \"aaaaaaaaab\", it takes O(nm)"
"Finite-state-automaton-based search"
"In this approach, we avoid backtracking by constructing a deterministic finite automaton (DFA) that recognizes stored search string. "
"These are expensive to construct—they are usually created using the powerset construction—but are very quick to use. For example, "
"the DFA shown to the right recognizes the word \"MOMMY\". This approach is frequently generalized in practice "
"to search for arbitrary regular expressions."
"Stubs"
"Knuth–Morris–Pratt computes a DFA that recognizes inputs with the string to search for as a suffix, "
"Boyer–Moore starts searching from the end of the needle, so it can usually jump ahead a whole needle-length at each step. "
"Baeza–Yates keeps track of whether the previous j characters were a prefix of the search string, "
"and is therefore adaptable to fuzzy string searching. The bitap algorithm is an application of Baeza–Yates' approach."
"Index methods"
"Faster search algorithms preprocess the text. After building a substring index, for example a suffix tree or suffix array, "
"the occurrences of a pattern can be found quickly. As an example, a suffix tree can be built in Theta (n) time, "
"and all z occurrences of a pattern can be found in O(m) time under the assumption that the alphabet has a constant size and "
"all inner nodes in the suffix tree know what leaves are underneath them. The latter can be accomplished by running a DFS algorithm "
"from the root of the suffix tree."
"Other variants"
"Some search methods, for instance trigram search, are intended to find a \"closeness\" score between the search string and the text "
"rather than a \"match/non-match\". These are sometimes called \"fuzzy\" searches."
);
    const std::string sub1("variants");
    const std::string sub2("Theta");
    std::cout << "sunday_search" << std::endl;
    std::cout << sunday_search(str, sub1) << std::endl;
    std::cout << sunday_search(str, sub2) << std::endl;
    std::cout << "kmp_search" << std::endl;
    std::cout << kmp_search(str, sub1) << std::endl;
    std::cout << kmp_search(str, sub2) << std::endl;
    return 0;
}
