#include	<stdlib.h>
#include	<string.h>
#include	"CList.h"

static CLink*	newLink(CList* li, void const* data, size_t sz)
{
  CLink*	new = malloc(sizeof(*new) + sz);

  if (new)
    {
      new->list = li;
      new->prev = new->next = NULL;
      sz && data ? memcpy(&new->data, data, sz) : (new->data = data);
      new->ptr_data = sz ? &new->data : data;
      if (++li->size == 1)
	li->first = li->last = new;
    }
  return new;
}

CLink*		CList_push_front(CList* li, void const* data, size_t sz)
{
  CLink*	new = newLink(li, data, sz);

  if (new && li->size > 1)
    {
      new->next = li->first;
      li->first->prev = new;
      li->first = new;
    }
  return new;
}

CLink*		CList_push_back(CList* li, void const* data, size_t sz)
{
  CLink*	new = newLink(li, data, sz);

  if (new && li->size > 1)
    {
      new->prev = li->last;
      li->last->next = new;
      li->last = new;
    }
  return new;
}
