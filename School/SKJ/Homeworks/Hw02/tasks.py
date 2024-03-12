def is_palindrome(data): 
    for i in range(len(data) // 2):
        if data[i] != data[len(data) - 1 - i]:
            return False
    return True

def lex_compare(a, b): 
     
    min_length = min(len(a), len(b))
    
    for i in range(min_length):
        if ord(a[i]) < ord(b[i]):
            return a
        elif ord(b[i]) < ord(a[i]):
            return b
     
    return a if len(a) < len(b) else b
            
    
def count_successive(string): 
    data = []
    char = ''
    count = 0

    for i in string:
        if char == i:
            count += 1
        else:
            if char:
                data.append((char, count))
            char = i
            count = 1

    if char:
        data.append((char, count))

    return data

def find_positions(items): 
    data = {}

    for i in range(len(items)):
        if items[i] in data:
            data[items[i]].append(i)
        else:
            data[items[i]] = [i]

    return data

def invert_dictionary(dictionary):  
    inverted_dict = {}
    seen_values = set()

    for key, value in dictionary.items():
        if value in inverted_dict or value in seen_values: 
            return None
        else:
            inverted_dict[value] = key
            seen_values.add(value)

    return inverted_dict