#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list_node {
  char *name;
  struct list_node *previous;
  struct list_node *next;
};

typedef struct list_node node;

// count the elements in the list.
int count(node *head) {
  int count = 0;
  while (head) {
    count++;
    head = head->next;
  }
  return count;
}

node *get_by_index(int index, node *head) {
  int counter = count(head);
  int i = 0;
  if (index < 0 || index > counter) {
    return NULL;
  }
  for (i = 0; i <= index; i++) {
    if (i == index) {
      return head;
    }
    head = head->next;
  }
  return head;
}

node *remove_first(node *head) {
  head = head->next;
  free(head->previous);
  head->previous = NULL;
  return head;
}

int remove_last(node *head) {
  while (head) {
    if (head->next->next == NULL) {
      free(head->next);
      head->next = NULL;
      return 0;
    }
    head = head->next;
  }
  return -1;
}

node *remove_at_index(int index, node *head) {
  node *current;
  if (index == 0) {
    return remove_first(head);
  } else if (index < 0) {
    return head;
  }
  current = get_by_index(index, head);
  if (current == NULL) {
    return head;
  }

  // jump over current element
  current->previous->next = current->next;
  if (current->next != NULL) {
    // cut out current from the next element
    current->next->previous = current->previous;
  }
  free(current);
  return head;
}

node *add_first(char *name, node *head) {
  node *new_node;
  new_node = (node *)malloc(sizeof(node));
  new_node->name = name;
  new_node->next = head;
  if (head != NULL) {
    head->previous = new_node;
  }
  head = new_node;
  return head;
}

void add_after(char *name, node *head) {
  node *new_node;
  new_node = (node *)malloc(sizeof(node));
  new_node->name = name;
  new_node->next = head->next;
  new_node->previous = head;
  new_node->next->previous = new_node;
  head->next = new_node;
}

void add_last(char *name, node *current) {
  node *new_node;
  new_node = (node *)malloc(sizeof(node));
  while (current) {
    if (current->next == NULL) {
      current->next = new_node;
      new_node->name = name;
      new_node->previous = current;
      return;
    }
    current = current->next;
  }
}

void print_list(node *current) {
  printf("HEAD: ");
  while (current) {
    printf("%s", current->name);
    printf(" -> ");
    current = current->next;
  }
  printf("\b\b\b\b :TAIL\n");
}

void print_list_from_tail(node *current) {
  // get the last element
  current = get_by_index(count(current) - 1, current);
  printf("TAIL: ");
  while (current) {
    printf("%s", current->name);
    printf(" <- ");
    current = current->previous;
  }
  printf("\b\b\b\b :HEAD\n");
}

void print_list_backwards(node *current) {
  printf("TAIL: ");
  while (current) {
    printf("%s", current->name);
    printf(" <- ");
    current = current->previous;
  }
  printf("\b\b\b\b :HEAD\n");
}

int main(void) {
  node *head = NULL;
  node *tail = NULL;
  int number = 0;

  // set the head
  head = add_first("Alpha", head);

  // add to the end
  add_last("Bravo", head);
  add_last("Charlie", head);
  add_last("Delta", head);
  add_last("Echo", head);
  add_last("Foxtrot", head);
  add_last("Golf", head);
  add_last("Hotel", head);
  add_last("India", head);
  add_last("Juliet", head);
  add_last("Kilo", head);
  add_last("Lima", head);

  // print original list
  print_list(head);
  tail = get_by_index(count(head) - 1, head);
  printf("\nPrinted backwards:\n");
  print_list_backwards(tail);
  printf("\n");

  // remove the last element
  tail = get_by_index(count(head) - 1, head);
  printf("Remove the last element: [%s]\n", tail->name);
  number = remove_last(head);
  print_list(head);
  printf("\n");

  return 0;
}
