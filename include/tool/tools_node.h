#ifndef NODE_CONTAINER
#define NODE_CONTAINER
#include<stdlib.h>
typedef struct Node
{
    void* Prev=0;
    void* value=0;
    void*  Next=0;
    void* traits=0;

}Node;
void free_node(Node*);
Node* node_find(Node*,void*);
void Node_init(Node*);
Node* node_copy(Node*);
int node_size(Node*);
Node* node_overlying(Node*,void*);
Node* node_reverse(Node*);

void node_elimnate(Node*);
Node *node_delete_value(Node*,void*);
#endif
