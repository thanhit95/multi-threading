'''
BARRIERS AND LATCHES
Version B: Count-down latches

Main thread waits for 3 child threads to get enough data to progress.

Count-down latches in Python are not supported by default.
So, I use mylib_latch for this demonstration.
'''

import time
import threading
from mylib_latch import CountDownLatch



def do_task(message: str, wait_time: int):
    time.sleep(wait_time)

    print(message)
    sync_point.count_down()

    time.sleep(8)
    print('Cleanup')



lstarg = [
    ('Send request to egg.net to get data', 6),
    ('Send request to foo.org to get data', 2),
    ('Send request to bar.com to get data', 4)
]

sync_point = CountDownLatch(count=len(lstarg))

_ = [ threading.Thread(target=do_task, args=arg).start() for arg in lstarg ]

sync_point.wait()
print('\nNow we have enough data to progress to next step\n')
