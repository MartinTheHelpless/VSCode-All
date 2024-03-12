def fizzbuzz(num):

    if(num % 5 == 0 and num % 3 == 0):
        return "FizzBuzz" 
    elif(num % 3 == 0):
        return "Fizz"
    elif(num % 5 == 0):
        return "Buzz"

    return num


def fibonacci(n):
     
    a = 0;
    b = 1;

    for i in range(1, n):
        tmp = a + b
        a = b
        b = tmp

    return a;
    pass


def dot_product(a, b):
    """
    Calculate the dot product of `a` and `b`.
    Assume that `a` and `b` have same length.
    Hint:
        lookup `zip` function
    Example:
        dot_product([1, 2, 3], [0, 3, 4]) == 1*0 + 2*3 + 3*4 == 18
    """
    pass


def redact(data, chars):
    """
    Return `data` with all characters from `chars` replaced by the character 'x'.
    Characters are case sensitive.
    Example:
        redact("Hello world!", "lo")        # Hexxx wxrxd!
        redact("Secret message", "mse")     # Sxcrxt xxxxagx
    """
    pass


def count_words(data):
    """
    Return a dictionary that maps word -> number of occurences in `data`.
    Words are separated by spaces (' ').
    Characters are case sensitive.

    Hint:
        "hi there".split(" ") -> ["hi", "there"]

    Example:
        count_words('this car is my favourite what car is this')
        {
            'this': 2,
            'car': 2,
            'is': 2,
            'my': 1,
            'favourite': 1,
            'what': 1
        }
    """
    pass


def bonus_fizzbuzz(num):
    """
    Implement the `fizzbuzz` function.
    `if`, match-case and cycles are not allowed.
    """
    pass


def bonus_utf8(cp):
    """
    Encode `cp` (a Unicode code point) into 1-4 UTF-8 bytes - you should know this from `Základy číslicových systémů (ZDS)`.
    Example:
        bonus_utf8(0x01) == [0x01]
        bonus_utf8(0x1F601) == [0xF0, 0x9F, 0x98, 0x81]
    """
    pass
