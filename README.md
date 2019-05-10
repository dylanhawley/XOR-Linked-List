# XORLinkedList

This is an experimental data structure that implements a more memory efficient doubly linked list

Instead of storing a `prev` and `next` pointer in each Node, we store a single pointer that is the bitwise XOR of these pointers. When traversing the linked list, we keep track of two Nodes in order to calculate the next Node.
