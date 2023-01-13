#include <iostream>
#include "ddgstring.h"
#include <string.h>

#define marime_vector 6
#define marime_str 7
#define sus_size 12
#define verbtor_size 1

namespace ddg
{
    char string::delim[marime_vector] = { ' ', '.', ',', '\0', '?', '!' };
    string cuvsus[sus_size] = { "tiam", "miai","sami","neam","sati","nui","neati","iam", "sa","ia","uitel","nam" };
    string verbtor[verbtor_size] = { "cunoscut" };

    char* data;
    static char delim[marime_vector];
    unsigned int m_size;

    string::string()
    {
        data = NULL;    //Stringul null
        m_size = 0;
    }

    string::string(const char* str)
    {
        data = (char*)malloc(sizeof(char) * strlen(str) + 1);
        strcpy_s(data,sizeof(char)*strlen(str)+1, str);
        m_size = strlen(str);
        data[m_size] = '\0';
    }

    string::string(const string& other)
    {
        data = (char*)malloc(sizeof(char) * other.m_size + 1);
        strcpy_s(data,sizeof(char) * other.m_size + 1, other.data);
        m_size = other.m_size;
    }

    void string::operator=(const string& str)
    {
        if (data != NULL)
            free(data);
        data = (char*)malloc(sizeof(char) * str.m_size + 1);    //operatorul egal
        strcpy_s(data, sizeof(char) * str.m_size +1 , str.data);
        m_size = str.m_size;
    }

    string string::operator+(const char* str)
    {
        char* ret = (char*)malloc(sizeof(char) * m_size + strlen(str) + 1);     //operatorul plus intre un string si un sir de caractere
        strcpy_s(ret, sizeof(char) * m_size + strlen(str) + 1, data);
        strcat_s(ret, sizeof(char) * m_size + strlen(str) + 1, str);
        m_size = m_size + strlen(str);
        return ret;
    }

    string string::operator+(const string& str)
    {
        string ret;
        ret.data = (char*)malloc(sizeof(char) * (m_size + str.m_size) + 2);   //operatorul plus intre 2 stringuri
        ret[0] = '\0';
        strcat_s(ret.data, sizeof(char) * m_size  , data);
        strcat_s(ret.data,1, " ");
        strcat_s(ret.data, sizeof(char)* str.m_size +1, str.data);
        return ret;
    }

    string string::operator-(const char cifra)
    {
        int r = 0;                                      //operatorul minus intre un ddg::string si un char
        int j = 0;
        for (int i = 0; i < strlen(data); ++i) {
            if (data[i] == cifra)
                r++;
        }
        char* ret = (char*)malloc(sizeof(char) * (strlen(data) - r) + 1);
        for (int i = 0; i < strlen(data); ++i)
        {
            if (data[i] != cifra)
            {
                ret[j] = data[i];
                j++;
            }
            else if (i > 0 && i < strlen(data) - 1 && data[i - 1] == ' ' && data[i + 1] == ' ')
            {
                i++;
            }
        }
        ret[j] = '\0';
        return ret;
    }

    unsigned int string::size() { return m_size; }

    string string::operator-(const char* sir)
    {
        int count = 0;
        int index = 0;
        for (int i = 0; i < m_size; ++i)
        {
            int gasit = 1;
            for (int j = 0; j < strlen(sir); ++j)
            {
                if (data[i + j] != sir[j])           //face scaderea intre un string si un sir de caractere
                {
                    gasit = 0;
                    break;
                }
            }
            if (gasit)
            {
                index++;
            }
        }
        char* ret = (char*)malloc(sizeof(char) * (strlen(data) - strlen(sir) * index) + 1);
        for (int i = 0; i < m_size; ++i)
        {
            int rep = 1;
            for (int j = 0; j < strlen(sir); ++j)
            {
                if (data[i + j] != sir[j])
                {
                    rep = 0;
                    break;
                }
            }
            if (rep)
            {
                if (isDelim(data[i + strlen(sir)]) && isDelim(data[i - 1]))
                {
                    rep = 1;
                }
                else
                    rep = 0;
                if (!i)     // BIG BRAIN MOVE!!!!!!!!!! P.S.: Scoate cuvantul chiar daca e primul, nu facea asta pana acum
                    rep = 1;
            }
            if (rep)
            {
                i = i + strlen(sir);
            }
            else
            {
                ret[count] = data[i];
                count++;
            }
        }
        ret[count] = '\0';
        return ret;
    }

