'''
THE DATA SERVER PROBLEM
Version A: Solving the problem using a condition variable
'''

from dataclasses import dataclass
import time
import threading



@dataclass
class Counter:
    value: int = 0
    cond: threading.Condition = threading.Condition()



def check_auth_user():
    print('[   Auth   ] Start')
    # Send request to authenticator, check permissions, encrypt, decrypt...
    time.sleep(20)
    print('[   Auth   ] Done')



def process_files(lst_file_name: list, counter: Counter):
    for file_name in lst_file_name:
        # Read file
        print('[ ReadFile ] Start', file_name)
        time.sleep(10)
        print('[ ReadFile ] Done ', file_name)

        with counter.cond:
            counter.value -= 1
            counter.cond.notify()

        # Write log into disk
        time.sleep(5)
        print('[ WriteLog ]')



def process_request():
    lst_file_name = [ 'foo.html', 'bar.json' ]
    counter = Counter(value=len(lst_file_name))

    # The server checks auth user while reading files, concurrently
    threading.Thread(target=process_files, args=(lst_file_name, counter)).start()
    check_auth_user()

    # The server waits for completion of loading files
    with counter.cond:
        while counter.value > 0:
            counter.cond.wait(10) # timeout = 10 seconds

    print('\nNow user is authorized and files are loaded')
    print('Do other tasks...\n')



process_request()
