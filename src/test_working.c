#include <stdio.h>
#include <stdlib.h>

struct Node {
  const int item;
  struct Node *prev;
  struct Node *next;
};

struct LinkedList {
  struct Node *fst;
  struct Node *lst;
  size_t size;
};

void add(struct LinkedList *list, struct Node *addable) {
  struct Node *l = list->lst;
  list->lst = addable;

  if (l == NULL) {
    list->fst = addable;
  } else {
    l->next = addable;
  }
  list->size++;
}

void printEach(struct LinkedList *list) {
    struct Node *node = list -> fst;
    do {
        printf("%d\n", node -> item);
        node = node -> next;        
    } while (node != NULL);
}

int main() {
    struct LinkedList *list = malloc(sizeof(struct Node));
    list = &(struct LinkedList){ .fst = NULL, .lst = NULL, .size = 0 };

    struct Node *ele = malloc(sizeof(struct Node));
    ele = &(struct Node){ .prev = NULL, .next = NULL, .item = -25 };

    struct Node *ele2 = malloc(sizeof(struct Node));
    ele2 = &(struct Node){ .prev = NULL, .next = NULL, .item = 13 };

    add(list, ele);    
    add(list, ele2);    
    
    // printf("%d\n", list -> fst -> item);
    printEach(list);
}
