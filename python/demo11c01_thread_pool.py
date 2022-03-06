'''
THREAD POOLS
Version C01: Thread pools and Future objects
'''

from concurrent.futures import ThreadPoolExecutor



def get_squared(x):
    return x * x



executor = ThreadPoolExecutor(max_workers=1)

future = executor.submit(get_squared, 7)
# print(future.done())

print(future.result())

executor.shutdown(wait=True)
