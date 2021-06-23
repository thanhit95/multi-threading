# NOTES OF DEMOS AND EXERCISES

## DESCRIPTION

This file contains descriptions/notes of demo and exercise in the repo.

---

## DEMOSTRATIONS

### DEMO 01 - HELLO

Hello multiple threading!!!

You learn how to create a thread, and how to join a thread.

&nbsp;

### DEMO 02 - PASSING ARGUMENTS

You learn how to pass arguments to a thread:

- Passing various data types of variables.
- Passing some special types (such as C++ references).

&nbsp;

### DEMO 03 - SLEEP

Making a thread sleep for a while.

&nbsp;

### DEMO 08 - DETACH

When a thread is created, one of its attributes defines whether it is joinable or detached. Only threads that are created as joinable can be joined. If a thread is created as detached, it can never be joined.

&nbsp;

### DEMO 11A - RACE CONDITION

A race condition or race hazard is the condition of an electronics, software, or other system where the system's substantive behavior is dependent on the sequence or timing of other uncontrollable events.

This program illustrates race condition: Each time you run the program, the results displayed are different.

&nbsp;

### DEMO 11B - DATA RACE

Data race specifically refers to the non-synchronized conflicting "memory accesses" (or actions, or operations) to the same memory location.

&nbsp;

### DEMO 11C - RACE CONDITION AND DATA RACE

Many people are confused about race condition and data race.

- There is a case that race condition appears without data race. That is demo A.
- There is also a case that data race appears without race condition. That is demo B.

Ususally, race condition happens together with data race. A race condition often occurs when two or more threads need to perform operations on the same memory area (data race) but the results of computations depends on the order in which these operations are performed.

Concurrent accesses to shared resources can lead to unexpected or erroneous behavior, so parts of the program where the shared resource is accessed need to be protected in ways that avoid the concurrent access. This protected section is the critical section or critical region.

&nbsp;

### DEMO 12 - MUTEX

Mutexes are used to prevent data inconsistencies due to race conditions.

Mutexes are used for serializing shared resources. Anytime a global resource is accessed by more than one thread the resource should have a Mutex associated with it.

One can apply a mutex to protect a segment of memory ("critical region") from other threads. Mutexes can be applied only to threads in a single process and do not work between processes as do semaphores.

&nbsp;

### DEMO 13 - DEADLOCK

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

### DEMO 15 - REENTRANT LOCK (RECURSIVE MUTEX)

The reason for using reentrant lock is to avoid a deadlock due to e.g. recursion.

A reentrant lock is a synchronization primitive that may be acquired multiple times by the same thread. Internally, it uses the concepts of "owning thread" and "recursion level" in addition to the locked/unlocked state used by primitive locks.

In the locked state, some thread owns the lock; in the unlocked state, no thread owns it.

&nbsp;

### DEMO 16 - BARRIER

In cases where you must wait for a number of tasks to be completed before an overall task can proceed, barrier synchronization can be used.

&nbsp;

### DEMO 17 - READ-WRITE LOCK

In many situations, data is read more often than it is modified or written. In these cases, you can allow threads to read concurrently while holding the lock and allow only one thread to hold the lock when data is modified. A multiple-reader single-writer lock (or read/write lock) does this.

A read/write lock is acquired either for reading or writing, and then is released. The thread that acquires the read-write lock must be the one that releases it.

&nbsp;

### DEMO 18A - SEMAPHORE

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

### DEMO 18B - SEMAPHORE

A car is manufactured at each stop on a conveyor belt in a car factory.

A car is constructed from thefollowing parts: chassis, tires. Thus there are 2 tasks in manufacturing a car. However, 4 tires cannot be added until the chassis is placed on the belt.

There are:

- 2 production lines (i.e. 2 threads) of making tires.
- 1 production line (i.e. 1 thread) of making chassis.

Write a program to illustrate this scenario.

---

## EXERCISES
