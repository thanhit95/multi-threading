/*
HELLO WORLD VERSION MULTITHREADING
Version B: Using the individual source code files:
- Main thread: demo01b-hello.js
- Worker thread: demo01b-hello-worker.js
*/

import * as path from 'path';
import { Worker, isMainThread } from 'worker_threads';

const workerFn = `./${path.parse(import.meta.url).name}-worker.js`;
const worker = new Worker(workerFn);

console.log('Hello from main thread');
