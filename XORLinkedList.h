#ifndef XORLinkedList_h
#define XORLinkedList_h
#include <iostream>
#include <vector>

template <typename T>
class XORLinkedList {
  public:
    struct Node {
      T data;
      Node *npx;
      Node(T data): data(data), npx(nullptr) {}
    };

    // Accessors
    void PrintForward() const;
    void PrintReverse() const;
    unsigned int NodeCount() const;
    void FindAll(std::vector<Node *> &outData, const T&value) const;
    const Node *Find(const T &data) const;
    const Node *GetNode(unsigned int index) const;
    Node *GetNode(unsigned int index);
    const Node *Head() const;
    Node *Head();
    const Node *Tail() const;
    Node *Tail();

    // Insertion
    void AddHead(const T &data);
    void AddTail(const T &data);
    void AddNodesHead(const T *data, unsigned int count);
    void AddNodesTail(const T *data, unsigned int count);
    void InsertAfter(Node *node, const T &data);
    void InsertBefore(Node *node, const T &data);
    void InsertAt(const T &data, unsigned int index);

    // Removal
    bool RemoveHead();
    bool RemoveTail();
    unsigned int Remove(const T &data);
    bool RemoveAt(unsigned int index);
    void Clear();

    // Operaters
    const T &operator[](unsigned int index) const;
    T &operator[](unsigned int index);
    bool operator==(const XORLinkedList<T> &rhs) const;
    XORLinkedList<T> &operator=(const XORLinkedList<T> &rhs);

    // Construction & Destruction
    XORLinkedList();
    XORLinkedList(const XORLinkedList<T> &list);
    ~XORLinkedList();
  private:
    Node *first, *last;
    unsigned int count;
    Node *XOR(Node *a, Node *b) const;
    void NextNode(Node *&currNode, Node *&prevNode) const;
};

template <typename T>
void XORLinkedList<T>::PrintForward() const {
  Node *tempNode = first, *prevNode = nullptr;
  while (tempNode) {
    std::cout << tempNode->data << std::endl;
    NextNode(tempNode, prevNode);
  }
}

template <typename T>
void XORLinkedList<T>::PrintReverse() const {
  Node *tempNode = last, *prevNode = nullptr;
  while (tempNode) {
    std::cout << tempNode->data << std::endl;
    NextNode(tempNode, prevNode);
  }
}

template <typename T>
unsigned int XORLinkedList<T>::NodeCount() const {
  return count;
}

// TODO: get node from back of list as well
template <typename T>
const typename XORLinkedList<T>::Node *XORLinkedList<T>::GetNode(unsigned int index) const {
  Node *tempNode = first, *prevNode = nullptr;
  if (index < count)
    for (unsigned int i = 0; i < index; i++)
      NextNode(tempNode, prevNode);
  else throw -1;
  return tempNode;
}

// TODO: get node from back of list as well
template <typename T>
typename XORLinkedList<T>::Node *XORLinkedList<T>::GetNode(unsigned int index) {
  Node *tempNode = first, *prevNode = nullptr;
  if (index < count)
    for (unsigned int i = 0; i < index; i++)
      NextNode(tempNode, prevNode);
  else throw -1;
  return tempNode;
}

template <typename T>
const typename XORLinkedList<T>::Node *XORLinkedList<T>::Head() const {
  return first;
}

template <typename T>
typename XORLinkedList<T>::Node *XORLinkedList<T>::Head() {
  return first;
}

template <typename T>
const typename XORLinkedList<T>::Node *XORLinkedList<T>::Tail() const {
  return last;
}

template <typename T>
typename XORLinkedList<T>::Node *XORLinkedList<T>::Tail() {
  return last;
}

// Insertion
template <typename T>
void XORLinkedList<T>::AddHead(const T &data) {
  Node *newNode = new Node(data);
  newNode->npx = first;
  if(count) first->npx = XOR(newNode, first->npx);
  else last = newNode;
  first = newNode;
  count++;
}

template <typename T>
void XORLinkedList<T>::AddTail(const T &data) {
  Node *newNode = new Node(data);
  newNode->npx = last;
  if(count) last->npx = XOR(newNode, last->npx);
  else first = newNode;
  last = newNode;
  count++;
}

template <typename T>
void XORLinkedList<T>::AddNodesHead(const T *data, unsigned int count) {
  for (int i = count - 1; i >= 0; i--)
    AddHead(data[i]);
}

