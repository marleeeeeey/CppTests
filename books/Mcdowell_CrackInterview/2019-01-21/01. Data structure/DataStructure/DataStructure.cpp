// DataStructure.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <map>

bool isAllSymbolsAreDifferent(std::string msg)
{
    std::sort(msg.begin(), msg.end());
    for (unsigned i = 1; i < msg.size(); i++)
    {
        if (msg[i - 1] == msg[i])
            return false;
    }
    return true;
}

bool isAllSymbolsAreDifferent2(const std::string & msg)
{
    std::vector<char> char_set(128);
    for (unsigned i = 0; i < msg.size(); i++)
    {
        if (char_set[msg[i]] == 1)
            return  false;
        else
            char_set[msg[i]] = 1;
    }
    return true;
}

void task_1_1()
{
    assert(isAllSymbolsAreDifferent("qwert") == true);
    assert(isAllSymbolsAreDifferent("") == true);
    assert(isAllSymbolsAreDifferent("qwtert") == false);
    assert(isAllSymbolsAreDifferent("    ") == false);    

    assert(isAllSymbolsAreDifferent2("qwert") == true);
    assert(isAllSymbolsAreDifferent2("") == true);
    assert(isAllSymbolsAreDifferent2("qwtert") == false);
    assert(isAllSymbolsAreDifferent2("    ") == false);
}

bool isPermutation(std::string s1, std::string s2)
{
    if (s1.size() != s2.size())
        return false;

    std::sort(s1.begin(), s1.end());
    std::sort(s2.begin(), s2.end());
    if (s1 == s2)
        return true;

    return false;
}

void task_1_2()
{
    assert(isPermutation("qwert", "qwert") == true);
    assert(isPermutation("qwert", "qwera") == false);
    assert(isPermutation("qwert", "trewq") == true);
    assert(isPermutation("qwert", "treqw") == true);
    assert(isPermutation("", "") == true);
    assert(isPermutation("123", "") == false);
    assert(isPermutation("123", " ") == false);
}

bool isPalindromPermutation(const std::string & str)
{
    std::map<char, int> charCount;
    for (auto ch : str)
    {
        charCount[ch] += 1;
    }
    bool isOddFound = false;
    for (const auto & p : charCount)
    {
        if(p.first == ' ')
            continue;

        if (p.second % 2 == 1)
        {
            if(isOddFound == false)
            {
                isOddFound = true;
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

void task_1_4()
{
    assert(isPalindromPermutation("qweqwea") == true);
    assert(isPalindromPermutation("qweasd") == false);
    assert(isPalindromPermutation("qw eq wea") == true);
    assert(isPalindromPermutation("q we asd  ") == false);
    assert(isPalindromPermutation("") == true);
}

bool isOneMOdification(const std::string & str1, const std::string & str2)
{
    const std::string & maxStr = str1.size() >= str2.size() ? str1 : str2;
    const std::string & minStr = str1.size() < str2.size() ? str1 : str2;

    int maxIndex = 0;
    int minIndex = 0;
    char minValue = minStr[minIndex];
    char maxValue = maxStr[maxIndex];

    for( ; ; )
    {
        bool hasInconsistent = false;

        if(minValue != maxValue)
        {
            if(hasInconsistent == true)
            {
                return false;
            }

            hasInconsistent = true;
            maxIndex++;
            if(maxIndex < maxStr.size())
            {
                maxValue = maxStr[maxIndex];
                continue;
            }
            else
            {
                return false;
            }

        } // if(*minValue != *maxValue)
        minIndex++;
        maxIndex++;

        if(minIndex >= minStr.size() || maxIndex >= maxStr.size())
            return hasInconsistent;

        minValue = minStr[minIndex];
        maxValue = maxStr[maxIndex];
    } // for
    return true;
}

void task_1_5()
{
    assert(isOneMOdification("pale", "ple") == true);
    assert(isOneMOdification("pales", "pale") == true);
    assert(isOneMOdification("pale", "bale") == true);
    assert(isOneMOdification("pale", "bake") == false);
}

int main()
{
    task_1_5();
}
