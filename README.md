# Heuristic to solve the Travelling Salesman Problem
During my first year at Télécom SudParis I had to solve the Travelling Salesman Problem using several heuristics. I finally chose to implement 5 heuristics to solve the problem:

- Nearest neighbor
- Nearest addition
- Nearest insertion
- Farthest insertion
- 2-opt


I also wanted to create a user interface using GTK3+. I have created all the code, assets, documentation. I also implemented
unit tests to check my implementation of linked lists.

**Note**: the code can be greatly improved. I coded this in 2013. Also, there are some minor UI bugs. Finally, my implementation of the save functionality is not good at all. I could have saved only the point and not a big matrice
of distance....

# Installation
1. Install GTK3+ before using the program
2. Clone the repository to your machine
3. Open a shell and go to the main directory
    ```sh
    $ cd go\to\the\directory
    ```
4. Compile the program using make command from your terminal
    ```sh
    $ make
    ```
5. Launch the program using:
    ```sh
    $ ./tsp
    ```

# Demonstration
You can see how to use the program by clicking on the **demonstration.avi** file from the main directory.