#include	"CList.h"

size_t		CList__len_n_li(CLink* a, CLink* b, CList* la)
{
  size_t        s = 0;

  do
    ++s, a->list = la;
  while (a != b && (a = a->next));
  return s;
}