    bool string::operator==(const string& str)
    {
        bool egal = true;
        for (int i = 0; i < str.m_size; ++i)         //operatorul egal egal
        {
            if (data[i] != str[i])
                egal = false;
        }
        return egal;
    }

    bool string::operator!=(const string& str)
    {
        bool egal = true;
        for (int i = 0; i < str.m_size; ++i)         //operatorul non egal
        {
            if (data[i] != str[i])
                egal = false;
        }
        return !egal;
    }

    char& string::operator[](int index)
    {
        return data[index];                 //operatorul [] ca sa pot sa fac vectori de stringuri
    }

    const char& string::operator[](int index) const
    {
        return data[index];                     //acelasi operatori dar pentru constante
    }

    bool string::isDelim(char ch)
    {
        for (int i = 0; i < marime_vector; ++i)      // o functie care verifica daca caracterul respectiv este o delimitare(micunealta ce ne va ajuta mai tarziu sau mai devreme)
            if (ch == delim[i])
                return true;
        return false;
    }

    unsigned int size() { return m_size; }           //efectiv size

    void string::space_sort()
    {
        int poz = 0;
        int index = 0;
        int spatii = 0;
        for (int i = 0; i < m_size; ++i)
        {
            if (i != 0)
                index = 1;
            if (data[i] == delim[0])
            {                                       //functie sper ca originala care sterge toate spatiile in plus dintre subsiruri
                poz = i;
            }
            while (data[poz + index] == delim[0])
            {
                for (int j = poz; j < m_size - 1; ++j)
                {
                    data[j] = data[j + 1];
                }
                spatii++;
            }
            data[m_size - spatii] = '\0';
        }
    }

    string string::substr(unsigned int pos, unsigned int count ) const
    {
        string tmp;
        int j = 0;
        if (count > m_size - pos)
        {
            tmp.data = (char*)malloc(sizeof(char) * (m_size - pos) + 1);
            for (int i = pos; i < m_size; ++i)
            {
                tmp.data[j] = data[i];                                  //extrage un substring
                j++;
            }
            tmp.data[j] = '\0';
        }
        else
        {
            tmp.data = (char*)malloc(sizeof(char) * count + 1);
            for (int i = pos; i < count + pos; ++i)
            {
                tmp.data[j] = data[i];
                j++;
            }
            tmp.data[j] = '\0';
        }
        return tmp;
    }

    unsigned int string::find(char ch, unsigned int i )
    {
        for (i; i < m_size; ++i)               //gaseste pozitia unui char pe care dorim sa-l cautam si returneaza indexul
        {
            if (data[i] == ch)
                return i;
        }
        return m_size;
    }

    unsigned int string::find(const string& str, unsigned int i)
    {
        int index;
        int gasit;
        for (int i = 0; i < m_size; ++i)                         // la fel dar pentru stringuri
        {
            gasit = 1;
            index = i;
            for (int j = 0; j < str.m_size; ++j)
            {
                if (data[index] != str.data[j])
                    gasit = 0;
                index++;
            }
            if (gasit == 1 && (data[index] == ' ' || data[index] == '\0'))
                return i;
        }
        return m_size;
    }

    /*unsigned int string::myFind(const string& str, unsigned int pos)
    {
        if (m_size < str.m_size)
            return m_size;

        for (uint32_t i = 0; i < m_size - str.m_size + 1; ++i)
        {
            bool found = true;
            for (uint32_t j = 0; j < str.m_size; ++j)
            {
                if (data[i] != data[j])
                    found = false;
            }
            if (found)
                return i;
        }
        return m_size;
    }

    void myCratime(string& str)
    {

        string v[3] = { "tiam", "uitel", "miai" };
        string v_corect[3] = { "ti-am", "uite-l", "mi-ai" };

        uint32_t whitespace = str.find(' ');
        uint32_t last = 0;
        while (whitespace < str.size())
        {
            ddg::string cuvant = str.substr(last, whitespace - last);
            
            bool sus = false;
            int index;
            for (int i = 0; i < 3; ++i)
            {
                if (cuvant == v[i])
                {
                    index = i;
                    sus = true;
                    break;
                }
            }
            if (sus)
            {
                char* temp = (char*)malloc(str.m_size + 2);
                for (int i = 0; i < str.m_size + 1; ++i)
                {
                    temp[i] = str[i];
                }
                for (int i = str.m_size + 1; i >= last + v_corect[index].find('-'); --i)
                {
                    temp[i] = temp[i - 1];
                }
                temp[last + v_corect[index].find('-')] = '-';
                free(str.data);
                str.data = temp;
                str.m_size += 1;
                
            }

            last = whitespace + 1;
            whitespace = str.find(' ', last);
        }
    }
    */

