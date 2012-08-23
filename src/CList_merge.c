#include	<stdlib.h>
#include	"CList.h"

CList*		CList_merge_back(CList* li, CList* la)
{
  if (li && la && la->size)
    {
      li->end->next = la->begin;
      la->begin->prev = li->end;
      li->end = la->end;
      li->size += la->size;
      CList_init(la, la->free);
    }
  return li;
}

CList*		CList_merge_front(CList* li, CList* la)
{
  if (li && la && la->size)
    {
      li->begin->prev = la->end;
      la->end->next = li->begin;
      li->begin = la->begin;
      li->size += la->size;
      CList_init(la, la->free);
    }
  return li;
}
