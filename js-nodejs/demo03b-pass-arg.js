/*
PASSING ARGUMENTS
*/

import * as mylib from './mylib.js';
import { isMainThread, workerData } from 'worker_threads';


//---------------------------------------------
//            WORKER THREAD SECTION
//---------------------------------------------


const doTask = input => {
  console.log('Input value is', input);
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

    const [worker, prom] = mylib.createThread(
      new URL(import.meta.url), 12345
    );

    const [worker2, prom2] = mylib.createThread(
      new URL(import.meta.url),
      {
          name: 'foo',
          types: [9, 0, 55]
      }
    );

    console.log('Created 2 worker threads');
    await Promise.all([prom, prom2]);
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
