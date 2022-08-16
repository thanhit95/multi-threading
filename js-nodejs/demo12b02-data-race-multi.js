/*
DATA RACES
Version 02: Multithreading
*/

import * as mylib from './mylib.js';
import { isMainThread, workerData } from 'worker_threads';


//---------------------------------------------
//            WORKER THREAD SECTION
//---------------------------------------------


const markDiv2 = (a, N) => {
  for (let i = 2; i <= N; i += 2) {
    a[i] = 1;
  }
};

const markDiv3 = (a, N) => {
  for (let i = 3; i <= N; i += 3) {
    a[i] = 1;
  }
};

const workerFunc = () => {
  try {
    const [action, a, N] = workerData;
    switch (action) {
      case 'markDiv2':
        markDiv2(a, N);
        break;
      case 'markDiv3':
        markDiv3(a, N);
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

    const N = 1024;
    const a = new Int8Array(new SharedArrayBuffer((N + 1) * Int8Array.BYTES_PER_ELEMENT));

    const [wkr2, prom2] = mylib.createThread(new URL(import.meta.url), [
      'markDiv2', a, N
    ]);
    const [wkr3, prom3] = mylib.createThread(new URL(import.meta.url), [
      'markDiv3', a, N
    ]);

    await Promise.all([prom2, prom3]);

    const result = a.reduce((x, y) => x + y, 0);
    console.log('Number of integers that are divisible by 2 or 3 is:', result);

  } catch (error) {
    console.error(error);
  }
};


if (isMainThread) {
  await mainFunc();
} else {
  workerFunc();
}
