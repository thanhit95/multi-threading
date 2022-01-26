# MULTIPLE THREADING IN PRACTICE

## DESCRIPTION

This repo helps you to practise multithreading in a logical sequence, which is divided into several demonstrations.
Plus, you could apply your learning better by doing exercises.

The repo consists of two main sections:

- "demo" (demostrations).
- "exer" (exercises).

All the demos (and exers) are really simple, easy to understand, even for difficult terms.

If you find it helpful, please give me a star. Thank you.

&nbsp;

## AUTHOR & LICENSE

Author: Thanh Nguyen

- Email: thanh.it1995@gmail.com
- Facebook: <https://www.facebook.com/thanh.it95>

This repo is licensed under the [3-Clause BSD License](LICENSE.txt).

&nbsp;

## REPO STRUCTURE

- ```cpp-pthread```: C++ POSIX threading.
- ```cpp-std```: C++ std threading.
- ```csharp```: C# std threading.
- ```java```: Java threading.

&nbsp;

---

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

In fact, multithreading is extremely important in the current software industry. It lets you do concurrency. It solves asynchronous problems.

&nbsp;

If you want to explore more articles, read here: [notes-articles.md](notes-articles.md).

&nbsp;

Article references:

- [Oracle Documentation Home, Multithreaded Programming Guide, Chapter 1 Covering Multithreading Basics, Benefiting From Multithreading](https://docs.oracle.com/cd/E19455-01/806-5257/6je9h032d/index.html)
- [Oracle Documentation Home, JDK 1.1 for Solaris Developer's Guide, Chapter 2 Multithreading, Benefits of Multithreading](https://docs.oracle.com/cd/E19455-01/806-3461/6jck06gqj/index.html)

&nbsp;

---

&nbsp;

## REFERENCES

All general references in my repo.

Read here: [references.md](references.md).
