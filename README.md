# What it does

The Game of Life, created by mathematician John Conway, is a “game” that demonstrates how complex behaviors can emerge from a set of simple rules. 
It is not, strictly speaking, a game, but rather a cellular automaton, which is a mathematical model that describes the functioning of computing systems (hardware or software).

For more details, check https://site-pa.netlify.app/proiecte/game_of_life/

The program has several versions, each corresponding to a specific task: 

### Task 1
Implement the rules of the Game of Life so that, starting from an N × M matrix representing the initial generation, 
the following K generations are obtained, each also saved as matrices.

### Task 2
The program creates a stack in which each element corresponds to a generation. Each generation is represented by a list of 
cells that have changed their state compared to the previous generation. Therefore, the program will create a stack of lists.

#### Bonus
Given the contents of the stack for K generations and the matrix corresponding to generation K, the program will write to a file
the matrix corresponding to the initial configuration (generation 0).
This program is created separately from the others, in the file bonusT2.c.

### Task 3
The program will create an alternative to the Game of Life with a single rule, B, namely: any cell with exactly two live neighbors becomes a live cell.
Given an initial configuration (the root of the tree), the program will create two child nodes:
- The left child represents generation 1 obtained using the new rule B.
- The right child represents generation 1 obtained using the standard rules.

This operation is repeated for all newly created nodes until the given generation K is reached.

### Task 4
The program determines, for each node of the tree obtained in Task 3, up to a given generation K, the longest Hamiltonian path.

# Usage
Sample call:

```
make build
make run ARGS="InputData/data19.in out/data19.out"
```

You can use the files from InputData or you can make new ones that respect this format:
- T - task number
- N, M - matirx dimensions
- K - the number of generations 
- The matrix 

# Structural details

- gol.c: tha main source code
- tasks.c: contains the functions used for each task
- f_structuri: contains the function made for data structure like lists,  stack, trees, graphs
- functii_uzuale: contains some usual functions like: the ones for reading or copying a matrix, freeing the memory etc.
- bonusT2.c: contains the source code for the bonus task







