/*
DATA RACES
Version 01: Without multithreading
*/

const getResult = N => {
  const a = new Int8Array(N + 1).fill(0);
  for (let i = 1; i <= N; ++i) {
    if (i % 2 === 0 || i % 3 === 0)
      a[i] = 1;
  }
  const result = a.reduce((x, y) => x + y, 0);
  return result;
};


const mainFunc = () => {
  const N = 1024;
  const result = getResult(N);
  console.log('Number of integers that are divisible by 2 or 3 is:', result);
};


mainFunc();
