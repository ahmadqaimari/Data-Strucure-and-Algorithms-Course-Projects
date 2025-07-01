# Data Structure and Algorithms Course Projects

This repository contains four programming projects implemented in C as part of a Data Structures and Algorithms course. Each project demonstrates different data structures and algorithms concepts.

**Author:** Ahmad Qaimari  
**Student ID:** 1210190  
**Section:** 4

## Table of Contents

- [Project 1: Large Number Arithmetic with Doubly Linked Lists](#project-1-large-number-arithmetic-with-doubly-linked-lists)
- [Project 2: Infix to Prefix Converter and Expression Evaluator](#project-2-infix-to-prefix-converter-and-expression-evaluator)
- [Project 3: Student Management System using Binary Search Tree](#project-3-student-management-system-using-binary-search-tree)
- [Project 4: Shortest Path Finder using Graph Algorithms](#project-4-shortest-path-finder-using-graph-algorithms)

---

## Project 1: Large Number Arithmetic with Doubly Linked Lists
**File:** `P1_1210190_AhmadQaimari_4.c`

### Description
A calculator program that performs arithmetic operations on very large numbers (beyond standard integer limits) by storing digits in doubly linked lists.

### Features
- **Data Structure:** Doubly Linked Lists
- **Operations Supported:**
  - Addition of large numbers
  - Subtraction of large numbers
  - Multiplication of large numbers
  - Division of large numbers (with quotient and remainder)
- **Input:** Reads numbers from `input.txt` file
- **Output:** Results can be saved to `test.txt` file

### Key Functions
- `ReadData()`: Reads large numbers from input file and stores digits in linked lists
- `Add()`, `Sub()`, `Mul()`, `Div()`: Arithmetic operations on linked list representations
- `CMP()`: Compares two numbers stored as linked lists
- Menu-driven interface for user interaction

### Usage
1. Create an `input.txt` file with large numbers (one per line)
2. Run the program and choose option 1 to read data
3. Select two numbers and perform desired arithmetic operations
4. Optionally save results to output file

---

## Project 2: Infix to Prefix Converter and Expression Evaluator
**File:** `P2_1210190_AhmadQaimari_4.c`

### Description
A comprehensive expression processor that validates mathematical expressions, converts them from infix to prefix notation, and evaluates the results.

### Features
- **Data Structures:** Stacks and Linked Lists
- **Functionality:**
  - Expression validation (balanced parentheses, operator placement)
  - Infix to Prefix conversion using stack-based algorithm
  - Prefix expression evaluation
  - Batch processing from input files

### Key Functions
- `isBalanced()`: Checks if brackets are properly balanced
- `op_check()`: Validates operator placement and syntax
- `convert()`: Converts infix expressions to prefix notation
- `EvaluatePrefix()`: Evaluates prefix expressions and returns results
- File I/O operations for batch processing

### Supported Operations
- Basic arithmetic: `+`, `-`, `*`, `/`
- Parentheses: `()`, `[]`
- Negative numbers
- Multi-digit numbers

### Usage
1. Create input file with mathematical expressions (one per line)
2. Run program and load expressions
3. Check validity, convert to prefix, and evaluate expressions
4. Results saved to `p2_output.txt`

---

## Project 3: Student Management System using Binary Search Tree
**File:** `P3_1210190_AhmadQaimari_4.c`

### Description
A student information management system that uses Binary Search Trees for efficient data organization and retrieval.

### Features
- **Data Structure:** Binary Search Tree (BST)
- **Student Information:**
  - Student ID (used as BST key)
  - Name
  - City
  - Class ID (1-12)
  - Date of enrollment

### Operations
1. **Insert Student**: Add new student with unique ID
2. **Update Information**: Modify existing student data
3. **List by Name**: Display students in lexicographic order
4. **Search by City**: Find all students from a specific city
5. **List by Class**: Display students grouped by class
6. **Delete Student**: Remove student record
7. **Save to File**: Persist data to `students.dat`

### Key Functions
- `Insert()`, `Delete()`: BST operations
- `find()`: Search for student by ID
- `CloneTree()`: Create name-sorted copy of BST
- `SearchCitizens()`, `SearchClasses()`: Filtered searches
- File I/O for data persistence

### Usage
- Run program and use menu-driven interface
- Student data persists between program runs via file storage
- Input format for student info: `name,city,class_id,date`

---

## Project 4: Shortest Path Finder using Graph Algorithms
**File:** `P4_1210190_AhmadQaimari_4.c`

### Description
A pathfinding application that finds shortest routes between cities using graph algorithms. Implements both Breadth-First Search and Dijkstra's algorithm.

### Features
- **Data Structure:** Adjacency List representation of weighted graph
- **Algorithms:**
  - Breadth-First Search (BFS) - finds path with minimum edges
  - Dijkstra's Algorithm - finds path with minimum total weight
- **Input:** City connections from `cities.txt`
- **Output:** Path details and distances

### File Format (`cities.txt`)
```
SourceCity    DestinationCity    Distance
```

### Key Components
- **Graph Structure**: Adjacency list with city names and distances
- **Queue Implementation**: For BFS algorithm
- **Min-Heap Implementation**: For Dijkstra's algorithm
- **Path Reconstruction**: Traces back optimal routes

### Key Functions
- `ReadFile()`: Constructs graph from input file
- `BFS()`: Implements breadth-first search pathfinding
- `djikstra()`: Implements Dijkstra's shortest path algorithm
- `createMinHeap()`, `Heapify()`: Min-heap operations for Dijkstra

### Usage
1. Create `cities.txt` with city connections and distances
2. Run program and load cities (option 1)
3. Enter source city (option 2)
4. Enter destination city (option 3)
5. View both BFS and Dijkstra results
6. Results also saved to `shortest_distance.txt`

---

## Compilation and Execution

To compile any project:
```bash
gcc P[X]_1210190_AhmadQaimari_4.c -o project[X]
./project[X]
```

Replace `[X]` with the project number (1, 2, 3, or 4).

## Input Files Required

- **Project 1**: `input.txt` (large numbers, one per line)
- **Project 2**: Input file with mathematical expressions
- **Project 3**: `students.dat` (auto-generated for persistence)
- **Project 4**: `cities.txt` (city connections with distances)

## Learning Objectives

These projects demonstrate:

1. **Dynamic Memory Management**: Proper allocation and deallocation
2. **Data Structure Implementation**: Linked lists, stacks, trees, graphs
3. **Algorithm Design**: Arithmetic operations, expression parsing, tree traversals, shortest path
4. **File I/O Operations**: Reading from and writing to files
5. **Menu-Driven Programming**: User-friendly interfaces
6. **Error Handling**: Input validation and edge cases

Each project builds upon fundamental data structures and algorithms concepts, providing practical implementation experience with real-world applications.
