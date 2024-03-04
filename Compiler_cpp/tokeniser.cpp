#include <iostream>

#include "headers/tokeniser.h"


bool validNamingChar(char);
int readWord(char*,std::string*);

void tknsr::tokenise(std::string filecontent)
{
    std::cout << filecontent<<"\n";
    int index = 0;
    std::string word;
    for(index = 0; index < filecontent.length(); index++)
    {
        if(validNamingChar(filecontent.at(index)))
        {
            index = index + readWord(&(filecontent.at(index)), &word);
            std::cout<<word<<"\n";
        }
        else
        {
            word = "";
        }
    }
}

int readWord(char* word_begin,std::string* word)
{
    int i = 0;
    bool end = false;
    while (!end)
    {
        if (validNamingChar(*(word_begin+i)))
        {
            (*word).push_back(*(word_begin+i));
            i++;
        }
        else
        {
            end = true;
            i--; //Sets to the last index of the word
        }
    }
    return i;
}

bool validNamingChar(char character)
{
    if (character >= 'a' && character <= 'z')
        return true;
    if (character >= 'A' && character <= 'Z')
        return true;
    if (character >= '0' && character <= '9')
        return true;
    if (character == '_')
        return true;
    
    return false;
}

/*bool iskeyword()
{
}*/