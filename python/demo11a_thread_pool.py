'''
THREAD POOLS
Version A: Thread pools containing a single thread
'''

from concurrent.futures import ThreadPoolExecutor



def do_task():
    print('Hello Thread Pool')



executor = ThreadPoolExecutor(max_workers=1)

executor.submit(lambda: print('Hello World'))
executor.submit(do_task)

executor.shutdown(wait=True)
