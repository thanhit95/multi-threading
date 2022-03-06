'''
THREAD POOL & EXECUTOR SERVICE IMPLEMENTATION
'''

import time
from exer07_thread_pool_itask import ITask
from exer07_thread_pool_v1 import ThreadPoolV1
from exer07_thread_pool_v2a import ThreadPoolV2A
from exer07_thread_pool_v2b import ThreadPoolV2B



class MyTask(ITask):
    def __init__(self, task_id: str):
        self.id = task_id

    def run(self):
        print(f'Task {self.id} is starting')
        time.sleep(3)
        print(f'Task {self.id} is completed')



NUM_THREADS = 2
NUM_TASKS = 5

thread_pool = ThreadPoolV2B(NUM_THREADS)

lsttask = [MyTask(chr(i + 65)) for i in range(NUM_TASKS)]

for task in lsttask:
    thread_pool.submit(task)

print('All tasks are submitted')

thread_pool.wait_task_done()
print('All tasks are completed')

thread_pool.shutdown()
