#include	<stdlib.h>
#include	"CList.h"

static CLink*	newLink(CList* li, void *data)
{
  CLink*	new = malloc(sizeof *new);

  if (new)
    {
      ++li->length;
      new->list = li;
      new->data = data;
      new->prev = new->next = NULL;
      if (!li->first)
	li->first = li->last = new;
    }
  return new;
}

CLink*		CList_push_front(CList* li, void *data)
{
  CLink*	new = newLink(li, data);

  if (new && li->length > 1)
    {
      new->next = li->first;
      li->first->prev = new;
      li->first = new;
    }
  return new;
}

CLink*		CList_push_back(CList* li, void *data)
{
  CLink*	new = newLink(li, data);

  if (new && li->length > 1)
    {
      new->prev = li->last;
      li->last->next = new;
      li->last = new;
    }
  return new;
}
