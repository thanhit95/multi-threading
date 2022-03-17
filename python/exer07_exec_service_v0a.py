'''
MY EXECUTOR SERVICE

Version 0A: The easiest executor service
- It uses a blocking queue as underlying mechanism.
'''

import time
from queue import Queue
import threading
from exer07_exec_service_itask import ITask



class MyExecServiceV0A:
    class EmptyTask(ITask):
        def run(self):
            pass


    def __init__(self, num_threads: int):
        self.__num_threads = num_threads
        self.__lstth = []
        self.__task_pending = Queue()

        for _ in range(self.__num_threads):
            self.__lstth.append(
                threading.Thread(target=MyExecServiceV0A.__thread_worker_func, args=(self,))
            )

        for th in self.__lstth:
            th.start()


    def submit(self, task: ITask):
        self.__task_pending.put_nowait(task)


    def wait_task_done(self):
        # This ExecService is too simple,
        # so there is no implementation for waitTaskDone()
        time.sleep(11) # fake behaviour


    def shutdown(self):
        # This ExecService is too simple,
        # so there is no implementation for shutdown()
        print('No implementation for shutdown().')
        print('You need to exit the app manually.')


    @staticmethod
    def __thread_worker_func(selfptr: 'MyExecServiceV0A'):
        task_pending = selfptr.__task_pending

        while True:
            # WAIT FOR AN AVAILABLE PENDING TASK
            task = task_pending.get()

            # DO THE TASK
            task.run()
