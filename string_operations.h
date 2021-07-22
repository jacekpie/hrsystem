#include <string>

#ifndef STRING_OP
#define STRING_OP

// Syntactic sugar type declarations
typedef std::string S;
typedef unsigned int uint;

uint read_integer(const S& sLine_, const uint inx);
S read_string(const S& sLine_, const uint inx);
std::size_t find_equal_sign(const S& sLine_);
std::size_t find_comma(const S& sLine_);
bool is_line_starting(const S& sLine, const S& sStart);

#endif  // STRING_OP

