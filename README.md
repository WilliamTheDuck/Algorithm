# **Algorithm**

> _This repository comprises a couple of stuff you will need in order to learn **Design and Analysis of Algorithm**: functions used to operate and evaluate algorithms, measure time and space complexity, and demonstrate classical algorithmic paradigms. Each section includes example .c files to illustrate both implementation and theoretical insights.._

#

### ***Complexity Of An Algorithm***
---
> _This chapter focuses on analyzing the efficiency of algorithms in terms of time and space. You’ll learn how to compute the asymptotic behavior using Big-O, Ω (Omega), and Θ (Theta) notations. Example programs show how to measure runtime experimentally and compare algorithm growth rates (e.g., O(n), O(n log n), O(2ⁿ))._

Topics included:

+ Asymptotic Analysis

+ Worst / Average / Best Case

+ Empirical Time Measurement

+ Growth Function Comparison

### ***Sorting***
---
> _This section introduces various sorting algorithms, analyzed by their performance and design strategies. Each .c file includes both implementation and complexity discussion for every algorithm._

**[1] Elementary Sorts**

+ Selection Sort
  
+ Insertion Sort

+ Bubble Sort

**[2] Efficient Sorts**

+ Merge Sort
  
+ Quick Sort
  
+ Heap Sort

**[3] Non-comparison Sorts**

+ Counting Sort
  
+ Radix Sort
  
+ Bucket Sort

### ***Designing Algorithm Techniques***
---
> _This chapter focuses on the core paradigms used in algorithm design, helping you learn how to approach new problems systematically. Each paradigm is implemented through practical examples and problem demonstrations._

**[1] Divide and Conquer**

+ Merge Sort
  
+ Binary Search
  
+ Closest Pair of Points

**[2] Greedy Approach**

+ Activity Selection

+ Huffman Coding
  
+ Minimum Spanning Tree

**[3] Dynamic Programming** 

+ Knapsack

+ Matrix Chain Multiplication

+ LCS

**[4] Backtracking**

+ N-Queens

+ Subset Generation

+ Hamiltonian Cycle

**[5] Branch and Bound**

+ Travelling Salesman Problem (TSP)

+ Job Scheduling

#

### ***Installation And Customization Library Guide***
---

> _To install and use my static library in your MSYS2/MinGW environment, follow these steps._

- Copy the header file (`DataStructure.h`) and place it into the global include directory:  
```
C:\msys64\ucrt64\include
```

- Copy the compile static library (`libdatastructure.a`) and place it into the global library directory:  
```
C:\msys64\ucrt64\lib
```

- Usage in your project: Include the header as if it were a system library:  
```c
#include <DataStructure.h>
```

- When compiling, link against the static library by adding `-ldatastructure`: The prefix lib and the suffix .a are omitted when using the -l option. For example, `-ldatastructure` links against `libdatastructure.a`. Notice that you also need to replace your own file names `main.c` and `main.exe` accordingly.
```shell
gcc main.c -ldatastructure -o main.exe
```
- Or we could insert `-ldatastructure` before the `-o` in `args`-`tasks.json` (in `.vscode` folder). In that way, we simply push `f5` to debug without inserting the line above into the terminal.
```json
"args": [
        "-fdiagnostics-color=always",
        "-g",
        "${file}",
        "-ldatastructure",
        "-o",
        "${fileDirname}\\${fileBasenameNoExtension}.exe"
      ],
```
> _You can also customize these files as you prefer. Here are the steps you can follow to recreate your own static library._

- First, make your own `.c` file with  definitions (implementations) of functions. For instance:
```c
#include <stdio.h>
#include <string.h>
#include "DataStructure.h"

/* ================== LIST ================== */
void init_list(List* pL)
{
    pL->size = 0;
}
void append_list(List* pL, int x)
{
    pL->size++;
    pL->data[pL->size] = x;
}
```
- Worthy noticing that you also need to have this line in the `.c` file.
```c
#include "DataStructure.h"
```
- After that, we make a header file with the same name of the `DataStructure.c` file (`DataStructure.h`). This header file will include the declarations of mentioned functions in the `.c` file.
```c
#ifndef DATA_STRUCTURE_SETUP_H
#define DATA_STRUCTURE_SETUP_H

#define MAX 200

/* ================== LIST ================== */
typedef struct
{
    int data[MAX];
    int size;
} List;

void init_list(List* pL); // Initializes pL->size to 0
void append_list(List* pL, int x);

#endif /* DATA_STRUCTURE_SETUP_H */
```
- `#ifndef` means _"if not defined"_ and `#endif` stands for _"end if"_. A primary use of `#ifndef` is to prevent multiple inclusions of header files, a technique called _"header guarding"_. 

- The next step is making an object `.o` file of `.c` file (you should name it the same). Change the directory containing your `.c` file in shell to use the below command. 
```shell
cd <"Your directory containing the .c file">
gcc -c -Wall -g <Your file name>.c -o <Your file name>.o
```
- Last but not least, make a static library with this command. Name your library `lib<Name>.a`.
```shell
ar rcs <lib___>.a <Object file>.o
```
- Copy the header file `.h` to `include` and `lib...a` to `lib` as I meantioned above with shell commands or manually like the above steps.
```shell
xcopy /Y DataStructure.h C:\msys64\ucrt64\include
xcopy /Y libdatastructure.a C:\msys64\ucrt64\lib
```

### ***Autofill Section Header In Code Guide***
---

> _To make code files more structured and readable, we can use VSCode user snippets to quickly insert section headers with different divider styles._

- Copy `sectioncomment.code-snippets` and put it in your `.vscode` folder.

- Usage: In any `.c` or `.h` file, just type the prefix (`sec`, `sdc`, or `ssc`) and press `Tab`.
It will automatically expand into a section header with a placeholder for you to type in the section name. Ex: type "sec" and a `Tab`, it will be like this:
```c
/* ==================  ================== */
```









