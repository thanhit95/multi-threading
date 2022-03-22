'''
DEADLOCK
Version A
'''

import threading



mutex = threading.Lock()



def do_task(name: str):
    mutex.acquire()
    print(f'{name} acquired resource')
    # mutex.release() # Forget this statement ==> deadlock



th_foo = threading.Thread(target=do_task, args=('foo',))
th_bar = threading.Thread(target=do_task, args=('bar',))

th_foo.start()
th_bar.start()
th_foo.join()
th_bar.join()

print('You will never see this statement due to deadlock!')
