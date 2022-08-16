/*
MAXIMUM NUMBER OF DIVISORS
*/


const hrtimeToNumber = hrtime => (hrtime[0] + (hrtime[1] / 1e9)).toFixed(6);


const mainFunc = () => {
  try {

    const RANGE_START = 1;
    const RANGE_END = 100000;

    let resValue = 0;
    let resNumDiv = 0;

    const tpStart = process.hrtime();

    for (let i = RANGE_START; i <= RANGE_END; ++i) {
      let numDiv = 0;

      for (let j = i / 2; j > 0; --j)
          if (i % j == 0)
              ++numDiv;

      if (resNumDiv < numDiv) {
          resNumDiv = numDiv;
          resValue = i;
      }
    }

    const timeElapsed = hrtimeToNumber(process.hrtime(tpStart));

    console.log('The integer which has largest number of divisors is', resValue);
    console.log('The largest number of divisor is', resNumDiv);
    console.log('Time elapsed =', timeElapsed);

  } catch (error) {
    console.error(error);
  }
};


mainFunc();
