#include	"CList.h"

CList*		CList_move_back(CLink* lna, CLink* lnb, CList* li)
{
  CList		tmpli;

  CList_extract(lna, lnb, &tmpli);
  return CList_merge_back(li, &tmpli);
}

CList*		CList_move_front(CLink* lna, CLink* lnb, CList* li)
{
  CList		tmpli;

  CList_extract(lna, lnb, &tmpli);
  return CList_merge_front(li, &tmpli);
}

CList*		CList_move_after(CLink* lna, CLink* lnb, CLink* lnc)
{
  CList		tmpli;

  CList_extract(lna, lnb, &tmpli);
  return CList_merge_after(lnc, &tmpli);
}

CList*		CList_move_before(CLink* lna, CLink* lnb, CLink* lnc)
{
  CList		tmpli;

  CList_extract(lna, lnb, &tmpli);
  return CList_merge_before(lnc, &tmpli);
}
