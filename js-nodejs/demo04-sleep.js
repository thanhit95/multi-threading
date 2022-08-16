/*
SLEEP
*/

import * as mylib from './mylib.js';
import { isMainThread, workerData } from 'worker_threads';


//---------------------------------------------
//            WORKER THREAD SECTION
//---------------------------------------------


const doTask = async (name, timems) => {
  console.log(name, 'is sleeping');
  await mylib.sleep(timems);
  console.log(name, 'wakes up');
};

const workerFunc = async () => {
  try {
    await doTask(workerData.name, workerData.timems);
  } catch (error) {
    console.error(error);
  }
};


//---------------------------------------------
//             MAIN THREAD SECTION
//---------------------------------------------


const mainFunc = async () => {
  try {

    const [workerFoo, promFoo] = mylib.createThread(
      new URL(import.meta.url),
      { name: 'foo', timems: 3000 }
    );

    const [workerBar, promBar] = mylib.createThread(
      new URL(import.meta.url),
      { name: 'bar', timems: 2900 }
    );

    console.log('Created 2 worker threads');
    await Promise.all([promFoo, promBar]);
    console.log('Good bye');

  } catch (error) {
    console.error(error);
  }
};


if (isMainThread) {
  await mainFunc();
} else {
  await workerFunc();
}
