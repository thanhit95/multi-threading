# ARTICLES AND LEARNING NOTES

## DESCRIPTION

Some articles and learning notes taken from my research.

&nbsp;

---

&nbsp;

## CONTENT

### VOLATILE VS ATOMIC

There are two important concepts in multithreading environment:

- Atomicity.
- Visibility.

The volatile keyword eradicates visibility problems, but it does not deal with atomicity.

Consider this snippet in a concurrent environment:

```code
boolean isStopped = false;

while (!isStopped) {
    // Do some kind of work
}
```

The idea here is that some thread could change the value of ```isStopped``` from false to true in order to indicate to the subsequent loop that it is time to stop looping.

Intuitively, there is no problem. Logically if another thread makes ```isStopped``` equal to true, then the loop must terminate. The reality is that the loop will likely never terminate even if another thread makes ```isStopped``` equal to true.

The reason for this is not intuitive, but consider that modern processors have multiple cores and that each core has multiple registers and multiple levels of cache memory that are **not accessible to other processors**. In other words, values that are cached in one processor's local memory are **not visisble** to threads executing on a different processor. Herein lies one of the central problems with concurrency: visibility.

The Java Memory Model makes no guarantees whatsoever about when changes that are made to a variable in one thread may become visible to other threads. In order to guarantee that updates are visisble as soon as they are made, you must synchronize.

The ```volatile``` keyword is a weak form of synchronization. While it does nothing for mutual exclusion or atomicity, it does provide a guarantee that changes made to a variable in one thread will become visible to other threads as soon as it is made. Because individual reads and writes to variables that are not 8-bytes are atomic in Java, declaring variables ```volatile``` provides an easy mechanism for providing visibility in situations where there are no other atomicity or mutual exclusion requirements.

&nbsp;

Take the following example:

```code
Thread A:
    i = i + 1

Thread B:
    i = 1000
```

No matter how you define ```i```, a different thread reading the value just when the above line is executed might get ```i```, or ```i + 1```, because the operation is not atomically. Explanation:

- Assume ```i = 0```
- Thread A reads ```i```, calculates ```i + 1```, which is ```1```
- Thread B sets ```i = 1000``` and returns
- Thread A now sets ```i``` to the result of the operation, which is ```i = 1```

Atomics like AtomicInteger ensure, that such operations happen atomically. So the above issue cannot happen, ```i``` would either be ```1000``` or ```1001``` once both threads are finished.

&nbsp;

Notably, an operation that requires more than one read/write, such as ```i++```, which is equivalent to ```i = i + 1```, which does one read and one write, **is not atomic**, since another thread may write to ```i``` between the read and the write.

The ```Atomic``` classes, like ```AtomicInteger``` and ```AtomicReference```, provide a wider variety of operations atomically, specifically including increment for ```AtomicInteger```.

&nbsp;

Volatile only ensures that the access is atomically, while Atomics ensure that the operation is atomically.

&nbsp;

References:

- <https://stackoverflow.com/questions/19744508/volatile-vs-atomic/19744523>

&nbsp; &nbsp;
