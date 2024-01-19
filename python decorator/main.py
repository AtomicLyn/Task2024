cash = 0
count = 0

def func_decorator(func):
    def wrapper(*args):
        global count, cash
        if count != 0 and count < 3:
            count += 1
            return cash
        else:
            cash = func(*args)
            count = 1
            return cash
    return wrapper

@func_decorator
def func(num):
    return num+1

for number in range(0, 30):
    print(func(number))