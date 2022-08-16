# MULTIPLE THREADING IN PRACTICE

## DESCRIPTION

This repo helps you to practise multithreading in a logical sequence, which is divided into several demonstrations.
Plus, you could apply your learning better by doing exercises.

The repo consists of two main sections:

- "demo" (demostrations).
- "exer" (exercises).

All the demos (and exers) are really simple, easy to understand, even for difficult terms.

If you find it helpful, please give my repo a star. Thank you.

&nbsp;

## AUTHOR & LICENSE

Author: Thanh Nguyen

- Email: thanh.it1995@gmail.com
- Facebook: <https://www.facebook.com/thanh.it95>

This repo is licensed under the [3-Clause BSD License](LICENSE.txt).

&nbsp;

## LANGUAGES SUPPORTED

| Directory name | Description                  |
| -------------- | ---------------------------- |
| `cpp-std`      | C++20 std threading          |
| `cpp-pthread`  | C++11 POSIX threading        |
| `cpp-boost`    | C++98 Boost threading        |
| `csharp`       | C# 7.3 with Dot Net 6        |
| `java`         | Java JDK 17                  |
| `python`       | Python 3.10                  |
| `js-nodejs`    | Javascript ES2019/Nodejs 18  |

Special notes for C++ demos/exers: Please read the specified `readme.md` in corresponding directory.

&nbsp;

## THE NOTES AND ARTICLES

The notes and articles are the additional resources for the source code, which guides you for better research, step by step. You may consider it the comment/description at the beginning of the source code.

```text
  ORIGINAL SOURCE CODE FILE                  SOURCE CODE FILE              NOTES AND ARTICLES
------------------------------        ------------------------------     ----------------------
|                            |        |                            |     |                    |
| /* THE COMMENTS... */      |        |                            |     |    THE COMMENTS    |
|                            |        |                            |     |                    |
| #include <iostream>        |        | #include <iostream>        |     |                    |
| using namespace std;       |        | using namespace std;       |     |                    |
|                            |  ===>  |                            |  +  |                    |
| int main() {               |        | int main() {               |     |                    |
|   cout << "Hello thread";  |        |   cout << "Hello thread";  |     |                    |
|   return 0;                |        |   return 0;                |     |                    |
| }                          |        | }                          |     |                    |
|                            |        |                            |     |                    |
------------------------------        ------------------------------     ----------------------
```

There are 2 notes:

- [notes-demos-exercises.md](notes-demos-exercises.md): The notes that go along with original source code.
- [notes-articles.md](notes-articles.md): Extra helpful notes during my research.

&nbsp;

**For your best result, I strongly recommend that you read [notes-demos-exercises.md](notes-demos-exercises.md) while enjoying source code (demos and exercises).**

&nbsp;

## ROADMAP FOR THE LEARNERS

This is the roadmap for you, which is composed and researched carefully with all my heart. You should learn in the sequence listed below.

**If you just want to learn the basis to understand the taste of multithreading:**

- Demo: hello, join, pass arg, sleep, list-threads, race-condition, mutex, synchronized-block.
- Exer: max-div.

**If you are oriented to be a Software Developer:**

- Demo: hello, join, pass arg, sleep, list-threads, terminate, return-value, exec-service, race-condition, mutex, synchronized-block, deadlock, blocking-queue, atomic.
- Exer: max-div, producer-consumer, product-matrix, data-server.

**If you really want to do an in-depth research:** Learn all!!!

&nbsp;

---

## INTRODUCTION TO MULTITHREADING

### GETTING STARTED

Bob sends four messages to Alice: `I love`, `you`, `not`, `her`.

Surprisingly, Alice receives `I love`, `her`, `not`, `you` (That means "I love her not you"). So sad!

```text
TRADITIONAL (ONE THREAD)

    ===========================================> Time

                 Main thread
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~>
      "I love"   "you"   "not"   "her"



MULTITHREADING (FOUR THREADS)

    ===========================================> Time

    ~~~~~~~~~~~~>
      "I love"

                      ~~~~~~~~~~~~>
                          "you"

              ~~~~~~~~~~~~>
                  "not"

        ~~~~~~~~~~~~>
            "her"
```

If you use multithreading or something similar, the context above is truly possible. The reason is that multithreading allows four messages to be sent in parallel, so message order is changed unpredictably when they come to Alice.

In a traditional simple app, there is only one thread (the "main thread"). If you apply multithreading then your app may have multiple threads (including the "main thread").

By learning multithreading:

- You get closer to the operating system.
- You can understand various terms: concurrency, parallel, asynchronous, synchronization.
- You have additional knowledge to learn asynchronous programming and parallel programming.

So, why multithreading?

### WHY MULTITHREADING

Multithreaded programs can improve performance compared to traditional simple programs (which use only a single thread).

Multithreading is used as an underlying technique in various fields:

- Web browsers (Chrome, Edge, Firefox...).
- Web servers.
- Graphic editors (Adobe Photoshop, Corel Draw...).
- Computer games.
- Database management systems.
- Networking programming.
- Video encoders.
- And more...

Benefits of multithreading:

- Improving application responsiveness.
  - Any program in which many activities are not dependent upon each other can be redesigned so that each activity is defined as a thread. For example, the user of a multithreaded GUI does not have to wait for one activity to complete before starting another.

- Using multiprocessors efficiently.
  - Typically, applications that express concurrency requirements with threads need not take into account the number of available processors. The performance of the application improves transparently with additional processors.
  - Numerical algorithms and applications with a high degree of parallelism, such as matrix multiplications, can run much faster when implemented with threads on a multiprocessor.

- Improving throughput.
  - Many concurrent compute operations and I/O requests within a single process.

- Program structure simplification.
  - Threads can be used to simplify the structure of complex applications, such as server-class and multimedia applications. Simple routines can be written for each activity, making complex programs easier to design and code, and more adaptive to a wide variation in user demands.

- Using fewer system resources.
  - Threads impose minimal impact on system resources. Threads require less overhead to create, maintain, and manage than a traditional process.

- Better communication.
  - Thread synchronization functions can be used to provide enhanced process-to-process communication.
  - In addition, sharing large amounts of data through separate threads of execution within the same address space provides extremely high-bandwidth, low-latency communication between separate tasks within an application.

&nbsp;

If you want to explore more articles, read here: [notes-articles.md](notes-articles.md).

&nbsp;

Article references:

- [Oracle Documentation Home, Multithreaded Programming Guide, Chapter 1 Covering Multithreading Basics, Benefiting From Multithreading](https://docs.oracle.com/cd/E19455-01/806-5257/6je9h032d/index.html)
- [Oracle Documentation Home, JDK 1.1 for Solaris Developer's Guide, Chapter 2 Multithreading, Benefits of Multithreading](https://docs.oracle.com/cd/E19455-01/806-3461/6jck06gqj/index.html)

&nbsp;

---

## REFERENCES

All general references in my repo.

Read here: [references.md](references.md).
