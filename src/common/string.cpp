
#include <common/string.h>

using namespace kiteos::common;

string::string(char *str)
{
    this->value = str;
}

string::~string()
{

}

void string::deleteLast()
{
    value[length() - 1] = '\0';
}


int32_t string::length()
{
    int32_t tmp;
    while (value[tmp] != '\0')
        tmp ++;
    return tmp;
}

char *string::c_str()
{
    return value;
}

string string::operator =(char *str)
{
    value = str;
    return *this;
}

bool string::operator ==(string x)
{
    bool isEq = false;
    int32_t len1 = length();
    int32_t len2 = x.length();
    if (len1 == len2)
    {
        for (int i = 0; i < len1; i++)
            isEq = c_str()[i] == x.c_str()[i];
    }

    return isEq;
}

string string::operator +=(char *str)
{
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++, j += length() + i)
    {

        value[j] = str[i];
    }

    value[j] = '\0';
    
    return *this;
}

