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

void add(struct LinkedList *list, struct Node *addable, const int item) {
  addable = &(struct Node){ .prev = NULL, .next = NULL, .item = item };
  struct Node *l = malloc(sizeof(struct Node));
  l = list->lst;


  list->lst = addable;

  if (l == NULL) {
    printf("lst is null.\n");
    list->fst = addable;
  } else {
    printf("last is not null.\n");
    l->next = addable;
  }
  list->size++;
  printf("%d\n", list->fst->item);
}

void printEach(struct LinkedList *list) {
    struct Node *node = list -> fst;
    // do {
    //     printf("%d\n", node -> item);
    //     node = node -> next;
    // } while (node != NULL);
    for (size_t i = 0; i < 10; i++) {
        printf("%d\n", node -> item);
        node = node -> next;        
    }
}

int main() {
    struct LinkedList *list = malloc(sizeof(struct Node));
    list = &(struct LinkedList){ .fst = NULL, .lst = NULL, .size = 0 };

    struct Node *ele = malloc(sizeof(struct Node));
    struct Node *ele2 = malloc(sizeof(struct Node));
    struct Node *ele3 = malloc(sizeof(struct Node));

    add(list, ele, 256);    
    add(list, ele2, 124);
    // add(list, ele3, -245);
    
    // printf("%d\n", list -> fst -> item);
    // printEach(list);
}
