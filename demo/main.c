#include	<stdio.h>
#include	<stdlib.h>
#include	"../inc/CList.h"

typedef	struct { int v; } Obj;

static void	show(Obj* o)
{
  printf("%d ", o->v);
}

static void	del_even(CList* li)
{
  CLink*	ln = li->first;
  Obj*		o;

  while (ln && !CList_empty(li))
    {
      o = ln->data;
      if (o->v % 2)
	ln = ln->next;
      else
	ln = CList_erase(ln);
    }
}

static void	del_odd(CList* li)
{
  CLink*	ln = li->first;
  Obj*		o;

  while (ln && !CList_empty(li))
    {
      o = ln->data;
      if (o->v % 2 == 0)
	ln = ln->next;
      else
	ln = CList_erase(ln);
    }
}

int		main(void)
{
  CList		l;
  Obj*		o;
  int		i;
  int		lim = 1000;

  CList_init(&l, free);
  
  for (i = 0; i < lim; ++i)
    {
      if (!(o = malloc(sizeof *o)))
	{printf("malloc fail\n"); break;}
      o->v = i;
      if (!CList_push_back(&l, o))
	{printf("CList_push_back fail\n"); break;}
    }

  for (i = 0; i > -lim; --i)
    {
      if (!(o = malloc(sizeof *o)))
	{printf("malloc fail\n"); break;}
      o->v = i;
      if (!CList_push_front(&l, o))
	{printf("CList_push_front fail\n"); break;}
    }

  CList_foreach(&l, show);
  printf("\n-------- size = %u ------------\n", CList_size(&l));

  del_even(&l);
  CList_foreach(&l, show);
  printf("\n-------- size = %u ------------\n", CList_size(&l));

  del_odd(&l);
  CList_foreach(&l, show);
  printf("\n-------- size = %u ------------\n", CList_size(&l));

  CList_clear(&l);

  return 0;
}
