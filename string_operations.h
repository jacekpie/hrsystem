/*
 * This file contains definition of auxiliary functions which handle string operations.
 */

#include <string>
#include <vector>

#ifndef STRING_OP
#define STRING_OP

// Syntactic sugar type declarations
typedef std::string S;
typedef unsigned int uint;

uint read_integer(const S& sLine_, const uint inx);
S read_string(const S& sLine_, const uint inx);
std::vector<S> read_comma_separated(const S&  sLine, const uint  inx);


std::size_t find_equal_sign(const S& sLine_);
std::size_t find_comma(const S& sLine_);
std::size_t find_question_mark(const S& sLine);
bool is_line_starting(const S& sLine, const S& sStart);
int find_word_among_arguments(const S& sWord, const int argc, char* argv[], const int inxStart);

bool is_string_a_number(const S& sLine);

S connect_arguments(const int argc, char* argv[], const int inxStart);
S connect_arguments_until(const int argc, char* argv[], const int inxStart, const S& sUntil);
#endif  // STRING_OP

