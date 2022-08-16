/*
INTRODUCTION TO MULTITHREADING
You should try running this app several times and see results.
*/

import * as mylib from './mylib.js';
import { Worker, isMainThread } from 'worker_threads';


const workerFunc = async () => {
  for (let i = 0; i < 300; ++i) {
    await mylib.sleep(1);
    process.stdout.write('B');
  }
};


const mainFunc = async () => {
  const worker = new Worker(new URL(import.meta.url));

  for (let i = 0; i < 300; ++i) {
    await mylib.sleep(1);
    process.stdout.write('A');
  }
};


if (isMainThread) {
  await mainFunc();
} else {
  await workerFunc();
}
