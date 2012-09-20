#include	<stdlib.h>
#include	<stdio.h>
#include	"CList.h"

/* <Object> */
typedef		struct
{
  int		val;
}		_int;
void*		newInt(int val)
{
  _int*		i = malloc(sizeof i);

  if (i)
    i->val = val;
  return i;
}

/* <Print> */
static int	printInt(_int* i)
{
  if (i)
    printf(" %d", i->val);
  else
    printf(" (nil)");
  return CLIST_CONTINUE;
}
void		printList(CList* li, char const* name)
{
  printf("%s(%lu) :", name, CList_size(li));
  CList_foreach(li, printInt);
  printf("\n");
}
void		printAll(CList* li, CList* la)
{
  printList(li, "li");
  printList(la, "la");
  printf("\n");
}

/* <Find> */
static int	searchValue;
static int	findInt(_int* i)
{
  return i && i->val == searchValue ? CLIST_BREAK : CLIST_CONTINUE;
}
CLink*		findLink(CList* li, int val)
{
  searchValue = val;
  return CList_ffind_front(li, findInt);
}

/* <Pop> */
int		popEvenNumber(_int* i)
{
  return i && !(i->val % 2) ? CLIST_ERASE : CLIST_CONTINUE;
}

int		main(void)
{
  CList		list0, *li = &list0;
  CList		list1, *la = &list1;

  CList_init(li);
  CList_init(la);

  printf("push back/front\n");
  CList_push_back(li, newInt(55), 0, free);
  CList_push_back(li, newInt(89), 0, free);
  CList_push_front(li, newInt(21), 0, free);
  CList_push_back(la, newInt(610), 0, free);
  CList_push_front(la, newInt(233), 0, free);
  CList_push_front(la, newInt(144), 0, free);
  printAll(li, la);

  printf("push after/before\n");
  CList_push_after(findLink(la, 233), newInt(377), 0, free);
  CList_push_before(findLink(li, 55), newInt(34), 0, free);
  printAll(li, la);

  printf("merge front\n");
  CList_merge_front(li, la);
  printAll(li, la);

  printf("move back (in the same list)\n");
  CList_move_back(CList_begin(li), findLink(li, 610), li);
  printAll(li, la);

  printf("pop via foreach\n");
  CList_foreach(li, popEvenNumber);
  printAll(li, la);

  printf("move front (in an empty list)\n");
  CList_move_front(CList_begin(li), CList_next(li, 2), la);
  printAll(li, la);

  printf("some push front/after\n");
  CList_push_front(li, newInt(13), 0, free);
  CList_push_front(li, newInt(5), 0, free);
  CList_push_after(findLink(la, 55), newInt(987), 0, free);
  printAll(li, la);

  printf("move after/before (and a merge after)\n");
  CList_move_after(findLink(la, 21), findLink(la, 55), findLink(li, 13));
  CList_move_before(CList_end(la), CList_end(la), findLink(li, 233));
  CList_merge_after(findLink(li, 377), la);
  printAll(li, la);

  CList_clear(li);
  CList_clear(la);
  return 0;
}
