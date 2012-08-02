#include	<stdlib.h>
#include	"CList.h"

void		CList_clear(CList* li)
{
  CLink*	ln = li->first;
  CLink*	tmp;

  for (; ln; ln = tmp)
    {
      tmp = ln->next;
      if (li->des)
	li->des(ln->ptr_data);
      free(ln);
    }
  li->first = li->last = NULL;
  li->size = 0;
}
