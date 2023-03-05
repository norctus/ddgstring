#ifndef DDGSTRING_
#define DDGSTRING_
#include <iostream>
#include <string.h>

#define marime_vector 6
#define marime_str 7
#define sus_size 16
#define defsus 4
#define verbtor_size 14

namespace ddg {

    struct string
    {
        string();

        string(const char* str);

        string(const string& other);

        void operator=(const string& str);

        string operator+(const char* str);

        string operator+(const string& str);

        string operator-(const char cifra);

        string operator-(const char* sir);

        bool operator==(const string& str);

        bool operator!=(const string& str);

        char& operator[](int index);

        const char& operator[](int index) const;

        bool isDelim(char ch);

        unsigned int size();

        void space_sort();

        string substr(unsigned int pos, unsigned int count = -1) const;

        unsigned int find(char ch, unsigned int i = 0);

        unsigned int find(const string& str, unsigned int i = 0);

        void erase(unsigned int poz);

        void erase(unsigned int first, unsigned int last);

        ~string();

        char* data;
        static char delim[marime_vector];
        unsigned int m_size;
    };

    void concat(string& dest, string& src);

    int crat(string& str);

    void cratime(string& str);

    std::ostream& operator<<(std::ostream& os, const string& var);
}

#endif