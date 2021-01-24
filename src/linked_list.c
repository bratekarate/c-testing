#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODE_SIZE sizeof(Node)
#define LINKED_LIST_SIZE sizeof(LinkedList)

typedef struct Node Node;
typedef struct LinkedList LinkedList;

// High level functions
LinkedList *new_list();
void list_add(LinkedList *list, const int item);
void list_add_all(LinkedList *list, LinkedList *addable);
int list_get(LinkedList *list, const size_t index);
int list_remove(LinkedList *list, const size_t index);
int list_remove_h(LinkedList *list);
void list_print(LinkedList *list);
void list_free(LinkedList *list);

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

  for(int i = 0; i < 15; i++) {
      list_add(list, i);
  }

  list_print(list);

  LinkedList *list2 = new_list();

  for(int i = 500; i < 500 + list -> size; i++) {
      list_add(list2, i);
  }

  list_print(list2);

  list_add_all(list, list2);

  list_print(list);
  printf("list[%d] = %d\nremove %d.\n", 1, 1, list_remove(list, 1));
  list_print(list);
  printf("list[%d] = %d\n", 1, list_get(list, 1));
  printf("list[0] = %d\nremove 0.\n", list_remove_h(list));
  list_print(list);
  printf("list[0] = %d\n", list_get(list, 0));

  list_free(list);
  list = NULL;

  return EXIT_SUCCESS;
}

LinkedList *new_list() {
  LinkedList *list = malloc(LINKED_LIST_SIZE);
  init_list(&list);
  return list;
}

void list_add(LinkedList *list, const int item) {
  Node *node = malloc(NODE_SIZE);
  /*printf("Create node %p\n", node);*/
  add_node(list, &node, item);
}

void list_add_all(LinkedList *list, LinkedList *addable) {
   Node *cur = addable -> fst;  
   while (cur != NULL) {
       list_add(list, cur -> item);
       cur = cur -> next;
   }
}

// TODO: handle index out of bounds
int list_get(LinkedList *list, const size_t index){
    // TODO: if index is past middle, go backwards
    Node *cur = list -> fst;
    for(size_t i = 0; i < index; i++) {
        cur = cur -> next;
    }
    return cur -> item;
}

// TODO: handle index out of bounds
int list_remove(LinkedList *list, const size_t index){
    Node *cur = list -> fst;
    for(size_t i = 0; i < index; i++) {
        cur = cur -> next;
    }

    Node *prev = cur -> prev;
    Node *next = cur -> next;
    if(prev != NULL) {
        /*printf("cur -> prev: %d\n", cur -> prev -> item);*/
        prev -> next = next;
    }

    if(next != NULL) {
        /*printf("cur -> next: %d\n", cur -> next -> item);*/
        next -> prev = prev;
    }

    if (cur == list -> fst) {
        list -> fst = cur -> next;
    }

    if (cur == list -> lst) {
        list -> lst = cur -> prev;
    }

    list -> size--;

    int item = cur -> item;
    free(cur);

    return item;
}

// TODO: handle list empty
int list_remove_h(LinkedList *list){
    return list_remove(list, 0);
}

// TODO: how to set null
void list_free(LinkedList *list) {
    free_nodes(list->lst);
    free(list);
}

// TODO: how to set null
void free_nodes(Node *node) {
    while(node != NULL) {
        Node *prev = node->prev;
        /*printf("Free node %p with item %d\n", node, node -> item);*/
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

// TODO: make tostring
void list_print(LinkedList *list) {
    print_nodes(list->fst);
}

void print_nodes(Node *node) {
    printf("[ ");
    while (node != NULL) {
        char *rest = node -> next == NULL ? " " : ", ";
        printf("%d%s", node->item, rest);
        node = node -> next;
    }
    printf("]\n");
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

