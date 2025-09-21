# 🧮 Parallel Matrix Multiplication with Pthreads

This project demonstrates the implementation of **parallel matrix multiplication** in the **C programming language** using the **pthreads (POSIX threads)** library. The primary goal is to address the computational intensity of standard matrix multiplication by distributing the workload among multiple threads, leveraging the power of modern multicore processors.

The program concurrently computes the product of two matrices, with each element of the resulting matrix handled independently by a separate thread. It also uses **mutexes** to ensure thread safety and prevent data races when accessing the shared result matrix.

---

## 🌟 Key Features

- **🧵 Multithreaded Implementation**  
  Utilizes the pthreads library to enable concurrent execution of matrix multiplication.

- **💾 Dynamic Memory Allocation**  
  Allocates memory for matrices at runtime, supporting a variety of matrix sizes.

- **👤 User Interaction**  
  Users can define the dimensions of the matrices and choose between manual input or random value generation.

- **🔒 Synchronization**  
  Employs mutexes to synchronize access to the shared result matrix, ensuring data integrity.

- **⚡ Performance Optimization**  
  Showcases the benefits of parallelization in reducing execution time for computationally intensive tasks.

---

## 🛠️ Technologies Used

- **C Programming Language**  
- **Pthreads (POSIX threads)** – Standard library for multithreaded programming in C

---

## ⚡ Setup and Installation

1. Ensure you have a **C compiler** (like GCC) and the pthreads library installed on your system.
2. **Note:** This program works on **Linux-based systems** or inside a **virtual machine** running Linux, as pthreads may not work correctly on some Windows environments.
---

## 💻 Compiling the Code

Open your terminal or command prompt, navigate to the project directory, and compile the program:

```bash
gcc multithreadingPC.c -o multithreadingPC -pthread
```

---
## 🚀 Running the Program

```sh
# After compilation, run the executable
./multithreadingPC

# Follow the on-screen prompts to:
# 1️⃣ Enter matrix dimensions
# 2️⃣ Input matrix values manually or generate them randomly

