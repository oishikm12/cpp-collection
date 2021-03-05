# C++ Data Structures, Algorithms & Problems

My own collection of useful data structures, algorithms & competitve questions, implemented in C++

---

## Algorithms

* **Combinatorics** - Simple implementation of factorial to demonstrate permutation & combination.
* **Kadane's Algorithm** - It is used to find the maximum sum of possible subarrays of a given set of integers. (Circular & Non-Circular Implementation)
* **Sieve of Eratostenes** - A table of primes is prepared by eliminating multiples of each number as non prime
* **Euclid's Algorithm** - Simple Modulo Operations to find out HCF / GCD & LCM of numbers
* **Bubble Sort** - It is a simple sorting algorithm that repeatedly steps through the list, compares adjacent elements and swaps them if they are in the wrong order. 
* **Insertion Sort** - It is a simple sorting algorithm that builds the final sorted array (or list) one item at a time.
* **Selection Sort** - The selection sort algorithm sorts an array by repeatedly finding the minimum element (considering ascending order) from unsorted part and putting it at the beginning.
* **Counting Sort** - It is an algorithm for sorting a collection of objects according to keys that are small integers; that is, it is an integer sorting algorithm
* **Merge Sort** - It is a Divide & Conquer algorithm for dividing the input array into two halves, calls itself for the two halves, and then sorts them and merges the two sorted halves.
* **Quick Sort** - It is a Divide and Conquer algorithm for picking an element as pivot and partitioning the given array around the picked pivot, thereby moving the pivot element into its sorted position
* **Staircase Search** - Fastest way to search in a 2D matrix by traversing in a diagonal fashiont.
* **Linear Search** - Simple Array Iteration to find a required element
* **Binary Search** - It works by repeatedly dividing in half the portion of the list that could contain the item, until its narrowed down the possible locations to just one.
* **Fast Power** - Finding out power of a number in log n time
  
## Data Structures

* **Linked List** - A linked list is a linear collection of data elements whose order is not given by their physical placement in memory. Instead, each element points to the next.
* **Stack** - Stack is a linear data structure which follows a particular order in which the operations are performed. The order may be LIFO (Last In First Out) or FILO (First In Last Out).
* **Queue** - A Queue is a linear structure which follows a particular order in which the operations are performed. The order is FIFO (First In First Out)

## Random Problems

* **Rainwater Trapping** - Given n non-negative integers representing an elevation map where the width of each bar is 1, the task is to compute how much water it is able to trap after raining.
* **Spiral Printing** - Given a 2D matrix, the task is to print each element in the matrix in order of their apperance, i.e. for, ``[[1 2 3] [4 5 6] [7 8 9]]``, spiral would be ``[[1 2 3] [6 9 8] [7 4 5]]``.
* **Image Rotation** - Given a 2D matrix, the task is to rotate the given matrix 90 degrees, in O(1) time, i.e. w/o use of any other array.
* **Wave Sorting** - Given a list of numbers, the task is to sort the array in such a way that for any element in the list, it's two adjacent elements would either be less or more than the element.
* **Square Root** - Given a number & its precision value, the task is to find it's plausible square root as fast as possible
* **Read The Pages** - Given books with pages in sorted order, our task is two divide the books between multiple readers such that the maximum pages each reader has to read is minimum
* **Get Bits** - Given an integer, the task is to acquire the total no. of bits in it as well as how many bits are set in it
* **Paying Up** - Given a set of notes and the total no. we need to pay, our task is to check if the sum of subset of the notes we have, amounts to what we have to pay
* **Finding Unique** - Given a set of integers, task is to find such nos. which are not repeated, rest all are in pairs
* **Tavaas & Sadaas** - Given a nos with only 4 & 7 in it, task is to find its position if all nos preceding it have only 7s & 4s, and the list itself is ascending
* **Divisible Subarrays** - Given a list of integers, the task is to find how many subarrays exist whose sum is divisble by the number of elements in the list
* **Tiling Floors** - Given a floor with space 4 * N, the task is to find out how many possible combinations of tiles 1 * 4 can be placed either horizontally or vertically to fill the floor
* **Tower of Hanoi** - Given 3 towers, each accepting a ring, the task is to move n rings from one to another, under the constraint that no bigger ring can be placed over a smaller one
* **Keypad Strings** - Given a set of numbers, the task is to find out all possible names that could have been written should the numbers have been written on a mobile keypad
* **String Permutation** - Given a string input, the task is to find out all possible permutations of that string or its subsequence
* **N-Queens** - Given a chess board of size n * n, the task is to find out all possible configurations of placing n queens on the board such that none can reach the other in a single move
* **Rat In a Maze** - Given a grid, filled with obstacles, task is to find all possible paths from one end of diagonal to other
* **Sudoku** - Given a x * x board, task is to place a number in each block such that the number does not repeat in the entire row, or column, and also does not repeat if a section of 3 * 3 is taken from the board
* **Balanced Parenthesis** - Given a mathematical equation, the task is to check if the number of opening parenthesis matches the number of closing parenthesis in order
* **Stock Span** - Given stock values over multiple days, the task is to find for every given day, the no. of days one can go back such that the value of stock was less than that of current day
* **Area under Histogram** - Given a histogram with random heights, the task is to find the largest possible rectangle that can be formed traversing across multiple histogram bars, limited by the bar with minimum height
* **Max in Window** - Given a set of numbers and a given sub array size, the task is to find the maximum element in all possible contigious sub arrays of the given size
* **Max Length Unique Word** - Given a string without a delimiter, the task is to find out the max length substring that only has unique letters in it