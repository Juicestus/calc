#include "util/util.h"


bool IsWhitespace(const char ch) {
    return (ch == ' ') || (ch == '\t') || (ch == '\n') || (ch == '\r');
}

bool IsNumeric(const char ch) {
    return (ch >= '0') && (ch <= '9');
}

bool IsNumber(const std::string& str) {
    for (int i = 0; i < str.size(); i++)
        if (!IsNumeric(str[i])) return false;
    return true;
}

bool IsHexadecimal(const char ch) {
    return ((ch >= '0') && (ch <= '9')) || ((ch >= 'a') && (ch <= 'f')) ||
           ((ch >= 'A') && (ch <= 'F'));
}

bool IsAlpha(const char ch) {
    return ((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')) ||
           ch == '_';
}

bool IsIdentString(const char* s) {
    if (!IsAlpha(*s)) return false;

    while (*s) {
        if (!(IsAlpha(*s) || IsNumeric(*s))) return false;
        s++;
    }

    return true;
}

std::string CurrentDateStr(void) {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    return buf;
}

std::string LoadStrFromFileAtPath(const std::filesystem::path input_path) {
    std::ifstream input_file(input_path);
    if (!input_file.is_open()) return std::string();
    return std::string(std::istreambuf_iterator<char>(input_file),
                       std::istreambuf_iterator<char>());

    // std::string str;
    // if (!input_file.is_open()) return str;
    // input_file >> str;
    // return str;
}

void DumpStrToFileAtPath(const std::filesystem::path output_path, const std::string& str) {
    std::ofstream output_file(output_path);
    output_file << str;
}