#include "solution.hpp"

unsigned int StrLen(const char* c_str) {
    int count = 0;
    int i = 0;
    while(c_str[i] != '\0') {
        count += 1;
        i++;
    }
    return count;
}

void StrCpy(char*& to, const char* from) {
    if (from == nullptr) {
        return;
    } 
    char* copy = new char[StrLen(from) + 1];
    for (unsigned int i = 0; i < StrLen(from) + 1; i++) {
        copy[i] = from[i];
    }
    delete[] to;
    to = copy;
}
