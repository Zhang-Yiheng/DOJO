/*
Knuth-Morris-Pratt 算法
设模式串失配字符的下标为 n，若存在 pattern[0]~pattern[k-1] == pattern[n-k-2]~pattern[n-1]
则主串的失配字符可以从模式串 pattern.at(k) 开始匹配，因为 pattern[n-k-2]~pattern[n-1] 已经与主串匹配过了，所以可以跳过相同值的 pattern[0]~pattern[k-1]
KMP 算法的关键是构建一个跳转表 next，该表储存了每个模式串字符在失配后，与主串失配字符配对的模式串字符的下标，即 k，等于 pattern.at(n) 之前首尾重复字段的长度
当 pattern[0] 失配时，需要主串下一个字符与 pattern[0] 配对。设 next[0] = -1 并设置条件检查，使得主串与模式串下标可以同时+1

算法复杂度为 O(m+n)，该算法的优势依赖于拥有非连续重复字段的模式串，若模式串无重复或连续重复，则其效率有时比暴力查找都要差，故不实用
*/
#pragma once
#ifndef KMP_HPP
#define KMP_HPP
#include <string>
#include <vector>

int kmp_search(const std::string& str, const std::string& pattern)
{
    int k = -1, n = 0, sl = str.length(), pl = pattern.length();
    std::vector<int> next(pl);
    next[0] = -1;
    while (n < pl-1)       // 可以视作模式串的子串 pattern[0~k] 匹配整个模式串的过程
    {
        if (k == -1 or pattern.at(n) == pattern.at(k))
        {
            ++k, ++n;
            if (pattern.at(n) == pattern.at(k))
                next.at(n) = next.at(k); // 若模式串后缀字符与主串失配，则用前缀段替代后缀段时都在同一处失配，故其跳转下标相同
            else
                next.at(n) = k;         // pattern.at(k) 与 pattern.at(n) 失配，意味着 pattern[0 ~ k-1] 已和 pattern[n-k-2 ~ n-1] 匹配
        }
        else
            k = next.at(k);    // 从子串失配时的下标得到子串下一个配对字符的下标
    }
    
    n = 0, k = 0;
    while (n < sl and k < pl)
    {
        if (k == -1 or str.at(n) == pattern.at(k))
            ++n, ++k;
        else
            k = next.at(k);    // 从模式串失配时的下标得到下一个模式串配对字符的下标
    }

    if (k == pl)            // 匹配完毕
        return n - pl;      // 主串第一个匹配的子串的下标
    else
        return -1;          // 无匹配
}
#endif