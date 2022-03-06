'''
THREAD-LOCAL STORAGE
Avoiding synchronization using thread-local storage
'''

import time
import threading



data = threading.local()



def do_task(t: int):
    time.sleep(1)
    data.counter = 0

    for _ in range(1000):
        data.counter += 1

    print(f'Thread {t} gives counter = {data.counter}')



NUM_THREADS = 3

for i in range(NUM_THREADS):
    threading.Thread(target=do_task, args=(i,)).start()

# By using thread-local storage, each thread has its own counter.
# So, the counter in one thread is completely independent of each other.
# Thread-local storage helps us to AVOID SYNCHRONIZATION.
