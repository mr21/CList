#include	<stdlib.h>
#include	"CList.h"

void		CList_clear(CList* li)
{
  CLink*	ln = li->begin;
  CLink*	tmp;

  for (; ln; ln = tmp)
    {
      tmp = ln->next;
      if (li->des)
	li->des(ln->data);
      free(ln);
    }
  li->begin = li->end = NULL;
  li->size = 0;
}
