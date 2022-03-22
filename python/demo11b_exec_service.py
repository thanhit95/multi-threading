'''
EXECUTOR SERVICES AND THREAD POOLS
Version B: The executor service containing multiple threads
'''

import time
from concurrent.futures import ThreadPoolExecutor



def do_task(name: str):
    print(f'Task {name} is starting')
    time.sleep(3)
    print(f'Task {name} is completed')



NUM_TASKS = 5
executor = ThreadPoolExecutor(max_workers=2)

for i in range(NUM_TASKS):
    task_name = chr(i + 65)
    executor.submit(do_task, task_name)

executor.shutdown(wait=True)
