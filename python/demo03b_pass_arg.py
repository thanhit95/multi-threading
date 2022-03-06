'''
PASSING ARGUMENTS
Version B: Using lambdas
'''

import threading



def do_task(a: int, b: float, c: str):
    print(f'{a}  {b}  {c}')



th_foo = threading.Thread(target=lambda:do_task(1, 2, 'red'))
th_bar = threading.Thread(target=lambda:do_task(3, 4, 'blue'))

th_foo.start()
th_bar.start()
