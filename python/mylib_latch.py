'''
MYLIB / LATCH
'''

import threading



class CountDownLatch:
    def __init__(self, count: int):
        if count < 0:
            raise ValueError('count must be a non-negative integer')

        self.__count = count
        self.__cond = threading.Condition()


    def get_count(self):
        return self.__count


    def count_down(self):
        with self.__cond:
            if self.__count <= 0:
                return

            self.__count -= 1

            if self.__count <= 0:
                self.__cond.notify_all()


    def wait(self):
        with self.__cond:
            self.__cond.wait_for(lambda : self.__count <= 0)
