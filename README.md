# ST5004CEM Operating Systems and Security Assignment

## Overview

This repository contains the coursework implementation for the **ST5004CEM - Operating Systems and Security** module.

The project demonstrates important Operating System concepts including:

- Process Management
- Multithreading and Synchronization
- Memory Management
- Virtual Memory and Page Replacement
- File System Security
- Encryption and Decryption
- Inter-Process Communication (IPC)
- Client-Server Communication using Socket Programming

All programs are implemented using the **C programming language** and developed and tested in an Ubuntu Linux environment.

---

# Repository Structure

```
ST5004CEM-Operating-Systems-Assignment
│
├── task1.c
├── Task2.c
├── task3.c
├── client.c
├── server.c
└── README.md
```

---

# Task 1: Process Management and Threading

## Description

Task 1 focuses on process management and multithreading concepts in Operating Systems.

The program creates multiple threads and demonstrates how synchronization mechanisms are used to safely manage shared resources. It also includes a simulation of CPU scheduling techniques.

## Features Implemented

- Creation of multiple threads
- Thread execution management
- Thread synchronization
- Mutex-based resource protection
- Handling race conditions
- Deadlock prevention techniques
- Round-robin CPU scheduling simulation

## Operating System Concepts Covered

- Processes
- Threads
- Critical sections
- Mutual exclusion
- Synchronization
- CPU scheduling
- Context switching

## Compilation

```bash
gcc task1.c -o task1 -pthread
```

## Execution

```bash
./task1
```

---

# Task 2: Memory Management Simulation

## Description

Task 2 implements a memory management simulator that demonstrates how Operating Systems handle virtual memory and page replacement.

The program converts logical addresses into page numbers and manages memory frames using different page replacement algorithms.

## Features Implemented

- Configurable page size
- Configurable number of frames
- Logical address translation
- Page number calculation
- Page fault detection
- Page hit calculation
- FIFO page replacement algorithm
- LRU page replacement algorithm
- Memory usage tracking
- Performance analysis

## Operating System Concepts Covered

- Virtual memory
- Paging
- Page tables
- Address translation
- Page faults
- Page replacement strategies
- Memory allocation

## Compilation

```bash
gcc Task2.c -o Task2
```

## Execution

```bash
./Task2
```

---

# Task 3: Secure File Management System

## Description

Task 3 implements a secure file management system that demonstrates how Operating Systems handle files while maintaining security and access control.

The system provides authentication, file operations, encryption, permissions management, and activity logging.

## Features Implemented

- User authentication system
- User login verification
- File creation
- File writing
- File reading
- File deletion
- File encryption
- File decryption
- File permission management
- Audit log generation

## Security Features

- Access control
- Permission checking
- Data encryption
- Secure file handling
- User activity monitoring

## Operating System Concepts Covered

- File systems
- File permissions
- Security mechanisms
- Authentication
- Data protection
- Cryptography

## Compilation

```bash
gcc task3.c -o task3 -lcrypto
```

## Execution

```bash
./task3
```

---

# Client-Server Communication

## Description

The client and server programs demonstrate communication between two processes using socket programming.

The server waits for client connections and exchanges data through network sockets.

## Files

```
server.c
client.c
```

## Features Implemented

- TCP socket communication
- Client-server architecture
- Inter-Process Communication
- Data exchange between processes
- Network communication handling

## Operating System Concepts Covered

- IPC mechanisms
- Socket programming
- Process communication
- Network-based communication

## Compilation

### Server

```bash
gcc server.c -o server
```

### Client

```bash
gcc client.c -o client
```

## Execution

First run the server:

```bash
./server
```

Then open another terminal and run the client:

```bash
./client
```

---

# Development Environment

## Operating System

Ubuntu Linux 24.04

## Programming Language

C Programming Language

## Compiler

GCC Compiler

## Version Control

Git and GitHub

## Development Platform

VirtualBox Ubuntu Virtual Machine

---

# Learning Outcomes

Through this assignment, the following Operating System concepts were explored:

- Understanding process and thread management
- Implementing thread synchronization techniques
- Preventing race conditions and deadlocks
- Understanding CPU scheduling algorithms
- Learning memory management techniques
- Implementing page replacement algorithms
- Understanding virtual memory concepts
- Developing secure file management systems
- Applying encryption and security methods
- Understanding inter-process communication
- Using Linux development tools and Git version control

---

# Compilation Summary

## Task 1

```bash
gcc task1.c -o task1 -pthread
```

## Task 2

```bash
gcc Task2.c -o Task2
```

## Task 3

```bash
gcc task3.c -o task3 -lcrypto
```

## Server

```bash
gcc server.c -o server
```

## Client

```bash
gcc client.c -o client
```

---

# GitHub Repository Information

**Module:** ST5004CEM - Operating Systems and Security

**Assignment Type:** Coursework Assignment

**Programming Language:** C

**Operating System:** Ubuntu Linux 24.04

**Version Control:** GitHub

---

# Author

**Rizzardzz**

ST5004CEM Operating Systems and Security Assignment
