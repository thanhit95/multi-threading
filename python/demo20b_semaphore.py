'''
SEMAPHORES
Version B: Tires and chassis
'''

import time
import threading



sem_tire = threading.Semaphore(4)
sem_chassis = threading.Semaphore(0)



def make_tire():
    for _ in range(8):
        sem_tire.acquire()

        print('Make 1 tire')
        time.sleep(1)

        sem_chassis.release()



def make_chassis():
    for _ in range(4):
        sem_chassis.acquire()
        sem_chassis.acquire()
        sem_chassis.acquire()
        sem_chassis.acquire()

        print('Make 1 chassis')
        time.sleep(3)

        sem_tire.release()
        sem_tire.release()
        sem_tire.release()
        sem_tire.release()



threading.Thread(target=make_tire).start()
threading.Thread(target=make_tire).start()
threading.Thread(target=make_chassis).start()
