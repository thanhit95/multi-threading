'''
/******************************************************
*
* File name:    mylib_latch.py
*
* Author:       Name:   Thanh Nguyen
*               Email:  thanh.it1995(at)gmail(dot)com
*
* License:      3-Clause BSD License
*
* Description:  The count-down latch implementation in Python 3
*
******************************************************/
'''


import threading



class CountDownLatch:
    def __init__(self, count: int):
        if count < 0:
            raise ValueError('count must be a non-negative integer')

        self.__count = count
        self.__cond = threading.Condition()


    def get_count(self) -> int:
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
