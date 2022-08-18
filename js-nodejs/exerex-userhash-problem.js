/*
USERNAME HASH PROBLEM

This is an app using expressJS framework to serve "The Username Hash Service". The app provides 2 APIs:

GET /?name=<UserName>
  Returns the <UserName> and the hashed value from <UserName>

GET /history
  Returns request history. Each <UserName> is in one line.

The Hash Task is consider CPU consuming. You should wait for a long time to get result (may upto 24 seconds).

Now, let's get started:
- Run the app. Open the web browser and visit http://localhost:8081/?name=JohnnyTeo
- While waiting for result, try visiting http://localhost:8081/history
  Notice that /history is blocked until completion of hash result calculation.

The reason is Javascript by default runs in a single thread.
This thread is busy calculating hash result from request /?name=JohnnyTeo
so it cannot serve the next request /history

Your task is making /history "non-blocking" i.e. app can serve /history while doing hashing job.

P/S: The problem idea is inspired by a great article at:
https://www.digitalocean.com/community/tutorials/how-to-use-multithreading-in-node-js
*/

import * as mylib from './mylib.js';
import express from 'express';
import { getHash, splitStrInToChunks } from './exerex-userhash-util.js';


const PORT = 8081;
const app = express();


const getSuperHash = plainText => {
  const numChunks = 8;
  const lstChunks = splitStrInToChunks(numChunks, plainText);
  const lstHashes = lstChunks.map(chunk => getHash(2**21, chunk));
  const finalHash = getHash(1, lstHashes.join(''));
  return finalHash;
};


const userNameHistory = [];


app.get('/history', async (req, res) => {
  const html = userNameHistory.join('<br/>') || '&lt;Empty history&gt;';
  res.status(200).send(html).end();
});


app.get('/', (req, res) => {
  const userName = req.query.name;
  if (!userName) {
    res.status(400).end();
    return;
  }
  userNameHistory.push(userName);

  const tpStart = process.hrtime();

  // GET USERNAME HASH
  const userNameHash = getSuperHash(userName);

  const timeElapsed = mylib.hrtimeToNumber(process.hrtime(tpStart));
  console.log(`userName = ${userName}; Time elapsed = ${timeElapsed}`);

  const html = userName + '<br/>' + userNameHash;
  res.status(200).setHeader('Content-Type', 'text/html').send(html).end();
});


console.log('Server is listening on port', PORT);
const server = app.listen(PORT);
