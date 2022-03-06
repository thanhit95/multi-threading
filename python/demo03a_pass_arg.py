'''
PASSING ARGUMENTS
Version A: Using the Thread's constructor
'''

import threading



def do_task(a: int, b: float, c: str):
    print(f'{a}  {b}  {c}')



th_foo = threading.Thread(target=do_task, args=(1, 2, 'red'))
th_bar = threading.Thread(target=do_task, args=(3, 4, 'blue'))

th_foo.start()
th_bar.start()
