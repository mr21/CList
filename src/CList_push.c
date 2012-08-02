#include	<stdlib.h>
#include	<string.h>
#include	"CList.h"

static CLink*	newLink(CList* li, void* data, size_t sz)
{
  CLink*	new = malloc(sizeof(*new) + sz);

  if (new)
    {
      new->list = li;
      new->prev = new->next = NULL;
      if (!sz)
	new->data = data;
      else
	{
	  data ? memcpy(&new->data_area, data, sz) :
	    memset(&new->data_area, 0, sz);
	  new->data = &new->data_area;
	}
      if (++li->size == 1)
	li->begin = li->end = new;
    }
  return new;
}

CLink*		CList_push_front(CList* li, void* data, size_t sz)
{
  CLink*	new = newLink(li, data, sz);

  if (new && li->size > 1)
    {
      new->next = li->begin;
      li->begin->prev = new;
      li->begin = new;
    }
  return new;
}

CLink*		CList_push_back(CList* li, void* data, size_t sz)
{
  CLink*	new = newLink(li, data, sz);

  if (new && li->size > 1)
    {
      new->prev = li->end;
      li->end->next = new;
      li->end = new;
    }
  return new;
}
