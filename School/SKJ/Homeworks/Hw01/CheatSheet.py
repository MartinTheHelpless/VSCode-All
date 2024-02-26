########################
# Declaring a variable #
########################
a = 5           # integer
b = 6.0         # float
c = "hello"     # string
e = False       # bool

a = 6           # variable can be redefined

############
# Printing #
############
print("Hello")
print(f"1 + 1 is {2}")

################
# Control flow #
################
for <variable> in <iterable>:
    <body>

for x in range(5):  # range(n) returns values from interval [0, n), range(a, b) from interval [a, b)
    print(x)

for i, x in enumerate([2, 3, 5]):  # enumerate(sequence) returns pairs (index, sequence element)
    print(i, x)  # (0, 2), (1, 3), (2, 5)

while <condition>:
    <body>
else:       # this is optional, it executes if the cycle had no iterations (works with for too)
    ...

while a < b:
    a -= 1

# condition is generally a boolean value, but it can be anything that evaluates to a boolean value
if <condition>:
    ...
elif <condition>:
    ...
else:
    ...

if a and b:  # logical AND
    pass  # if there's no code, you have to write pass (it cannot be empty)

if a or b:  # logical OR
    pass

1 if <condition> else 2  # ternary operator (condition ? 1 : 2)

if a > b and c == "hello":
    print("Condition holds!")
elif a < b:
    print("a < b")
else:
    print("Condition does not hold")

###########
# Numbers #
###########
a = 5
b = 5
5 == 5      # True, same value
-5 is -5    # True, same address (same object)
-6 is -6    # False, different object (only integers [-5, 256] are interned/cached in CPython)
a = 555555555555555555555555555555555555  # arbitrarily large ints
2 / 4       # 0.5, float division by default
2 // 4      # 0, integer division

type(5)     # int
type(5.0)   # float

###########
# Strings #
###########
a = 'hello'
a[0] = 'a'      # error, strings are immutable
len(a)          # 5
'h' in a        # True
a + ' world'    # 'hello world'
emoji = '👍'     # Unicode by default
'  data \n'.strip()  # 'data' (strips whitespace)
'hey how are you'.split(' ')  # ['hey', 'how', 'are', 'you'] (splits string by spaces)

# Multi-line strings
"""
This string spans multiple lines and keeps whitespace
    space before this is kept
"""

######################################
# Useful functions, numbers, strings #
######################################
type(a)     # returns the type of an object
id(a)       # return the address of an object
dir(a)      # returns the attributes and methods of an object
help(a)     # returns documentation of an object

##############
# Formatting #
##############
f"Hello {1 + 2}"    # Hello 3
f"{2.33333:.2f}"    # 2.33

##########################################
# Strong typing (data types are checked) #
##########################################
'1' + 2         # error
int('1') + 2    # 3
'1' + str(2)    # '12'

#########
# Lists #
#########
l = [1, 2, 3]
[i * 2 for i in l if i % 2 == 0]  # [0, 4]
len(l)          # 3
l.append(0)     # l == [1, 2, 3, 0]
2 in l          # True
10 in l         # False
l[0] = 5        # l == [5, 2, 3, 0]
del l[0]        # l == [2, 3, 0]
l.sort()        # l == [0, 2, 3]
l + l           # [0, 2, 3, 0, 2, 3]
sum(l)          # 4

###########################
# Everything is a pointer #
###########################
a = [1]
b = a
a += [2]
b               # [1, 2]


###########
# Slicing #
###########
# [from:to:increment], `from` is by default the first element, `to` is by default the last element, `increment` is by default 1
l = [1, 2, 3, 4, 5, 6]
l[1]            # 2
l[-1]           # 6
l[1:3]          # [2, 3]
l[:3]           # [1, 2, 3]
l[1:]           # [2, 3, 4, 5, 6]
l[:]            # [1, 2, 3, 4, 5, 6] (copy)
l[::-1]         # [6, 5, 4, 3, 2, 1] (reverse)
l[5:3:-1]       # [6, 4] (with negative increment `from` and `to` swap their meaning)

##########
# Tuples #
##########
t = (1, 2, 3)
a, b, c = t     # a == 1, b == 2, c == 3

################
# Dictionaries #
################
d = {'milan': 1, 'frantisek': 4}
'milan' in d    # True
'jaromir' in d  # False
d['milan']      # 1
d['jaromir']    # raises KeyError exception
d.get('jaromir', 0)  # 0
[k for k in d]  # ['milan', 'frantisek'] or ['frantisek', 'milan']
d.items()       # [('milan', 1), ('frantisek', 4)]
del d['milan']  # d == {'frantisek': 4}
d.update({'jana': 2})  # d == {'frantisek': 4, 'jana': 2}

########
# Sets #
########
s = {1, 2, 3}
s.add(1)        # s == {1, 2, 3}
s.add(4)        # s == {1, 2, 3, 4}
1 in s          # True
5 in s          # False
s.remove(1)     # s == {2, 3, 4}
s.union({2, 6}) # {2, 3, 4, 6}
s.difference({2, 4}) # {3}
