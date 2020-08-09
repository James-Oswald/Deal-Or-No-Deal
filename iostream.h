//This program was originally meant to be run on VS 97, all of the libraries assumed that was the IDE, this file corrects for that.

#ifndef IO_GLUE
#define IO_GLUE
#define _MSC_VER 1200 //the og MSC version, hopefully this works
#include<iostream>
#include<istream>
#include<ostream>
using std::ostream;
using std::istream;
using std::cout;
using std::cerr;
using std::endl;
#endif