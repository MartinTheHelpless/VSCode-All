def add(a, b):
    return a + b


def what_number(number):
    if number < 0:
        return "Negative"
    elif number > 0:
        return "Positive"
    else:
        return "Zero"


def sum_pf_numbers(numbers):
    return sum(numbers)


def ship_name(fleet, designated_no):
    if designated_no in fleet:
        return fleet[designated_no]
    else:
        return 0


def how_many_5(numbers):
    res = 0
    for number in numbers:
        if number > 5:
            res += 1
    return res


def gen_list(lst, no):
    output = []
    for item in lst:
        if item > no:
            output.append(item)
    return output
