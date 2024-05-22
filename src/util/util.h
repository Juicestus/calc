#ifndef __JUSTUS_UTIL_H__
#define __JUSTUS_UTIL_H__

#define DO_SRC_LOGGING

#ifdef DO_SRC_LOGGING
    #define LOG(I) std::cout << "(" << __FILE__ << ":" << __LINE__ << ") \t" << __FUNCTION__ << " " << I << std::endl;
#else
    #define LOG(I) ;
#endif


#include "common.h"

// The following Is{} functions are commonly used
// functions to check if the content of a strings
// or character satisfies a given condition.
bool IsWhitespace(const char);
bool IsNumeric(const char);
bool IsNumber(const std::string&);
bool IsHexadecimal(const char);
bool IsAlpha(const char);
bool IsIdentString(const char*);

// A function to extend the functionality of the Java
// Map interface's getOrDefault method to the C++ map.
// template<typename K, typename V>
template<typename K, typename V>
V MapGetOrDefault(const std::map<K, V> map, const K key, const V default_val) {
    auto it = map.find(key);
    return it == map.end() ? default_val : it->second;
}

// Bellow is a macro implementaiton of the same thing.
// It is unused because macros are evil.
// #define MapGetOrDefault(map, key, default_val) (map.find(key) == map.end() ? default_val : map.find(key)->second)

// A constant expression function that converts std::string
// types to char* C strings in variatic argument lists. The
// function works by evaulating if a given type is of the
// std::string type. If so, it returns the result of .c_str(),
// otherwise, it just returns the param. This is designed to
// be used in variatic argument comprehention. 
template<typename T>
auto _convert(T&& t) {
    if constexpr (std::is_same<std::remove_cv_t<std::remove_reference_t<T>>, std::string>::value)
        return std::forward<T>(t).c_str();
    else 
        return std::forward<T>(t);
}

// Internal function to perform a C snprintf style format 
// string. The problem with this function, the reason it's
// the internal function, is that it cannot take std::string
// types as arguments, only char* C strings. Wrapping this
// function solves this problem.
template<typename... A>
std::string _strfmt(const std::string& fmt, A&&... args) {
    const auto size = _snprintf(nullptr, 0, fmt.c_str(), std::forward<A>(args)...) + 1;
    if (size <= 0) return "<StrFmt error>";
    std::unique_ptr<char[]> buf(new char[size]);
    _snprintf(buf.get(), size, fmt.c_str(), args...);
    return std::string(buf.get(), buf.get() + size - 1);
}

// Formats a string the same way C snprintf does it,
// returning the formatted string. This method can take
// std::string objects as arguments (for the %s format).
template<typename... A>
std::string StrFmt(const std::string& fmt, A&&... args) {
    return _strfmt(fmt, _convert(std::forward<A>(args))...);
}

// Prints a string the same way C printf does it, however
// this method is modernized for C++, and can use std::string
// objects as arguments (for the %s format).
template<typename... A>
void PrintFmt(const std::string& fmt, A&&... args) {
    std::cout << _strfmt(fmt, _convert(std::forward<A>(args))...);
}

// The same as PrintFmt but has a newline appended to the end.
template<typename... A>
void PrintLnFmt(const std::string& fmt, A&&... args) {
    std::cout << _strfmt(fmt + "\n", _convert(std::forward<A>(args))...);
}

// Handle errors.
template<typename... A>
void ErrFmt(const std::string& fmt, A&&... args) {
    std::cerr << _strfmt(fmt + "\n", _convert(std::forward<A>(args))...);
    exit(1);
}

// Returns true if element x is present inside of the vector v.
template<typename T>
bool VectorContains(const std::vector<T> v, const T x) {
    return std::find(v.begin(), v.end(), x) != v.end();
}

// Returns the index of element x if it is present inside of the
// vector v, otherwise returns -1.
template<typename T>
long VectorIndexOf(const std::vector<T> v, const T x) {
    ptrdiff_t pos = find(v.begin(), v.end(), x) - v.begin();
    if (pos >= v.size()) return -1;
    return pos;
}

// Returns a YYYY-MM-DD format date for the current day.
std::string CurrentDateStr(void);

// Reads and returns an entire file located at a path.
std::string LoadStrFromFileAtPath(const std::filesystem::path);

// Writes an entire string to a file located at a path.
void DumpStrToFileAtPath(const std::filesystem::path, const std::string&);

#endif
