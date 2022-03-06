'''
GETTING RETURNED VALUES FROM THREADS
'''

import threading



def double_value(result: dict, name: str, value):
    result[name] = value * 2



res = {}

th_foo = threading.Thread( target=double_value, args=(res, 'foo', 5) )
th_bar = threading.Thread( target=double_value, args=(res, 'bar', 80) )

th_foo.start()
th_bar.start()

# Wait until th_foo and th_far finish
th_foo.join()
th_bar.join()

print(res['foo'])
print(res['bar'])
