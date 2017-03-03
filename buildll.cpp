#include "header.h"
#include "member.h"

member* buildll(head &top)
{
  // Declaration(s)
  nav *pointer;

  // Create new nav node
  pointer = new nav;

  // Point at the top node
  pointer->list = &top;

  // Next points at nothing
  pointer->next = NULL;

  // Previous points at last
  pointer->prev = top.last;

  // The previous node points to the new node
  if(top.last != NULL)
  {
    top.last->next = pointer;
  }

  // Last points at created nav node
  top.last = pointer;

  // Top's first pointer points to the new node
  if(top.first == NULL)
  {
    top.first = pointer;
  }

  // Create new member node
  pointer->mem = new member;

  // Increment list size
  ++top.size;

  return pointer->mem;
}
