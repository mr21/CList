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
  if (li->des)
    li->des(ln->data);
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
  if (li->des)
    li->des(ln->data);
  free(ln);
  return li->end;
}
