/*
DEADLOCK
Version EX
*/

import * as mylib from './mylib.js';
import express from 'express';
import { Mutex } from 'async-mutex';


const createServer = () => {
  const app = express();
  const mutex = new Mutex();

  const doTask = async name => {
    const release = await mutex.acquire();
    try {
      console.log(`Server: ${name} acquired resource`);
    } finally {
      // release(); // Forget this statement ==> deadlock
    }
  };

  app.get('/', async (req, res) => {
    const name = req.query.name;
    await doTask(name);
    res.status(200).setHeader('Content-Type', 'text/html');
    res.send(name).end();
  });

  const server = app.listen(8081);
  return server;
};


const runClient = async () => {
  const respFoo = await mylib.makeHttpGet(new URL('http://localhost:8081/?name=foo'));
  console.log(`Client: response: ${respFoo}`);

  const respBar = await mylib.makeHttpGet(new URL('http://localhost:8081/?name=bar'));

  console.log('You will never see this statement due to deadlock!');

  console.log(`Client: response: ${respBar}`);
};


const server = createServer();
await runClient();
server.close();
