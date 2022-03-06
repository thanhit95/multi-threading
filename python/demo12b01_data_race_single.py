'''
DATA RACES
Version 01: Without multithreading
'''



def get_result(n: int):
    a = [False] * (n + 1)

    for i in range(1, n + 1):
        if i % 2 == 0 or i % 3 == 0:
            a[i] = True

    res = a.count(True)
    return res



N = 8
result = get_result(N)
print('Number of integers that are divisible by 2 or 3 is:', result)
