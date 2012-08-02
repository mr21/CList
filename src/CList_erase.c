#include	<stdlib.h>
#include	"CList.h"

CLink*		CList_erase(CLink* ln)
{
  CList*	li;
  CLink*	ln_ret;

  if (!ln)
    return NULL;
  li = ln->list;
  if (ln == li->begin)
    return CList_pop_front(li);
  if (ln == li->end)
    return CList_pop_back(li);
  ln->prev->next = ln_ret = ln->next;
  ln->next->prev = ln->prev;
  --li->size;
  if (li->des)
    li->des(ln->data);
  free(ln);
  return ln_ret;
}
