'''
CONDITION VARIABLES
'''

import threading



condition_var = threading.Condition()

counter = 0

COUNT_HALT_01 = 3
COUNT_HALT_02 = 6
COUNT_DONE = 10



def foo():
    '''
    Write numbers 1-3 and 8-10 as permitted by egg()
    '''
    global counter

    while True:
        with condition_var:
            condition_var.wait()

            counter += 1
            print(f'foo counter = {counter}')

            if counter >= COUNT_DONE:
                return



def bar():
    '''
    Write numbers 4-7
    '''
    global counter

    while True:
        with condition_var:
            if counter < COUNT_HALT_01 or counter > COUNT_HALT_02:
                # Signal to free waiting thread by freeing the mutex
                # Note: foo() is now permitted to modify "counter"
                condition_var.notify()
            else:
                counter += 1
                print(f'egg counter = {counter}')

            if counter >= COUNT_DONE:
                return



threading.Thread(target=foo).start()
threading.Thread(target=bar).start()
