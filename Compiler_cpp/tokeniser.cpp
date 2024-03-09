#include <iostream>
#include <vector>

#include "headers/tokeniser.h"

int readWord(char *, std::string *);
int readNumberConstant(char *, std::string *);
int readStringConstant(char *, std::string *);
void assign_wrdtkntype(tknzr::token *);

bool isNamingChar(char);
bool isNumberConstant(char);
bool isNumber(char);
bool iskeyword(std::string);
bool isidentifier(std::string);

void printtokens();
std::string printtkntypename(int);

std::vector<tknzr::token> tokenlist;
std::vector<tknzr::identifier> identifierlist;
std::vector<std::string> keywordlist = {"if", "else"};

void tknzr::tokenize(std::string filecontent)
{
    std::cout << filecontent << "\n";
    int index = 0;
    tknzr::token token;
    for (index = 0; index < filecontent.length(); index++)
    {
        if (isNamingChar(filecontent.at(index)) && (!isNumber(filecontent.at(index))))
        { // IF true it means the following word is either a identifier or keyword
            index = index + readWord(&(filecontent.at(index)), &(token.data));
            assign_wrdtkntype(&token);
            tokenlist.push_back(token);
        }
        else if (isNumberConstant(filecontent.at(index)))
        { // IF true it means the following word is a non-string constant/literal
            index = index + readNumberConstant(&(filecontent.at(index)), &(token.data));
            token.type = tknzr::CONSTANT;
            tokenlist.push_back(token);
        }
        else if (filecontent.at(index) == '\"')
        { // IF true it means the following word is a string constant/literal
            token.data = filecontent.at(index);
            token.type = tknzr::DITTO_START;
            tokenlist.push_back(token); // A new token which shows the start of a string is pushed
            token.data = "";

            index = index + readStringConstant(&(filecontent.at(index)), &(token.data));
            token.type = tknzr::STRING_CONSTANT;
            tokenlist.push_back(token); // A new token which shows the contents of the string is pushed
            token.data = "";

            token.data = filecontent.at(index);
            token.type = tknzr::DITTO_END;
            tokenlist.push_back(token); // A new token which shows the end of the string is pushed
        }
        else if (filecontent.at(index) == '\'')
        {
            token.data = filecontent.at(index);
            token.type = tknzr::APOSTROPHE_START;
            index++;
            tokenlist.push_back(token);

            token.data = filecontent.at(index);
            token.type = tknzr::CONSTANT;
            index++;
            tokenlist.push_back(token);

            token.data = filecontent.at(index);
            token.type = tknzr::APOSTROPHE_END;
            tokenlist.push_back(token);
        }
        else
        {
        }
        token.data = "";
    }
    printtokens();
}

void assign_wrdtkntype(tknzr::token *tkn)
{
    if (iskeyword((*tkn).data))
    {
        (*tkn).type = tknzr::KEYWORD;
        return;
    }

    if (isidentifier((*tkn).data))
    {
        (*tkn).type = tknzr::IDENTIFIER;
        return;
    }
    else
    {
        tknzr::identifier new_identifier;
        new_identifier.name = (*tkn).data;
        identifierlist.push_back(new_identifier);
        (*tkn).type = tknzr::IDENTIFIER;
        return;
    }
}

int readWord(char *word_begin, std::string *word)
{
    int i = 0;
    bool end = false;
    while (!end)
    {
        if (isNamingChar(*(word_begin + i)))
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
int readNumberConstant(char *constant_begin, std::string *constant)
{
    int i = 0;
    bool end = false;
    while (!end)
    {
        if (isNumberConstant(*(constant_begin + i)))
        {
            (*constant).push_back(*(constant_begin + i));
            i++;
        }
        else
        {
            end = true;
            i--; // Sets to the last index of the constant
        }
    }
    return i;
}
int readStringConstant(char *sconstant_begin, std::string *sconstant)
{
    int i = 0;
    bool end = false;
    while (!end)
    {
        if (i == 0)
            i++;
        else if (*(sconstant_begin + i) != '\"')
        {
            (*sconstant).push_back(*(sconstant_begin + i));
            i++;
        }
        else
        {
            end = true;
        }
    }
    return i;
}

bool isNamingChar(char character)
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
bool isNumber(char character)
{
    if (character >= '0' && character <= '9')
        return true;

    return false;
}
bool isNumberConstant(char character)
{
    if (character >= '0' && character <= '9')
        return true;
    if (character == '.')
        return true;

    return false;
}

bool iskeyword(std::string word)
{
    int i = 0;
    for (i = 0; i < keywordlist.size(); i++)
    {
        if (word == keywordlist.at(i))
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

void printtokens()
{
    int i = 0;
    for (i = 0; i < tokenlist.size(); i++)
    {
        std::cout << "Token " << i + 1 << ":\n";
        std::cout << "\tData:" << tokenlist.at(i).data << "\n";
        std::cout << "\tType:" << printtkntypename(tokenlist.at(i).type) << "\n\n";
    }
}
std::string printtkntypename(int type)
{
    std::string str;
    switch (type)
    {
    case tknzr::tokentype::CONSTANT:
        str = "CONSTANT";
        break;
    case tknzr::tokentype::IDENTIFIER:
        str = "IDENTIFIER";
        break;
    case tknzr::tokentype::KEYWORD:
        str = "KEYWORD";
        break;
    case tknzr::tokentype::OPERATOR:
        str = "OPERATOR";
        break;
    case tknzr::tokentype::DITTO_START:
        str = "DITTO_START";
        break;
    case tknzr::tokentype::DITTO_END:
        str = "DITTO_END";
        break;
    case tknzr::tokentype::STRING_CONSTANT:
        str = "STRING_CONSTANT";
        break;
    default:
        str = "UIT";
        break;
    }
    return str;
}