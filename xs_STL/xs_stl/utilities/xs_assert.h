#pragma once
#include <iostream>

#ifdef NDEBUG
#define xsassert(condition, message) 0
#else
#define xsassert(condition, message)\
   (!(condition)) ?\
      (std::cerr << "Assertion failed: (" << #condition << ") \n"\
      << "FUNCTION: " << __FUNCTION__ << "\n"\
      << "FILE: " << __FILE__<< "\n"\
      << "LINE: " << __LINE__ << "\n"\
      << "REASON: " << message << std::endl, abort(), 0) : 1
#endif