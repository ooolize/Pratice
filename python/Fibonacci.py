'''
Description: 
Author: lize
Date: 2024-07-15
LastEditors: lize
'''
def qwq(x):
    result =123414
    pred=0
    ppred=1
    for i in range(1,x+1):
        result=pred+ppred
        ppred=pred
        pred=result
    return result


def rec(x):
    if(x == 1 or x == 2): 
        return 1
    return rec(x-1)+rec(x-2)

# 快速幂
# 通项公式

if __name__ == '__main__':
    n=100
    print(qwq(n))
    print(rec(n))

