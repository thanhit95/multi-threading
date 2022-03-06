'''
GETTING THREAD'S ID
'''

import time
import threading



def do_task():
    time.sleep(1)
    tid = threading.get_ident()
    tid_native = threading.get_native_id()
    print('id of current thread:', tid)
    print('native id of current thread from operating system:', tid_native)



th_foo = threading.Thread(target=do_task)
th_bar = threading.Thread(target=do_task)

th_foo.start()
th_bar.start()

print("foo's id:", th_foo.ident)
print("foo's native id:", th_foo.native_id)
print("bar's id:", th_bar.ident)
print("bar's native id:", th_bar.native_id)
