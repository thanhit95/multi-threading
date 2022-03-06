'''
THE DINING PHILOSOPHERS PROBLEM
'''

import time
import threading



def do_task_philosopher(chstk: list, n_philo: int, id_philo: int):
    time.sleep(1)

    with chstk[id_philo]:
        with chstk[(id_philo + 1) % n_philo]:
            print(f'Philosopher #{id_philo} is eating the rice')



NUM_PHILOSOPHERS = 5
chopstick = [threading.Lock() for _ in range(NUM_PHILOSOPHERS)]

for i in range(NUM_PHILOSOPHERS):
    threading.Thread(target=do_task_philosopher, args=(chopstick, NUM_PHILOSOPHERS, i)).start()
