#include <functional>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <regex>
#include <cctype>

using Parser = std::function<const char *(const char *)>;

Parser create_char_parser(char c);

Parser create_word_parser(const char *word);

Parser skip_ws();

Parser sequence(std::vector<Parser> parsers);

Parser repeat(Parser parser, uint32_t count);

Parser any_of(std::vector<Parser>);

Parser regex_match(const char *regx);
