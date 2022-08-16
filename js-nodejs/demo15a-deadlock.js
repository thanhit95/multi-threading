/*
DEADLOCK
Version A
*/

import * as mylib from './mylib.js';
import { Mutex } from './mylib_mutex.js';
import { isMainThread, workerData } from 'worker_threads';


//---------------------------------------------
//            WORKER THREAD SECTION
//---------------------------------------------


const doTask = async (name, mutex) => {
  mutex.acquire();

  console.log(name, 'acquired resource');

  // mutex.release(); // Forget this statement ==> deadlock
};

const workerFunc = async () => {
  try {
    const [name, mutexsab] = workerData;
    const mutex = new Mutex(mutexsab);
    doTask(name, mutex);
  } catch (error) {
    console.error(error);
  }
};


//---------------------------------------------
//             MAIN THREAD SECTION
//---------------------------------------------


const mainFunc = async () => {
  try {

    const mutex = new Mutex();

    const [wkFoo, promFoo] = mylib.createThread(new URL(import.meta.url), [
      'foo', mutex.getSAB()
    ]);
    const [wkBar, promBar] = mylib.createThread(new URL(import.meta.url), [
      'bar', mutex.getSAB()
    ]);

    await Promise.all([promFoo, promBar]);

    console.log('You will never see this statement due to deadlock!');

  } catch (error) {
    console.error(error);
  }
};


if (isMainThread) {
  await mainFunc();
} else {
  await workerFunc();
}
