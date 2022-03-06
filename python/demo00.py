'''
INTRODUCTION TO MULTITHREADING
You should try running this app several times and see results.
'''

import threading



def do_task():
    for _ in range(300):
        print('B', end='')



th = threading.Thread(target=do_task)
th.start()

for _ in range(300):
    print('A', end='')

th.join()
print()
