/*
PASSING ARGUMENTS
*/

import { isMainThread, Worker, workerData } from 'worker_threads';


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


const mainFunc = () => {
  try {

    const worker = new Worker(
      new URL(import.meta.url),
      {
        workerData: 12345
      }
    );

    const worker2 = new Worker(
      new URL(import.meta.url),
      {
        workerData: {
          name: 'foo',
          types: [9, 0, 55]
        }
      }
    );

  } catch (error) {
    console.error(error);
  }
};


if (isMainThread) {
  mainFunc();
} else {
  workerFunc();
}
