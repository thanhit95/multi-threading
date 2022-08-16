/*
MUTEXES
*/

import * as mylib from './mylib.js';
import { Mutex } from './mylib_mutex.js';
import { isMainThread, workerData } from 'worker_threads';


//---------------------------------------------
//            WORKER THREAD SECTION
//---------------------------------------------


const increaseCounter = async (bufArr, mutex) => {
  await mylib.sleep(1000);

  mutex.acquire();

  try {
    for (let i = 0; i < 1000; ++i) {
      // increase counter by one
      ++bufArr[0];
    }
  } finally {

    mutex.release();

  }

  // or...
  // mutex.runExclusive(() => {
  //   for (let i = 0; i < 1000; ++i) {
  //     // increase counter by one
  //     ++bufArr[0];
  //   }
  // });
};

const workerFunc = async () => {
  try {
    const [bufArr, mutexsab] = workerData;
    const mutex = new Mutex(mutexsab);
    await increaseCounter(bufArr, mutex);
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
    const bufArr = new Int32Array(new SharedArrayBuffer(Int32Array.BYTES_PER_ELEMENT));
    // counter is the first element of bufArr

    const NUM_THREADS = 16;
    const lstTh = new Array(NUM_THREADS);

    for (let i = 0; i < NUM_THREADS; ++i) {
      lstTh[i] = mylib.createThread(new URL(import.meta.url), [
        bufArr, mutex.getSAB()
      ]);
    }

    await Promise.all(lstTh.map(([_,pr]) => pr));

    console.log('counter =', bufArr[0]);
    // We are sure that counter = 16000

  } catch (error) {
    console.error(error);
  }
};


if (isMainThread) {
  await mainFunc();
} else {
  await workerFunc();
}
