#include	<stdlib.h>
#include	"CList.h"

CList*		CList_cut(CLink* lna, CLink* lnb)
{
  CList*	li = lna->list;
  CList*	la = malloc(sizeof *la);
  size_t	sz;

  if (la)
    {
      sz = CList__len_n_li(lna, lnb, la);
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
