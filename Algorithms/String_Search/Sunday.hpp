/*
主串：  SUBSTRING SEARCH
失配：   |    | I 不存在于模式串，故将模式串右移 pattern.length + 1 位后配对
模式串：SEARCH
主串：  SUBSTRING SEARCH
失配：         |     |最近的 R 存在于模式串倒数第 3 位，故将模式串右移 3 位后配对
模式串：       SEARCH
主串：  SUBSTRING SEARCH
模式串：          SEARCH
*/
#pragma once
#ifndef SUNDAY_HPP
#define SUNDAY_HPP
#include <string>
#include <vector>

int sunday_search(const std::string& str, const std::string& pattern)
{
    const int pl = pattern.length();
    std::vector<int> step(256);
    for (int i = 1; i <= pl; i++)
    {
        if (step[pattern[pl-i]]==0)
            step[pattern[pl-i]] = i;
    }

    auto sp = str.begin(), pp = pattern.begin();
    int i = 0;
    while (i < pl)
    {
        if (str.end()-sp < pl)
            return -1;
        if (*(sp+i) != *(pp+i)) // 存在失配字符
        {
            auto jump = step[*(sp+pl)];
            if (jump)           // 主串配对段的后一位字符存在于模式串
                sp+=jump;       // 配对段右移
            else                // 主串配对段的后一位字符不存在于模式串
                sp = sp+pl+1;   // 配对段跳过模式串长度+1
            pp = pattern.begin();
            i = 0; continue;
        }
        ++i;
    }
    
    return sp-str.begin();
}
#endif