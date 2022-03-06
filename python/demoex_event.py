'''
EVENT OBJECTS
'''

import time
import threading



# Event to notify the speakers
ev = threading.Event()
running = True



def func_speaker(name: str):
    while True:
        ev.wait()

        if not running:
            return

        print(f'{name}: ring ring ring')



def func_clock():
    global running

    for i in range(89, -1, -1):
        minute = i // 60
        second = i % 60
        print(f'{minute:02d}:{second:02d}')

        if i % 30 == 0:
            ev.set()    # let speakers do speak 'ring ring ring'
            ev.clear()  # reset internal flag to reuse the event in the future

        time.sleep(0.2)

    running = False
    ev.set()



threading.Thread(target=func_speaker, args=('ham',)).start()
threading.Thread(target=func_speaker, args=('egg',)).start()
threading.Thread(target=func_clock).start()
