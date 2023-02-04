
My namespace with my own implementation of string with original methods and functions

# Funtions include:
## cratime(string&)
###### This function will put hypens where they are needed in a phrase in the romanian dialect

## crat(string&)
###### Returns the position in a word where there is the hypen needed

# Some methods are:
## space_sort()
###### It removes aditional spaces in a ddg::string 

## I included some of the default string functions too

A code example:
```cpp
#include <iostream>
#include "ddgstring.h"

using namespace ddg;

int main()
{
	string s1("Un copil mia gasit mingea si iam spus multumesc uiteo fama ca mai ajutat si ne mai vedem, sper ca lam cunoscut bine");
	cratime(s1);
	std::cout << s1;
	
	return 0;
}
```

The output will be:
```
Un copil mi-a gasit mingea si i-am spus multumesc uite-o fa-ma ca mai ajutat si ne mai vedem, sper ca l-am cunoscut bine
```
