/*
USERNAME HASH PROBLEM

Each time users send request to hash, threads are created.
Creation of threads is not cheap.
By using Execution Service/Thread Pool, threads can be reused for next tasks.
*/

import * as mylib from './mylib.js';
import { isMainThread } from 'worker_threads';
import { Piscina } from 'piscina';
import express from 'express';
import { getHash, splitStrInToChunks } from './exerex-userhash-util.js';


//---------------------------------------------
//            WORKER THREAD SECTION
//---------------------------------------------


export const workerFunc = ({idx, chunk}) => {
  try {
    const chunkHash = getHash(2**21, chunk);
    return chunkHash;
  } catch (error) {
    console.error(error);
  }
};


//---------------------------------------------
//             MAIN THREAD SECTION
//---------------------------------------------


const getSuperHashByMain = async (execService, plainText) => {
  const numChunks = 8; // It is also the number of threads

  const lstChunks = splitStrInToChunks(numChunks, plainText);
  const lstWorkerProm = [];

  for (let i = 0; i < numChunks; ++i) {
    const chunk = lstChunks[i];
    lstWorkerProm.push(execService.run({ idx: i, chunk: chunk }, { name: 'workerFunc' }));
  }

  const lstHashes = await Promise.all(lstWorkerProm);
  const finalHash = getHash(1, lstHashes.join(''));
  return finalHash;
};


const mainFunc = () => {
  const PORT = 8081;
  const app = express();
  const userNameHistory = [];

  const execService = new Piscina({
    filename: new URL(import.meta.url).href,
    minThreads: 8,
    maxThreads: 8
  });

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
    const userNameHash = await getSuperHashByMain(execService, userName);

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
}
