/*
DEADLOCK
Version B
*/

import * as mylib from './mylib.js';
import { Mutex } from './mylib_mutex.js';
import { isMainThread, workerData } from 'worker_threads';


//---------------------------------------------
//            WORKER THREAD SECTION
//---------------------------------------------


const foo = async (mutResourceA, mutResourceB) => {
  mutResourceA.acquire();

  console.log('foo acquired resource A');
  await mylib.sleep(2000);

  mutResourceB.acquire();
  console.log('foo acquired resource B');
  mutResourceB.release();

  mutResourceA.release();
};

const bar = async (mutResourceA, mutResourceB) => {
  mutResourceB.acquire();

  console.log('bar acquired resource B');
  await mylib.sleep(2000);

  mutResourceA.acquire();
  console.log('bar acquired resource A');
  mutResourceA.release();

  mutResourceB.release();
};

const workerFunc = async () => {
  try {
    const [action, mutexsabA, mutexsabB] = workerData;
    const mutResourceA = new Mutex(mutexsabA);
    const mutResourceB = new Mutex(mutexsabB);

    switch (action) {
      case 'foo':
        await foo(mutResourceA, mutResourceB);
        break;
      case 'bar':
        await bar(mutResourceA, mutResourceB);
        break;
    }
  } catch (error) {
    console.error(error);
  }
};


//---------------------------------------------
//             MAIN THREAD SECTION
//---------------------------------------------


const mainFunc = async () => {
  try {

    const mutResourceA = new Mutex();
    const mutResourceB = new Mutex();

    const [wkFoo, promFoo] = mylib.createThread(new URL(import.meta.url), [
      'foo', mutResourceA.getSAB(), mutResourceB.getSAB()
    ]);
    const [wkBar, promBar] = mylib.createThread(new URL(import.meta.url), [
      'bar', mutResourceA.getSAB(), mutResourceB.getSAB()
    ]);

    await Promise.all([promFoo, promBar]);

    console.log('You will never see this statement due to deadlock!');

  } catch (error) {
    console.error(error);
  }
};


if (isMainThread) {
  await mainFunc();
} else {
  await workerFunc();
}
