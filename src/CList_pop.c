#include	<stdlib.h>
#include	"CList.h"

CLink*		CList_pop_front(CList* li)
{
  CLink*	ln = li->begin;

  if (!ln)
    return NULL;
  --li->size;
  if (!(li->begin = ln->next))
    li->end = NULL;
  else
    li->begin->prev = NULL;
  if (ln->free)
    ln->free(ln->data);
  free(ln);
  return li->begin;
}

CLink*		CList_pop_back(CList* li)
{
  CLink*	ln = li->end;

  if (!ln)
    return NULL;
  --li->size;
  if (!(li->end = ln->prev))
    li->begin = NULL;
  else
    li->end->next = NULL;
  if (ln->free)
    ln->free(ln->data);
  free(ln);
  return li->end;
}

CLink*		CList_pop(CLink* ln)
{
  CList*	li = CLink_list(ln);
  CLink*	ln_ret;

  if (!li)
    return NULL;
  if (ln == li->begin)
    return CList_pop_front(li);
  if (ln == li->end)
    return CList_pop_back(li), NULL;
  ln->prev->next = ln_ret = ln->next;
  ln->next->prev = ln->prev;
  --li->size;
  if (ln->free)
    ln->free(ln->data);
  free(ln);
  return ln_ret;
}

CLink*		CList_popn(CLink* a, CLink* b)
{
  CList*	li = a->list;
  CLink*	ln = a, *tmp, *b_next = b->next;

  if (!a->prev)
    li->begin = b->next;
  else
    a->prev->next = b->next;
  if (!b->next)
    li->end = a->prev;
  else
    b->next->prev = a->prev;
  for (; ln != b_next; ln = tmp)
    {
      tmp = ln->next;
      if (ln->free)
        ln->free(ln->data);
      free(ln);
      --li->size;
    }
  return tmp;
}
