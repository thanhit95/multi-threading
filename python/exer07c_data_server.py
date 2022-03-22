'''
THE DATA SERVER PROBLEM
Version C: Solving the problem using a count-down latch
'''

import time
import threading
from mylib_latch import CountDownLatch



def check_auth_user():
    print('[   Auth   ] Start')
    # Send request to authenticator, check permissions, encrypt, decrypt...
    time.sleep(20)
    print('[   Auth   ] Done')



def process_files(lst_file_name: list[str], latch: CountDownLatch):
    for file_name in lst_file_name:
        # Read file
        print('[ ReadFile ] Start', file_name)
        time.sleep(10)
        print('[ ReadFile ] Done ', file_name)

        latch.count_down()

        # Write log into disk
        time.sleep(5)
        print('[ WriteLog ]')



def process_request():
    lst_file_name = [ 'foo.html', 'bar.json' ]
    latch = CountDownLatch(len(lst_file_name))

    # The server checks auth user while reading files, concurrently
    threading.Thread(target=process_files, args=(lst_file_name, latch)).start()
    check_auth_user()

    # The server waits for completion of loading files
    latch.wait()

    print('\nNow user is authorized and files are loaded')
    print('Do other tasks...\n')



process_request()
