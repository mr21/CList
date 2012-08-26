#include	<stdlib.h>
#include	"CList.h"

static void	add(CList* li, CList* la)
{
  li->size += la->size;
  CList_init(la);
}

CList*		CList_merge_back(CList* li, CList* la)
{
  if (li != la && la && la->size)
    {
      li->end->next = la->begin;
      la->begin->prev = li->end;
      li->end = la->end;
      add(li, la);
    }
  return li;
}

CList*		CList_merge_front(CList* li, CList* la)
{
  if (li != la && la && la->size)
    {
      li->begin->prev = la->end;
      la->end->next = li->begin;
      li->begin = la->begin;
      add(li, la);
    }
  return li;
}

CList*		CList_merge_after(CList* li, CLink* ln, CList* la)
{
  if (li && li->end == ln)
    return CList_merge_back(li, la);
  if (li != la && la && la->size && ln)
    {
      la->begin->prev = ln;
      la->end->next = ln->next;
      ln->next->prev = la->end;
      ln->next = la->begin;
      add(li, la);
    }
  return li;
}

CList*		CList_merge_before(CList* li, CLink* ln, CList* la)
{
  if (li && li->begin == ln)
    return CList_merge_front(li, la);
  if (li != la && la && la->size && ln)
    {
      la->begin->prev = ln->prev;
      la->end->next = ln;
      ln->prev->next = la->begin;
      ln->prev = la->end;
      add(li, la);
    }
  return li;
}
