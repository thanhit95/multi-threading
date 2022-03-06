'''
SEMAPHORES
Version A: Paper sheets and packages
'''

import time
import threading



sem_package = threading.Semaphore(0)



def make_one_sheet():
    for _ in range(4):
        print('Make 1 sheet')
        time.sleep(1)
        sem_package.release()



def combine_one_package():
    for _ in range(4):
        sem_package.acquire()
        sem_package.acquire()
        print('Combine 2 sheets into 1 package')



threading.Thread(target=make_one_sheet).start()
threading.Thread(target=make_one_sheet).start()
threading.Thread(target=combine_one_package).start()
