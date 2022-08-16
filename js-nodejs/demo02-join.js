/*
THREAD JOINS
*/

import * as mylib from './mylib.js';
import { isMainThread } from 'worker_threads';


//---------------------------------------------
//            WORKER THREAD SECTION
//---------------------------------------------


const doHeavyTask = async () => {
  // Do a heavy task, which takes a little time
  for (let i = 0; i < 2000000000; ++i);
  console.log('Done!');
};

const workerFunc = async () => {
  try {
    await doHeavyTask();
  } catch (error) {
    console.error(error);
  }
};


//---------------------------------------------
//             MAIN THREAD SECTION
//---------------------------------------------


const mainFunc = async () => {
  try {

    const [worker, prom] = mylib.createThread(new URL(import.meta.url));
    console.log('Begin creating worker thread...');
    await prom; // join worker thread (i.e. waiting for the thread completion)
    console.log('Good bye!');

  } catch (error) {
    console.error(error);
  }
};


if (isMainThread) {
  await mainFunc();
} else {
  await workerFunc();
}
