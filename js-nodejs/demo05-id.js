/*
GETTING THREAD'S ID
*/

import * as mylib from './mylib.js';
import { isMainThread, workerData } from 'worker_threads';


//---------------------------------------------
//            WORKER THREAD SECTION
//---------------------------------------------


const doTask = async () => {
  await mylib.sleep(2000);
  console.log('Done');
};

const workerFunc = async () => {
  try {
    await doTask();
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
    const [worker2, prom2] = mylib.createThread(new URL(import.meta.url));
    console.log(worker.threadId, worker2.threadId);

  } catch (error) {
    console.error(error);
  }
};


if (isMainThread) {
  await mainFunc();
} else {
  await workerFunc();
}
