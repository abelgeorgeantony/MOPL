#include <iostream>
#include <vector>

#include "headers/tokeniser.h"

int readWord(char *, std::string *);
void assign_wrdtkntype(tknzr::token *);

bool validNamingChar(char);
bool iskeyword(std::string);
bool isidentifier(std::string);

std::vector<tknzr::token> tokenlist;
std::vector<tknzr::identifier> identifierlist;

void tknzr::tokenize(std::string filecontent)
{
    std::cout << filecontent << "\n";
    int index = 0;
    tknzr::token token;
    for (index = 0; index < filecontent.length(); index++)
    {
        if (validNamingChar(filecontent.at(index)))
        {
            index = index + readWord(&(filecontent.at(index)), &(token.data));
            assign_wrdtkntype(&token);
            tokenlist.push_back(token);
        }
        else
        {
            token.data = "";
        }
    }
}

void assign_wrdtkntype(tknzr::token *tkn)
{
    if (iskeyword((*tkn).data))
    {
        (*tkn).type == tknzr::KEYWORD;
        return;
    }

    if (isidentifier((*tkn).data))
    {
        (*tkn).type == tknzr::IDENTIFIER;
        return;
    }
    else
    {
        tknzr::identifier new_identifier;
        new_identifier.name = (*tkn).data;
        identifierlist.push_back(new_identifier);
        (*tkn).type == tknzr::IDENTIFIER;
        return;
    }
}

int readWord(char *word_begin, std::string *word)
{
    int i = 0;
    bool end = false;
    while (!end)
    {
        if (validNamingChar(*(word_begin + i)))
        {
            (*word).push_back(*(word_begin + i));
            i++;
        }
        else
        {
            end = true;
            i--; // Sets to the last index of the word
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

bool iskeyword(std::string word)
{
    int i = 0;
    for (i = 0; i < tknzr::keywordlist.size(); i++)
    {
        if (word == tknzr::keywordlist.at(i))
        {
            return true;
        }
    }
    return false;
}
bool isidentifier(std::string word)
{
    int i = 0;
    for (i = 0; i < identifierlist.size(); i++)
    {
        if (word == identifierlist.at(i).name)
        {
            return true;
        }
    }
    return false;
}