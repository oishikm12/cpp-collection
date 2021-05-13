# C++ Data Structures, Algorithms & Problems

My own collection of useful data structures, algorithms & competitve questions, implemented in C++

---

## Algorithms

* [**Combinatorics**](algorithms/combinatorics.cpp) - Simple implementation of factorial to demonstrate permutation & combination.
* [**Kadane's Algorithm**](algorithms/kadane_subarr.cpp) - It is used to find the maximum sum of possible subarrays of a given set of integers. (Circular & Non-Circular Implementation)
* [**Sieve of Eratostenes**](algorithms/sieve_eratostenes.cpp) - A table of primes is prepared by eliminating multiples of each number as non prime
* [**Euclid's Algorithm**](algorithms/euclid_hcf_lcm.cpp) - Simple Modulo Operations to find out HCF / GCD & LCM of numbers
* [**Bubble Sort**](algorithms/bubble_sort.cpp) - It is a simple sorting algorithm that repeatedly steps through the list, compares adjacent elements and swaps them if they are in the wrong order.
* [**Insertion Sort**](algorithms/insertion_sort.cpp) - It is a simple sorting algorithm that builds the final sorted array (or list) one item at a time.
* [**Selection Sort**](algorithms/selection_sort.cpp) - The selection sort algorithm sorts an array by repeatedly finding the minimum element (considering ascending order) from unsorted part and putting it at the beginning.
* [**Counting Sort**](algorithms/counting_sort.cpp) - It is an algorithm for sorting a collection of objects according to keys that are small integers; that is, it is an integer sorting algorithm
* [**Merge Sort**](algorithms/merge_sort.cpp) - It is a Divide & Conquer algorithm for dividing the input array into two halves, calls itself for the two halves, and then sorts them and merges the two sorted halves.
* [**Quick Sort**](algorithms/quick_sort.cpp) - It is a Divide and Conquer algorithm for picking an element as pivot and partitioning the given array around the picked pivot, thereby moving the pivot element into its sorted position
* [**Staircase Search**](algorithms/staircase_search.cpp) - Fastest way to search in a 2D matrix by traversing in a diagonal fashiont.
* [**Linear Search**](algorithms/linear_search.cpp) - Simple Array Iteration to find a required element
* [**Binary Search**](algorithms/binary_search.cpp) - It works by repeatedly dividing in half the portion of the list that could contain the item, until its narrowed down the possible locations to just one.
* [**Fast Power**](algorithms/fast_power.cpp) - Finding out power of a number in log n time
* [**Floyd's Cycle**](algorithms/floyds_cycle.cpp) - It is a pointer algorithm that uses only two pointers, moving through the sequence at different speeds. Should the two meet, we confirm presence of cycle in the list
  
## Data Structures

* [**Linked List**](datastructures/linked_list.cpp) - A linked list is a linear collection of data elements whose order is not given by their physical placement in memory. Instead, each element points to the next.
  * [**Linked List STL Implementation**](datastructures/linked_list_stl.cpp) - Linked list using ``list`` header provided by C++
* [**Stack**](datastructures/stack.cpp) - Stack is a linear data structure which follows a particular order in which the operations are performed. The order may be LIFO (Last In First Out) or FILO (First In Last Out).
  * [**Stack STL Implementation**](datastructures/stack_stl.cpp) - Stack using ``stack`` header provided by C++
* [**Queue**](datastructures/queue.cpp) - A Queue is a linear structure which follows a particular order in which the operations are performed. The order is FIFO (First In First Out)
  * [**Queue STL Implementation**](datastructures/queue_stl.cpp) - Queue using ``queue`` header provided by C++
* [**Binary Tree**](datastructures/binary_tree.cpp) - A binary tree is a tree-type non-linear data structure with a maximum of two children for each parent. Every node in a binary tree has a left and right reference along with the data element
  * [**n-ary Tree STL Implementation**](datastructures/tree_stl.cpp) - A Tree using 2D array / vectors provided by C++
  * [**Max Tree Diameter**](datastructures/binarytrees/tree_diameter.cpp) - Given a binary tree, task is to find the maximum possible diameter wrapped around the tree irrespective of values
  * [**Sum of Nodes**](datastructures/binarytrees/sum_of_nodes.cpp) - Given a binary tree, task is to replace each node with the sum of its children
  * [**Tree from Array**](datastructures/binarytrees/tree_from_arr.cpp) - Given a preorder or an inorder array, the task is to reconstruct a binary tree from the configuration
  * [**Mirror Tree**](datastructures/binarytrees/mirror_tree.cpp) - Given a binary tree task is to print a mirrored version of the tree where left is right & vice-versa
  * [**Directional Views**](datastructures/binarytrees/tree_directional_views.cpp) - Given a binary tree task is to print nodes which are only visible from top, bottom, left & right
  * [**ZigZag Printing**](datastructures/binarytrees/tree_zigzag_trav.cpp) - Given a binary tree task is to alternate direction of printing of every level in the tree
  * [**Is Balanced**](datastructures/binarytrees/is_balanced.cpp) - Given a binary tree, task is to check if the tree is balanced or not
  * [**Diagonal Traversal**](datastructures/binarytrees/diagonal_traversal.cpp) - Given a binary tree, task is to print the tree in a diagonal manner
  * [**Boundary View**](datastructures/binarytrees/boundary_view.cpp) - Given a binary tree, the task is to print all nodes which form the boundary of the tree
* [**Binary Search Tree**](datastructures/binary_search_tree.cpp) - A binary search tree, also called an ordered or sorted binary tree, is a rooted binary tree whose internal nodes each store a key greater than all the keys in the node's left subtree and less than those in its right subtree

## Competitive Problems

### Basics (Arrays, Strings & Matrices)

* [**Spiral Printing**](problems/spiral_print.cpp) - Given a 2D matrix, the task is to print each element in the matrix in order of their apperance, i.e. for, ``[[1 2 3] [4 5 6] [7 8 9]]``, spiral would be ``[[1 2 3] [6 9 8] [7 4 5]]``.
* [**Image Rotation**](problems/image_rotation.cpp) - Given a 2D matrix, the task is to rotate the given matrix 90 degrees, in O(1) time, i.e. w/o use of any other array.

### Recursion

* [**Tiling Floors**](problems/tiling_floors.cpp) - Given a floor with space 4 \*x N, the task is to find out how many possible combinations of tiles 1 \* 4 can be placed either horizontally or vertically to fill the floor
* [**Tower of Hanoi**](problems/tower_of_hanoi.cpp) - Given 3 towers, each accepting a ring, the task is to move n rings from one to another, under the constraint that no bigger ring can be placed over a smaller one

### Backtracking

* [**Keypad Strings**](problems/keypad_strings.cpp) - Given a set of numbers, the task is to find out all possible names that could have been written should the numbers have been written on a mobile keypad
* [**String Permutation**](problems/string_permutation.cpp) - Given a string input, the task is to find out all possible permutations of that string or its subsequence
* [**N-Queens**](problems/nqueens.cpp) - Given a chess board of size n * n, the task is to find out all possible configurations of placing n queens on the board such that none can reach the other in a single move
* [**Rat In a Maze**](problems/rat_in_maze.cpp) - Given a grid, filled with obstacles, task is to find all possible paths from one end of diagonal to other
* [**Sudoku**](problems/sudoku.cpp) - Given a x \* x board, task is to place a number in each block such that the number does not repeat in the entire row, or column, and also does not repeat if a section of 3 \* 3 is taken from the board
* [**Crosswords**](problems/crossword.cpp) - Given a board of arbritary size consisting of blank spaces and some letters, the task is to place a given set of words in the empty spaces

### Language Tools & STL

* [**Sum of Three**](problems/three_sum.cpp) - Given a set of numbers, task is to find total possible number of combination of triplets such that each triplet adds up to a specific number
* [**Longest Consecutive Sequence**](problems/longest_cons_seq.cpp) - Given an array, the task is to find and print the longest consecutive increasing sequence
* [**K Concat**](problems/k_concatenation.cpp) - Given an array of fixed size, the task is to duplicate & concatenate the array a certain number of times and then find the maximum sum subarray from it
* [**Maximum Product Subarray**](problems/max_product_subarray.cpp) - Given an array, the task is to find maximum product of any subarray inside the main array
* [**Warm Reception**](problems/warm_reception.cpp) - Given timings of arrival of guest, find out optimal number of chairs required such that no guest is left standing
* [**Array Rotation**](problems/array_rotation.cpp) - Given an array of specified length, the task is to rotate the array to the left by a given amount in linear time

### Searching & Sorting

* [**Wave Sorting**](problems/wave_sorting.cpp) - Given a list of numbers, the task is to sort the array in such a way that for any element in the list, it's two adjacent elements would either be less or more than the element.
* [**Square Root**](problems/square_root.cpp) - Given a number & its precision value, the task is to find it's plausible square root as fast as possible
* [**Read The Pages**](problems/read_the_pages.cpp) - Given books with pages in sorted order, our task is two divide the books between multiple readers such that the maximum pages each reader has to read is minimum
* [**Agressive Cows**](problems/aggressive_cows.cpp) - Given positions of different stalls, task is to place n cows into them such that the minimum distance between them is maximum
* [**Inversion Count**](problems/inversion_count.cpp) - Given an unsorted array, task is to find out how many possible inversions exist, i.e. elements to left are greater & smaller to left
* [**Taj Mahal Entry**](problems/taj_mahal.cpp) - Given a list of ticket counters to enter Taj Mahal, each value represents number of people currently in waiting. If each counter processes 1 person / minute, the task is to figure out when you will get the ticket if you move to the next counter every minute
* [**Sorting the Skills**](problems/sorting_the_skills.cpp) - Given an array representing skill points, the task is to check if it can be sorted when we can only swap adjacent skill points if they differ by 1
* [**Collecting the Balls**](problems/collecting_the_balls.cpp) - Given a certain number of balls, two players will be taking turns in collecting balls, the first player takes an arbitary number each turn, and the other will take 1/10 of the rest. Task is to choose such an arbitary number that the first player has more than half the no. of balls by the end

### Modulo Arithmetic

* [**No. of Balanced Binary Trees**](problems/num_of_bbt.cpp) - Given number of nodes, the task is to find out how many possible balanced binary trees can be constructed with that many nodes
* [**Power of a Number**](problems/pow_num.cpp) - Given a number, and it's exponent, task is to find it's power under integer limits

### Adhoc Problems

* [**Rainwater Trapping**](problems/rain_water_trapping.cpp) - Given n non-negative integers representing an elevation map where the width of each bar is 1, the task is to compute how much water it is able to trap after raining.

### Dynamic Programming

### Bit Manipulation & Bit Masking

* [**Get Bits**](problems/count_bits.cpp) - Given an integer, the task is to acquire the total no. of bits in it as well as how many bits are set in it
* [**Paying Up**](problems/paying_up.cpp) - Given a set of notes and the total no. we need to pay, our task is to check if the sum of subset of the notes we have, amounts to what we have to pay
* [**Finding Unique**](problems/finding_unique.cpp) - Given a set of integers, task is to find such nos. which are not repeated, rest all are in pairs
* [**Tavaas & Sadaas**](problems/tavaas_sadaas.cpp) - Given a nos with only 4 & 7 in it, task is to find its position if all nos preceding it have only 7s & 4s, and the list itself is ascending
  
### Number Theory

* [**Divisible Subarrays**](problems/divisible_subarrays.cpp) - Given a list of integers, the task is to find how many subarrays exist whose sum is divisble by the number of elements in the list

### Greedy Techniques

### Range Based Queries

### Stack

* [**Balanced Parenthesis**](problems/balanced_parenthesis.cpp) - Given a mathematical equation, the task is to check if the number of opening parenthesis matches the number of closing parenthesis in order
* [**Stock Span**](problems/stock_span.cpp) - Given stock values over multiple days, the task is to find for every given day, the no. of days one can go back such that the value of stock was less than that of current day
* [**Area under Histogram**](problems/area_histogram.cpp) - Given a histogram with random heights, the task is to find the largest possible rectangle that can be formed traversing across multiple histogram bars, limited by the bar with minimum height

### Queue

* [**Max in Window**](problems/max_window.cpp) - Given a set of numbers and a given sub array size, the task is to find the maximum element in all possible contigious sub arrays of the given size
* [**Max Length Unique Word**](problems/max_len_words.cpp) - Given a string without a delimiter, the task is to find out the max length substring that only has unique letters in it

### Trees

* [**Catalan Numbers**](problems/catalan.cpp) - Given a limit, print all consequetive catalan number upto that point (Number of BST with 'n' nodes)

### Heaps

### Tries

### Graphs

### Game Theory

### Computational Geometry

### Fast Fourier Transform (FLT)

### Heavy Light Decomposition (HLD)
