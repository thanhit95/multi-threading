'''
EXECUTOR SERVICE & THREAD POOL IMPLEMENTATION
'''

import time
from exer07_exec_service_itask import ITask
from exer07_exec_service_v0a import MyExecServiceV0A
from exer07_exec_service_v0b import MyExecServiceV0B
from exer07_exec_service_v1a import MyExecServiceV1A
from exer07_exec_service_v1b import MyExecServiceV1B
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

exec_service = MyExecServiceV0A(NUM_THREADS)

lsttask = [MyTask(chr(i + 65)) for i in range(NUM_TASKS)]

for task in lsttask:
    exec_service.submit(task)

print('All tasks are submitted')

exec_service.wait_task_done()
print('All tasks are completed')

exec_service.shutdown()
