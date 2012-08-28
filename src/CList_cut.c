#include	<stdlib.h>
#include	"CList.h"

static size_t	len(CLink* a, CLink* b)
{
  size_t	s;

  if (!a || !b)
    return 0;
  for (s = 1; a != b; a = a->next)
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

  if (!li || !(sz = len(lna, lnb)) || !(la = malloc(sizeof *la)))
    return NULL;
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
  return la;
}

CList*		CList_cut_back(CList* li, CLink* ln)
{
  return CList_cut(li, ln, CList_end(li));
}

CList*		CList_cut_front(CList* li, CLink* ln)
{
  return CList_cut(li, CList_begin(li), ln);
}
