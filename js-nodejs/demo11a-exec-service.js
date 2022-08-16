/*
EXECUTOR SERVICES AND THREAD POOLS
*/

import { isMainThread } from 'worker_threads';
import { Piscina } from 'piscina';


//---------------------------------------------
//            WORKER THREAD SECTION
//---------------------------------------------


export const printMsg = () => {
  console.log('Hello Nodejs');
};

export const addTwoNumbers = ({a, b}) => {
  return a + b;
};


//---------------------------------------------
//             MAIN THREAD SECTION
//---------------------------------------------


const mainFunc = async () => {
  try {
    const execService = new Piscina({filename: new URL(import.meta.url).href});

    await execService.run(undefined, { name: 'printMsg'});

    const result = await execService.run({a: 1000, b: -400}, { name: 'addTwoNumbers'});
    console.log('Result is', result);

    await execService.destroy();

  } catch (error) {
    console.error(error);
  }
};


if (isMainThread) {
  await mainFunc();
}
