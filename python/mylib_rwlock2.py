'''
/******************************************************
*
* File name:    mylib_rwlock2.py
*
* Author:       Name:   Thanh Nguyen
*               Email:  thanh.it1995(at)gmail(dot)com
*
* License:      3-Clause BSD License
*
* Description:  The read-write lock implementation in Python 3
*               Underlying mechanism: The Condition Variable
*
******************************************************/
'''


import threading



class ReadWriteLock:
    def __init__(self):
        self.__cond = threading.Condition()
        self.__reader_count = 0
        self.__writer = False
        self.__rlock = self.ReadLock(self)
        self.__wlock = self.WriteLock(self)


    def get_reader_count(self) -> int:
        return self.__reader_count


    def acquire_write(self):
        with self.__cond:
            self.__cond.wait_for(lambda: not self.__writer and self.__reader_count == 0)
            self.__writer = True


    def release_write(self):
        with self.__cond:
            self.__writer = False
            self.__cond.notify_all()


    def acquire_read(self):
        with self.__cond:
            self.__cond.wait_for(lambda: not self.__writer)
            self.__reader_count += 1


    def release_read(self):
        with self.__cond:
            self.__reader_count -= 1
            if self.__reader_count == 0:
                self.__cond.notify_all()


    def readlock(self) -> 'ReadWriteLock.ReadLock':
        return self.__rlock


    def writelock(self) -> 'ReadWriteLock.WriteLock':
        return self.__wlock


    class ReadLock:
        def __init__(self, owner: 'ReadWriteLock'):
            self.__owner = owner

        def __enter__(self):
            self.__owner.acquire_read()

        def __exit__(self, exc_type, exc_value, exc_traceback):
            self.__owner.release_read()


    class WriteLock:
        def __init__(self, owner: 'ReadWriteLock'):
            self.__owner = owner

        def __enter__(self):
            self.__owner.acquire_write()

        def __exit__(self, exc_type, exc_value, exc_traceback):
            self.__owner.release_write()
