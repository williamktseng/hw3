#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot)
{
    if (head == NULL) {
        smaller = NULL;
        larger = NULL;
        return;
    }
    
    Node* current = head;
    head = head->next; // Move head to the next node
    
    llpivot(head, smaller, larger, pivot); // Recurse
    
    if (current->val <= pivot) {
        current->next = smaller;
        smaller = current;
    } else {
        current->next = larger;
        larger = current;
    }
    
    head = NULL; // Ensure the original list no longer exists
}
