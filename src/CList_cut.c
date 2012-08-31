#include	<stdlib.h>
#include	"CList.h"

static size_t	len(CLink* a, CLink* b, CList* la)
{
  size_t	s = 0;

  do
    ++s, a->list = la;
  while (a != b && (a = a->next));
  return s;
}

CList*		CList_cut(CLink* lna, CLink* lnb)
{
  CList*	li = lna->list;
  CList*	la = malloc(sizeof *la);
  size_t	sz;

  if (la)
    {
      sz = len(lna, lnb, la);
      la->begin = lna;
      la->end = lnb;
      la->size = sz;
      li->size -= sz;
      if (lna->prev)
	lna->prev->next = lnb->next;
      else
	li->begin = lnb->next;
      if (lnb->next)
	lnb->next->prev = lna->prev;
      else
	li->end = lna->prev;
      la->begin->prev = lnb->next = NULL;
    }
  return la;
}

CList*		CList_cut_back(CLink* ln)  { return CList_cut(ln, ln->list->end);   }
CList*		CList_cut_front(CLink* ln) { return CList_cut(ln->list->begin, ln); }
