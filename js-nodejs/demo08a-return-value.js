/*
GETTING RETURNED VALUES FROM THREADS
*/

import * as mylib from './mylib.js';
import { isMainThread, workerData, parentPort } from 'worker_threads';


//---------------------------------------------
//            WORKER THREAD SECTION
//---------------------------------------------


const doubleValue = x => {
  return x * 2;
};

const squareValue = x => {
  return x * x;
};

const workerFunc = () => {
  try {
    const [command, inp] = workerData;
    let result;
    switch (command) {
      case 'double':
        result = doubleValue(inp);
        console.log({command, inp, result});
        break;
      case 'square':
        result = squareValue(inp);
        console.log({command, inp, result});
        break;
    }
  } catch (error) {
    console.error(error);
  }
};


//---------------------------------------------
//             MAIN THREAD SECTION
//---------------------------------------------


const mainFunc = () => {
  try {

    mylib.createThread(new URL(import.meta.url), ['double', 5]);
    mylib.createThread(new URL(import.meta.url), ['double', 80]);
    mylib.createThread(new URL(import.meta.url), ['square', 7]);

  } catch (error) {
    console.error(error);
  }
};


if (isMainThread) {
  mainFunc();
} else {
  workerFunc();
}
