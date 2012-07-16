#include	"CList.h"

CLink*		CList_find_data(CList* li, void* data)
{
  CLink*	ln = li->first;

  while (ln && ln->data != data)
    ln = ln->next;
  return ln;
}
