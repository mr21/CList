#include	<stdlib.h>
#include	"CList.h"

void		CList_pop_front(CList* li)
{
  CLink*	ln;

  if (!li->first)
    return;
  --li->length;
  ln = li->first;
  if (!(li->first = ln->next))
    li->last = NULL;
  else
    li->first->prev = NULL;
  if (li->des)
    li->des(ln->data);
  free(ln);
}

void		CList_pop_back(CList* li)
{
  CLink*	ln;

  if (!li->last)
    return;
  --li->length;
  ln = li->last;
  if (!(li->last = ln->prev))
    li->first = NULL;
  else
    li->last->next = NULL;
  if (li->des)
    li->des(ln->data);
  free(ln);
}

CLink*		CList_erase(CLink* ln)
{
  CList*	li;
  CLink*	ln_ret;

  if (!ln)
    return NULL;
  li = ln->list;
  if (ln == li->first)
    CList_pop_front(li);
  else if (ln == li->last)
    CList_pop_back(li);
  else
    {
      ln->prev->next = ln_ret = ln->next;
      ln->next->prev = ln->prev;
      --li->length;
      if (li->des)
	li->des(ln->data);
      free(ln);
    }
  return ln_ret;
}
