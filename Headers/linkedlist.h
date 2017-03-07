#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include "header.h"
#include "member.h"

// Trick the Compiler
typedef struct head head;
typedef struct nav nav;

// Navigation Node (LL)
struct nav
{
  head   *list;
  nav    *next;
  nav    *prev;
  member *mem;
};

// Head Node (LL)
struct head
{
  int size;
  nav *first;
  nav *last;
};

/***********************************************************
 * BuildList - Add to Linked List
 * Returns the address for the member node to be filled out
 * *********************************************************/
member* buildll(head &top);


#endif