/*
USERNAME HASH PROBLEM

Although the problem is solved in previous solution, the calculation speed keeps too slow.

Analyze the Hash Task and you realize that
this task can be divided into multiple individual sub tasks.
Each sub task is corresponding to hashing one chunk.

Hence, multithreading makes sense: Each thread does each sub task in parallel.
*/

import * as mylib from './mylib.js';
import { isMainThread, workerData, parentPort } from 'worker_threads';
import express from 'express';
import { getHash, splitStrInToChunks } from './exerex-userhash-util.js';


//---------------------------------------------
//            WORKER THREAD SECTION
//---------------------------------------------


export const workerFunc = () => {
  try {
    const [idx, chunk] = workerData;
    const chunkHash = getHash(2**21, chunk);
    parentPort.postMessage([idx, chunkHash]);
  } catch (error) {
    console.error(error);
  }
};


//---------------------------------------------
//             MAIN THREAD SECTION
//---------------------------------------------


const getSuperHashByMain = async (plainText) => {
  const numChunks = 8; // It is also the number of threads

  const lstChunks = splitStrInToChunks(numChunks, plainText);
  const lstHashes = new Array(numChunks);

  const lstWorkerProm = [];

  for (let i = 0; i < numChunks; ++i) {
    const chunk = lstChunks[i];
    const [worker, prom] = mylib.createThread(new URL(import.meta.url), [i, chunk]);
    worker.on('message', ([idx, chunkHash]) => lstHashes[idx] = chunkHash);
    lstWorkerProm.push(prom);
  }

  await Promise.all(lstWorkerProm);
  const finalHash = getHash(1, lstHashes.join(''));
  return finalHash;
};


const mainFunc = () => {
  const PORT = 8081;
  const app = express();
  const userNameHistory = [];

  app.get('/history', async (req, res) => {
    const html = userNameHistory.join('<br/>') || '&lt;Empty history&gt;';
    res.status(200).send(html).end();
  });

  app.get('/', async (req, res) => {
    const userName = req.query.name;
    if (!userName) {
      res.status(400).end();
      return;
    }
    userNameHistory.push(userName);

    const tpStart = process.hrtime();

    // GET USERNAME HASH
    const userNameHash = await getSuperHashByMain(userName);

    const timeElapsed = mylib.hrtimeToNumber(process.hrtime(tpStart));
    console.log(`userName = ${userName}; Time elapsed = ${timeElapsed}`);

    const html = userName + '<br/>' + userNameHash;
    res.status(200).setHeader('Content-Type', 'text/html').send(html).end();
  });

  console.log('Server is listening on port', PORT);
  const server = app.listen(PORT);
};


if (isMainThread) {
  try {
    mainFunc();
  } catch (error) {
    console.error(error);
  }
} else {
  workerFunc();
}
