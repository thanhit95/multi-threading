/*
GETTING RETURNED VALUES FROM THREADS
*/

import * as mylib from './mylib.js';
import { isMainThread, parentPort } from 'worker_threads';


//---------------------------------------------
//            WORKER THREAD SECTION
//---------------------------------------------


const doubleValue = x => {
  return x * 2;
};

const squareValue = x => {
  return x * x;
};

const onRecvMessage = message => {
  const [command, inp] = message;
  let result;
  switch (command) {
    case 'double':
      result = doubleValue(inp);
      parentPort.postMessage({command, inp, result});
      break;
    case 'square':
      result = squareValue(inp);
      parentPort.postMessage({command, inp, result});
      break;
    case 'exit':
      parentPort.unref();
      // parentPort.close();
  }
};

const workerFunc = () => {
  try {
    parentPort.on('message', onRecvMessage);
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
    worker.on('message', console.log);
    worker.postMessage(['double', 5]);
    worker.postMessage(['double', 80]);
    worker.postMessage(['square', 7]);
    worker.postMessage(['exit']);
    await prom;

  } catch (error) {
    console.error(error);
  }
};


if (isMainThread) {
  await mainFunc();
} else {
  workerFunc();
}
