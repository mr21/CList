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
