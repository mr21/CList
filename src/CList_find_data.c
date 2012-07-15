#include	"CList.h"

CLink*		CList_find_data(CList* li, void* data)
{
  CLink*	ln;

  for (ln = li->first; ln && ln->data != data; ln = ln->next);
  return ln;
}
