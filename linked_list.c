#include <stdlib.h>
#include "linked_list.h"

struct Node* ll_new(void)
{
    struct Node* ll = malloc(sizeof(struct Node));
    ll->next = NULL;
    ll->data = NULL;
    return ll;
}
// A linked list must have a head. If the head doesn't point to any next
// element then the list is empty.
int ll_isempty(struct Node* head)
{
    if(head->next == NULL)
    {
        return 1;
    } else {
        return 0;
    }
}
