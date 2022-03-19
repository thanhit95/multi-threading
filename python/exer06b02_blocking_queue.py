'''
BLOCKING QUEUE IMPLEMENTATION
Version B02: General blocking queues
             Underlying mechanism: Condition variables
'''

import time
import threading



class BlockingQueue:
    def __init__(self, capacity: int):
        if capacity <= 0:
            raise ValueError('capacity must be a positive integer')
        self.__capacity = capacity
        self.__lk = threading.Lock()
        self.__cond_empty = threading.Condition(self.__lk)
        self.__cond_full = threading.Condition(self.__lk)
        self.__q = [] # queue


    def put(self, value):
        with self.__lk:
            while len(self.__q) >= self.__capacity:
                self.__cond_full.wait()

            self.__q.append(value)
            self.__cond_empty.notify()


    def take(self):
        result = None

        with self.__lk:
            while len(self.__q) == 0:
                self.__cond_empty.wait()

            result = self.__q.pop(0)
            self.__cond_full.notify()

        return result



def producer(q: BlockingQueue):
    arr = [ 'nice', 'to', 'meet', 'you' ]

    for value in arr:
        print(f'Producer: {value}')
        q.put(value)
        print(f'Producer: {value} \t\t\t[done]')



def consumer(q: BlockingQueue):
    time.sleep(5)

    for i in range(4):
        value = q.take()
        print(f'\tConsumer: {value}')

        if i == 0:
            time.sleep(5)



blkqueue = BlockingQueue(2) # capacity = 2
threading.Thread(target=producer, args=(blkqueue,)).start()
threading.Thread(target=consumer, args=(blkqueue,)).start()
