/******************************************************
*
* File name:    mylib_mutex.js
*
* Author:       Name:   Thanh Nguyen
*               Email:  thanh.it1995(at)gmail(dot)com
*
* License:      3-Clause BSD License
*
* Description:  The mutex implementation in Javascript ES2019
*
* Warning:      This mutex shall be used for truly-multithreading conditions (e.g. NodeJS Worker)
*
******************************************************/


export class Mutex {

  #sabuff;
  #sa;


  constructor(sharedArrayBuffer) {
    if (!sharedArrayBuffer) {
      this.#sabuff = new SharedArrayBuffer(Int32Array.BYTES_PER_ELEMENT);
    } else {
      Mutex.#requireValidStateSAB(sharedArrayBuffer);
      this.#sabuff = sharedArrayBuffer;
    }
    this.#sa = new Int32Array(this.#sabuff );
  }


  getSAB() {
    return this.#sabuff;
  }


  static #requireValidStateSAB(sharedArrayBuffer) {
    if (! sharedArrayBuffer ) {
      throw 'sharedArrayBuffer is null or undefined';
    }
    if (! (sharedArrayBuffer instanceof SharedArrayBuffer)) {
      throw 'Illegal type of sharedArrayBuffer';
    }
    if (sharedArrayBuffer.byteLength < Int32Array.BYTES_PER_ELEMENT) {
      throw `Illegal sharedArrayBuffer: byteLength=${sharedArrayBuffer.byteLength} < Int32Array.BYTES_PER_ELEMENT`;
    }
  }


  static #requireValidStateSA(sharedArray) {
    if (! sharedArray ) {
      throw 'sharedArray is null or undefined';
    }
    if (! (sharedArray instanceof Int32Array) ) {
      throw 'Illegal type of sharedArray';
    }
    if (sharedArray.byteLength < Int32Array.BYTES_PER_ELEMENT) {
      throw `Illegal sharedArray: byteLength=${sharedArray.byteLength} < Int32Array.BYTES_PER_ELEMENT`;
    }
    const sab = sharedArray.buffer;
    this.#requireValidStateSAB(sab);
  }


  #requireValidState() {
    Mutex.#requireValidStateSA(this.#sa);
  }


  acquire() {
    this.#requireValidState();

    while (true) {
      if (Atomics.load(this.#sa, 0) > 0) {
        while (Atomics.wait(this.#sa, 0, 0) !== 'ok');
      }

      let oldCounter = Atomics.add(this.#sa, 0, 1);
      if (oldCounter >= 1) {
        Atomics.sub(this.#sa, 0, 1);
        continue;
      }

      // Atomics.notify(this.#sa, 0, 1);
      return;
    }
  }


  release() {
    this.#requireValidState();

    if (Atomics.load(this.#sa, 0) > 0) {
      Atomics.sub(this.#sa, 0, 1);
    }
    Atomics.notify(this.#sa, 0, 1);
  }


  runExclusive(callbackFunc) {
    this.#requireValidState();

    if (typeof callbackFunc !== 'function') {
      throw 'Illegal type of callbackFunc';
    }
    let res = undefined;

    this.acquire();
    try {
      res = callbackFunc();
    } finally {
      this.release();
    }

    return res;
  }

}


//---------------------------------------------
//               TESTING AREA
//---------------------------------------------


// import { Worker, isMainThread, workerData } from 'worker_threads';


// const sleep = timems => new Promise(resolve => setTimeout(resolve, timems));


// const createThread = (filename, input_args) => {
//   const worker = new Worker(filename, { workerData: input_args });
//   const prom = new Promise((resolve, reject) => {
//     // worker.on('message', msg => resolve(msg));
//     worker.on('error', error => reject([worker, error]));
//     worker.on('exit', code => code !== 0 ? reject([worker, code]) : resolve(worker));
//   });
//   return [worker, prom];
// };


// const workerFunc = async () => {
//   try {
//     const [sab, msg] = workerData;
//     const mutex = new Mutex(sab);
//     await sleep(1000);
//     mutex.acquire();
//     // await sleep(20);
//     console.log(msg);
//     mutex.release();

//   } catch (error) {
//     console.error(error);
//   }
// };


// const mainFunc = async () => {
//   try {
//     const mutex = new Mutex();
//     const lstProm = [];

//     console.log('Begin creating worker thread...');
//     for (let i = 0; i < 200; ++i) {
//       const [worker, prom] = createThread(
//         new URL(import.meta.url),
//         [
//           mutex.getSAB(),
//           'foo' + i
//         ]);
//       lstProm.push(prom);
//     }

//     await Promise.all(lstProm);
//     console.log('Exit app');

//   } catch (error) {
//     console.error(error);
//   }
// };


// if (isMainThread) {
//   await mainFunc();
// } else {
//   await workerFunc();
// }
