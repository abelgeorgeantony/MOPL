#include <iostream>
namespace tknzr
{
    enum tokentype
    {
        KEYWORD,
        IDENTIFIER,
        OPERATOR,
        CONSTANT,
        STRING_CONSTANT,
        DITTO_START,
        DITTO_END,
        APOSTROPHE_START,
        APOSTROPHE_END
    };
    enum datatype
    {
        MOPL_INT,
        MOPL_FLOAT,
        MOPL_CHAR
    };

    struct token
    {
        std::string data;
        enum tokentype type;
    };
    struct identifier
    {
        std::string name;
        enum datatype type;
    };

    void tokenize(std::string filecontent);
}