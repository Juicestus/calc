#ifndef _CALC_EXCEPTION_H_
#define _CALC_EXCEPTION_H_

#include "common.h"
#include "util/util.h"

class Exception {
private:

    std::string err_type, err_msg;
    int location;

    std::string c_file;
    int c_line;

public:
    Exception(std::string err_type, std::string err_msg, int location, std::string c_file, int c_line) 
        : err_type(err_type), err_msg(err_msg), location(location), c_file(c_file), c_line(c_line) {}

    std::string Str();
};

#endif