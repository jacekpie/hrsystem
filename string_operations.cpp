#include <sstream>

#include "string_operations.h"

uint read_integer(
    const S& sLine_,
    const uint inx)
{
    if(inx < 0)
    {
        return 0;
    }

    // Read characters which are numbers
    std::ostringstream ossInt;
    for(const char c: sLine_.substr(inx))
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
    const S& sLine_,
    const uint inx)
{
    if(inx < 0)
    {
        return "";
    }

    // Read characters which are letters
    std::ostringstream ossS;
    for(const char c: sLine_.substr(inx))
    {
        if(!isalpha(c))
        {
            break;
        }
        ossS << c;
    }

    return ossS.str();
}



std::size_t find_equal_sign(const S& sLine_)
{
    return sLine_.find('=');
}

std::size_t find_comma(const S& sLine_)
{
    return sLine_.find(',');
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
