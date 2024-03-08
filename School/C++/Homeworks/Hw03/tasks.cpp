#include "tasks.h"

// TODO: implement functions from tasks.h

Parser create_char_parser(char c)
{

    auto lambda = [c](const char *str) -> const char *
    {
        if (*str != c)
            return nullptr;

        str += 1;

        return str;
    };

    return lambda;
}

Parser create_word_parser(const char *word)
{
    auto lambda = [word](const char *str) -> const char *
    {
        if (str != std::strstr(str, word))
            return nullptr;

        return (str + strlen(word));
    };

    return lambda;
}

Parser skip_ws()
{

    auto lambda = [](const char *str) -> const char *
    {
        while (std::isspace(*str))
            str += 1;

        return str;
    };

    return lambda;
}

Parser sequence(std::vector<Parser> parsers)
{
    auto lambda = [parsers](const char *str) -> const char *
    {
        const char *tmp = str;
        for (size_t i = 0; i < parsers.size(); i++)
        {
            tmp = parsers[i](tmp);
            if (tmp == nullptr)
                return nullptr;
        }

        return tmp;
    };

    return lambda;
}

Parser repeat(Parser parser, uint32_t count)
{
    auto lambda = [parser, count](const char *str) -> const char *
    {
        for (size_t i = 0; i < count; i++)
        {
            str = parser(str);
            if (str == nullptr)
                return nullptr;
        }

        return str;
    };

    return lambda;
}

Parser any_of(std::vector<Parser> parsers)
{
    auto lambda = [parsers](const char *str) -> const char *
    {
        for (size_t i = 0; i < parsers.size(); i++)
            if (parsers[i](str) != nullptr)
                return parsers[i](str);

        return nullptr;
    };

    return lambda;
}

Parser regex_match(const char *regx)
{
    auto lambda = [regx](const char *str) -> const char *
    {
        std::regex reg(regx);
        std::cmatch m;
        if (std::regex_search(str, m, reg))
        {
            if (m.position() > 0)
                return nullptr;

            return str + m.position() + m.length();
        }
        return nullptr;
    };

    return lambda;
}
