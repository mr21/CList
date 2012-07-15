#include	"CList.h"

void		CList_foreach(CList* li, void (*f)())
{
  CLink*	ln;

  for (ln = li->first; ln; ln = ln->next)
    f(ln->data);
}
