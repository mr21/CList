#include	<stdlib.h>
#include	"CList.h"

CLink*		CList_pop_front(CList* li)
{
  CLink*	ln = li->first;

  if (!ln)
    return NULL;
  --li->length;
  if (!(li->first = ln->next))
    li->last = NULL;
  else
    li->first->prev = NULL;
  if (li->des)
    li->des(ln->data);
  free(ln);
  return li->first;
}

CLink*		CList_pop_back(CList* li)
{
  CLink*	ln = li->last;

  if (!ln)
    return NULL;
  --li->length;
  if (!(li->last = ln->prev))
    li->first = NULL;
  else
    li->last->next = NULL;
  if (li->des)
    li->des(ln->data);
  free(ln);
  return li->last;
}

CLink*		CList_erase(CLink* ln)
{
  CList*	li;
  CLink*	ln_ret;

  if (!ln)
    return NULL;
  li = ln->list;
  if (ln == li->first)
    return CList_pop_front(li);
  if (ln == li->last)
    return CList_pop_back(li);
  ln->prev->next = ln_ret = ln->next;
  ln->next->prev = ln->prev;
  --li->length;
  if (li->des)
    li->des(ln->data);
  free(ln);
  return ln_ret;
}
