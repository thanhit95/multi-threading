'''
BARRIERS AND LATCHES
Version B: Count-down latches

Count-down latches in Python are not supported by default.
So, I use mylib_latch for this demonstration.
'''

import time
import threading
from mylib_latch import CountDownLatch



def process_request(user_name: str, wait_time: int):
    time.sleep(wait_time)

    print(f'Get request from {user_name}')

    sync_point.count_down()
    sync_point.wait()

    print(f'Done {user_name}')



lstarg = [
    ('lorem', 1),
    ('ipsum', 2),
    ('dolor', 3)
]

sync_point = CountDownLatch(count=3)

_ = [ threading.Thread(target=process_request, args=arg).start() for arg in lstarg ]
