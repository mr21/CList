#include	"CList.h"

CLink*		CList_find_after(CLink const* ln, void const* data)
{
  for (; ln && ln->data != data; ln = ln->next);
  return (CLink*)ln;
}

CLink*		CList_find_before(CLink const* ln, void const* data)
{
  for (; ln && ln->data != data; ln = ln->prev);
  return (CLink*)ln;
}

CLink*		CList_find_front(CList const* li, void const* data)
{
  return CList_find_after(CList_begin(li), data);
}

CLink*		CList_find_back(CList const* li, void const* data)
{
  return CList_find_before(CList_end(li), data);
}
