#include	"CList.h"

size_t		CList_count(CLink const* a, CLink const* b)
{
  size_t	n = 1;

  for (; a && a != b; a = a->next)
    ++n;
  return n;
}

size_t		CList_count_n_li(CLink* a, CLink* b, CList const* li)
{
  size_t	s = 0;

  do
    ++s, a->list = (CList*)li;
  while (a != b && (a = a->next));
  return s;
}
