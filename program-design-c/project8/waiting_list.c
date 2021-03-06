/* Author: Oleksandr Lisnichenko
 * this program implements a day care
 * center management system
 * 
 * I implemented the functions
 * add, update, etc.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ROOM_LEN 100
#define NAME_LEN 30
#define PHONE_LEN 15

struct request {
	char classroom[ROOM_LEN];
	char first[NAME_LEN + 1];
	char last[NAME_LEN + 1];
	char phone[PHONE_LEN + 1];

	struct request *next;
};


struct request *append_to_list(struct request *list);
void update(struct request *list);
void printList(struct request *list);
void clearList(struct request *list);
int read_line(char str[], int n);

// function for error exit
void err(char *message) {
  puts(message);
  exit(1);
}

/**********************************************************
 * main: Prompts the user to enter an operation code,     *
 *       then calls a function to perform the requested   *
 *       action. Repeats until the user enters the        *
 *       command 'q'. Prints an error message if the user *
 *       enters an illegal code.                          *
 **********************************************************/
int main(void) {
  char code;

  struct request *wait_list = NULL;
  printf("Operation Code: a for appending to the list, u for updating a book"
	  ", p for printing the list; q for quit.\n");
  for (;;) {
    printf("Enter operation code: ");
    scanf(" %c", &code);
    while (getchar() != '\n')   /* skips to end of line */
      ;
    switch (code) {
      case 'a': wait_list = append_to_list(wait_list); break;
      case 'u': update(wait_list); break;
      case 'p': printList(wait_list); break;
      case 'q': clearList(wait_list); return 0;
      default:  printf("Illegal code\n");
    }
    printf("\n");
  }
}

//function to append a new request to the list
struct request *append_to_list(struct request *list){
    struct request *child = malloc(sizeof(struct request));
    struct request *head;
    if (!(child)) { err("Failed to allocate memory in append_to_list()"); }

    //getting new request details
    printf("Enter child's classroom: ");
    read_line(child->classroom, ROOM_LEN);

    printf("Enter child's first name: ");
    read_line(child->first, NAME_LEN);

    printf("Enter child's last name : ");
    read_line(child->last, NAME_LEN);

    // looping through the list and looking for duplicate
    head = list;
    while (head != NULL) {
        // checking if the record already exists
        if (!(strcmp(head->classroom, child->classroom)) && !(strcmp(head->first, child->first)) && !(strcmp(head->last, child->last))) {
            printf("Oopsie, the record already exists. Please use update option\n");
            // deallocate memory and return list
            free(child);
            return list;
        }
        // go onto the next one
        head = head->next;
    }

    printf("Enter phone number : ");
    read_line(child->phone, PHONE_LEN);
    //setting next pointer of new request struct to NULL
    child->next = NULL;

    if (list == NULL) { return child; }

    //finding the las element in the list
    head = list;
    while (head->next != NULL)
        head = head->next;

    //linking the new request node to the last node of the list
    head->next = child;
    return list;
}

//function to update a child details
void update(struct request *list) {
    char classroom[ROOM_LEN];
    char first[NAME_LEN + 1];
    char last[NAME_LEN + 1];
    struct request *head;

    // check for dynamic allocation?
    // this doesn't work and I don't know why
    // struct request *head = malloc(sizeof(struct request *))

    //if the queue is empty
    if (list == NULL) { printf("The list is empty\n"); return; }

    printf("Enter the classroom: ");
    read_line(classroom, ROOM_LEN);

    printf("Enter child's first name: ");
    read_line(first, NAME_LEN);

    printf("Enter child's last name : ");
    read_line(last, NAME_LEN);

    head = list;
    while (head != NULL) {
        // if the info entered is in the list
        if (!(strcmp(head->classroom, classroom)) && !(strcmp(head->first, first)) && !(strcmp(head->last, last))) {
            printf("Enter the new class room: ");
            read_line(head->classroom, ROOM_LEN);
            // exiting the function if the record is found
            return;
        }
        head = head->next;
    }

    //child details not found
    printf("Oopsie, we couldn't find the info entered. Please check back in later\n");
}

//function to print the whole list
void printList(struct request *list) {
    printf("Classroom            First name           Last name            Phone\n");
    // looping through the list
    while (list != NULL) {
        // printing in format
        printf("%-20s %-20s %-20s %-20s\n", list->classroom, list->first, list->last, list->phone);
        list = list->next;
    }
}

void clearList(struct request *list) {
    struct request *next = NULL;
    while (list != NULL) {
        next = list->next;
        // deallocating the node and skipping to the next one
        free(list);
        list = next;
    }
}

int read_line(char str[], int n) {
    int ch, i = 0;

    while (isspace(ch = getchar()))
    ; // that is a weird style...
    str[i++] = ch;
    while ((ch = getchar()) != '\n') {
        if (i < n)
            str[i++] = ch;
    
    }
   str[i] = '\0';
   return i;
}