/*
FORCING A THREAD TO TERMINATE (i.e. killing the thread)
*/

import * as mylib from './mylib.js';
import { isMainThread, parentPort } from 'worker_threads';


//---------------------------------------------
//            WORKER THREAD SECTION
//---------------------------------------------


let workerThreadIsRunning = true;

const doTask = async () => {
  while (workerThreadIsRunning) {
    console.log('Running...');
    await mylib.sleep(2000);
  }
};

const onRecvMessage = msg => {
  if (msg === 'term') {
    workerThreadIsRunning = false;
  }
};

const workerFunc = async () => {
  try {
    parentPort.once('message', onRecvMessage);
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
    await mylib.sleep(6000);
    worker.postMessage('term');
    await prom;
    console.log('Worker thread is terminated');

  } catch (error) {
    console.error(error);
  }
};


if (isMainThread) {
  await mainFunc();
} else {
  await workerFunc();
}
