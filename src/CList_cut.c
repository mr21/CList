#include	<stdlib.h>
#include	"CList.h"
/*
static size_t	len(CLink* a, CLink* b)
{
  size_t	s = 1;

  for (; a != b; a = a->next)
    if (a)
      ++s;
    else
      return 0;
  return s;
}

CList*		CList_cut(CList* li, CLink* lna, CLink* lnb)
{
  CList*	la;
  size_t	sz;

  if (li && lna && lnb && (la = malloc(sizeof *la)))
    {
      la->begin = lna;
      la->end = lnb;

      if (lna->prev)
	lna->prev->next = lnb->next;
      else
	li->begin = lnb->next;

      if (lnb->next)
	lnb->next->prev = lna->prev;
      else
	li->end = lna->prev;

      la->begin->prev = lnb->next = NULL;

      la->size = sz;
      li->size -= sz;
    }
  return la;
}
*/
