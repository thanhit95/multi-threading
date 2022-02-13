# NOTES OF DEMOS AND EXERCISES

## DESCRIPTION

This file contains descriptions/notes of demo and exercise in the repo.

&nbsp;

## TABLE OF CONTENTS

I am sorry that generated table of contents contains too many uppercase stuff...

- [NOTES OF DEMOS AND EXERCISES](#notes-of-demos-and-exercises)
  - [DESCRIPTION](#description)
  - [TABLE OF CONTENTS](#table-of-contents)
  - [DEMOSTRATIONS](#demostrations)
    - [DEMO 00 - INTRODUCTION TO MULTITHREADING](#demo-00---introduction-to-multithreading)
    - [DEMO 01 - HELLO](#demo-01---hello)
    - [DEMO 02 - THREAD JOINS](#demo-02---thread-joins)
    - [DEMO 03 - PASSING ARGUMENTS](#demo-03---passing-arguments)
    - [DEMO 04 - SLEEP](#demo-04---sleep)
    - [DEMO 05 - GETTING THREAD'S ID](#demo-05---getting-threads-id)
    - [DEMO 06 - LIST OF MULTIPLE THREADS](#demo-06---list-of-multiple-threads)
    - [DEMO 07 - FORCING A THREAD TO TERMINATE](#demo-07---forcing-a-thread-to-terminate)
    - [DEMO 08 - GETTING RETURNED VALUES FROM THREADS](#demo-08---getting-returned-values-from-threads)
    - [DEMO 09 - THREAD DETACHING](#demo-09---thread-detaching)
    - [DEMO 10 - THREAD YIELDING](#demo-10---thread-yielding)
    - [DEMO 11 - THREAD POOLS](#demo-11---thread-pools)
    - [DEMO 12A - RACE CONDITIONS](#demo-12a---race-conditions)
    - [DEMO 12B - DATA RACES](#demo-12b---data-races)
    - [DEMO 12C - RACE CONDITIONS AND DATA RACES](#demo-12c---race-conditions-and-data-races)
    - [IMPORTANT NOTES](#important-notes)
    - [DEMO 13 - MUTEXES](#demo-13---mutexes)
    - [DEMO 14 - SYNCHRONIZED BLOCKS](#demo-14---synchronized-blocks)
    - [DEMO 15 - DEADLOCK](#demo-15---deadlock)
      - [Version A](#version-a)
      - [Version B](#version-b)
    - [DEMO 16 - MONITORS](#demo-16---monitors)
    - [DEMO 17 - REENTRANT LOCKS (RECURSIVE MUTEXES)](#demo-17---reentrant-locks-recursive-mutexes)
    - [DEMO 18 - BARRIERS AND LATCHES](#demo-18---barriers-and-latches)
    - [DEMO 19 - READ-WRITE LOCKS](#demo-19---read-write-locks)
    - [DEMO 20A - SEMAPHORES](#demo-20a---semaphores)
      - [Version A01](#version-a01)
      - [Version A02](#version-a02)
      - [Version A03](#version-a03)
    - [DEMO 20B - SEMAPHORES](#demo-20b---semaphores)
    - [DEMO 21 - CONDITION VARIABLES](#demo-21---condition-variables)
    - [DEMO 22 - BLOCKING QUEUES](#demo-22---blocking-queues)
    - [DEMO 23 - THREAD-LOCAL STORAGE](#demo-23---thread-local-storage)
    - [DEMO 24 & 25 - THE VOLATILE KEYWORD AND ATOMIC ACCESS](#demo-24--25---the-volatile-keyword-and-atomic-access)
  - [EXERCISES](#exercises)
    - [EX01 - MAXIMUM NUMBER OF DIVISORS](#ex01---maximum-number-of-divisors)
      - [Version A](#version-a-1)
      - [Version B](#version-b-1)
      - [Version C](#version-c)
    - [EX02 - THE PRODUCER-CONSUMER PROBLEM](#ex02---the-producer-consumer-problem)
    - [EX03 - THE READERS-WRITERS PROBLEM](#ex03---the-readers-writers-problem)
      - [Problem statement](#problem-statement)
      - [Problem variations](#problem-variations)
        - [Second readers-writers problem](#second-readers-writers-problem)
        - [Third readers-writers problem](#third-readers-writers-problem)
    - [EX04 - THE DINING PHILOSOPHERS PROBLEM](#ex04---the-dining-philosophers-problem)
      - [Problem statement](#problem-statement-1)
      - [Solution](#solution)
    - [EX05 - MATRIX PRODUCTION](#ex05---matrix-production)
      - [Version A: Matrix-vector multiplication](#version-a-matrix-vector-multiplication)
      - [Version B: Matrix-matrix production (dot product)](#version-b-matrix-matrix-production-dot-product)
    - [EX06 - BLOCKING QUEUE IMPLEMENTATION](#ex06---blocking-queue-implementation)
    - [EX07 - THREAD POOL & EXECUTOR SERVICE IMPLEMENTATION](#ex07---thread-pool--executor-service-implementation)

&nbsp;

---

&nbsp;

## DEMOSTRATIONS

### DEMO 00 - INTRODUCTION TO MULTITHREADING

Just run the code several times and see results: The results are not the same!!!

This is because threads execute concurrently. The operating system shall care the order of thread execution. Depend on current state, the coressponding result varies.

&nbsp;

### DEMO 01 - HELLO

You learn how to create a thread. That's all.

&nbsp;

### DEMO 02 - THREAD JOINS

When I say: "Thread X waits for thread Y to join". It means thread X shall wait for thread Y to complete, then thread X continues its execution.

&nbsp;

### DEMO 03 - PASSING ARGUMENTS

You learn how to pass arguments to a thread:

- Passing various data types of variables.
- Passing some special types (such as C++ references).

&nbsp;

### DEMO 04 - SLEEP

Making a thread sleep for a while.

Note that thread sleep is:

- Useful, when you want to wait for something to be ready.
- Awful, when performance is important, you may waste a lot of resources while thread is asleep.

&nbsp;

### DEMO 05 - GETTING THREAD'S ID

Each thread has its own identification. This demo helps you learn how to get the thread's id.

&nbsp;

### DEMO 06 - LIST OF MULTIPLE THREADS

Handling a list of multiple threads.

Be careful when you pass arguments to threads due to variable reference mechanism. In C/C++ you can forget this warning because variables are usually passed by values.

For an example:

```code
function doTask(i) {

}

for (int i = 0; i < 3; ++i) {
    th = new Thread(doTask(i));
    th.start();
}
```

There is only one variable `i` and its reference is passed into thread `th`. In the end, all 3 threads will receive `i = 3` as the parameter.

How to solve this problem? Just create new variables.

```code
function doTask(i) {

}

for (int i = 0; i < 3; ++i) {
    arg = i;
    th = new Thread(doTask(arg));
    th.start();
}
```

&nbsp;

### DEMO 07 - FORCING A THREAD TO TERMINATE

Forcing a thread to terminate aka. "killing the thread".

Sometimes, we want to force a thread to terminate (for convenient).

However, to be careful, the thread should terminate by itself, not by external factors. Assume that a thread is using resource or locking a mutex, and then it is suddenly killed by external factors, so the harmful results are:

- Resource may not be disposed/freed.
- Mutex is not unlocked, which is strongly possible to leads to the deadlock.

&nbsp;

### DEMO 08 - GETTING RETURNED VALUES FROM THREADS

You learn how to return value from a thread, and how to use that value for future tasks.

Please note that if you do not use a synchronization mechanism (e.g. thread join, mutex...) then the result may be incorrect. To be clear, let's see this:

```code
result = 0;

function doTask() {
  do something for a while;
  result = 9;
}

th = new Thread(doTask);
th.start();
print(result);
```

We are not sure that result printed is `9`, because at the time `print(result)` executes, `th` does not complete yet (`result = 9` are not executed).

So, we need to wait for `th` to complete before printing the result.

```code
result = 0;

function doTask() {
  do something for a while;
  result = 9;
}

th = new Thread(doTask);
th.start();
th.join(); // wait for th to complete to make sure result is set
print(result);
```

&nbsp;

### DEMO 09 - THREAD DETACHING

When a thread is created, one of its attributes defines whether it is joinable or detached. Only threads that are created as joinable can be joined. If a thread is created as detached, it can never be joined.

&nbsp;

### DEMO 10 - THREAD YIELDING

Yield is an action that occurs in a computer program during multithreading, of forcing a processor to relinquish control of the current running thread, and sending it to the end of the running queue, of the same scheduling priority.

&nbsp;

### DEMO 11 - THREAD POOLS

You learn how to use thread pool and how thread pool works.

A thread pool is a software design pattern for achieving concurrency of execution in a computer program. Often also called a replicated workers or worker-crew model, a thread pool maintains multiple threads waiting for tasks to be allocated for concurrent execution by the supervising program. By maintaining a pool of threads, the model increases performance and avoids latency in execution due to frequent creation and destruction of threads for short-lived tasks.

&nbsp;

### DEMO 12A - RACE CONDITIONS

A race condition or race hazard is the condition of an electronics, software, or other system where the system's substantive behavior is dependent on the sequence or timing of other uncontrollable events.

This program illustrates race condition: Each time you run the program, the results displayed are different.

&nbsp;

### DEMO 12B - DATA RACES

Data race specifically refers to the non-synchronized conflicting "memory accesses" (or actions, or operations) to the same memory location.

I use a problem statement for illustration: From range [ 1..N ], count numbers of integers which are divisible by 2 or by 3.

For an example of N = 8, the integers that match the requirements are 2, 3, 6 and 8. Hence, the result is four numbers.

Of course, you can easily solve the problem by a single loop. However, we need to go deeper. There is another solution using "marking array".

- Let `a` be array of boolean values. Initialize all elements in `a` by `false`.
- For `i` in range `1` to `N`, if `i` is divisible by `2` or by `3`, then assign `a[i] = true`.
- Finally, the result is now counting number of `true` in `a`.

With `N = 8`, `a[2], a[3], a[4], a[6], a[8]` are marked by `true`.

&nbsp;

About the source code, there are two versions:

- Version 01 uses traditional single threading to let you get started.

- Version 02 uses multithreading.
  - Thread `markDiv2` will mark `true` for all numbers divisible by 2.
  - Thread `markDiv3` will mark `true` for all numbers divisible by 3.
  - **The rule of threading tell us that `a[6]` might be accessed by both threads at the same time ==> DATA RACE**. However, in the end, `a[6] = true` is obvious, so the final result is still correct ==> not race condition.

&nbsp;

### DEMO 12C - RACE CONDITIONS AND DATA RACES

Many people are confused about race conditions and data races.

- There is a case that race condition appears without data race. That is demo version A.
- There is also a case that data race appears without race condition. That is demo version B.

*Small note: Looking from a deeper perspective, demo version A still causes data race (that is... output console terminal, hahaha).*

Ususally, race condition happens together with data race. A race condition often occurs when two or more threads need to perform operations on the same memory area (data race) but the results of computations depends on the order in which these operations are performed.

Concurrent accesses to shared resources can lead to unexpected or erroneous behavior, so parts of the program where the shared resource is accessed need to be protected in ways that avoid the concurrent access. This protected section is the **critical section** or **critical region**.

&nbsp;
&nbsp;

### IMPORTANT NOTES

&nbsp;

Race conditions (and data races) are essential contents when you learn multithreading. How to solve race conditions? There are several techniques, which are divided into two types: synchronization and non-synchronization.

|             | SYNCHRONIZATION | NON-SYNCHRONIZATION |
| ----------- | --------------- | ------------------- |
| Description | To block threads until a condition is satisfy | Not to block threads |
| Other names | Blocking | Non-blocking, lock-free |
| Techniques  | Mutex, synchronized block, semaphore, condition variable, barrier and latch | Atomic, thread-local storage |
| Pros        | - To give you in-depth controls<br>- To cooperate among threads | - Your app may improve performance<br>- You may avoid deadlock |
| Cons        | - Hard to control in complex synchronization<br>- May be dangerous (when deadlock appears) | Usually too simple |

&nbsp;

In practical:

- We mostly use mutexes, synchronized blocks and atomic operations.
- We usually combine sync and non-sync techniques.

&nbsp;

`------------------ End of important notes ------------------`

&nbsp;
&nbsp;

### DEMO 13 - MUTEXES

Mutexes are used to prevent data inconsistencies due to race conditions.

Mutexes are used for serializing shared resources. Anytime a global resource is accessed by more than one thread the resource should have a Mutex associated with it.

One can apply a mutex to protect a segment of memory ("critical region") from other threads. Mutexes can be applied only to threads in a single process and do not work between processes as do semaphores.

&nbsp;

### DEMO 14 - SYNCHRONIZED BLOCKS

Synchronized blocks are the blocks of code which prevent executions of multiple threads, that means only one thread can execute a synchronized block at a time although multiple threads are running this block. A synchronized block can be made by using a mutex:

- Lock the mutex at the begin of the block.
- Unlock the mutex at the end of the block.

In some programming languages, synchronized blocks are supported by default, such as Java and C#.

&nbsp;

### DEMO 15 - DEADLOCK

#### Version A

A simple demo of deadlock: Forgetting to release mutex.

&nbsp;

#### Version B

There are 2 workers "foo" and "bar".

They try to access resource A and B (which are protected by mutResourceA and mutResourceB).

Scenario:

```text
foo():
    synchronized:
        access resource A

        synchronized:
            access resource B

bar():
    synchronized:
        access resource B

        synchronized:
            access resource A
```

After foo accessing A and bar accessing B, foo and bar might wait other together ==> Deadlock occurs.

&nbsp;

### DEMO 16 - MONITORS

Monitor: Concurrent programming meets object-oriented programming.

- When concurrent programming became a big deal, object-oriented programming too.
- People started to think about ways to make concurrent programming more structured.

A monitor is a thread-safe class, object, or module that wraps around a mutex in order to safely allow access to a method or variable by more than one thread.

&nbsp;

### DEMO 17 - REENTRANT LOCKS (RECURSIVE MUTEXES)

The reason for using reentrant lock is to avoid a deadlock due to e.g. recursion.

A reentrant lock is a synchronization primitive that may be acquired multiple times by the same thread. Internally, it uses the concepts of "owning thread" and "recursion level" in addition to the locked/unlocked state used by primitive locks.

In the locked state, some thread owns the lock; in the unlocked state, no thread owns it.

&nbsp;

### DEMO 18 - BARRIERS AND LATCHES

In cases where you must wait for a number of tasks to be completed before an overall task can proceed, barrier synchronization can be used.

There are two types of barriers:

- Cyclic barrier: A general, *reusable barrier*.
- Count down latch: There is no possibility to increase or reset the counter, which makes the latch a *single-use barrier*.

&nbsp;

### DEMO 19 - READ-WRITE LOCKS

In many situations, data is read more often than it is modified or written. In these cases, you can allow threads to read concurrently while holding the lock and allow only one thread to hold the lock when data is modified. A multiple-reader single-writer lock (or read-write lock) does this.

A read-write lock is acquired either for reading or writing, and then is released. The thread that acquires the read-write lock must be the one that releases it.

&nbsp;

### DEMO 20A - SEMAPHORES

#### Version A01

In an exam, each candidate is given a couple of 2 scratch papers. Write a program to illustrate this scenario.

The program will combine 2 scratch papers into one test package, concurrenly.

&nbsp;

#### Version A02

The problem in version 01 is:

- When "makeOnePaper" produces too fast, there are a lot of pending papers...

This version 02 solves the problem:

- Use a semaphore to restrict "makeOnePaper": Only make papers when a package is finished.

&nbsp;

#### Version A03

The problem in this version is DEADLOCK, due to a mistake of semaphore synchronization.

&nbsp;

### DEMO 20B - SEMAPHORES

A car is manufactured at each stop on a conveyor belt in a car factory.

A car is constructed from thefollowing parts: chassis, tires. Thus there are 2 tasks in manufacturing a car. However, 4 tires cannot be added until the chassis is placed on the belt.

There are:

- 2 production lines (i.e. 2 threads) of making tires.
- 1 production line (i.e. 1 thread) of making chassis.

Write a program to illustrate this scenario.

&nbsp;

### DEMO 21 - CONDITION VARIABLES

Condition variables are synchronization primitives that enable threads to wait until a particular condition occurs. Condition variables are user-mode objects that cannot be shared across processes.

&nbsp;

### DEMO 22 - BLOCKING QUEUES

A blocking queue is a queue that blocks when you:

- try to dequeue from it and the queue is empty, or...
- try to enqueue items to it and the queue is already full.

There is a special type of the blocking queue, that is "synchronous queue". A synchronous queue is a blocking queue with capacity = 0 (i.e. it does not store any value at all).

&nbsp;

### DEMO 23 - THREAD-LOCAL STORAGE

In some cases, shared resources could be used individually for each thread. Every thread has its own copy of the shared resources. Therefore, race condition disappears.

```text
BEFORE:
            X = 8          (X is shared resource)
              |
    ---------------------
    |         |         |
    v         v         v
 ThreadA   ThreadB   ThreadC


AFTER:
    ---------------------
    |         |         |
    v         v         v
 ThreadA   ThreadB   ThreadC
  X = 8     X = 8     X = 8
```

Thread-local storage helps you to **avoid synchronization**, because synchronization might be dangerous and hard to handle.

Application of thread-local storage:

- Counter: Each thread does its own counting job. In the end, we can sum all the counters in threads.

- Security: The random function often use an initialization seed. When multiple threads calling the random function, results may be the same for some threads. This may lead to security issues. Using synchronization of course solve this problem, but it is too overhead. In this case, using thread-local storage is great. Each thread use an individual random function, which has a different random seed.

In the demo code, by using thread-local storage, each thread has its own counter. So, the counter in one thread is completely independent of each other.

&nbsp;

### DEMO 24 & 25 - THE VOLATILE KEYWORD AND ATOMIC ACCESS

Please read article "Volatile vs Atomic" in [notes-articles.md](notes-articles.md) for better understanding.

&nbsp;

---

&nbsp;

## EXERCISES

### EX01 - MAXIMUM NUMBER OF DIVISORS

Problem statement: Find the integer in the range 1 to 100000 that has the largest number of divisors.

&nbsp;

#### Version A

The solution without multithreading.

&nbsp;

#### Version B

This source code file contains the solution using multithreading.

There are 2 phases:

- Phase 1:
  - Each worker finds result on a specific range.
  - This phase uses multiple threads.

- Phase 2:
  - Based on multiple results from workers, main function gets the final result with maximum numDiv.
  - This phase uses a single thread (i.e. main function).

&nbsp;

#### Version C

The difference between version C and version B is:

- Each worker finds result on a specific range, and then updates final result itself.
- So, main function does nothing.

&nbsp;

### EX02 - THE PRODUCER-CONSUMER PROBLEM

The producer–consumer problem (also known as the bounded-buffer problem) is a classic example of a multi-process synchronization problem. The first version of which was proposed by Edsger W. Dijkstra in 1965.

In the producer-consumer problem, there is one producer that is producing something and there is one consumer that is consuming the products produced by the producer. The producers and consumers share the same memory buffer that is of fixed-size.

The job of the producer is to generate the data, put it into the buffer, and again start generating data. While the job of the consumer is to consume the data from the buffer.

In the later formulation of the problem, Dijkstra proposed multiple producers and consumers sharing a finite collection of buffers.

**What are the problems here?**

- The producer and consumer should not access the buffer at the same time.

- The producer should produce data only when the buffer is not full.
  - If the buffer is full, then the producer shouldn't be allowed to put any data into the buffer.

- The consumer should consume data only when the buffer is not empty.
  - If the buffer is empty, then the consumer shouldn't be allowed to take any data from the buffer.

&nbsp;

### EX03 - THE READERS-WRITERS PROBLEM

#### Problem statement

Consider a situation where we have a file shared between many people.

If one of the people tries editing the file, no other person should be reading or writing at the same time, otherwise changes will not be visible to him/her. However if some person is reading the file, then others may read it at the same time.

Precisely in Computer Science we call this situation as the readers-writers problem.

**What are the problems here?**

- One set of data is shared among a number of processes.
- Once a writer is ready, it performs its write. Only one writer may write at a time.
- If a process is writing, no other process can read it.
- If at least one reader is reading, no other process can write.

&nbsp;

#### Problem variations

##### Second readers-writers problem

The first solution is suboptimal, because it is possible that a reader R1 might have the lock, a writer W be waiting for the lock, and then a reader R2 requests access.

It would be unfair for R2 to jump in immediately, ahead of W; if that happened often enough, W would STARVE. Instead, W should start as soon as possible.

This is the motivation for the second readers–writers problem, in which the constraint is added that no writer, once added to the queue, shall be kept waiting longer than absolutely necessary. This is also called writers-preference.

##### Third readers-writers problem

In fact, the solutions implied by both problem statements can result in starvation - the first one may starve writers in the queue, and the second one may starve readers.

Therefore, the third readers–writers problem is sometimes proposed, which adds the constraint that no thread shall be allowed to starve; that is, the operation of obtaining a lock on the shared data will always terminate in a bounded amount of time.

Solution:

- The idea is using a semaphore "serviceQueue" to preserve ordering of requests (signaling must be FIFO).

&nbsp;

### EX04 - THE DINING PHILOSOPHERS PROBLEM

#### Problem statement

The dining philosophers problem states that there are 5 philosophers sharing a circular table and they eat and think alternatively. There is a bowl of rice for each of the philosophers and 5 chopsticks.

A philosopher needs both their right and left chopstick to eat.

A hungry philosopher may only eat if there are both chopsticks available.

Otherwise a philosopher puts down their chopstick and begin thinking again.

&nbsp;

#### Solution

A solution of the dining philosophers problem is to use a semaphore to represent a chopstick.

A chopstick can be picked up by executing a wait operation on the semaphore and released by executing a signal semaphore.

The structure of a random philosopher ```i``` is given as follows:

```pseudocode
while true do
    wait( chopstick[i] );
    wait( chopstick[ (i+1) % 5] );

    EATING THE RICE

    signal( chopstick[i] );
    signal( chopstick[ (i+1) % 5] );

    THINKING
```

**What are the problems here?**

- Deadlock.
- Starvation.

The above solution makes sure that no two neighboring philosophers can eat at the same time. But this solution can lead to a deadlock. This may happen if all the philosophers pick their left chopstick simultaneously. Then none of them can eat and deadlock occurs.

Some of the ways to avoid deadlock are as follows:

- An even philosopher should pick the right chopstick and then the left chopstick while an odd philosopher should pick the left chopstick and then the right chopstick.
- A philosopher should only be allowed to pick their chopstick if both are available at the same time.

&nbsp;

### EX05 - MATRIX PRODUCTION

#### Version A: Matrix-vector multiplication

For an example:

Matrix A:

```text
|   1   2   3   |
|   4   5   6   |
|   7   8   9   |
```

Vector b:

```text
|   3   |
|   -1  |
|   0   |
```

The multiplication of A and b is the vector:

```text
|   1   |
|   7   |
|   13  |
```

**Solution:**

- Separate matrix A into list of rows.
- For each row, calculate scalar product with vector b.
- We can process each row individually. Therefore multithreading will get the job done.

&nbsp;

#### Version B: Matrix-matrix production (dot product)

For an example:

Matrix A:

```text
|   1   3   5   |
|   2   4   6   |
```

Matrix B:

```text
|   1   0   1   0   |
|   0   1   0   1   |
|   1   0   0   -2  |
```

The result of dot(A, B) is the matrix:

```text
|   6   3   1   -7  |
|   8   4   2   -8  |
```

&nbsp;

### EX06 - BLOCKING QUEUE IMPLEMENTATION

Blocking queues strongly relate to the producer-consumer problem:

- The `enqueue` method is corresponding to the `produce` action, which creates an object and push it into the rear of the queue.
- The `dequeue` method is corresponding to the `consume` action, which removes an object from the front of the queue.

There are many methods to implement the producer-consumer problem and this is similar to implementation of the blocking queues.

&nbsp;

### EX07 - THREAD POOL & EXECUTOR SERVICE IMPLEMENTATION

To implement a thread pool, you need to focus on the worker function (the function that is executed by threads in the pool). For an idle thread:

1. Pick a task (a job) in the queue.
2. Do the task.

Step 1 requires synchronization (by a blocking queue, a queue with mutex/synchronized block/condition variable...).

It looks simple, but if we need to expand features for our thread pool, things start to get complicated. You may take care of synchronization everywhere:

- When a task is dequeued.
- When a task is done.
- When all tasks are done.
- When users want to shutdown thread pool.
- ...
