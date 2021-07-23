/*
 * This file contains implementation of auxiliary functions which handle string operations.
 */

#include <sstream>

// Local include
#include "string_operations.h"

uint read_integer(
    const S& sLine,
    const uint inx)
{
//
//  Read interger from string starting from a given index.
//  Return 0 uf no integers found.
//
    if(inx < 0)
    {
        return 0;
    }

    // Read characters which are numbers
    std::ostringstream ossInt;
    for(const char c: sLine.substr(inx))
    {
        if(!isdigit(c))
        {
            break;
        }
        ossInt << c;
    }

    // Change read stream to a string
    const S sNumber = ossInt.str();

    // If string is empty, return 0
    if(sNumber.size() == 0)
    {
        return 0;
    }

    //
    const uint intgr = std::stoi(sNumber);
    return intgr;
}

S read_string(
    const S& sLine,
    const uint inx)
{
//
//  Read substring from a given string starting from a given index.
//  The substring may contin only - letters, digits and space.
//

    if(inx < 0)
    {
        return "";
    }

    // Read characters which are letters, or digits, or space
    std::ostringstream outS;
    for(const char c: sLine.substr(inx))
    {
        if(c == ' ' || isalpha(c) || isdigit(c))
        {
            outS << c;
        }
        else
        {
            break;
        }
    }

    return outS.str();
}

std::vector<S> read_comma_separated(const S&  sLine, const uint inx)
{
//
//  Read comma separated substring from aa given string, starting at a given idnex.
//
    std::vector<S> vOut;
    if(inx < 0)
    {
        return vOut;
    }

    std::ostringstream outS;
    for(const char c: sLine.substr(inx))
    {
        if(c == ',')
        {
            vOut.push_back(outS.str());
            outS.clear();
            outS.str("");
        }
        else
        {
            outS << c;
        }
    }

    return vOut;
}



std::size_t find_equal_sign(const S& sLine)
{
    return sLine.find('=');
}

std::size_t find_comma(const S& sLine)
{
    return sLine.find(',');
}

std::size_t find_question_mark(const S& sLine)
{
    return sLine.find('?');
}


bool is_line_starting(const S& sLine, const S& sStart)
{
//
//  Check if a given string line starts with a given start string.
//

    const int iLen = sLine.size();
    const int iLenStart = sStart.size();
    if(iLen < iLenStart)
    {
        return false;
    }

    const S sLineStart = sLine.substr(0, iLenStart);
    return sLineStart == sStart;
}

int find_word_among_arguments(const S& sWord, const int argc, char* argv[], const int inxStart)
{
//
//  Check if a given word is among user arguments, starting from a argument with a given index.
//

    for(int inx = inxStart; inx < argc; inx++)
    {
        if(argv[inx] == sWord)
        {
            return inx;
        }
    }

    return -1;
}

bool is_string_a_number(const S& sLine)
{
//
//  Check if a given string contains only numbers.
//

    if(sLine.size() == 0)
    {
        return false;
    }

    for(const char c: sLine)
    {
        if(!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

S connect_arguments(const int argc, char* argv[], const int inxStart)
{
//
//  Connect arguments given by user starting with argument with a given index.
//  Space is added between arguments.
//  e.g.:
//        ./hrsystem  Joe Doe    start: 1  ---->   "Joe Doe"
//

    std::ostringstream outS;
    for(int inx = inxStart; inx < argc; inx++)
    {
        outS << argv[inx];
        if(inx < (argc -1))
        {
            outS << " ";
        }
    }
    return outS.str();
}

S connect_arguments_until(const int argc, char* argv[], const int inxStart, const S& sUntil)
{
//
//  Connect arguments given by user starting with argument with a given index, unntil a certain argument
//  is found.
//
//  Space is added between arguments.
//  e.g.:
//        ./hrsystem apply  Joe Doe  for F22 Pilot   start: 2, end 'for'  ---->   "Joe Doe"

    std::ostringstream outS;
    for(int inx = inxStart; inx < argc; inx++)
    {
        if(argv[inx] == sUntil)
        {
            break;
        }

        outS << argv[inx];
        if(argv[inx+1] != sUntil)
        {
            outS << " ";
        }
    }
    return outS.str();
}
