'''
EXECUTOR SERVICE & THREAD POOL IMPLEMENTATION
'''

import time
from exer07_exec_service_itask import ITask
from exer07_exec_service_v1 import MyExecServiceV1
from exer07_exec_service_v2a import MyExecServiceV2A
from exer07_exec_service_v2b import MyExecServiceV2B



class MyTask(ITask):
    def __init__(self, task_id: str):
        self.id = task_id

    def run(self):
        print(f'Task {self.id} is starting')
        time.sleep(3)
        print(f'Task {self.id} is completed')



NUM_THREADS = 2
NUM_TASKS = 5

exec_service = MyExecServiceV2B(NUM_THREADS)

lsttask = [MyTask(chr(i + 65)) for i in range(NUM_TASKS)]

for task in lsttask:
    exec_service.submit(task)

print('All tasks are submitted')

exec_service.wait_task_done()
print('All tasks are completed')

exec_service.shutdown()
