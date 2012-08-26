#include	<stdlib.h>
#include	<stdio.h>
#include	"../inc/CList.h"

typedef		struct
{
  char*		buf;
  int		a, b;
}		Obj;

Obj*		o(int a, int b)
{
  Obj*		oo = malloc(sizeof *oo);

  oo->a = a, oo->b = b;
  return oo;
}

int		opr(Obj* o)
{
  printf("%p %d %d\n", (void*)o, o->a, o->b);
  return CLIST_CONTINUE;
}

int		ocl(Obj* o)
{
  return o->b == 1337 ? CLIST_CONTINUE : CLIST_ERASE;
}

int		ofn2(Obj* o)
{
  return o->a == 2 ? CLIST_BREAK : CLIST_CONTINUE;
}

int		ofn3(Obj* o)
{
  return o->a == 3 ? CLIST_BREAK : CLIST_CONTINUE;
}

int		main(void)
{
  CList		list0, *li = &list0;
  CList		list1, *la = &list1;
  CLink		*lno0, *lno1;
  Obj		*o0, *o1;
  size_t	s0, s1;
  unsigned	u;

  CList_init(li);
  CList_init(la);

  lno0 = CList_push_back(li, (o0 = o(6666, 9999)), 0, free);

  for (u = 1; u < 5; ++u)
    CList_push_back(li, o(u, u * 10), 0, free);

  lno1 = CList_push_back(li, (o1 = o(0, 1337)), 0, free);

  for (u = 5; u < 10; ++u)
    CList_push_back(li, o(u, u * 10), 0, free);

  for (u = 1; u < 10; ++u)
    CList_push_front(li, o(-u, -u * 10), 0, free);

  printf("%d\n", ((Obj*)CList_begin(li)->data)->b == -90);
  printf("%d\n", ((Obj*)CList_end(li)->data)->b == 90);
  CList_pop_front(li);
  CList_pop_back(li);
  printf("%d\n", ((Obj*)CList_end(li)->data)->b == 80);
  printf("%d\n", ((Obj*)CList_begin(li)->data)->b == -80);
  printf("%d\n", CList_pfind_front(li, o0) == lno0 && CList_pfind_back(li, o0) == lno0);
  printf("%d\n", CList_pfind_front(li, o1) == lno1 && CList_pfind_back(li, o1) == lno1);
  printf("%d\n", CList_pfind_after(lno0, o1) == lno1 && CList_pfind_before(lno1, o0) == lno0);
  printf("%d\n", CList_pfind_after(lno0, o0) == lno0 && CList_pfind_before(lno1, o1) == lno1);
  CList_erase(li, lno0);
  printf("%d\n", CList_pfind_back(li, o0) == NULL);
  printf("%d\n", CList_pfind_front(li, o1) == lno1 && CList_pfind_back(li, o1) == lno1);
  while (((Obj*)CLink_data(CList_end(li)))->b != 1337)
    CList_pop_back(li);

  for (u = 1; u < 10; ++u)
    CList_push_back(la, o(u, u * 111111), 0, free);

  s0 = CList_size(li);
  s1 = CList_size(la);
  CList_merge_back(li, la);
  printf("%d merge (size)\n", CList_size(li) == s0 + s1);
  printf("%d merge (end)\n", ((Obj*)CLink_data(CList_end(li)))->a == 9);
  while (((Obj*)CLink_data(CList_begin(li)))->b != 1337)
    CList_pop_front(li);
  
  for (u = 1; u < 10; ++u)
    CList_push_front(la, o(u, -u * 111111), 0, free);
  s0 = CList_size(li);
  s1 = CList_size(la);
  CList_merge_front(li, la);
  printf("%d\n", CList_size(li) == s0 + s1);
  CList_pop_front(li);
  CList_pop_back(li);
  printf("%d\n", ((Obj*)CLink_data(CList_begin(li)))->a == 8);

  CList_foreach(li, ocl);
  printf("%d\n", ((Obj*)CList_end(li)->data)->b == 1337 && ((Obj*)CList_begin(li)->data)->b == 1337);
  for (u = 1; u < 5; ++u)
    CList_push_back(la, o(u, 0), 0, free);
  CList_merge_before(li, li->begin, la);
  for (u = 1; u < 5; ++u)
    CList_push_back(la, o(-1, 10 + u), 0, free);
  CList_merge_after(li, li->begin, la);
  for (u = 1; u < 5; ++u)
    CList_push_back(la, o(-4, 40 + u), 0, free);
  CList_merge_before(li, li->end, la);
  for (u = 1; u < 5; ++u)
    CList_push_back(la, o(-3, 30 + u), 0, free);
  CList_merge_after(li, CList_ffind_front(li, ofn3), la);
  for (u = 1; u < 5; ++u)
    CList_push_back(la, o(-2, 20 + u), 0, free);
  CList_merge_before(li, CList_ffind_front(li, ofn2)->next, la);

  printf("%d CLink_prev/next\n", CLink_next(CList_begin(li), 0) == li->begin && CLink_prev(CList_end(li), 0) == li->end);
  printf("%d\n", ((Obj*)CLink_data(CLink_next(CList_begin(li)->next, 10)))->b ==
	 ((Obj*)CLink_data(CLink_prev(CList_end(li)->prev, 8)))->b);

  CList_foreach(li, opr);

  CList_clear(li);
  return 0;
}
