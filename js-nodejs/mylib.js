import * as http from 'http';
import { Worker } from 'worker_threads';


export const sleep = timems => new Promise(resolve => setTimeout(resolve, timems));


export const createThread = (filename, input_args) => {
  const worker = new Worker(filename, { workerData: input_args });
  const prom = new Promise((resolve, reject) => {
    // worker.on('message', msg => resolve(msg));
    worker.on('error', error => reject([worker, error]));
    worker.on('exit', code => code !== 0 ? reject([worker, code]) : resolve(worker));
  });
  return [worker, prom];
};


export const makeHttpGet = requestUrl => new Promise((resolve, reject) => {
  const req = http.get(requestUrl, res => {
    let body = '';
    res.on('data', chunk => body += chunk);
    res.on('end', () => {
      resolve(body);
    });
    res.on('error', error => reject(error));
  });
  req.end();
});
