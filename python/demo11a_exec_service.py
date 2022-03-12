'''
EXECUTOR SERVICES AND THREAD POOLS
Version A: The executor service (of which thread pool) containing a single thread
'''

from concurrent.futures import ThreadPoolExecutor



def do_task():
    print('Hello the Executor Service')



executor = ThreadPoolExecutor(max_workers=1)

executor.submit(lambda: print('Hello World'))
executor.submit(do_task)

executor.shutdown(wait=True)
