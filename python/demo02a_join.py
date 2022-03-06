'''
THREAD JOINS
'''

import threading



def do_heavy_task():
    # Do a heavy task, which takes a little time
    for _ in range(0, 2 * 10**8):
        pass

    print('Done!')



th = threading.Thread(target=do_heavy_task)

th.start()
th.join()

print('Good bye!')
