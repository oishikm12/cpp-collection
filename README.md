# C++ Data Structures, Algorithms & Problems

My own collection of useful data structures, algorithms & competitve questions, implemented in C++

---

## Algorithms

* [**Combinatorics**](algorithms/combinatorics.cpp) - Simple implementation of factorial to demonstrate permutation & combination
* [**Kadane's Algorithm**](algorithms/kadane_subarr.cpp) - It is used to find the maximum sum of possible subarrays of a given set of integers (Circular & Non-Circular Implementation)
* [**Sieve of Eratostenes**](algorithms/sieve_eratostenes.cpp) - A table of primes is prepared by eliminating multiples of each number as non prime
* [**Euclid's Algorithm**](algorithms/euclid_hcf_lcm.cpp) - Simple Modulo Operations to find out HCF / GCD & LCM of numbers
* [**Bubble Sort**](algorithms/bubble_sort.cpp) - It is a simple sorting algorithm that repeatedly steps through the list, compares adjacent elements and swaps them if they are in the wrong order
* [**Insertion Sort**](algorithms/insertion_sort.cpp) - It is a simple sorting algorithm that builds the final sorted array (or list) one item at a time
* [**Selection Sort**](algorithms/selection_sort.cpp) - The selection sort algorithm sorts an array by repeatedly finding the minimum element (considering ascending order) from unsorted part and putting it at the beginning
* [**Counting Sort**](algorithms/counting_sort.cpp) - It is an algorithm for sorting a collection of objects according to keys that are small integers; that is, it is an integer sorting algorithm
* [**Merge Sort**](algorithms/merge_sort.cpp) - It is a Divide & Conquer algorithm for dividing the input array into two halves, calls itself for the two halves, and then sorts them and merges the two sorted halves
* [**Quick Sort**](algorithms/quick_sort.cpp) - It is a Divide and Conquer algorithm for picking an element as pivot and partitioning the given array around the picked pivot, thereby moving the pivot element into its sorted position
* [**Staircase Search**](algorithms/staircase_search.cpp) - Fastest way to search in a 2D matrix by traversing in a diagonal fashiont
* [**Linear Search**](algorithms/linear_search.cpp) - Simple Array Iteration to find a required element
* [**Binary Search**](algorithms/binary_search.cpp) - It works by repeatedly dividing in half the portion of the list that could contain the item, until its narrowed down the possible locations to just one
* [**Fast Power**](algorithms/fast_power.cpp) - Finding out power of a number in log n time
* [**Floyd's Cycle**](algorithms/floyds_cycle.cpp) - It is a pointer algorithm that uses only two pointers, moving through the sequence at different speeds. Should the two meet, we confirm presence of cycle in the list
  
## Data Structures

* [**Singly Linked List**](datastructures/singly_linkedlist.cpp) - A linked list is a linear collection of data elements whose order is not given by their physical placement in memory. Instead, each element points to the next
  * [**Add One**](datastructures/singlylinkedlists/add_one.cpp) - Task is to consider a number represented via linked list and add 1 to it
  * [**Add Two Numbers**](datastructures/singlylinkedlists/add_two_num.cpp) - Given two linked lists, task is to consider them a number and add them into one
  * [**Clone Arbitary Pointers**](datastructures/singlylinkedlists/clone_random_ptr.cpp) - Given a linked list with arbitary connection between nodes, task is to clone such a list
  * [**Delete Greater Right**](datastructures/singlylinkedlists/delete_greater_right.cpp) - Given a linked list, task is to delete every such node which has a greater element to its right
  * [**Flatten a List**](datastructures/singlylinkedlists/flatten_list.cpp) - Given a 2D linked list consisitong of right & bottom pointers, task is to flatten the list into a single list with only nodes in bottom pointers
  * [**Group Reverse**](datastructures/singlylinkedlists/group_reverse.cpp) - Given a linked list, we need to reverse every ``k`` subsections of the list
  * [**nth From End**](datastructures/singlylinkedlists/nth_from_end.cpp) - Given a linked list, task is to print the nth number from the end in a single traversal
  * [**Palindrome**](datastructures/singlylinkedlists/palindrome.cpp) - Given a linked list, task is to check if the list is palindromic i.e. the list remains the same when read from end
  * [**Intersection**](datastructures/singlylinkedlists/list_intersection.cpp) - Given two linked lists, task is to check how many elements are common to both
  * [**Quicksort**](datastructures/singlylinkedlists/list_qsort.cpp) - Given a linked list, task is to sort the list via quicksort
  * [**Segregate Odd Even**](datastructures/singlylinkedlists/segregate_odd_even.cpp) - Given a linked list, task is to order all the even elements to the front & odd to end
* [**Doubly Linked List**](datastructures/doubly_linkedlist.cpp) - It is a type of linked list in which each node apart from storing its data has two links. The first link points to the previous node in the list and the second link points to the next node in the list
  * [**DLL STL Implementation**](datastructures/doubly_linkedlist_stl.cpp) - Doubly Ended Linked list using ``list`` header provided by C++
  * [**K-Distance Selection Sort**](datastructures/doublylinkedlists/selection_sort.cpp) - Given a doubly linked list, task is to sort it, when every node is at most ``k`` position away from its sorted position
  * [**Triplets in DLL**](datastructures/doublylinkedlists/finding_triplets.cpp) - Given a doubly linked list and a certain sum, task is to find triplets that equal the sum
  * [**Non Repeating String in List**](datastructures/doublylinkedlists/non_rep_str.cpp) - Given a string, task is to used a doubly linked list in order to replace the list with non repeating letters in the string
* [**Circular Linked List**](datastructures/circular_linkedlist.cpp) - Circular Linked List is a variation of Linked list in which the first element points to the last element and the last element points to the first element
* [**Stack**](datastructures/stack.cpp) - Stack is a linear data structure which follows a particular order in which the operations are performed. The order may be LIFO (Last In First Out) or FILO (First In Last Out)
  * [**Stack STL Implementation**](datastructures/stack_stl.cpp) - Stack using ``stack`` header provided by C++
* [**Queue**](datastructures/queue.cpp) - A Queue is a linear structure which follows a particular order in which the operations are performed. The order is FIFO (First In First Out)
  * [**Queue STL Implementation**](datastructures/queue_stl.cpp) - Queue using ``queue`` header provided by C++
* [**Binary Tree**](datastructures/binary_tree.cpp) - A binary tree is a tree-type non-linear data structure with a maximum of two children for each parent. Every node in a binary tree has a left and right reference along with the data element
  * [**n-ary Tree STL Implementation**](datastructures/nary_tree_stl.cpp) - A Tree using 2D array / vectors provided by C++
  * [**Max Tree Diameter**](datastructures/binarytrees/tree_diameter.cpp) - Given a binary tree, task is to find the maximum possible diameter wrapped around the tree irrespective of values
  * [**Sum of Nodes**](datastructures/binarytrees/sum_of_nodes.cpp) - Given a binary tree, task is to replace each node with the sum of its children
  * [**Tree from Array**](datastructures/binarytrees/tree_from_arr.cpp) - Given a preorder or an inorder array, the task is to reconstruct a binary tree from the configuration
  * [**Mirror Tree**](datastructures/binarytrees/mirror_tree.cpp) - Given a binary tree task is to print a mirrored version of the tree where left is right & vice-versa
  * [**Directional Views**](datastructures/binarytrees/tree_directional_views.cpp) - Given a binary tree task is to print nodes which are only visible from top, bottom, left & right
  * [**ZigZag Printing**](datastructures/binarytrees/tree_zigzag_trav.cpp) - Given a binary tree task is to alternate direction of printing of every level in the tree
  * [**Is Balanced**](datastructures/binarytrees/is_balanced.cpp) - Given a binary tree, task is to check if the tree is balanced or not
  * [**Diagonal Traversal**](datastructures/binarytrees/diagonal_traversal.cpp) - Given a binary tree, task is to print the tree in a diagonal manner
  * [**Boundary View**](datastructures/binarytrees/boundary_view.cpp) - Given a binary tree, the task is to print all nodes which form the boundary of the tree
  * [**Tree from Balanced Parenthesis**](datastructures/binarytrees/tree_from_string.cpp) - Given a string with parenthesis representing left and then right subtree, task is to construct an actual tree from it
  * [**Tree to DLL**](datastructures/binarytrees/tree_to_doubly_linked_list.cpp) - Given a binary tree, task is to convert it into a doubly linked list
  * [**Leaves at Tree**](datastructures/binarytrees/leaves_at_level.cpp) - Given a binary tree, task is to confirm that all leaves are at the same level
  * [**Duplicate SubTree**](datastructures/binarytrees/duplicate_subtree.cpp) - Given a binary tree, task is to find if there exists a duplicte subtree with height at min 2
  * [**Largest Subtree Sum**](datastructures/binarytrees/largest_subtree_sum.cpp) - Given a binary tree, task is to find such a subtree whose sum is the maximum
  * [**Largest Non-Adjacent Sum**](datastructures/binarytrees/largest_nonadj_sum.cpp) - Given a binary tree task is to find the largest possible sum such that no two nodes are adjacent
  * [**Lowest Common Ancestor**](datastructures/binarytrees/least_common_ancestor.cpp) - Given a binary tree and two nodes, task is to find out the node where they meet
  * [**k-th Ancestor**](datastructures/binarytrees/kth_ancestor.cpp) - Given a binary tree and a node, task is to fins the k-th ancestor of this node
  * [**Isomorphic Tree**](datastructures/binarytrees/isomorphic_tree.cpp) - Given two binary trees, task is to check if the trees are isomorphic, i.e. one can be derived from other by swapping some nodes
  * [**n-Ary Mirror**](datastructures/binarytrees/nary_mirror.cpp) - Given two n-Ary trees, task is to check if the two trees are mirrors of each other or not
* [**Binary Search Tree**](datastructures/binary_search_tree.cpp) - A binary search tree, also called an ordered or sorted binary tree, is a rooted binary tree whose internal nodes each store a key greater than all the keys in the node's left subtree and less than those in its right subtree
  * [**Inorder Predecessor & Successor**](datastructures/binarysearchtrees/predecessor_successor.cpp) - Given a binary search tree, and a specific node, task is to find its inorder predecessor and inorder successor
  * [**Lowest Common Ancestor**](datastructures/binarysearchtrees/lca_bst.cpp) - Given a binary search tree and two nodes, task is to find the their lowest common ancestor
  * [**Tree from Preorder**](datastructures/binarysearchtrees/bst_from_preorder.cpp) - Given a preorder traversal of a BST, task is to construct a binary search tree from this
  * [**BT to BST**](datastructures/binarysearchtrees/bt_to_bst.cpp) - Given a binary tree, task is to convert this into a binary search tree, keeping the structure intact
  * [**Balancing Skewness**](datastructures/binarysearchtrees/balanced_bst.cpp) - Given a skewed binary search tree, task is to convert this into a balanced binary search tree
  * [**Merge Balanced Trees**](datastructures/binarysearchtrees/merge_balanced.cpp) - Given two balanced Binary Search Trees, task is to merge them into one
  * [**Dead Nodes**](datastructures/binarysearchtrees/dead_nodes.cpp) - Given a binary search tree, task is to find all the leaf nodes that cannot have any more children, i.e. any of its possible children would either be a repetition or be present elsewhere
  * [**Flatten a Tree**](datastructures/binarysearchtrees/flatten_bst.cpp) - Given a binary search tree, task is to convert this into a sorted linked list
  * [**kTh Largest & Smallest**](datastructures/binarysearchtrees/kth_largest_smallest.cpp) - Given a binary search tree, task is to find a certain indexed largest & another certain indexed smallest number in it
  * [**Largest Binary Search Subtree**](datastructures/binarysearchtrees/largest_subBST.cpp) - Given a binary tree, task is to traverse it's nodes and find out the largest possible binary search tree as a subtree of it
  * [**Median of Tree**](datastructures/binarysearchtrees/median_tree.cpp) - Given a binary search tree, task is to find the median node in this tree
  * [**Nodes in a Range**](datastructures/binarysearchtrees/nodes_in_range.cpp) - Given a binary search tree, task is to find out the number of nodes lying between a given range(inclusive)
* [**Heap**](datastructures/minmax_heap.cpp) - A Heap is a special Tree-based data structure in which the tree is a complete binary tree. Generally, Heaps can be either a Max Heap wherein the root of the tree is the maximal element, or a Min Heap where the root is minimal
  * [**Heap STL Implementation**](datastructures/minmax_heap_stl.cpp) - Min & Max Heap using the ``priority_queue`` in ``queue`` header provided by C++

## Competitive Problems

### Basics (Arrays, Strings & Matrices)

* [**Smallest Difference**](problems/smallest_difference.cpp) - Given two arrays, task is to find two elements in the arrays such that their difference is the minimal and print that difference
* [**Longest Peak**](problems/longest_peak.cpp) - Given a list of numbers, task is to find out largest length of a subsequence where numbers are ascending to a point and descending after that
* [**Minimize the Heights**](problems/minimize_heights.cpp) - Given an array of heights and a integer ``K``, the task is to to modify the height of each tower either by increasing or decreasing them by K only once and then find the difference between max & min heights
* [**Spiral Printing**](problems/spiral_print.cpp) - Given a 2D matrix, the task is to print each element in the matrix in order of their apperance, i.e. for, ``[[1 2 3] [4 5 6] [7 8 9]]``, spiral would be ``[[1 2 3] [6 9 8] [7 4 5]]``
* [**Image Rotation**](problems/image_rotation.cpp) - Given a 2D matrix, the task is to rotate the given matrix 90 degrees, in O(1) time, i.e. w/o use of any other array
* [**ZigZag Printing**](problems/zigzag_matrix.cpp) - Given a 2D matrix, the task is to traverse this matrix in diagonal first manner where the direction of printing alternates everytime we reach an edge

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
* [**Equalize Strings**](problems/equalize_str.cpp) - Given two strings task is to convert one to another in minimum cost, where swappings costs distance between swap, and flipping costs 1
* [**Rectangular Area**](problems/rectangular_area.cpp) - Given N rectangles, which are centered in the center of the Cartesian coordinate system and their sides are parallel to the coordinate axes, task is to find the area covered by these rectangles on the grid
* [**Light Up the Bulbs**](problems/light_up_bulbs.cpp) - Given a set of bulbs in random state, task is to find minimum cost to turn on all lights, given reversing a set of bulbs takes some cost and toggling adjacent bulbs takes another
* [**Interesting Sequences**](problems/interesting_seq.cpp) - Given a series of numbers, task is to convert all the numbers into the same in minimal cost wherein we can either increase 1 & decrease 1 or just increase 1; each with its own cost.
* [**Winning Strategy**](problems/winning_strategy.cpp) - Given a sequential series of numbers from 1, task is to check if it is possible to convert this into another sequence, given you can only swap adjacents and can swap any player at most twice

### Dynamic Programming

* [**Alpha Code**](problems/alpha_code.cpp) - Given a sequence of numbers wherein each number represents an alphabet, task is to find out how many possible sequence of characters are possible
* [**Coin Change**](problems/coin_change.cpp) - Given a certain value and certain denominations, task is to find out how many ways can we achieve the value by using those denominations
* [**Magic Grid**](problems/magic_grid.cpp) - Given a 2D grid consisting of both positive & negative values, task is to find the least starting energy needed to travel from top left to bottom right, such that the energy value never drops below 1, when travelling to any grid
* [**Numerical Substrings**](problems/numerical_substrings.cpp) - Given a number as a string, task is to find the sum of all possible substrings of the string as number
* [**Construct the Array**](problems/construct_the_array.cpp) - Given the length of an array, starting and ending of the array, the task is to find the number of ways to construct an array such that consecutive positions contain different values
* [**Boredom**](problems/boredom.cpp) - Given a set of numbers, the task is to find the maximum points one can earn if at any turn, they can select a number, get that much points, however all number +1 & -1 to that number gets destroyed
* [**Minimum Chocolates**](problems/minimum_chocolates.cpp) - Given a number of students with scores, task is to ditribute chocolates between them such that, in case of adjacent people, the one with more score gets more, equal score may get different. Everyone gets at least 1 chocolate
* [**Square Count**](problems/min_square_count.cpp) - Given a number, task is to find out the count of sequences where sum of squares of those numbers in the sequence would result in the selected number
* [**Vanya & GCD**](problems/vanya_gcd.cpp) - Given a list of numbers, task is to find the number of increasing subsequences possible with ``GCD = 1``
* [**Angry Children**](problems/angry_children.cpp) - Given a list of numbers and a number ``k``, task is to select k such numbers such that the absolute difference between them is the minimal

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
* [**Min Swaps Required**](problems/min_swaps_bt2bst.cpp) - Given a complete binary tree in array format, task is to determine how many swaps will be required to convert this into a binary search tree
* [**Smallest Distance between Nodes**](problems/smallest_node_distance.cpp) - Given a binary tree and two nodes, task is to find the smallest distance between them
* [**Overlapping Appointment Timings**](problems/appointment_timings.cpp) - Given times of arrival of guests and their departure, task is to find out which sequences overlap with others
* [**Least Greatest Right**](problems/least_greatest_right.cpp) - Given a list of numbers, task is to replace each number with a it's least greatest number present to it's right side

### Heaps

* [**K Largest in Stream**](problems/k_largest_stream.cpp) - Given a continious stream of characters with a small window of size `k`, task is to maintain the largest `k` numbers in this window at all times
* [**Running Meadian**](problems/running_median.cpp) - Given a list of numbers, task is to find out the median every time a new number is read

### Tries

### Graphs

### Game Theory

### Computational Geometry

### Fast Fourier Transform (FLT)

### Heavy Light Decomposition (HLD)
