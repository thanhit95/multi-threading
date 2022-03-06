'''
MY THREAD POOL

Version 1:
- Simple thread pool.
- Method "wait_task_done" consumes CPU (due to bad synchronization).
'''

import time
import threading
from exer07_thread_pool_itask import ITask



class ThreadPoolV1:
    def __init__(self, num_threads: int):
        self.shutdown()
        self.__num_threads = num_threads
        self.__lstth = []
        self.__task_pending = []
        self.__lk_task_pending = threading.Lock()
        self.__cond_task_pending = threading.Condition(self.__lk_task_pending)
        self.__force_thread_shutdown = False

        with self.__lk_task_pending:
            self.__counter_task_running = 0

        for _ in range(self.__num_threads):
            self.__lstth.append(
                threading.Thread(target=ThreadPoolV1.__thread_worker_func, args=(self,))
            )

        for th in self.__lstth:
            th.start()


    def submit(self, task: ITask):
        with self.__lk_task_pending:
            self.__task_pending.append(task)
            self.__cond_task_pending.notify()


    def wait_task_done(self):
        done = False
        while True:
            with self.__lk_task_pending:
                if len(self.__task_pending) == 0 and self.__counter_task_running == 0:
                    done = True

            if done:
                break

            time.sleep(0.5)


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
    def __thread_worker_func(selfptr: 'ThreadPoolV1'):
        task_pending = selfptr.__task_pending
        lk_task_pending = selfptr.__lk_task_pending
        cond_task_pending = selfptr.__cond_task_pending

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
                selfptr.__counter_task_running += 1

            # DO THE TASK
            task.run()

            with lk_task_pending:
                selfptr.__counter_task_running -= 1
