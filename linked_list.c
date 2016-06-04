#include <stdlib.h>
#include "linked_list.h"

struct Node* ll_new(void)
{
    struct Node* ll = malloc(sizeof(struct Node));
    ll->next = NULL;
    ll->data = NULL;
    return ll;
}
