/*
MUTEXES
Version EX

Using a mutex to solve the problem.
*/

import * as mylib from './mylib.js';
import express from 'express';
import { Mutex } from 'async-mutex';


const createServer = () => {
  const users = new Map();
  const app = express();
  const mutex = new Mutex();

  const createUser = async (userid, username) => {
    if (!userid || !username) {
      return false;
    }
    if (users.has(userid)) {
      return false;
    }
    // Assume that creating user takes a little time
    await mylib.sleep(1000);
    users.set(userid, username);
    return true;
  };

  app.get('/register', async (req, res) => {
    const ret = await mutex.runExclusive(() => createUser(req.query.id, req.query.name));
    // const ret = await createUser(req.query.id, req.query.name);
    res.status(200).send(ret).end();
  });

  app.get('/', (req, res) => {
    const resStr = JSON.stringify(
      [...users].map(([k,v]) => ({ id: k, name: v }))
    , null, 2);
    res.status(200).setHeader('Content-Type', 'application/json');
    res.send(resStr).end();
  });

  const server = app.listen(8081);
  return server;
};


const runClient = async () => {
  const registerUrl1 = new URL('/register?id=teo&name=Tran Teo', 'http://localhost:8081');
  const registerUrl2 = new URL('/register?id=teo&name=Le Teo', 'http://localhost:8081');
  const infoUrl = new URL('/', 'http://localhost:8081');

  const prom1 = mylib.makeHttpGet(registerUrl1);
  await mylib.sleep(200);

  const prom2 = mylib.makeHttpGet(registerUrl2);
  await mylib.sleep(200);

  await Promise.all([prom1, prom2]);

  const result = await mylib.makeHttpGet(infoUrl);
  console.log(result);
};


const server = createServer();
await runClient();
server.close();
