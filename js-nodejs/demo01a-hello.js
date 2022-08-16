/*
HELLO WORLD VERSION MULTITHREADING
Version A: Using the same source code file for both main thread and worker thread
*/

import { Worker, isMainThread } from 'worker_threads';


//---------------------------------------------
//            WORKER THREAD SECTION
//---------------------------------------------
const workerFunc = () => {
  console.log('Hello from example thread');
};


//---------------------------------------------
//             MAIN THREAD SECTION
//---------------------------------------------
const mainFunc = () => {
  const worker = new Worker(new URL(import.meta.url));
  console.log('Hello from main thread');
};


if (isMainThread) {
  // If this is main thread then execute mainFunc()
  mainFunc();
} else {
  // If this is worker thread then execute workerFunc()
  workerFunc();
}
