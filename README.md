# Thread Pool
This module implements the Pool Object Pattern to manage multiple threads and tasks. It is part of the Code Examples for Multithreaded Programming with C++, specifically based on Chapter 27 of *the Modern C++ book*. The module is integrated into a larger C++ project, which serves as an HTTP server. 

## Steps to build
1. create a build directory inside the project's root directory
```bash
mkdir build
cd build
```
2. generate CMake build files (with/without testable executable)

    **2.1. Generate build files for building a library only without an executable for test**

**Linux**
```bash
cmake  -DGEN_TP_EXE=false .. 
```

**Windows (using MinGW)**
```bash
 cmake -G "MinGW Makefiles" -DGEN_TP_EXE=false .. 
```

    **2.2. Generate build files for building a library with an executable for test**

**Linux**
```bash
cmake  .. 
```
or
```bash
cmake  -DGEN_TP_EXE=true .. 
```

**Windows (using MinGW)**
```bash
 cmake -G "MinGW Makefiles"  .. 
```
or
```bash
 cmake -G "MinGW Makefiles"  -DGEN_TP_EXE=true ..  
```

3. build

**Linux**
```bash
make 
```

**Windows (using MinGW)**
```bash
  mingw32-make
```

4. run the executable (in case using `-DGEN_TP_EXE=true`)

**Linux**
```bash
./threadpooltest 
```

**Windows**
```bash
 .\threadpooltest.exe  
```

## Documentation
The following images are excerpts from the [complete chapter](https://drive.google.com/drive/folders/1TiBu1OhQoD36gtcdjmITu_9HvBfFwRLq?usp=drive_link).

![page 1](imgs/page1.PNG)
![page 2](imgs/page2.PNG)
![page 3](imgs/page3.PNG)
![page 4](imgs/page4.PNG)