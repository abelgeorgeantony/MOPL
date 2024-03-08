#include <iostream>
#include <vector>
namespace tknzr
{
    
    struct token
    {
        std::string data;
        tokentype type;
    };
    struct identifier
    {
        std::string name;
        datatype type;
    };

    enum tokentype {KEYWORD, IDENTIFIER, OPERATOR, CONSTANT};
    enum datatype {MOPL_INT, MOPL_FLOAT, MOPL_CHAR};
    std::vector<std::string> keywordlist = {"if", "else"};


    void tokenize(std::string filecontent);
}