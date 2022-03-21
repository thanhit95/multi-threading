'''
THE DATA SERVER PROBLEM
Version D: Solving the problem using a blocking queue
'''

import time
import threading
from queue import Queue



def check_auth_user():
    print('[   Auth   ] Start')
    # Send request to authenticator, check permissions, encrypt, decrypt...
    time.sleep(20)
    print('[   Auth   ] Done')



def process_files(lst_file_name: list, blkq: Queue):
    for file_name in lst_file_name:
        # Read file
        print('[ ReadFile ] Start', file_name)
        time.sleep(10)
        print('[ ReadFile ] Done ', file_name)

        blkq.put(file_name) # You may put file data here

        # Write log into disk
        time.sleep(5)
        print('[ WriteLog ]')



def process_request():
    lst_file_name = [ 'foo.html', 'bar.json' ]
    blkq = Queue()

    # The server checks auth user while reading files, concurrently
    threading.Thread(target=process_files, args=(lst_file_name, blkq)).start()
    check_auth_user()

    # The server waits for completion of loading files
    for _ in range(len(lst_file_name)):
        blkq.get()

    print('\nNow user is authorized and files are loaded')
    print('Do other tasks...\n')



process_request()
