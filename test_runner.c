#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linked_list.h"

#define TRUE  1
#define FALSE 0

void test_ll_new(void);
void test_ll_isempty(void);
struct Node* make_test_linkedlist(void);

int main() {
    printf("running tests\n");
    test_ll_new();
    test_ll_isempty();
}

void test_ll_new(void)
{
    struct Node* myll = ll_new();
    assert(sizeof(*myll) == sizeof(struct Node));
    assert(myll->next == NULL);
    assert(myll->data == NULL);
}

void test_ll_isempty(void)
{
    struct Node* empty_linkedlist;
    assert(ll_isempty(empty_linkedlist) == TRUE);

    struct Node* nonempty_linkedlist = ll_new();
    assert(ll_isempty(nonempty_linkedlist) == TRUE);

    struct Node* ll = make_test_linkedlist();
    assert(ll_isempty(ll) == FALSE);
}

struct Node* make_test_linkedlist(void)
{
    struct Node* node_a = malloc(sizeof(struct Node));
    int x = 1;
    node_a->data = &x;

    struct Node* node_b = malloc(sizeof(struct Node));
    int y = 2;
    node_b->data = &y;

    struct Node* node_c = malloc(sizeof(struct Node));
    int z = 3;
    node_c->data = &z;

    node_a->next = node_b;
    node_b->next = node_c;

    return node_a;
}
