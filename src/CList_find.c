#include	"CList.h"

CLink*		CList_pfind_after(CLink const* ln, void const* data)
{
  for (; ln && ln->data != data; ln = ln->next);
  return (CLink*)ln;
}

CLink*		CList_pfind_before(CLink const* ln, void const* data)
{
  for (; ln && ln->data != data; ln = ln->prev);
  return (CLink*)ln;
}

CLink*		CList_pfind_front(CList const* li, void const* data)
{
  return CList_pfind_after(CList_begin(li), data);
}

CLink*		CList_pfind_back(CList const* li, void const* data)
{
  return CList_pfind_before(CList_end(li), data);
}

CLink*          CList_ffind_after(CLink const* ln, int (*f)())
{
  for (; ln && f(ln->data) == CLIST_CONTINUE; ln = ln->next);
  return (CLink*)ln;
}

CLink*          CList_ffind_before(CLink const* ln, int (*f)())
{
  for (; ln && f(ln->data) == CLIST_CONTINUE; ln = ln->prev);
  return (CLink*)ln;
}

CLink*		CList_ffind_front(CList const* li, int (*f)())
{
  return CList_ffind_after(CList_begin(li), f);
}

CLink*		CList_ffind_back(CList const* li, int (*f)())
{
  return CList_ffind_before(CList_end(li), f);
}
