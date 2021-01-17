#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

struct Node {
  struct Node *next;
  int value;
};

void printList(struct Node *iter) {

  do {
    printf("%d\n", iter->value);
    iter = iter->next;
  } while (iter != NULL);
}

struct Node *Node(int i) {
  struct Node *head = (struct Node *)malloc(sizeof(struct Node));
  head->value = i;
  head->next = NULL;
  return head;
}

void prepend(struct Node **node, int i) {
  struct Node *new_node = Node(i);
  new_node->next = *node;
  *node = new_node;
}

void append(struct Node **node, int i) {
  struct Node *new_node = Node(i);
  
  struct Node *head_node = *node;

  while (head_node->next != NULL) {
      head_node = head_node-> next;
  }

  head_node->next = new_node;
}

int main() {
    struct GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
  /*struct Node *head = NULL;*/
  /*struct Node *ele1 = NULL;*/
  /*struct Node *tail = NULL;*/

  /*head = (struct Node *)malloc(sizeof(struct Node));*/
  /*ele1 = (struct Node *)malloc(sizeof(struct Node));*/
  /*tail = (struct Node *)malloc(sizeof(struct Node));*/

  /*head->value = 1;*/
  /*head->next = ele1;*/

  /*ele1->value = 2;*/
  /*ele1->next = tail;*/

  /*tail->value = 3;*/
  /*tail->next = NULL;*/

  struct Node *head = Node(1);
  prepend(&head, 2);
  prepend(&head, 3);
  append(&head, 10);

  printList(head);
  printf("\nhead is %d\n", head->value);
}
