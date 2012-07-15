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

  for (; ln; ln = ln->next)
    {
      o = ln->data;
      if (o->v % 2 == 0)
	CList_erase(CList_find_data(&l, o));
    }
}

int		main(void)
{
  CList		l;
  Obj*		o;
  int		i;

  CList_init(&l, free);
  
  for (i = 0; i < 1000; ++i)
    {
      if (!(o = malloc(sizeof *o)))
	{
	  printf("malloc fail\n");
	  break;
	}
      o->v = i;
      CList_push_back(&l, o);
    }

  for (i = 0; i > -1000; --i)
    {
      if (!(o = malloc(sizeof *o)))
	{
	  printf("malloc fail\n");
	  break;
	}
      o->v = i;
      CList_push_front(&l, o);
    }

  CList_foreach(&l, show);
  printf("\n--------------------\n");

  del_even(&l);

  CList_foreach(&l, show);

  CList_clear(&l);

  return 0;
}
