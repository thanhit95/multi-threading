'''
GETTING RETURNED VALUES FROM THREADS
'''

import threading



def double_value(value):
    return value * 2



res = {}

th_foo = threading.Thread( target=lambda: res.update({ 'foo': double_value(5) }) )
th_bar = threading.Thread( target=lambda: res.update({ 'bar': double_value(80) }) )

th_foo.start()
th_bar.start()

# Wait until th_foo and th_far finish
th_foo.join()
th_bar.join()

print(res['foo'])
print(res['bar'])
