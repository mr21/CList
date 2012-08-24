#include	<stdlib.h>
#include	"CList.h"

CLink*		CList_erase(CList* li, CLink* ln)
{
  CLink*	ln_ret;

  if (!ln)
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
