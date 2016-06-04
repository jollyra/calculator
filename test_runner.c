#include <stdio.h>
#include <assert.h>
#include "linked_list.h"

void test_ll_new(void);

int main() {
    printf("running tests\n");
    test_ll_new();
}

void test_ll_new(void)
{
    struct Node* myll = ll_new();
    assert(sizeof(*myll) == sizeof(struct Node));
    assert(myll->next == NULL);
    assert(myll->data == NULL);
}
