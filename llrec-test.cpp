#include <iostream>
#include <fstream>
#include <functional>
#include "llrec.h"
using namespace std;

/**
 * Reads integers (separated by whitespace) from a file
 * into a linked list.
 *
 * @param[in] filename
 *  The name of the file containing the data to read
 * @return
 *  Pointer to the linked list (or NULL if empty or the
 *  file is invalid)
 */
Node* readList(const char* filename);

/**
 * Prints the integers in a linked list pointed to
 * by head.
 */
void print(Node* head);

/**
 * Deallocates the linked list nodes
 */
void dealloc(Node* head);


Node* readList(const char* filename)
{
    Node* h = NULL;
    ifstream ifile(filename);
    int v;
    if( ! (ifile >> v) ) return h;
    h = new Node(v, NULL);
    Node *t = h;
    while ( ifile >> v ) {
        t->next = new Node(v, NULL);
        t = t->next;
    }
    return h;
}

void print(Node* head)
{
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void dealloc(Node* head)
{
    Node* temp;
    while(head) {
        temp = head->next;
        delete head;
        head = temp;
    }
}

// -----------------------------------------------
//   Add any helper functions or
//   function object struct declarations
// -----------------------------------------------
#include <functional>

struct OddValueRemover {
    bool operator()(int val) { return val % 2 != 0; }
};

struct EvenValueRemover {
    bool operator()(int val) { return val % 2 == 0; }
};




int main(int argc, char* argv[])
{
    if(argc < 2) {
        cout << "Please provide an input file" << endl;
        return 1;
    }

    // -----------------------------------------------
    // Feel free to update any code below this point
    // -----------------------------------------------
    Node* head = readList(argv[1]);
    cout << "Original list: ";
    print(head);

    // Test out your linked list code
    cout << "\n----- Testing llpivot -----" << endl;
    Node* head_copy = readList(argv[1]);
    Node* smaller = nullptr;
    Node* larger = nullptr;
    int pivot = 10;
    
    cout << "Original list for pivot: ";
    print(head_copy);
    cout << "Pivot value: " << pivot << endl;
    
    llpivot(head_copy, smaller, larger, pivot);
    
    cout << "After pivot:" << endl;
    cout << "Head (should be NULL): ";
    print(head_copy);
    cout << "Smaller list (values <= " << pivot << "): ";
    print(smaller);
    cout << "Larger list (values > " << pivot << "): ";
    print(larger);
    
    dealloc(smaller);
    dealloc(larger);
    
    cout << "\n----- Testing llfilter with OddValueRemover -----" << endl;
    Node* filter_test1 = readList(argv[1]);
    cout << "Original list: ";
    print(filter_test1);
    
    OddValueRemover odd_remover;
    Node* even_only = llfilter(filter_test1, odd_remover);
    
    cout << "After filtering out odd numbers: ";
    print(even_only);
    
    cout << "\n----- Testing llfilter with EvenValueRemover -----" << endl;
    Node* filter_test2 = readList(argv[1]);
    cout << "Original list: ";
    print(filter_test2);
    
    EvenValueRemover even_remover;
    Node* odd_only = llfilter(filter_test2, even_remover);
    
    cout << "After filtering out even numbers: ";
    print(odd_only);
    
    dealloc(even_only);
    dealloc(odd_only);


    
    return 0;

}
