#include	<stdlib.h>
#include	"CList.h"

void		CList_extract(CLink* lna, CLink* lnb, CList* newli)
{
  CList*	li = lna->list;

  newli->begin = lna;
  newli->end = lnb;
  newli->size = CList_count_n_li(lna, lnb, newli);
  li->size -= newli->size;
  if (lna->prev)
    lna->prev->next = lnb->next;
  else
    li->begin = lnb->next;
  if (lnb->next)
    lnb->next->prev = lna->prev;
  else
    li->end = lna->prev;
  lna->prev = lnb->next = NULL;
}

CList*		CList_cut(CLink* lna, CLink* lnb)
{
  CList*	la = malloc(sizeof *la);

  if (la)
    CList_extract(lna, lnb, la);
  return la;
}

CList*		CList_cut_back(CLink* ln)  { return CList_cut(ln, ln->list->end);   }
CList*		CList_cut_front(CLink* ln) { return CList_cut(ln->list->begin, ln); }