    string::~string()
    {
        free(data);
    }

    void concat(string& dest, string& src)
    {
        dest.data = (char*)realloc(dest.data, sizeof(char) * dest.m_size + src.m_size + 1);
        for (int j = 0; j < src.m_size; ++j)
        {
            dest.data[dest.m_size + j ] = src.data[j];
        }
        dest.data[dest.m_size + src.m_size] = '\0';
    }

    void putcrat(string& str)
    {
        int i = crat(str);
        int index = str.m_size;
        char aux;
        str.data = (char*)realloc(str.data, str.m_size + 2);
        if (i < str.m_size)
        {  
            for (int j = str.m_size; j >0; --j)
            {
                if (j == i)
                {

                    str.data[j] = { '-' };
                }
                if (j > i)
                {
                    str.data[j] = str.data[j - 1];
                }
            }
            str.data[str.m_size+1] = '\0';
        }
    }

    int crat(string& str)
    {
        string s1[4] = { "iam", "sa","ia","nam" };
        string s2[7] = { "tiam", "miai","sami","neam","sati","nui","neati" };
        string s3[1] = { "uitel" };
        for (int i = 0; i < 4; ++i)
        {
            if (str == s1[i] && str.m_size == s1[i].m_size)
                return 1;
        }
        for (int i = 0; i < 7; ++i)
        {
            if (str == s2[i] && str.m_size == s2[i].m_size)
                return 2;
        }
        for (int i = 0; i < 1; ++i)
        {
            if (str == s3[i] && str.m_size == s3[i].m_size)
                return s3[i].m_size - 1;
        }
        return 10000;
    }

    bool iscrat(const string& str1, const string& str2)
    {
        int count = 0;
        int poz1 = 0;
        int poz2 = 0;
        int dim = 0;
        string temp1, temp2;
        for (int i = 0; i < str1.m_size; ++i)
        {
            if (str1[i] == ' ' || str1[i] == '\0')
            {
                poz2 = i;
                if (i == 0)
                {
                    temp1 = str1.substr(0, poz2 - 1);
                }
                else
                {
                    temp1 = str1.substr(poz1 + 1, poz2 - poz1);
                }
                std::cout << temp1 << '\n';
                if (temp1 == str2)
                {
                    for (int k = i + 1; k < str1.m_size; ++k)
                    {
                        if (str1[k] == ' ' || str1[k] == '\0')
                        {
                            dim = k - i;
                            break;
                        }
                    }
                    temp2 = str1.substr(i + 1, dim);
                    std::cout << temp2 << '\n';
                    for (int j = 0; j < verbtor_size; ++j)
                    {
                        if (temp2 == verbtor[j])
                            return true;
                    }
                }
                poz1 = i;
            }
        }
        return false;
    }

    void cratime(string& str)
    {
        int found[100][marime_str];
        char aux, aux2,aux3;
        int k = 0,pozcrat = 0,pozcuv = 0;
        for (int i = 0; i < sus_size; ++i)
        {
            int index = 0;
            found[index][i] = str.find(cuvsus[i]);
            pozcrat = crat(cuvsus[i]);
            while (found[index][i] < str.m_size)
            {
                str.data = (char*)realloc(str.data, sizeof(char) * str.m_size + pozcuv + 2);
                aux3 = str.data[str.m_size-1+pozcuv];
                std::cout << aux3 << " ";
                aux = str.data[found[index][i] + pozcrat];
                aux2 = str.data[found[index][i] + pozcrat + 1];
                str.data[found[index][i] + pozcrat] = '-';                      
                str.data[found[index][i] + pozcrat + 1] = aux;
                aux = aux2;
                for (int j = found[index][i] + pozcrat + 2; j < str.m_size+pozcuv; ++j)
                {
                    aux2 = str.data[j];
                    str.data[j] = aux;
                    aux = aux2;
                }
                str.data[str.m_size+pozcuv] = aux3;
                std::cout << str.data[str.m_size+pozcuv] << " ";
                str.data[str.m_size + 1 + pozcuv] = '\0';
                std::cout << str.data << '\n';
                pozcuv++;
                index++;
                found[index][i] = str.find(cuvsus[i]);
                
            }
            std::cout << "Cuvantul " << cuvsus[i] << " a fost gasit de " << index << " ori" << '\n';
        }
    }

    std::ostream& operator<<(std::ostream& os, const ddg::string& str)
    {
        if(str.data)
            os << str.data;
        return os;
    }

}
