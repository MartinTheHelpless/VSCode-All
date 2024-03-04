def is_palindrome(data): 

    for i in range(len(data)):
        if(data[i] != data[len(data) - 1 - i]):
            return False
    return True



def lex_compare(a, b): 

    if(len(a) > len(b)):
        return b;
    elif(len(b) > len(a)):
        return a;
    else:
        if(ord(a) > ord(b)):
            return b;
    return a;


def count_successive(string): 
    
    data
    char 
    count = 0

    for i in string:
        if(char == i):
            count+=1
        else:
            data += (char, count)
            char = i
            count = 0

    return data


def find_positions(items): 
    data 

    for i in range(len(items)):
        if(data[items[i]]):
            data[items[i]].append(i)
        else:
            data += {items[i]: i}
    return data


def invert_dictionary(dictionary): 
    data = {}

    values = dictionary.values()
    keys = dictionary.keys()

    for i in range(len(dictionary)):
        data += {values[i] : keys[i]}

    return data