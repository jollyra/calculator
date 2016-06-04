#ifndef linked_list_h_
#define linked_list_h_

struct Node
{
    struct Node* next;
    void* data;
};

struct Node* ll_new(void);
void ll_append(struct Node* head, void* data);
struct Node* next(struct Node* current);
int ll_isempty(struct Node* head);
int ll_len(struct Node* head);

#endif
