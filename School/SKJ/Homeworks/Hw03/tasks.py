import dataclasses
from typing import Callable, Generic, List, Optional, TypeVar
 
def cached(f):
     
    cache = {}
    keys = []
 
    def wrapper(*args):
        if args in cache:
            return cache[args]
        result = f(*args)
        if len(keys) == 3:
            del cache[keys.pop(0)]
        cache[args] = result
        keys.append(args)
        return result

    return wrapper

T = TypeVar("T")


@dataclasses.dataclass
class ParseResult(Generic[T]): 
    value: Optional[T]
    rest: str

    @staticmethod
    def invalid(rest: str) -> "ParseResult":
        return ParseResult(value=None, rest=rest)

    def is_valid(self) -> bool:
        return self.value is not None

 
Parser = Callable[[str], ParseResult[T]]
 
def parser_char(char: str) -> Parser[str]:

    if not char:
        raise ValueError("Empty string provided to parser_char")

    def parse(input_string: str) -> ParseResult[str]:

        if input_string == "":
            return ParseResult.invalid(input_string)

        if input_string[0] == char:
            return ParseResult(value=char, rest=input_string[len(char):])
        else:
            return ParseResult.invalid(input_string)
    return parse


def parser_repeat(parser: Parser[T]) -> Parser[List[T]]: 

    if not parser:
        raise ValueError("Empty string provided to parser_char")
    
    def parserRepeat(input_string: str) -> ParseResult[List[T]]:
        
        if input_string == "":
            return ParseResult.invalid(input_string)

        results = []
        rest = input_string

        while True:
            result = parser(rest)
            if result.is_valid():
                results.append(result.value)
                rest = result.rest
            else:
                break
        
        return ParseResult(value=results, rest=rest)

    return parserRepeat


def parser_seq(parsers: List[Parser]) -> Parser:
    def parserSequence(input_string: str) -> ParseResult:

        if input_string == "":
            return ParseResult.invalid(input_string)

        results = []
        rest = input_string

        for parser in parsers:
            result = parser(rest)
            if result.is_valid():
                results.append(result.value)
                rest = result.rest
            else:
                return ParseResult(value=rest, rest=rest)
 
        if rest == "":
            return ParseResult(value=results, rest=rest)
        else:
            return ParseResult.invalid(input_string)

    return parserSequence


def parser_choice(parsers: List[Parser]) -> Parser: 
    def parserChoice(input_string: str) -> ParseResult:

        if input_string == "":
            return ParseResult.invalid(input_string)

        for parser in parsers: 
            result = parser(input_string)
            if result.is_valid():
                return result
        return ParseResult.invalid(input_string)

    return parserChoice


R = TypeVar("R")


def parser_map(parser: Parser[R], map_fn: Callable[[R], Optional[T]]) -> Parser[T]:
    def parse(input_string: str) -> ParseResult[T]:
        result = parser(input_string)
        if result.is_valid():
            mapped_value = map_fn(result.value)
            if mapped_value is not None:
                return ParseResult(value=mapped_value, rest=result.rest)
        return ParseResult.invalid(input_string)

    return parse



def parser_matches(filter_fn: Callable[[str], bool]) -> Parser[str]:
    def parse(input_string: str) -> ParseResult[str]:
                
        if input_string == "":
            return ParseResult.invalid(input_string)

        if input_string and filter_fn(input_string[0]):
            return ParseResult(value=input_string[0], rest=input_string[1:])
        else:
            return ParseResult.invalid(input_string)
    return parse


# Use the functions above to implement the functions below.


def parser_string(string: str) -> Parser[str]:
    def parse(input_string: str) -> ParseResult[str]:

        if input_string == "":
            return ParseResult(value="", rest="")

        if input_string.startswith(string):
            return ParseResult(value=string, rest=input_string[len(string):])
        else:
            return ParseResult.invalid(input_string)
    return parse


def parser_int() -> Parser[int]: 
    def parserInt(input_string: str) -> ParseResult[int]:

        if input_string == "" or not input_string[0].isdigit():
            return ParseResult.invalid(input_string)

        index = 0 
        result = 0

        while index < len(input_string) and input_string[index].isdigit():
            result = result * 10 + int(input_string[index])
            index += 1

        return ParseResult(value=result, rest=input_string[index:])

    return parserInt