#include "exception.h"

std::string Exception::Str() {
    return StrFmt("Error: %s at position %d. %s. (%s:%d)", 
            this->err_type, this->location, this->err_msg, this->c_file, this->c_line);
}