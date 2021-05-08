#include <iostream>
#include <iomanip>
#include <utility>
#include <fstream>

using namespace std;

struct Node {
  int value;
  int* address;
  Node *next;
  Node *prev;
} *head;

void CreateList(int a[], int n) {
  Node *new_node, *traverse_node;
  for (int i = 0; i < n; i++) {
    new_node = new Node();
    new_node->value = a[i];
    new_node->address = &a[i];
    new_node->next = NULL;
    traverse_node = head;
    if (head == NULL) {
      new_node->prev = NULL;
      head = new_node;
    } else {
      while (traverse_node->next != NULL) {
        traverse_node = traverse_node->next;
      }
      traverse_node->next = new_node;
      new_node->prev = traverse_node;
    }
  }
}

void BubbleSort() {
  bool checker = false;
  Node *pointer;
  Node *last_pointer = NULL;
  if (head == NULL) {
    return;
  } else {
    do {
      checker = false;
      pointer = head;
      while (pointer->next != last_pointer) {
        if (pointer->value > pointer->next->value) {
          pair<int, int*> a;
          a.first = pointer->value;
          a.second = pointer->address;
          pair<int, int*> b;
          b.first = pointer->next->value;
          b.second = pointer->next->address;
          swap(a, b);
          pointer->value = a.first;
          pointer->address = a.second;
          pointer->next->value = b.first;
          pointer->next->address = b.second;
          checker = true;
        }
        pointer = pointer->next;
      }
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
    if (option == 1) {
      output_file.open("output.txt");
      output_file << "Output Data File:\n";
    } else {
      output_file.open("output.txt", ios_base::app);
    }
    cout << setw(10) << "\nADDRESS";
    cout << setw(20) << "PREV";
    cout << setw(20) << "DATA";
    cout << setw(20) << "NEXT\n";
    output_file << setw(10) << "\nADDRESS";
    output_file << setw(20) << "PREV";
    output_file << setw(20) << "DATA";
    output_file << setw(20) << "NEXT\n";
    while (traverse_node != NULL) {
      cout << setw(5) << traverse_node->address;
      output_file << setw(5) << traverse_node->address;
      if (traverse_node->prev != NULL) {
        cout << setw(15) << traverse_node->prev->address;
        output_file << setw(15) << traverse_node->prev->address;
      } else {
        cout << setw(15) << "0x0";
        output_file << setw(15) << "0x0";
      }
      cout << setw(20) << traverse_node->value;
      output_file << setw(20) << traverse_node->value;
      if (traverse_node->next != NULL) {
        cout << setw(20) << traverse_node->next->address;
        output_file << setw(20) << traverse_node->next->address;
      } else {
        cout << setw(20) << "0x0";
        output_file << setw(20) << "0x0";
      }
      cout << '\n';
      output_file << '\n';
      traverse_node = traverse_node->next;
    }
    output_file.close();
  }
}

int main() {
  cout << "Enter the number of elements of the array: ";
  int n;
  cin >> n;
  cout << "Enter " << n << " elements: ";
  head = NULL;
  int a[n];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  CreateList(a, n);
  PrintList(1);
  BubbleSort();
  PrintList(2);
  return 0;
}
