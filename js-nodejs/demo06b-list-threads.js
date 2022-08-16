/*
LIST OF MULTIPLE THREADS
VERSION B: Using mylib.createThread
*/

import * as mylib from './mylib.js';
import { isMainThread, workerData } from 'worker_threads';


//---------------------------------------------
//            WORKER THREAD SECTION
//---------------------------------------------


const doTask = index => {
  console.log(index);
};

const workerFunc = () => {
  try {
    doTask(workerData);
  } catch (error) {
    console.error(error);
  }
};


//---------------------------------------------
//             MAIN THREAD SECTION
//---------------------------------------------


const mainFunc = async () => {
  try {

    const NUM_THREADS = 5;
    const lstTh = new Array(NUM_THREADS);

    for (let i = 0; i < NUM_THREADS; ++i) {
      lstTh[i] = mylib.createThread(new URL(import.meta.url), i);
    }

    await Promise.all(lstTh.map(([_,pr]) => pr));
    console.log('Good bye');

  } catch (error) {
    console.error(error);
  }
};


if (isMainThread) {
  await mainFunc();
} else {
  workerFunc();
}
