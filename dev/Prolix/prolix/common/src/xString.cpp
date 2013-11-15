//====================================================================================
// @Title:      STRING
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/xString.cpp
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//====================================================================================
#include "../include/xString.h"
#include <cctype>
#include <sstream>
#include <iostream>

//====================================================================================
//                                                                              String
//====================================================================================
String::String()
{
}

String::String(std::string str)
{
    mSource = str;
}

String String::operator=(char *str)
{
    mSource = std::string(str);
    return String(mSource);
}

String String::operator=(std::string str)
{
    mSource = str;
    return String(mSource);
}

bool String::IsWhitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

void String::SetSource(std::string str)
{
    mSource = str;
}

String String::UpperCase()
{
    std::string s = "";
	for (unsigned int i = 0 ; i < mSource.length() ; i++)
    {
		s += toupper(mSource[i]);
    }
	return String(s);
}

String String::LowerCase()
{
    std::string s = "";
	for (unsigned int i = 0 ; i < mSource.length() ; i++)
    {
		s += tolower(mSource[i]);
    }
	return String(s);
}

String String::Capitalize()
{
    std::string s = "";
	for (unsigned int i = 0 ; i < mSource.length() ; i++)
    {
		(i == 0)
            ? s += toupper(mSource[i]) 
            : s += tolower(mSource[i]); 
    }
	return String(s);
}

String String::CamelCase()
{
    std::string s = "";
    
    // format string properly before processing
    trim();
    
    for (unsigned int i=0; i<mSource.length(); i++)
    {
        // short circuit 'or' operator so that it doesn't
        // evaluate the second term (which would cause a
        // subscript error)
        if ((i == 0) || (mSource[i - 1] == ' '))
        {
            s += toupper(mSource[i]);
            continue;
        }

        s += tolower(mSource[i]);
    }
    return String(s);
}

std::string String::Source()
{
    return mSource;
}

unsigned int String::length()
{
    return mSource.length();
}

String String::replace(std::string query, std::string replacement)
{
    return replace(String(query), String(replacement));
}

String String::replace(String query, String replacement)
{
    std::string s = mSource.replace(mSource.find(query.mSource), query.length(), replacement.mSource);
    return String(s);
}

String String::remove(String query)
{
    return replace(query, String(""));
}

String String::remove(std::string query)
{
    return remove(String(query));
}

String String::trim()
{
    return String(Trim(mSource));
}

String String::format()
{
    mSource = Trim(mSource);
    std::string s = "";

    for (unsigned int i=0; i<mSource.length(); i++)
    {
        s += mSource[i];
        if (IsWhitespace(mSource[i]))
        {
            unsigned int j; 
            for (j=i; j<mSource.length(); j++)
            {
                if (!IsWhitespace(mSource[j]))
                {
                    break;
                }
            }
            i = j-1;
            continue;
        }
    }

    return String(s);
}

int String::find(std::string query)
{
    return find(String(query));
}

int String::find(String query)
{
    return mSource.find(query.mSource);
}

bool String::exists(std::string query)
{
    return (find(query) != -1);
}

bool String::exists(String query)
{
    return (find(query) != -1);
}

float String::ToNumber()
{
    return (float)atof(mSource.c_str());
}

//====================================================================================
//                                                                            External
//====================================================================================
std::string toString(char *char_array) 
{
	return std::string(char_array);
}

std::ostream &operator<<(std::ostream &os, String str)
{
    return os << str.mSource;
}

String operator+(String str1, String str2)
{
    return String(str1.mSource + str2.mSource);
}

String operator+(std::string str1, String str2)
{
    return String(str1 + str2.mSource);
}

String operator+(String str1, std::string str2)
{
    return String(str1.mSource + str2);
}

bool operator==(String str1, String str2)
{
    return str1.mSource == str2.mSource;
}

bool operator!=(String str1, String str2)
{
    return !(str1 == str2);
}

std::string Trim(std::string str)
{
    if (str.length() == 1) return String("");

    int start, end;
    start = end = 0;

    for (unsigned int i=0; i<str.length(); i++)
    {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            start = i;
            break;
        }
    }

    for (int j=str.length() - 1; j >= 0; j--)
    {
        if (str[j] != ' ' && str[j] != '\t' && str[j] != '\n')
        {
            end = j;
            break;
        }
    }
 
    std::string s = str.substr(start, end - start + 1);
    if (s == " ") s = "";

    return s;
}

float ToNumber(std::string s)
{
	return (float)atof(s.c_str());
}