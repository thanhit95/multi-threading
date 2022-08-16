/*
ATOMIC ACCESS
*/

import * as mylib from './mylib.js';
import { isMainThread, workerData } from 'worker_threads';


//---------------------------------------------
//            WORKER THREAD SECTION
//---------------------------------------------


const updateArr = async (arr) => {
  await mylib.sleep(1000);

  for (let i = 0; i < 1000; ++i) {
    // increase arr[0] by one atomically
    Atomics.add(arr, 0, 1);

    // decrease arr[4] by five atomically
    Atomics.sub(arr, 4, 5);
  }
};

const workerFunc = async () => {
  try {
    const sharedArr = workerData;
    const arr = new Int32Array(sharedArr);
    await updateArr(arr);
  } catch (error) {
    console.error(error);
  }
};


//---------------------------------------------
//             MAIN THREAD SECTION
//---------------------------------------------


const mainFunc = async () => {
  try {

    // bufArr is an array of which max length = 5
    // Its element is bufArr[0], bufArr[1], ... bufArr[4]
    const ARR_MAX_SIZE = 5;
    const sharedArr = new SharedArrayBuffer(Int32Array.BYTES_PER_ELEMENT * ARR_MAX_SIZE);
    const arr = new Int32Array(sharedArr);

    const NUM_THREADS = 16;
    const lstTh = new Array(NUM_THREADS);

    for (let i = 0; i < NUM_THREADS; ++i) {
      lstTh[i] = mylib.createThread(new URL(import.meta.url),
        sharedArr
      );
    }

    await Promise.all(lstTh.map(([_,pr]) => pr));

    console.log('The result:');
    console.log(arr);

  } catch (error) {
    console.error(error);
  }
};


if (isMainThread) {
  await mainFunc();
} else {
  await workerFunc();
}
