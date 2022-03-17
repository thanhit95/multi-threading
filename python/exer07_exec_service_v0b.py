'''
MY EXECUTOR SERVICE

Version 0B: The easiest executor service
- It uses a blocking queue as underlying mechanism.
- It supports waitTaskDone() and shutdown().
'''

import time
from queue import Queue
import threading
from exer07_exec_service_itask import ITask



class MyExecServiceV0B:
    class EmptyTask(ITask):
        def run(self):
            pass


    def __init__(self, num_threads: int):
        self.__num_threads = num_threads
        self.__lstth = []
        self.__task_pending = Queue()
        self.__counter_task_running = 0
        self.__force_thread_shutdown = False

        for _ in range(self.__num_threads):
            self.__lstth.append(
                threading.Thread(target=MyExecServiceV0B.__thread_worker_func, args=(self,))
            )

        for th in self.__lstth:
            th.start()


    def submit(self, task: ITask):
        self.__task_pending.put_nowait(task)


    def wait_task_done(self):
        # This ExecService is too simple,
        # so there is no good implementation for waitTaskDone()
        # Note: Bad implementation
        while self.__task_pending.qsize() > 0 or self.__counter_task_running > 0:
            time.sleep(1)


    def shutdown(self):
        self.__force_thread_shutdown = True

        # Wait until task_pending is empty
        self.__task_pending.join()

        # Invoke blocked threads by adding "empty" tasks
        for _ in range(self.__num_threads):
            self.__task_pending.put(self.EmptyTask())

        _ = [th.join() for th in self.__lstth]
        self.__num_threads = 0
        self.__lstth.clear()


    @staticmethod
    def __thread_worker_func(selfptr: 'MyExecServiceV0B'):
        task_pending = selfptr.__task_pending

        while True:
            # WAIT FOR AN AVAILABLE PENDING TASK
            task = task_pending.get()

            # If shutdown() was called, then exit the function
            if selfptr.__force_thread_shutdown:
                break

            # DO THE TASK
            selfptr.__counter_task_running += 1
            task.run()
            task_pending.task_done()
            selfptr.__counter_task_running -= 1
