/*
USERNAME HASH PROBLEM

To make /history "non-blocking", run app in 2 threads:
- The main thread: Serves I/O HTTP requests
- The worker thread: Does the Hash Task

When users visit http://localhost:8081/?name=JohnnyTeo,
the app delegates the Hash Task to the worker thread so it can serve the next requests.

The worker thread receives and does the Hash Task and returns result to main thread.
*/

import * as mylib from './mylib.js';
import { isMainThread, workerData, parentPort } from 'worker_threads';
import express from 'express';
import { getHash, splitStrInToChunks } from './exerex-userhash-util.js';


//---------------------------------------------
//            WORKER THREAD SECTION
//---------------------------------------------


const getSuperHashByWorker = plainText => {
  const numChunks = 8;
  const lstChunks = splitStrInToChunks(numChunks, plainText);
  const lstHashes = lstChunks.map(chunk => getHash(2**21, chunk));
  const finalHash = getHash(1, lstHashes.join(''));
  return finalHash;
};


const workerFunc = () => {
  try {
    const plainText = workerData;
    const hash = getSuperHashByWorker(plainText);
    parentPort.postMessage(hash);
  } catch (error) {
    console.error(error);
  }
};


//---------------------------------------------
//             MAIN THREAD SECTION
//---------------------------------------------


const getSuperHashByMain = async plainText => {
  let finalHash = '';
  const [worker, prom] = mylib.createThread(new URL(import.meta.url), plainText);
  worker.on('message', hash => finalHash = hash);
  await prom;
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
