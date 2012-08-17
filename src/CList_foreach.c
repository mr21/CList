#include	"CList.h"

void		CList_foreach(CList const* li, int (*f)())
{
  CLink*	ln = CList_begin(li);

  while (ln)
    switch (f(ln->data))
      {
      case CLIST_NEXT:	ln = ln->next;		break;
      case CLIST_ERASE:	ln = CList_erase(ln);	break;
      default:		return;
      }
}
