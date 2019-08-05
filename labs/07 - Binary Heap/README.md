# Binary Heap

## Definition
	A data structure that supports the following operations:
		Get the element with "highest priority" (in this case smallest element) in O(1) time
		Remove the element with "highest priority" in O(logn) time
		Add an element in the heap in O(logn) time

## Properties:
	1) Complete Binary Tree
	2) Every node stores an element with a higher priority than the elements in its 2 children

## Applications
	Heapsort (Stable in-place O(nlogn) comparision sort)
	Graph algorithms such as Djisktra's Shortest Path or Prim's Minimum Spanning Tree algorithms to quickly find the lighest available edge

## Operations

### top
	Return the root of the tree
	Using property 2 it is trivially proven that the root of the tree is the element with the highest priority. This is left as an exercise for the reader :D

### push
	In order to preseve property 1 we can only add a new node at the end of the tree.
	This may invalidate property 2.
	Until we reach the root or the parent of the new node has higher priority than it, we switch the new node with its parent
	Worst case we start from the new leaf and end at the root => O(height)
	The tree is complete => balanced => The height is at worst O(logn)

### pop
	In order to preserve property 1, we can only remove the last node.
	Swap the root with the last leaf and pop.
	Now the new root may invalidate property 2.
	Until property 2 is fixed (we reach a leaf node or both of the new nodes' children have lower priority than it) swap the new node with the child that has a higher priority
	Worst case O(logn) (see proof for push's complexity)

## Physical representation

### Array representation of a tree
	arr[0] holds the value of the root
	for each node, if its value is in arr[i] then arr[i*2+1] and arr[i*2+2] hold the values of its left and right children respectively while arr[(i-1) / 2] holds the value of it's parents (if the given indices are out of range => the respective node is not part of the tree)

### Problem with this representation
	For trees with height H this representation will always require O(2^H) memory
	Storing sparse trees may become extremely memory inefficient
	e.g. consider a super unbalanced tree with 10 nodes where every node (except the one leaf) has 1 child. To store the 10 nodes using this representation we may need an array with a size of up to 1024.

### Binary Heaps with this representation
	Binary Heaps are perfectly balanced and would use up almost all of the allocated memory (only the last layer may be almost empty)

### Advantages of this representation
	Simpler
	Using sequential memory over random pointers greatly improves cache performance

