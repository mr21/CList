#include	"CList.h"

void		CList_foreach(CList const* li, void (*f)())
{
  CLink*	ln;

  for (ln = CList_begin(li); ln; ln = ln->next)
    f(ln->data);
}
