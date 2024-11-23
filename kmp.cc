#include <cassert>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

class KMPPatternMatching {
    string text;
    string pattern;
    vector<int> buildFailureArray();
    public:
        KMPPatternMatching(const string &text, const string &pattern): text(text), pattern(pattern){}
        // findFirst returns the index of the first occurence of [pattern] in [text]
        int findFirst();
};

int KMPPatternMatching::findFirst() 
{
    int i = 0; // text
    int j = 0; // pattern
    vector<int> failureArray = buildFailureArray();

    while (i < text.size())
    {
        if (text[i] == pattern[j])
        {
            i += 1;
            j += 1;
            if (j == pattern.size()) {return i - j;}
        }
        else 
        {
            if (j > 0)
            {
                j = failureArray[j-1]; 
            } 
            else {
                i += 1;
            }
        }
    }

    return -1;
};


vector<int> KMPPatternMatching::buildFailureArray()
{
    vector<int> failureArray(pattern.size());
    failureArray[0] = 0;
    int i = 1; 
    int j = 0;

    while (i < pattern.size())
    {
        if (pattern[i] == pattern[j])
        {
            failureArray[i] = j + 1;
            i += 1;
            j += 1; 
        }
        else if (j == 0)
        {
            failureArray[i] = 0;
            i += 1;
        }
        else // j != 0
        {
            j = failureArray[j-1];
        }
    }

    return failureArray;
} 


int main() 
{
    auto pm = KMPPatternMatching("abaxyabacabbaababacaba", "abacaba");
    int n = pm.findFirst();
    assert(n == 15);
    return 0;
}

