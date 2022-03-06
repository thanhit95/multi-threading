'''
HELLO WORLD VERSION MULTITHREADING
Getting thread's name
'''

import threading



def do_task():
    print(f'My name is {threading.current_thread().name}')



th_foo = threading.Thread(target=do_task, name='foo')
th_bar = threading.Thread(target=do_task, name='bar')
th_foo.start()
th_bar.start()
