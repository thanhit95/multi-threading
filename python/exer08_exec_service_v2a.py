'''
MY EXECUTOR SERVICE

Version 2A: The executor service storing running tasks
- Method "waitTaskDone" uses a semaphore to synchronize.
'''

import threading
from exer08_exec_service_itask import ITask



class MyExecServiceV2A:
    def __init__(self, num_threads: int):
        # self.shutdown()
        self.__num_threads = num_threads
        self.__lstth = []
        self.__task_pending = []
        self.__lk_task_pending = threading.Lock()
        self.__cond_task_pending = threading.Condition(self.__lk_task_pending)
        self.__task_running = []
        self.__lk_task_running = threading.Lock()
        self.__counter_task_running = threading.Semaphore(0)
        self.__force_thread_shutdown = False

        for _ in range(self.__num_threads):
            self.__lstth.append(
                threading.Thread(target=MyExecServiceV2A.__thread_worker_func, args=(self,))
            )

        for th in self.__lstth:
            th.start()


    def submit(self, task: ITask):
        with self.__lk_task_pending:
            self.__task_pending.append(task)
            self.__cond_task_pending.notify()


    def wait_task_done(self):
        while True:
            self.__counter_task_running.acquire()

            with self.__lk_task_pending, self.__lk_task_running:
                if len(self.__task_pending) == 0 and len(self.__task_running) == 0:
                    break


    def shutdown(self):
        if not hasattr(self, f'_{self.__class__.__name__}__lstth'):
            return

        self.__force_thread_shutdown = True

        with self.__lk_task_pending:
            self.__task_pending.clear()
            self.__cond_task_pending.notify_all()

        _ = [th.join() for th in self.__lstth]
        self.__num_threads = 0
        self.__lstth.clear()


    @staticmethod
    def __thread_worker_func(selfptr: 'MyExecServiceV2A'):
        task_pending = selfptr.__task_pending
        lk_task_pending = selfptr.__lk_task_pending
        cond_task_pending = selfptr.__cond_task_pending

        task_running = selfptr.__task_running
        lk_task_running = selfptr.__lk_task_running
        counter_task_running = selfptr.__counter_task_running

        while True:
            with lk_task_pending:
                # WAIT FOR AN AVAILABLE PENDING TASK
                while len(task_pending) == 0 and not selfptr.__force_thread_shutdown:
                    cond_task_pending.wait()

                if selfptr.__force_thread_shutdown:
                    # lk_task_pending.release()
                    break

                # GET THE TASK FROM THE PENDING QUEUE
                task = task_pending.pop(0)

                # PUSH IT TO THE RUNNING QUEUE
                with lk_task_running:
                    task_running.append(task)

            # DO THE TASK
            task.run()

            # REMOVE IT FROM THE RUNNING QUEUE
            with lk_task_running:
                task_running.remove(task)
                counter_task_running.release()
