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
	  new->data = &new->data + 1;
	  data ? memcpy(new->data, data, sz) :
	    memset(new->data, 0, sz);
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
