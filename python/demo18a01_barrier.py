'''
BARRIERS AND LATCHES
Version A: Barriers
'''

import time
import threading



sync_point = threading.Barrier(parties=3)



def process_request(user_name: str, time_wait: int):
    time.sleep(time_wait)

    print(f'Get request from {user_name}')
    sync_point.wait()

    print(f'Process request for {user_name}')
    sync_point.wait()

    print(f'Done {user_name}')



lstarg = [
    ('lorem', 1),
    ('ipsum', 2),
    ('dolor', 3)
]

_ = [ threading.Thread(target=process_request, args=arg).start() for arg in lstarg ]
