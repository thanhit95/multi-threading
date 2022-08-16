/*
RACE CONDITIONS AND DATA RACES
*/

import * as mylib from './mylib.js';
import { isMainThread, workerData } from 'worker_threads';


//---------------------------------------------
//            WORKER THREAD SECTION
//---------------------------------------------


const increaseCounter = async bufArr => {
  await mylib.sleep(1000);
  for (let i = 0; i < 1000; ++i) {
    // increase counter by one
    ++bufArr[0];
  }
};

const workerFunc = async () => {
  try {
    await increaseCounter(workerData);
  } catch (error) {
    console.error(error);
  }
};


//---------------------------------------------
//             MAIN THREAD SECTION
//---------------------------------------------


const mainFunc = async () => {
  try {

    const bufArr = new Int32Array(new SharedArrayBuffer(Int32Array.BYTES_PER_ELEMENT));
    // counter is the first element of bufArr

    const NUM_THREADS = 16;
    const lstTh = new Array(NUM_THREADS);

    for (let i = 0; i < NUM_THREADS; ++i) {
      lstTh[i] = mylib.createThread(new URL(import.meta.url), bufArr);
    }

    await Promise.all(lstTh.map(([_,pr]) => pr));

    console.log('counter =', bufArr[0]);
    // We are NOT sure that counter = 16000

  } catch (error) {
    console.error(error);
  }
};


if (isMainThread) {
  await mainFunc();
} else {
  await workerFunc();
}
