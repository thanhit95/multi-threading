/*
EXECUTOR SERVICES AND THREAD POOLS
*/

import * as mylib from './mylib.js';
import { isMainThread } from 'worker_threads';
import { Piscina } from 'piscina';


//---------------------------------------------
//            WORKER THREAD SECTION
//---------------------------------------------


export const doTask = async ({index}) => {
  const id = String.fromCharCode(65 + index);
  console.log(`Task ${id} is starting`);
  await mylib.sleep(3000);
  console.log(`Task ${id} is completed`);
};


//---------------------------------------------
//             MAIN THREAD SECTION
//---------------------------------------------


const mainFunc = async () => {
  try {
    const NUM_THREADS = 2;
    const NUM_TASKS = 5;
    const lstPromRes = [];

    const execService = new Piscina({
      filename: new URL(import.meta.url).href,
      minThreads: NUM_THREADS,
      maxThreads: NUM_THREADS
    });

    for (let i = 0; i < NUM_TASKS; ++i) {
      lstPromRes.push(execService.run({ index: i }, { name: 'doTask'}));
    }
    console.log('All tasks are submitted');

    await Promise.all(lstPromRes);
    console.log('All tasks are completed');

    await execService.destroy();

  } catch (error) {
    console.error(error);
  }
};


if (isMainThread) {
  await mainFunc();
}
