#include	"CList.h"

CLink*		CList_find_data(CList const* li, void const* data)
{
  CLink*	ln = CList_begin(li);

  while (ln && ln->data != data)
    ln = ln->next;
  return ln;
}
