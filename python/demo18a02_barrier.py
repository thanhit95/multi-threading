'''
BARRIERS AND LATCHES
Version A: Barriers
'''

import time
import threading



sync_point = threading.Barrier(parties=2)



def process_request(user_name: str, time_wait: int):
    time.sleep(time_wait)

    print(f'Get request from {user_name}')
    sync_point.wait()

    print(f'Process request for {user_name}')
    sync_point.wait()

    print(f'Done {user_name}')



lstarg = [
    ('lorem', 1),
    ('ipsum', 3),
    ('dolor', 3),
    ('amet', 10)
]

_ = [ threading.Thread(target=process_request, args=arg) for arg in lstarg ]

# Thread with user_name = "amet" shall be FREEZED
