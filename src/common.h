#ifndef _CALC_COMMON_H_
#define _CALC_COMMON_H_


#include "argparse.hpp"

#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <assert.h>
#include <dlfcn.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ASSERT(X) assert(X)

// I need to take a look at this to confirm validity.
// #ifdef _WIN32
// #include <windows.h>
// #ifdef _DEBUG
// #define _CRTDBG_MAP_ALLOC
// #include <crtdbg.h>
// #include <stdlib.h>
// #endif
// #else
// #include <filesystem>
// #endif

#undef __STRICT_ANSI__

#ifdef __GNUC__
#define vsprintf_s vsnprintf
#define sprintf_s snprintf
#define _strdup strdup
#define _snprintf std::snprintf
#endif

#endif