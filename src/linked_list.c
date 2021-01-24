#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODE_SIZE sizeof(Node)
#define LINKED_LIST_SIZE sizeof(LinkedList)

typedef struct Node Node;
typedef struct LinkedList LinkedList;

// High level functions
LinkedList *new_list();
void add(LinkedList *list, const int item);
void free_list(LinkedList *list);
void print_list(LinkedList *list);

// Low level functions
void init_list(LinkedList **list);
void init_node_p(Node **node, const int item);
void add_node(LinkedList *list, Node **node, const int item);
void print_nodes_rec_broken(Node *node);
void print_nodes(Node *node);
void free_nodes(Node *node);
void free_nodes_rec_broken(Node *node);

typedef struct Node {
  const int item;
  struct Node *prev;
  struct Node *next;
} Node;

typedef struct LinkedList {
  Node *fst;
  Node *lst;
  int size;
} LinkedList;

int main() {
  LinkedList *list = new_list();

  for(int i = 0; i < 1000000; i++) {
      add(list, i);
  }

  print_list(list);

  free_list(list);
  list = NULL;

  return EXIT_SUCCESS;
}

LinkedList *new_list() {
  LinkedList *list = malloc(LINKED_LIST_SIZE);
  init_list(&list);
  return list;
}

void add(LinkedList *list, const int item) {
  Node *node = malloc(NODE_SIZE);
  /*printf("Create node %p\n", node);*/
  add_node(list, &node, item);
}

// TODO: how to set null
void free_list(LinkedList *list) {
    free_nodes(list->lst);
    free(list);
}

// TODO: how to set null
void free_nodes(Node *node) {
    while(node != NULL) {
        Node *prev = node->prev;
        /*printf("Free node %p\n", node);*/
        free(node);
        node = prev;
    }
}

void free_nodes_rec_broken(Node *node) {
  if (node == NULL) {
    return;
  }
  free_nodes_rec_broken(node->next);
  /*printf("Free node %p\n", node);*/
  free(node);
  node = NULL;
}

void print_list(LinkedList *list) {
    print_nodes(list->fst);    
}

void print_nodes(Node *node) {
    while (node != NULL) {
        printf("%d\n", node->item);
        node = node -> next;
    }
}

void print_nodes_rec_broken(Node *node) {
  if (node == NULL) {
    return;
  }
  printf("%d\n", node->item);
  print_nodes_rec_broken(node->next);
}

void init_list(LinkedList **list) {
  LinkedList l = {.fst = NULL, .lst = NULL};
  **list = l;
}

void init_node_p(Node **node, const int item) {
  Node n = {.item = item, .next = NULL, .prev = NULL};
  memcpy(*node, &n, NODE_SIZE);
}

void add_node(LinkedList *list, Node **node, const int item) {
  init_node_p(node, item);

  Node *l = list->lst;

  list->lst = *node;

  if (l == NULL) {
    list->fst = *node;
  } else {
    l->next = *node;
    (*node)->prev = l;
  }
  list->size++;
}

