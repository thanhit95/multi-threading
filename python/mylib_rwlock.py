'''
MYLIB / READ-WRITE LOCK
'''

import threading



class ReadWriteLock:
    def __init__(self):
        self.__lk_service_queue = threading.Lock()
        self.__lk_resource = threading.Lock()
        self.__lk_reader_count = threading.Lock()
        self.__reader_count = 0
        self.__rlock = self.ReadLock(self)
        self.__wlock = self.WriteLock(self)


    def get_reader_count(self) -> int:
        return self.__reader_count


    def acquire_write(self):
        with self.__lk_service_queue:
            self.__lk_resource.acquire()


    def release_write(self):
        self.__lk_resource.release()


    def acquire_read(self):
        with self.__lk_service_queue:
            with self.__lk_reader_count:
                self.__reader_count += 1
                if self.__reader_count == 1:
                    self.__lk_resource.acquire()


    def release_read(self):
        with self.__lk_reader_count:
            self.__reader_count -= 1
            if self.__reader_count == 0:
                self.__lk_resource.release()


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
