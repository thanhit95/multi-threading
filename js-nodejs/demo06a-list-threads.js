/*
LIST OF MULTIPLE THREADS
VERSION A: Using standard 'Worker' class
*/

import { Worker, isMainThread, workerData } from 'worker_threads';


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


const mainFunc = () => {
  try {

    const NUM_THREADS = 5;
    const lstTh = new Array(NUM_THREADS);

    for (let i = 0; i < NUM_THREADS; ++i) {
      lstTh[i] = new Worker(new URL(import.meta.url), { workerData: i });
    }

    console.log('Good bye');

  } catch (error) {
    console.error(error);
  }
};


if (isMainThread) {
  mainFunc();
} else {
  workerFunc();
}
