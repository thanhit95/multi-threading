# C++ MULTITHREADING

## DESCRIPTION

Multithreading in C++.

&nbsp;

## PROJECT STRUCTURE

| Directory name | Description           |
| -------------- | --------------------- |
| `cpp-std`      | C++20 std threading   |
| `cpp-pthread`  | C++11 POSIX threading |
| `cpp-boost`    | C++98 Boost threading |

&nbsp;

## COMPILATION

Ensure that your compiler meets the C++ standard as mentioned above.

### gcc compiler

To compile with specified C++ standard, use option `-std`:

- C++98: `g++ -o exec_filename filename.cpp -std=c++98`
- C++11: `g++ -o exec_filename filename.cpp -std=c++11`
- C++20: `g++ -o exec_filename filename.cpp -std=c++20`

Usually in Linux/Unix environments, we shall use POSIX threading. This leads to linking objects with pthread by option `-lpthread`.

Additionally, if you use Boost:

- Use option `-lboost_thread` for all code.
- Use option `-lboost_chrono` for the code using boost::chrono.

&nbsp;

Example 1:

```shell
# Compile
g++ -o output_exe demo00.cpp -lpthread -std=c++20

# Run
./output_exe
```

Example 2 for lib Boost:

```shell
# Compile
g++ -o output_exe demo04a-sleep.cpp -lpthread -lboost_thread -lboost_chrono

# Run
./output_exe
```

&nbsp;

### Other compilers and/or environments

You may consider a suitable IDE/compiler (e.g. Microsoft Visual Studio, mingw...).
