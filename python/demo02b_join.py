'''
THREAD JOINS
'''

import threading



th_foo = threading.Thread(target=lambda:print('foo'))
th_bar = threading.Thread(target=lambda:print('bar'))

th_foo.start()
th_bar.start()

# th_foo.join()
# th_bar.join()

'''
We do not need to call th_foo.join() and th_bar.join().
The reason is main thread will wait for the completion of all threads before app exits.
'''
