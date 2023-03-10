#include <string.h>
#include "ddgstring.h"

namespace ddg
{
    char string::delim[marime_vector] = { ' ' , '.', ',', '\0', '?', '!'};
    char spatiu[marime_vector] = { ' ' , '.', ',', '\0', '?', '!' };
    string cuvsus[sus_size] = { "tiam", "miai","sami","neam","sati","nui","neati","iam", "sa","ia","nam","lam","uiteo","uitel","prezinto","fama"};
    string sus[defsus] = { "uitel","fama","uiteo","prezinto" };
    string verbtor[verbtor_size] = { "gasit" ,"cunoscut","facut", "spus","cautat","luat","mancat","cercetat","promis","iertat","decis","dat","zis","iubit"};

    string::string()
        : data(NULL), m_size(0)
    {}

    string::string(const char* str)
        : data((char*)malloc(sizeof(char) * strlen(str) + 1)), m_size(strlen(str))
    {
        strcpy(data,str);
    }

    string::string(const string& other)
        : data((char*)malloc(sizeof(char) * other.m_size + 1)), m_size(other.m_size)
    {
        strcpy(data, other.data);
    }

    void string::operator=(const string& str)
    {
        if (data != NULL)
            free(data);
        data = (char*)malloc(sizeof(char) * str.m_size + 1);   
        strcpy(data, str.data);
        m_size = str.m_size;
    }

    string string::operator+(const char* str)
    {
        char* ret = (char*)malloc(sizeof(char) * m_size + strlen(str) + 1);     
        strcat(ret, str);
        m_size = m_size + strlen(str);
        return ret;
    }

    string string::operator+(const string& str)
    {
        string ret;
        ret.data = (char*)malloc(sizeof(char) * (m_size + str.m_size) + 2);   
        ret[0] = '\0';
        strcat(ret.data, data);
        strcat(ret.data, " ");
        strcat(ret.data, str.data);
        return ret;
    }

    string string::operator-(const char cifra)
    {
        int r = 0;                                     
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

    string string::operator-(const char* sir)
    {
        int count = 0;
        int index = 0;
        for (int i = 0; i < m_size; ++i)
        {
            int gasit = 1;
            for (int j = 0; j < strlen(sir); ++j)
            {
                if (data[i + j] != sir[j])        
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
                if (!i)    
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
        for (int i = 0; i < str.m_size; ++i)        
        {
            if (data[i] != str[i])
                egal = false;
        }
        return egal;
    }

    bool string::operator!=(const string& str)
    {
        bool egal = true;
        for (int i = 0; i < str.m_size; ++i)        
        {
            if (data[i] != str[i])
                egal = false;
        }
        return !egal;
    }

    char& string::operator[](int index)
    {
        return data[index];                 
    }

    const char& string::operator[](int index) const
    {
        return data[index];                     
    }

    bool string::isDelim(char ch)
    {
        for (int i = 0; i < marime_vector; ++i)     
            if (ch == delim[i])
                return true;
        return false;
    }

    unsigned int string::size() { return m_size; }

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
            {                                       
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
        m_size -= spatii;
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
                tmp.data[j] = data[i];                               
                j++;
            }
            tmp.data[j] = '\0';
            tmp.m_size = m_size - pos;
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
            tmp.m_size = count;
        }
        return tmp;
    }

    unsigned int string::find(char ch, unsigned int i )
    {
        for (; i < m_size; ++i)         
        {
            if (data[i] == ch)
                return i;
        }
        return m_size;
    }

    unsigned int string::find(const string& str, unsigned int i )
    {
        int index;
        int gasit;
        for (int i = 0; i < m_size; ++i)                 
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

    void string::erase(unsigned int poz)
    {
        data[poz] = ' ';
        for(int i = poz; i<m_size; ++i)
        {
            data[i] = data[i+1];
        }
        m_size--; 
    }

    void string::erase(unsigned int first, unsigned int last)
    {
        int j = 0;
        for(int i = 0; i<m_size; ++i)
        {
            if(i>=first && i<=last)
            {
                data[i] = ' ';
            }
            else
            {
                data[j] = data[i];
                ++j;
            }
        }
        m_size -= (last - first + 1);
        data[m_size] = '\0';
    }

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

    int crat(string& str)
    {
        string s1[5] = { "iam", "sa","ia","nam","lam"};
        string s2[8] = { "tiam", "miai","sami","neam","sati","nui","neati","fama"};
        string s3[3] = { "uitel","uiteo","prezinto"};
        for (int i = 0; i < 5; ++i)
        {
            if (str == s1[i] && str.m_size == s1[i].m_size)
                return 1;
        }
        for (int i = 0; i < 8; ++i)
        {
            if (str == s2[i] && str.m_size == s2[i].m_size)
                return 2;
        }
        for (int i = 0; i < 3; ++i)
        {
            if (str == s3[i] && str.m_size == s3[i].m_size)
                return s3[i].m_size - 1;
        }
        return 10000;
    }   

    void cratime(string& str)
    {
        int found[100][marime_str];
        int poz2 = 0;
        char aux, aux2,aux3;
        string temp;
        int pozcrat = 0,pozcuv = 0;
        bool isus = false;
        for (int i = 0; i < sus_size; ++i)
        {
            int index = 0;
            found[index][i] = str.find(cuvsus[i]);
            pozcrat = crat(cuvsus[i]);
            while (found[index][i] < str.m_size)
            {
                isus = false;
                for (int poz = found[index][i] + cuvsus[i].m_size + 1 ; poz <= str.m_size; ++poz)
                {
                    poz2 = poz;
                    if (str.data[poz] == ' ' || str.data[poz] == '\0')
                    {
                        break;
                    }
                }
                for(int l = 0; l<verbtor_size; ++l)
                { 
                    if (str.substr(found[index][i] + cuvsus[i].m_size + 1, poz2 - (found[index][i] + cuvsus[i].m_size)-1) == verbtor[l])
                    {
                        isus = true;
                        break;
                    }
                }
                for (int l = 0; l < defsus; ++l)
                {
                    if (cuvsus[i] == sus[l]) 
                    {
                        isus = true;
                        break;
                    }
                }
                if (isus)
                {
                    str.data = (char*)realloc(str.data, sizeof(char) * str.m_size + pozcuv + 2);
                    aux3 = str.data[str.m_size - 1 + pozcuv];
                    aux = str.data[found[index][i] + pozcrat];
                    aux2 = str.data[found[index][i] + pozcrat + 1];
                    str.data[found[index][i] + pozcrat] = '-';
                    str.data[found[index][i] + pozcrat + 1] = aux;
                    aux = aux2;
                    for (int j = found[index][i] + pozcrat + 2; j < str.m_size + pozcuv; ++j)
                    {
                        aux2 = str.data[j];
                        str.data[j] = aux;
                        aux = aux2;
                    }
                    str.data[str.m_size + pozcuv] = aux3;
                    str.data[str.m_size + 1 + pozcuv] = '\0';
                    pozcuv++;
                    index++;
                    found[index][i] = str.find(cuvsus[i]);
                }
                else
                {
                    index++;
                    found[index][i] = str.substr(poz2+1).find(cuvsus[i]) + poz2+1;
                    if (found[index][i] == str.substr(poz2 + 1).m_size)
                        found[index][i] = str.m_size;
                }
            }
            str.m_size += index;
        }
    }

    std::ostream& operator<<(std::ostream& os, const ddg::string& str)
    {
        if(str.data)
            os << str.data;
        return os;
    }
}
