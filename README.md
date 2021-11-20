# C++ Data Structures, Algorithms & Problems

My own collection of useful data structures, algorithms & competitve questions, implemented in C++

---

## Algorithms

* [**Combinatorics**](algorithms/combinatorics.cpp) - Simple implementation of factorial to demonstrate permutation & combination
* [**Kadane's Algorithm**](algorithms/kadane_subarr.cpp) - It is used to find the maximum sum of possible subarrays of a given set of integers (Circular & Non-Circular Implementation)
* [**Sieve of Eratosthenes**](algorithms/sieve_eratostenes.cpp) - A table of primes is prepared by eliminating multiples of each number as non prime
* [**Euclid's Algorithm**](algorithms/euclid_hcf_lcm.cpp) - Simple Modulo Operations to find out HCF / GCD & LCM of numbers
* [**Bubble Sort**](algorithms/bubble_sort.cpp) - It is a simple sorting algorithm that repeatedly steps through the list, compares adjacent elements and swaps them if they are in the wrong order
* [**Insertion Sort**](algorithms/insertion_sort.cpp) - It is a simple sorting algorithm that builds the final sorted array (or list) one item at a time
* [**Selection Sort**](algorithms/selection_sort.cpp) - The selection sort algorithm sorts an array by repeatedly finding the minimum element (considering ascending order) from unsorted part and putting it at the beginning
* [**Counting Sort**](algorithms/counting_sort.cpp) - It is an algorithm for sorting a collection of objects according to keys that are small integers; that is, it is an integer sorting algorithm
* [**Radix Sort**](algorithms/radix_sort.cpp) - It is a non-comparative sorting algorithm which avoids comparison by creating and distributing elements into buckets according to their radix (singular digits). This bucketing process is repeated for each digit, while preserving the ordering of the prior step, until all digits have been considered
* [**Merge Sort**](algorithms/merge_sort.cpp) - It is a Divide & Conquer algorithm for dividing the input array into two halves, calls itself for the two halves, and then sorts them and merges the two sorted halves
* [**Quick Sort**](algorithms/quick_sort.cpp) - It is a Divide and Conquer algorithm for picking an element as pivot and partitioning the given array around the picked pivot, thereby moving the pivot element into its sorted position
* [**Heap Sort**](algorithms/heap_sort.cpp) - It involves preparing the list by first turning it into a max heap. The algorithm then repeatedly swaps the first value with the last value, decreasing the range of values considered in the heap operation by one, and sifting the new first value into its position in the heap, thereby sorting the list in this process
* [**Topological Sort**](algorithms/topological_sort.cpp) - Topological sorting for Directed Acyclic Graph (DAG) is a linear ordering of vertices such that for every directed edge u v, vertex u comes before v in the ordering. While done via DFS, Kahn's algorithm allows for a BFS approach
* [**Staircase Search**](algorithms/staircase_search.cpp) - Fastest way to search in a 2D matrix by traversing in a diagonal fashiont
* [**Linear Search**](algorithms/linear_search.cpp) - Simple Array Iteration to find a required element
* [**Binary Search**](algorithms/binary_search.cpp) - It works by repeatedly dividing in half the portion of the list that could contain the item, until its narrowed down the possible locations to just one
* [**A\* Search**](algorithms/a_star_search.cpp) - A\* is a graph traversal and path search algorithm, which precomputes the cost to reach the destination via heuristic function, if a certain path is taken. This way an optimal result is always guaranteed
* [**KMP Pattern Search**](algorithms/kmp_pattern_search.cpp) - KMP matching algorithm uses degenerating property (pattern having same sub-patterns appearing more than once in the pattern) of the pattern, in order to search for a substring in a string in perfect linear time
* [**Z Pattern Search**](algorithms/z_pattern_search.cpp) - This algorithm finds all occurrences of a pattern in a text in linear time by recording how many characters match in current sequence with that of its prefix
* [**Fast Power**](algorithms/fast_power.cpp) - Finding out power of a number in log n time
* [**Modular Exponentiation**](algorithms/modular_exponentiation.cpp) - Finds out a power of a number, when the exponent is large, i.e. the answer is beyond integer limits; via modulus
* [**Extended Euclid's Algorithm**](algorithms/extended_euclid.cpp) - It is an extension to the Euclidean algorithm, and computes, in addition to the GCD of integers `a` and `b`, also the coefficients of Bézout's identity (Linear Diophantine Equation), which are integers x and y such that, ``ax + by = gcd(a, b)``
* [**Euler's Totient**](algorithms/euler_totient.cpp) - It allows us to calculate `phi(n)` for a given number, i.e. the number of elements co-prime to that number appearing before it
* [**Floyd's Cycle**](algorithms/floyds_cycle.cpp) - It is a pointer algorithm that uses only two pointers, moving through the sequence at different speeds. Should the two meet, we confirm presence of cycle in the list
* [**Dijkstra's Shortest Path**](algorithms/dijkstra_shortest_path.cpp) - It is an algorithm for finding the shortest paths between nodes in a weighted positive graph. It does this by repeatedly comparing cost to reach neighbouring nodes, with its previously recorded costs
* [**Bellman Ford's Shortest Path**](algorithms/bellman_ford_shortest_path.cpp) - It allows us to determine the shortest distance between two nodes in a weighted directed graph, however unlike Dijkstra's algorithm, it is able to detect negative weights
* [**Flood Fill**](algorithms/flood_fill.cpp) - This allows us to selectively change a certain element in a coloured graph. It is used to determine a bounded area connected to a given node in a multi-dimensional array.
* [**Floyd Warshall Algorithm**](algorithms/floyd_warshall.cpp) - This algorithm allows us to find shortest distances between every pair of vertices in a given edge weighted directed Graph.
* [**Kosaraju's Algorithm**](algorithms/kosaraju.cpp) - This algorithm allows us to check wether a given directed graph is strongly connected, i.e. every vertex is reachable from every other
* [**Tarjan's Algorithm**](algorithms/tarjan.cpp) - Unlike Kosaraju which requires two DFS traversals, strongly connected components can be found out in a single traversal, if we maintain two arrays, one to track discovery time & one to track subtree roots of possible SCC
* [**Prim's Algorithm**](algorithms/prim_mst.cpp) - It finds the subset of edges that includes every vertex of the graph such that the sum of the weights of the edges can be minimized. It starts with the single node and explore all the adjacent nodes with all the connecting edges at every step
* [**Kruskal's Algorithm**](algorithms/kruskal_mst.cpp) - It finds a minimum spanning forest of an undirected edge-weighted graph. If the graph is connected, it finds a minimum spanning tree, much like Prim
* [**Jarvis Convex Hull**](algorithms/jarvis_convex_hull.cpp) - Given a set of points in the plane, the task is to find the Convex Hull of the set, which is the smallest convex polygon that contains all the points of it
  
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
  * [**Get Minimum**](datastructures/stacks/getmin_stack.cpp) - Given a set of numbers, the task is to design a stack that can find the minimal element in constant time & space
  * [**Next Larger**](datastructures/stacks/next_larger.cpp) - Given a set of numbers, the task is to use a stack to find the next greater number to the right for every number
  * [**Polish Notation**](datastructures/stacks/polish_notation.cpp) - Given any of the polish notations, the task is to convert it to others, via stack
  * [**Reversal**](datastructures/stacks/reversal.cpp) - Given a stack, the task is to reverse this stack without using any other data structure
  * [**Sort a Stack**](datastructures/stacks/stack_sort.cpp) - Given a stack, the task is to sort the contents of this stack without other data structures
* [**Queue**](datastructures/queue.cpp) - A Queue is a linear structure which follows a particular order in which the operations are performed. The order is FIFO (First In First Out)
  * [**Queue STL Implementation**](datastructures/queue_stl.cpp) - Queue using ``queue`` header provided by C++
  * [**Queue Permutation**](datastructures/queues/queue_permutation.cpp) - Given two arrays, each representing two states of queue, the task is to check if one can be converted to another should a stack be given
  * [**Reversal**](datastructures/queues/reversal.cpp) - Given a queue, the task is to reverse this stack without using any other data structure
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
* [**N-Ary Tree STL**](datastructures/nary_tree_stl.cpp) - An n-ary tree is a special tree which can have multiple children, unlike binary tree which can have only 2 children. This is represented as an adjeceny collection of edges via vectors
  * [**n-Ary Mirror**](datastructures/narytrees/nary_mirror.cpp) - Given two n-Ary trees, task is to check if the two trees are mirrors of each other or not
* [**Binary Search Tree**](datastructures/binary_search_tree.cpp) - A binary search tree, also called an ordered or sorted binary tree, is a rooted binary tree whose internal nodes each store a key greater than all the keys in the node's left subtree and less than those in its right subtree
  * [**Threaded Binary Search Tree**](datastructures/threaded_bst.cpp) - Threaded BST is a simple binary search tree but they have a speciality that null pointers of leaf node of the tree is set to inorder predecessor or inorder successor depending on the node
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
* [**AVL Tree**](datastructures/avl_tree.cpp) - An AVL tree is a self-balancing Binary Search Tree where the difference between heights of left and right subtrees is not more than one for all nodes
* [**Red Black Tree**](datastructures/red_black_tree.cpp) - A red-black tree is a kind of self-balancing binary search tree where each node has an extra bit, and that bit is often interpreted as the colour (red or black). Operations in RB Tree always occur in logarithmic time
* [**Segment Tree**](datastructures/segment_tree.cpp) - A segment tree, also known as a statistic tree, is a tree data structure used for storing information about intervals, or segments. It allows querying which of the stored segments contain a given point
  * [**Lazy Propagation Segment Tree**](datastructures/lazy_segtree.cpp) - A lazy propagated segment tree, maintains a seperate tree tracking changes not yet implemented. These changes are reflected only on queries involving those nodes
* [**Fenwick Tree**](datastructures/fenwick_tree.cpp) - A Fenwick tree or binary indexed tree is a data structure that can efficiently update elements and calculate prefix sums in a table of numbers
* [**Heap**](datastructures/minmax_heap.cpp) - A Heap is a special Tree-based data structure in which the tree is a complete binary tree. Generally, Heaps can be either a Max Heap wherein the root of the tree is the maximal element, or a Min Heap where the root is minimal
  * [**Heap STL Implementation**](datastructures/minmax_heap_stl.cpp) - Min & Max Heap using the ``priority_queue`` in ``queue`` header provided by C++
  * [**Kth Min & Max**](datastructures/heaps/kth_min_max.cpp) - Given a list of numbers and certain values of `k`, the task is to find `kth` smallest and largest number in that list
  * [**Heap Merge K Sorted**](datastructures/heaps/heap_merge_ksorted.cpp) - Given k sorted arrays, the task is to merge them into one sorted array using Heap
  * [**Kth Largest Subarray Sum**](datastructures/heaps/kth_largest_subsum.cpp) - Given an array, the task is to construct a Min Heap and find out the Kth largest sum of all possible contigious subarrays of the array
  * [**Smallest Range in List**](datastructures/heaps/smallest_range.cpp) - Given `k` arrays of sorted elements, task is to find the smallest range which includes at least 1 element from each array
  * [**Tree is Heap**](datastructures/heaps/tree_is_heap.cpp) - Given a binary tree, the task is to check if this tree is a Max Heap or not
  * [**BST to Min Heap**](datastructures/heaps/bst_to_heap.cpp) - Given a Binary Search Tree, the task is to convert this tree into a Min Heap with an additional property that every node in its left subtree is smaller than right subtree
* [**Hash Map**](datastructures/hash_map.cpp) - A Hash Table / Hash Map is a data structure that implements an associative array abstract data type, a structure that can map keys to values. This allows accessing elements, if their key is known, in constant time
  * [**Hash Map STL Implementation**](datastructures/hash_map_stl.cpp) - Hash Map using the ``unordered_map`` header provided by C++
* [**Trie**](datastructures/trie.cpp) - A trie, also called digital tree or prefix tree, is a type of search tree, a tree data structure used for locating specific keys from within a set. In order to do this it stores characters of a string as nodes
* [**Graph**](datastructures/graph.cpp) - A graph is a pictorial representation of a set of objects where some pairs of objects are connected by links. The interconnected objects are represented by points termed as vertices, and the links that connect the vertices are called edges
  * [**Shortest Distance**](datastructures/graphs/shortest_distance.cpp) - Given an interconnected graph, and a starting value, the task is to find out the shortest path between this node and all other nodes
  * [**Is Cyclic**](datastructures/graphs/cyclic.cpp) - Given a graph, the task is to find out if it contains a cycle or not
  * [**Biparted Graph**](datastructures/graphs/biparted.cpp) - Given a graph, the task is to find out if this graph is biparted, i.e. to check if all of its nodes can be divided into two parts, where each node has edges only to opposite groups and not within its own group

## Competitive Problems

### Arrays

* [**Smallest Difference**](problems/smallest_difference.cpp) - Given two arrays, task is to find two elements in the arrays such that their difference is the minimal and print that difference
* [**Longest Peak**](problems/longest_peak.cpp) - Given a list of numbers, task is to find out largest length of a subsequence where numbers are ascending to a point and descending after that
* [**Minimize the Heights**](problems/minimize_heights.cpp) - Given an array of heights and a integer ``K``, the task is to to modify the height of each tower either by increasing or decreasing them by K only once and then find the difference between max & min heights
* [**Minimal Jumps**](problems/minimal_jumps.cpp) - Given a list of numbers indicating how many steps we can jump ahead at most, the task is to find out the minimal number of jumps required to travel from first to last index
* [**Duplicates**](problems/duped_number.cpp) - Given a list of numbers, with exactly one number repeated multiple times, the task is to find this number provided, every number is in the sequence `[1 .. n]`
* [**Next Permutation**](problems/next_permutation.cpp) - Given a certain number in the form an array, the task is to rearrange the numbers into the lexicographically next greater permutation of numbers, or if not possible, rearrange to ascending order
* [**Zero Sum Subarray**](problems/zero_sum_subarr.cpp) - Given a list of numbers, the task is to find out if there exists a subarray whose sum is equivalent to 0
* [**Smallest Greater Subarray Length**](problems/subarray_greater_sum.cpp) - Given a list of numbers and a certain sum, the task is to find the minimum subarray length, whose sum is greater than our given sum
* [**Opertations For Palindromic Array**](problems/operations_palindrome.cpp) - Given a list of numbers, the task is to calulate the minimum number of operations required to make the array palindromic, given each operation consisits of combining two numbers into their sum
* [**Median of Two Sorted Array**](problems/sorted_twice_median.cpp) - Given two sorted arrays of same length, the task is to find the median of combined array

### Matrices

* [**Spiral Printing**](problems/spiral_print.cpp) - Given a 2D matrix, the task is to print each element in the matrix in order of their apperance, i.e. for, ``[[1 2 3] [4 5 6] [7 8 9]]``, spiral would be ``[[1 2 3] [6 9 8] [7 4 5]]``
* [**Image Rotation**](problems/image_rotation.cpp) - Given a 2D matrix, the task is to rotate the given matrix 90 degrees, in O(1) time, i.e. w/o use of any other array
* [**ZigZag Printing**](problems/zigzag_matrix.cpp) - Given a 2D matrix, the task is to traverse this matrix in diagonal first manner where the direction of printing alternates everytime we reach an edge
* [**Sorted Median**](problems/sorted_median.cpp) - Given a row-wise sorted 2D matrix, the task is to find the median of this matrix, given rows & columns are always odd
* [**Largest Binary Rectangle**](problems/largest_binary_rectangle.cpp) - Given a binary matrix, the task is to find the area of largest rectangle covered bby `1`s

### Strings

* [**Longest Prefix Suffix**](problems/longest_prefix_suffix.cpp) - Given a string, the task is to find out the longest prefix that matches a certain non-overlapping portion of the suffix of that same string
* [**Longest Palindromic Subsequence**](problems/longest_palindromic_subsequence.cpp) - Given a string, the task is to find out how many palindromic subsequences are there, and the length of the longest one

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
* [**Palindromic Partitions**](problems/palindromic_partitions.cpp) - Given a string, the task is to partition it such that every substring of the partition is a palindrome, and as such find all possible partitions
* [**k-Partition**](problems/k_partitions.cpp) - Given an array of numbers and a number `k`, the task is to find out if it is possible to divide this array into `k` subsets such that sum of each subset is the same

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
* [**Read The Pages**](problems/read_the_pages.cpp) - Given books with pages in sorted order, our task is to divide the books between multiple readers such that the maximum pages each reader has to read is minimum
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
* [**Longest Common Subsequence**](problems/longest_common_sub.cpp) - Given two strings, the task is to find out the length of the longest sub-sequence that is common to both
* [**Edit Distance**](problems/edit_distance.cpp) - Given two strings, task is to convert one into another. At each step, one can insert, delete or replace a character, each taking 1 unit of work, we need to find minimal work needed
* [**0 / 1 Knapsack Problem**](problems/knapsack.cpp) - Given a bag of certain weight capacity, and a number of elments with certain value & weights, task is to find out the maximal value one can place inside the bag without going over its capacity
* [**Subset Sum**](problems/subset_sum.cpp) - Given a list of numbers, task is to find out if the sum of any subset of those numbers equal a desired sum or not
* [**Maximum Sum Rectangle**](problems/max_sum_rectangle.cpp) - Given a grid of numbers, task is to find out the maximum possible sum of a rectangle carved out of this grid
* [**Prime Possiblity**](problems/prime_possiblities.cpp) - Given a bag of certain capacity, and a set of items with specific values and weights, the task is to select items such that the value is maximum, wherein value of each item gets multiplied by a unique prime no. from first 10 primes
* [**Stock Profits**](problems/stock_profits.cpp) - Given the cost of stocks on a set of days, and ``k`` transactions to make, task is to maximize profit in those two transaction under the condition that only 1 stock can be bought at a time
* [**Distinct Substrings**](problems/distinct_substrings.cpp) - Given a string, task is to find out how many distinct substrings are possible
* [**Shortest Unique Substring Length**](problems/shortest_unisub.cpp) - Given two strings, task is to find out the length of the shortest substring in first that cannot be reciprocated in the second
* [**Number of APs**](problems/number_of_aps.cpp) - Given a list of numbers, task is to find out how many possible Arithmetic Progressions are present in this list

### Bit Manipulation & Bit Masking

* [**Manipulate Bits**](problems/manipulate_bits.cpp) - Given an integer, the task is to perform operations such as finding out number of bits, set & unset certain bits, find out if the number is a power of 2, and the XOR of natural numbers till it
* [**Paying Up**](problems/paying_up.cpp) - Given a set of notes and the total no. we need to pay, our task is to check if the sum of subset of the notes we have, amounts to what we have to pay
* [**Finding Unique**](problems/finding_unique.cpp) - Given a set of integers, task is to find such nos. which are not repeated, rest all are in pairs
* [**Tavaas & Sadaas**](problems/tavaas_sadaas.cpp) - Given a nos with only 4 & 7 in it, task is to find its position if all nos preceding it have only 7s & 4s, and the list itself is ascending
* [**Candies**](problems/candies.cpp) - Given a number of candies, and the same number of students, the task is to find out possible ways to distribute candies among them, given that each of them have preference towards certain candies
* [**String Dilemma**](problems/string_dilemma.cpp) - Given ``n`` binary strings, task is to find out minimum number of touches required to uniquely identify each string, wherein each touch allows one to compare same index of each string
  
### Number Theory

* [**Divisible Subarrays**](problems/divisible_subarrays.cpp) - Given a list of integers, the task is to find how many subarrays exist whose sum is divisble by the number of elements in the list
* [**Multiplicative Modular Inverse**](problems/multiplicative_modular_inverse.cpp) - Given a certain number and another number to divide it with, the task is to find a certain number which when multiplied with the number to be divided, changes the remainder of the division to 1
* [**Super Primes**](problems/super_primes.cpp) - Given a range from 1 to `n`, the task is to find out how many such numbers exist which have exactly 2 distinct prime divisors
* [**Weight Balancing**](problems/weight_balancing.cpp) - Given two weights, the task is to find out how many combination of those weights can be used to attain a third weight
* [**Divisors of Factorials**](problems/divisors_of_factorial.cpp) - Given a number, the task is to find out the total count of divisors of the factorial of the number
* [**Good Sets**](problems/good_sets.cpp) - Given a list of numbers, task is to find count of all such subsets of the list such that every number in the set is a divisor of the number next to it
* [**Card Game**](problems/card_game.cpp) - Given a list of cards having certain value, and a certain number, the task is to find count of all possible subarrays whose products are divisible by this number
* [**Strange Order**](problems/strange_order.cpp) - Given a number, the task is to print numbers from n to 1, in a specific order, wherein `n` should be followed by numbers whose `gcd(n, x) != 1`, and so on for next largest number till we reach 1
* [**Sum of LCM**](problems/sum_of_lcm.cpp) - Given a number, the task is to find the sum of LCM of all numbers till that numbers, with the number itself, i.e. `lcm(1, n) + lcm(2, n) + ... + lcm(n, n)`
* [**Segmented Sieve**](problems/segmented_sieve.cpp) - Given a range which can go upto 10^10, the task is to print all the primes in this range
* [**Fibonacci Sum**](problems/fibonacci_sum.cpp) - Given two large ranges, the task is to find the sum of fibonacci numbers lying within this range via matrix exponentiaition
* [**Boring Factorials**](problems/boring_factorials.cpp) - Given a number the task is to find the modulo of factorial of that number with some prime
* [**Extreme GCD**](problems/extreme_gcd.cpp) - Given a number the task is to find sum of GCD of all numbers from `1 ... N`, with `i + 1 ... N`
* [**kth Permutation**](problems/kth_permutation.cpp) - Given a number, the task is to consider all natural numbers upto that number and find the `k th` permutation of those numbers in lexographical order

### Greedy Techniques

* [**Activity Selection**](problems/activity_selection.cpp) - Given starting and ending duration of activities, the task is to find out how many activities can be performed in one day
* [**Fractional Knapsack**](problems/fractional_knapsack.cpp) - Given weights and values of `n` items, we need to put these items in a knapsack of capacity W to get the maximum total value in the knapsack, however we are allowed to break the items.
* [**Jewellery Theft**](problems/jewellery_theft.cpp) - Given `n` jewellery pieces each with certain value & weight, the task is to store these jewelleries in `k` bags which can hold a single jewellery of certain weight, such that profit is maximized
* [**MiniMax Discussion**](problems/minimax_discussion.cpp) - Given a list of numbers and a number `k`, the task is to find the minimal difference between the largest and smallest number in the list, after adding or subtracting `k` from each number

### Range Based Queries (Segment & Fenwick Trees)

* [**Max Subarray Sum Range**](problems/max_subarr_range.cpp) - Given a list of numbers and multiple set of ranges, the task is to find out the maximum subarray sum in all of those ranges
* [**Sum of Squares**](problems/sum_of_squares.cpp) - Given a list of numbers and multiple ranges, wherein we have to either update the values in ranges by something / to something, or we have to print sum of squares of numbers in that range
* [**Binary Query**](problems/binary_query.cpp) - Given a binary literal, the task is to modify a single bit or print the value of certain subsection of the literal
* [**Sheldon & Trains**](problems/sheldon_and_trains.cpp) - Given a list of stations, the task is to find the sum of minimum tickets required to travel from each station to every other station after it
* [**Distinct Queries**](problems/distinct_queries.cpp) - Given a sequence of numbers and a number of queries. A query is a pair of ranges, and for each query, the taks is to return the number of distinct elements in the subsequence
* [**Increasing Subsequences**](problems/increasing_subsequences.cpp) - Given a list of numbers, the task is to find out the number of increasing subsequences that are exactly a given size long

### Stack

* [**Balanced Parenthesis**](problems/balanced_parenthesis.cpp) - Given a mathematical equation, the task is to check if the number of opening parenthesis matches the number of closing parenthesis in order
* [**Stock Span**](problems/stock_span.cpp) - Given stock values over multiple days, the task is to find for every given day, the no. of days one can go back such that the value of stock was less than that of current day
* [**Area under Histogram**](problems/area_histogram.cpp) - Given a histogram with random heights, the task is to find the largest possible rectangle that can be formed traversing across multiple histogram bars, limited by the bar with minimum height
* [**Celebrity Problem**](problems/celebrity_problem.cpp) - Given a matrix representing how many other people a person knows in a party, the task is to spot a celebrity who does not recognize anyone else, but everyone else knows that person

### Queue

* [**Max in Window**](problems/max_window.cpp) - Given a set of numbers and a given sub array size, the task is to find the maximum element in all possible contigious sub arrays of the given size
* [**Max Length Unique Word**](problems/max_len_words.cpp) - Given a string without a delimiter, the task is to find out the max length substring that only has unique letters in it
* [**Rotten Oranges**](problems/rotten_oranges.cpp) - Given a grid where each element represents wether it is empty, filled with fresh or filled with rotten oranges, the task is to find out the time before all oranges are rotten, if rot spreads in all 4 grid directions in unit time

### Trees

* [**Catalan Numbers**](problems/catalan.cpp) - Given a limit, print all consequetive catalan number upto that point (Number of BST with 'n' nodes)
* [**Min Swaps Required**](problems/min_swaps_bt2bst.cpp) - Given a complete binary tree in array format, task is to determine how many swaps will be required to convert this into a binary search tree
* [**Smallest Distance between Nodes**](problems/smallest_node_distance.cpp) - Given a binary tree and two nodes, task is to find the smallest distance between them
* [**Overlapping Appointment Timings**](problems/appointment_timings.cpp) - Given times of arrival of guests and their departure, task is to find out which sequences overlap with others
* [**Least Greatest Right**](problems/least_greatest_right.cpp) - Given a list of numbers, task is to replace each number with a it's least greatest number present to it's right side

### Heaps

* [**K Largest in Stream**](problems/k_largest_stream.cpp) - Given a continious stream of characters with a small window of size `k`, task is to maintain the largest `k` numbers in this window at all times
* [**Running Meadian**](problems/running_median.cpp) - Given a list of numbers, task is to find out the median every time a new number is read
* [**Sliding Window Maximum**](problems/sliding_window_maximum.cpp) - Given a list of numbers and a certain window size, which iterates over this list, the task is to find out the maximum at each itertion of the window
* [**Reorganize Strings**](problems/reorganize_strings.cpp) - Given a string, the task is to reorganize the characters such that no two adjacent characters are the same
* [**Minimal Sum**](problems/minimal_sum.cpp) - Given digits in the form of array, task is to divide the digits into two combined numbers such that when they are added, the resultant sum is minimal

### Tries

* [**Maximum XOR Subarray**](problems/max_xor_subarr.cpp) - Given a list of numbers, the task is to find out maximum possible XOR of subarray
* [**Auto-Completion**](problems/autocompletion.cpp) - Given a list of strings from a dictionary and another word, the task is to find out all possible autocomplete patterns to that word from the dictionary

### Graphs

* [**Flight and Tours**](problems/catch_the_plane.cpp) - Given a list of places and the cost to travel between each via bus & plane, the task is to find the minimal cost needed to reach from the source to destination, given the passenger can take at most one flight in between
* [**Travelling Salesman**](problems/travelling_salesman.cpp) - Given a grid representing cost from travelling from one city to another, the task is to find the minimal cost of travelling to all cities and back to start
* [**Holiday Accomodations**](problems/holiday_accomodations.cpp) - Given a graph representing various people in various cities and the distance between cities, the task is to shuffle them such that each person travels the maximum distance while traversing through the shortest path to get there
* [**3 Cycles**](problems/three_cycles.cpp) - Given two list where same indices are connected similar to a graph, the task is to find the count of 3 unique points `x, y, z` such that `x, y`, `y, z` & `z, x` are all connected, present in the graph
* [**Permutation Swaps**](problems/permutation_swaps.cpp) - Given two lists of same size, the task is to find out if one can be converted to another, when only certain indices can be swapped in a list
* [**Edges in MST**](problems/edges_in_mst.cpp) - Given a graph, the task is to find out for each edge, wether it would be included in every possible MST of the graph, some possible or never at all

### Game Theory

* [**Game of Nim**](problems/game_of_nim.cpp) - Given multiple sets of pebbles, two players are playing the game wherein at each turn, one can take certain or any number of pebbles from one set only. The player which cannot remove any pebbles loses, hence the task is to find out the losing player if both play optimally
* [**8 Puzzle**](problems/8_puzzle.cpp) - Given a `3 * 3` grid, representing a state of a board with one empty cell, the task is to change the state into another with the least number of swaps
* [**Othello**](problems/othello.cpp) - Given an Othello board with a certain state, the task is to find out the best next move such that the first player wins with the maxium score possible
* [**Tic Tac Toe**](problems/tic_tac_toe.cpp) - Given a tic-tac-toe with partial filled cells, the task is to find out which player wins in the end

### Computational Geometry

* [**Area of Convex Polygon**](problems/area_convex_polygon.cpp) - Given `n` coordinates of a poygon in anticlockwise order, the task is to find its area if it were convex in nature, i.e. no angle over 180 and to find the distance between any two points
* [**Non-Collinear Intersection**](problems/non_collinear_intersection.cpp) - Given 4 coordinates, which represents two lines, the task is to find out if any 3 points are collinear, if not, to find the point of intersection of the two lines
* [**Bomb Investigation**](problems/bomb_investigation.cpp) - Given the coordinates of a bomb, the coordinates of a polygon representing the immidiate vicinity of the bomb, and the coordinates of people near it, the task is to find the probablity of a person wether they are present in the vicinity and could have planted the bomb
