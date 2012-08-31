#include	"CList.h"

CList*		CLink_list(CLink const* ln)      { return ln ? ln->list : NULL; }
void*		CLink_data(CLink const* ln)      { return ln ? ln->data : NULL; }
void		(*CLink_free(CLink const* ln))() { return ln ? ln->free : NULL; }

CLink*		CLink_prev(CLink const* ln, size_t n)
{
  for (; ln && n; ln = ln->prev, --n);
  return (CLink*)ln;
}

CLink*		CLink_next(CLink const* ln, size_t n)
{
  for (; ln && n; ln = ln->next, --n);
  return (CLink*)ln;
}
