//====================================================================================
// @Title:      STRING
//------------------------------------------------------------------------------------
// @Location:   /prolix/common/include/xString.h
// @Author:     Kevin Chen
// @Rights:     Copyright(c) 2011 Visionary Games
//------------------------------------------------------------------------------------
// @Description:
//
//  Simple string tools to manipulate string data types and enhance aesthetic for 
//  logging inFormation, conversion from numerical types, and the RPG component of
//  the project.
//
//====================================================================================
#ifndef __PROLIX_BASE_COMMON_STRING_H__
#define __PROLIX_BASE_COMMON_STRING_H__

#include <string>
#include <sstream>

//====================================================================================
//                                                                              String
//====================================================================================
class String : public std::string
{
    friend extern std::ostream &operator<<(std::ostream &os, String str);
    friend extern String operator+(String str1, String str2);
    friend extern String operator+(std::string str1, String str2);
    friend extern String operator+(String str1, std::string str2);
    friend extern bool operator==(String str1, String str2);
    friend extern bool operator!=(String str1, String str2);

    bool IsWhitespace(char c);

    std::string mSource;
  public:
    String UpperCase();    // converts String to all uppercase characters
    String LowerCase();    // converts String to all lowercase characters
    String Capitalize();   // capitalizes the first word
    String CamelCase();    // capitalizes every word
    float ToNumber();      // converts the String equivalent to a number (float)
    
    unsigned int length();  // returns length of the String
    std::string Source();   // returns source of the native C++ string
    
    void SetSource(std::string str);  // sets a string value to mSource

    // replaces a substring of a String
    String replace(String query, String replacement);
    String replace(std::string query, std::string replacement);

    // removes a substring from String
    String remove(String query);
    String remove(std::string query);

    // trims off leading and trailing whitespace    
    String trim();

    // removes any consective instances of whitespace + trims
    String format();

    // returns a String index if query exists in String else -1
    int find(String query);
    int find(std::string query);

    // returns true if query exists in string; else false
    bool exists(String query);
    bool exists(std::string query);

    // Constructors
    String();
    String(std::string str);
    String operator=(std::string str);
    String operator=(char *str);
};

//====================================================================================
//                                                                            External
//====================================================================================
// operations
extern std::ostream &operator<<(std::ostream &os, String str);
extern String operator+(String str1, String str2);
extern String operator+(std::string str1, String str2);
extern String operator+(String str1, std::string str2);
extern bool operator==(String str1, String str2);
extern bool operator!=(String str1, String str2);

// converts a char array to string
std::string toString(char *char_array);

// trim outlying whitespace characters
std::string Trim(std::string str);

// converts a number to type string
template <typename T> std::string toString(T n) 
{
    std::stringstream s;
    s << n;
    return s.str();
}

float ToNumber(std::string s);

#endif