#include <iostream>
#include <iomanip>
#include <utility>
#include <fstream>

using namespace std;

struct Node {
  // create a typical node for a doubly linked list
  // extra value -> 'address', this will store the
  // memory address of the current value
  int value;
  int *address;
  Node *next;
  Node *prev;
} *head;

void AddNode(int x) {
  // 'new_node' = for creating a new node
  // 'traverse_node' = for traversing the linked list
  Node *new_node, *traverse_node;
  // set the value of the node based on the current element
  new_node = new Node();
  new_node->value = x;
  new_node->address = &new_node->value;
  new_node->next = NULL;
  // set the 'traverse_node' to 'head'
  traverse_node = head;
  if (head == NULL) {
    // if 'head' is null, then set the previous pointer to null
    new_node->prev = NULL;
    // set 'head' to 'new_node'
    head = new_node;
  } else {
    // otherwise, traverse the linked list to find the last element
    while (traverse_node->next != NULL) {
      traverse_node = traverse_node->next;
    }
    // set the next pointer of the last element to 'new_node'
    traverse_node->next = new_node;
    // set the previous pointer of 'new_node' to 'traverse_node'
    new_node->prev = traverse_node;
  }
}

void BubbleSort() {
  // create 'checker' to control the loop below
  bool checker = false;
  // create two pointers:
  // 'pointer' = traverse the nodes in the linked list
  Node *pointer;
  // 'last_pointer' = point to null or last node
  Node *last_pointer = NULL;
  if (head == NULL) {
    // if 'head' is null, then return nothing
    return;
  } else {
    // create a loop that checks if 'checker' is true
    do {
      // set 'checker' to false
      checker = false;
      // set 'pointer' to head (first node)
      pointer = head;
      // create a loop until 'pointer' reaches 'last_pointer'
      while (pointer->next != last_pointer) {
        // if the currrent node is greater than the next node,
        // then it means it's not yet sorted
        if (pointer->value > pointer->next->value) {
          // create pairs of integer and integer pointer to store the
          // value and address of the current node as well as the next node
          pair<int, int*> a;
          a.first = pointer->value;
          a.second = pointer->address;
          pair<int, int*> b;
          b.first = pointer->next->value;
          b.second = pointer->next->address;
          // swap the two pairs
          swap(a, b);
          // store back to the 'pointer' the values of pair 'a'
          pointer->value = a.first;
          pointer->address = a.second;
          // store back to the 'pointer->next' the value of pair 'b'
          pointer->next->value = b.first;
          pointer->next->address = b.second;
          // set 'checker' to true
          checker = true;
        }
        // set 'pointer' to the next node
        pointer = pointer->next;
      }
      // set 'last_pointer' to the last node
      last_pointer = pointer;
    } while (checker);
  }
}

void PrintList(int option) {
  Node *traverse_node;
  traverse_node = head;
  if (head == NULL) {
    return;
  } else {
    ofstream output_file;
    // there will be two options:
    // 1 - the linked list hasn't been sorted yet
    // 2 - the linked list has been sorted
    if (option == 1) {
      output_file.open("output.txt");
      output_file << "Output Data File:\n";
    } else {
      // use append in this option to not overwrite the former contents
      output_file.open("output.txt", ios_base::app);
    }
    // print the values of the nodes based on the pattern given
    // TERMINAL
    cout << setw(10) << "\nADDRESS";
    cout << setw(20) << "PREV";
    cout << setw(20) << "DATA";
    cout << setw(20) << "NEXT\n";
    // IN FILE
    output_file << setw(10) << "\nADDRESS";
    output_file << setw(20) << "PREV";
    output_file << setw(20) << "DATA";
    output_file << setw(20) << "NEXT\n";
    while (traverse_node != NULL) {
      // TERMINAL
      cout << setw(5) << traverse_node->address;
      // INFILE
      output_file << setw(5) << traverse_node->address;
      if (traverse_node->prev != NULL) {
        // this condition works if the current node is not the first node
        // TERMINAL
        cout << setw(15) << traverse_node->prev->address;
        // IN FILE
        output_file << setw(15) << traverse_node->prev->address;
      } else {
        // if the current node is the first node, then this block is executed
        // TERMINAL
        cout << setw(15) << "0x0";
        // IN FILE
        output_file << setw(15) << "0x0";
      }
      // print the value of the current node
      // TERMINAL
      cout << setw(20) << traverse_node->value;
      // IN FILE
      output_file << setw(20) << traverse_node->value;
      if (traverse_node->next != NULL) {
        // this condition works if the current node is not the last node
        // TERMINAL
        cout << setw(20) << traverse_node->next->address;
        // IN FILE
        output_file << setw(20) << traverse_node->next->address;
      } else {
        // if the current node is the last node, then this block is executed
        // TERMINAL
        cout << setw(20) << "0x0";
        // IN FILE
        output_file << setw(20) << "0x0";
      }
      cout << '\n';
      output_file << '\n';
      // set the 'traverse_node' to the next node
      traverse_node = traverse_node->next;
    }
    // close the file
    output_file.close();
  }
}

int main() {
  // user input
  cout << "Enter the number of elements of the array: ";
  int n;
  cin >> n;
  cout << "Enter " << n << " elements: ";
  // set 'head' pointer to null
  head = NULL;
  for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      AddNode(x);
  }
  // PrintList(1) - print the linked list (before sorting)
  PrintList(1);
  // BubbleSort - sort the linked list using bubble sort algorithm
  BubbleSort();
  // PrintList(2) - print the linked list (after sorting)
  PrintList(2);
  return 0;
}
