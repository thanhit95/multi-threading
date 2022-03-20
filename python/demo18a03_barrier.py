'''
BARRIERS AND LATCHES
Version A: Barriers
'''

import time
import threading



sync_point_a = threading.Barrier(parties=2)
sync_point_b = threading.Barrier(parties=2)



def process_request(user_name: str, wait_time: int):
    time.sleep(wait_time)

    print(f'Get request from {user_name}')
    sync_point_a.wait()

    print(f'Process request for {user_name}')
    sync_point_b.wait()

    print(f'Done {user_name}')



lstarg = [
    ('lorem', 1),
    ('ipsum', 3),
    ('dolor', 3),
    ('amet', 10)
]

_ = [ threading.Thread(target=process_request, args=arg) for arg in lstarg ]
