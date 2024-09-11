'''
Description: 
Author: lize
Date: 2024-07-15
LastEditors: lize
'''

def add():
    result=0
    for i in  range(1,10,2) :
        result=result+i
    return result

def add(a):
    return a+1.0
b=add(2)
b=2
print(b)
# (function) def add(a: int) -> float
# (function) def add() -> int