template <typename T>
void XORLinkedList<T>::AddNodesTail(const T *data, unsigned int count) {
  for (unsigned int i = 0; i < count; i++)
    AddTail(data[i]);
}

template <typename T>
void XORLinkedList<T>::InsertAfter(Node *node, const T &data) {}

template <typename T>
void XORLinkedList<T>::InsertBefore(Node *node, const T &data) {}

template <typename T>
void XORLinkedList<T>::InsertAt(const T &data, unsigned int index) {}

// Removal
template <typename T>
bool XORLinkedList<T>::RemoveHead() {
  return RemoveAt(0);
}

template <typename T>
bool XORLinkedList<T>::RemoveTail() {
  return RemoveAt(count);
}

template <typename T>
unsigned int XORLinkedList<T>::Remove(const T &data) {}

// TODO: fix edge cases
template <typename T>
bool XORLinkedList<T>::RemoveAt(unsigned int index) {
  if(index < count) {
    Node *tempNode = first, *nextNode = nullptr, *prevNode = nullptr;
    for (unsigned int i = 0; i < index; i++)
        NextNode(tempNode, prevNode);
    // TODO: fix section of code to allow deletion from back of list to increase speed
    // if(index < count/2 || index == 0) {
    //   for (unsigned int i = 0; i < index; i++)
    //     NextNode(tempNode, prevNode);
    // }
    // else {
    //   tempNode = last;
    //   for (unsigned int i = count - 1; i >= index; i--)
    //     NextNode(tempNode, prevNode);
    // }
    nextNode = XOR(prevNode, tempNode->npx);
    if(prevNode) prevNode->npx = XOR(XOR(prevNode->npx, tempNode), nextNode);
    if(nextNode) nextNode->npx = XOR(XOR(tempNode, nextNode->npx), prevNode);

    // Edge Case: deleteing first node. Must reassign first pointer.
    if(index == 0) first = first->npx;
    // Edge Case: deleteing last node. Must reassign last pointer.
    if(index == count - 1) last = last->npx;

    delete tempNode;
    tempNode = nullptr;
    count--;
    return true;
  } else return false;
}

template <typename T>
void XORLinkedList<T>::Clear() {
  while(RemoveAt(0));
}

// Operaters
template <typename T>
const T &XORLinkedList<T>::operator[](unsigned int index) const {
  return GetNode(index);
}

template <typename T>
T &XORLinkedList<T>::operator[](unsigned int index) {
  return GetNode(index);
}

template <typename T>
bool XORLinkedList<T>::operator==(const XORLinkedList<T> &rhs) const {
  if(count == rhs.count) {
    Node *tempNode = first, *prevNode = nullptr;
    Node *rhs_tempNode = first, *rhs_prevNode = nullptr;
    while (tempNode) {
      if (tempNode->data != rhs_tempNode->data) return false;
      NextNode(tempNode, prevNode);
      NextNode(rhs_tempNode, rhs_prevNode);
    }
  } else return false;
  return true;
}

// TODO: reimplement to not use GetNode()
template <typename T>
XORLinkedList<T> &XORLinkedList<T>::operator=(const XORLinkedList<T> &rhs) {
  Node *tempNode = rhs.first, *prevNode = nullptr;
  while (tempNode) {
    AddTail(tempNode->data);
    NextNode(tempNode, prevNode);
  }
  return *this;
}

// Construction & Destruction
template <typename T>
XORLinkedList<T>::XORLinkedList(): count(0), first(nullptr), last(nullptr) {}

// TODO: reimplement to not use GetNode()
template <typename T>
XORLinkedList<T>::XORLinkedList(const XORLinkedList<T> &list) {
  Node *tempNode = list.first, *prevNode = nullptr;
  while (tempNode) {
    AddTail(tempNode->data);
    NextNode(tempNode, prevNode);
  }
}

template <typename T>
XORLinkedList<T>::~XORLinkedList() {
  while(RemoveAt(0));
}

template <typename T>
typename XORLinkedList<T>::Node *XORLinkedList<T>::XOR(Node *a, Node *b) const {
  return (Node*)((uintptr_t)a ^ (uintptr_t)b);
}

template <typename T>
void XORLinkedList<T>::NextNode(Node *&currNode, Node *&prevNode) const {
  Node *copyNode = currNode;
  currNode = XOR(currNode->npx, prevNode);
  prevNode = copyNode;
}

#endif
