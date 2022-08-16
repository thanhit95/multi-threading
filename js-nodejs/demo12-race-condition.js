/*
RACE CONDITIONS
*/

import * as mylib from './mylib.js';
import { isMainThread, workerData } from 'worker_threads';


//---------------------------------------------
//            WORKER THREAD SECTION
//---------------------------------------------


const doTask = async index => {
  await mylib.sleep(1000);
  console.log(index);
};

const workerFunc = async () => {
  try {
    await doTask(workerData);
  } catch (error) {
    console.error(error);
  }
};


//---------------------------------------------
//             MAIN THREAD SECTION
//---------------------------------------------


const mainFunc = () => {
  try {

    const NUM_THREADS = 4;
    const lstTh = new Array(NUM_THREADS);

    for (let i = 0; i < NUM_THREADS; ++i) {
      lstTh[i] = mylib.createThread(new URL(import.meta.url), i);
    }

  } catch (error) {
    console.error(error);
  }
};


if (isMainThread) {
  mainFunc();
} else {
  await workerFunc();
}
