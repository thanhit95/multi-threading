'''
EXECUTOR SERVICES AND THREAD POOLS
Version C02: The executor service and Future objects
'''

import time
from concurrent.futures import ThreadPoolExecutor



def get_squared(x):
    time.sleep(3)
    return x * x



executor = ThreadPoolExecutor(max_workers=1)

future = executor.submit(get_squared, 7)

print('Calculating...')
print(future.result())

executor.shutdown(wait=True)
