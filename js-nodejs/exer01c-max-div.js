/*
MAXIMUM NUMBER OF DIVISORS
*/

import * as mylib from './mylib.js';
import { Mutex } from './mylib_mutex.js';
import { isMainThread, workerData, parentPort } from 'worker_threads';


//---------------------------------------------
//            WORKER THREAD SECTION
//---------------------------------------------


const doTask = arg => {
  let resValue = 0;
  let resNumDiv = 0;

  for (let i = arg.iStart; i <= arg.iEnd; ++i) {
    let numDiv = 0;

    for (let j = i / 2; j > 0; --j)
        if (i % j == 0)
            ++numDiv;

    if (resNumDiv < numDiv) {
        resNumDiv = numDiv;
        resValue = i;
    }
  }

  parentPort.postMessage({ resValue, resNumDiv });
};

const workerFunc = () => {
  try {
    const arg = workerData;
    doTask(arg);
  } catch (error) {
    console.error(error);
  }
};


//---------------------------------------------
//             MAIN THREAD SECTION
//---------------------------------------------


const prepareArg = (rangeStart, rangeEnd, numThreads) => {
  let rangeA, rangeB, rangeBlock;

  rangeBlock = (rangeEnd - rangeStart + 1) / numThreads;
  rangeA = rangeStart;

  let lstWorkerArg = [];

  for (let i = 0; i < numThreads; ++i, rangeA += rangeBlock) {
      rangeB = rangeA + rangeBlock - 1;

      if (i == numThreads - 1)
          rangeB = rangeEnd;

      lstWorkerArg.push({ iStart: rangeA, iEnd: rangeB });
  }

  return lstWorkerArg;
};


const updateFinalResult = (mutex, finalRes, value, numDiv) => {
  // Should protect by a mutex?
  mutex.runExclusive(() => {
    if (finalRes.numDiv < numDiv) {
      finalRes.numDiv = numDiv;
      finalRes.value = value;
    }
  });
};


const mainFunc = async () => {
  try {

    const RANGE_START = 1;
    const RANGE_END = 100000;
    const NUM_THREADS = 8;

    const lstWorkerArg = prepareArg(RANGE_START, RANGE_END, NUM_THREADS);
    const finalRes = { value: 0, numDiv: 0 };

    const lstTh = new Array(NUM_THREADS);
    const mutex = new Mutex();

    const tpStart = process.hrtime();

    for (let i = 0; i < NUM_THREADS; ++i) {
      const arg = lstWorkerArg[i];
      const [worker, prom] = mylib.createThread(new URL(import.meta.url), arg);
      worker.on('message', res => updateFinalResult(mutex, finalRes, ...Object.values(res)));
      lstTh[i] = [worker, prom];
    }

    await Promise.all(lstTh.map(([_,pr]) => pr));
    const timeElapsed = mylib.hrtimeToNumber(process.hrtime(tpStart));

    console.log('The integer which has largest number of divisors is', finalRes.value);
    console.log('The largest number of divisor is', finalRes.numDiv);
    console.log('Time elapsed =', timeElapsed);

  } catch (error) {
    console.error(error);
  }
};


if (isMainThread) {
  await mainFunc();
} else {
  workerFunc();
}
