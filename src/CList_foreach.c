#include	"CList.h"

void		CList_foreach(CList* li, int (*f)())
{
  CLink*	ln = CList_begin(li);

  while (ln)
    switch (f(ln->data))
      {
      case CLIST_CONTINUE:	ln = ln->next;			break;
      case CLIST_ERASE:		ln = CList_erase(li, ln);	break;
      case CLIST_ERASE_STOP:	CList_erase(li, ln);
      default:			return;
      }
}
