'''
SEMAPHORES
Version A: Paper sheets and packages
'''

import time
import threading



sem_package = threading.Semaphore(0)
sem_sheet = threading.Semaphore(2)



def make_one_sheet():
    for _ in range(4):
        sem_sheet.acquire()
        print('Make 1 sheet')
        sem_package.release()



def combine_one_package():
    for _ in range(4):
        sem_package.acquire()
        sem_package.acquire()
        print('Combine 2 sheets into 1 package')
        time.sleep(2)
        sem_sheet.release()
        # sem_sheet.release() # Missing one statement: sem_sheet.release() ==> deadlock



threading.Thread(target=make_one_sheet).start()
threading.Thread(target=make_one_sheet).start()
threading.Thread(target=combine_one_package).start()
