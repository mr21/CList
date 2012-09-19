#include	"CList.h"

CList*		CList_move_back(CLink* lna, CLink* lnb, CList* la)
{
  CList		tmpli;

  CList_extract(lna, lnb, &tmpli);
  return CList_merge_back(la, &tmpli);
}

CList*		CList_move_front(CLink* lna, CLink* lnb, CList* la)
{
  CList		tmpli;

  CList_extract(lna, lnb, &tmpli);
  return CList_merge_front(la, &tmpli);
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
