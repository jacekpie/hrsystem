#include <sstream>

#include "string_operations.h"

uint read_integer(
    const S& sLine,
    const uint inx)
{
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
