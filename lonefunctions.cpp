#include "lonefunctions.h"

int LoneFunctions::findCh(char ch,std::string s)
{
    for(int i = 0; i <= s.size();i++)
    {
        if(s[i] == ch)
        {
            return i;
        }
    }
    return -1;
}

