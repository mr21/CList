#include	<stdlib.h>
#include	"CList.h"

void		CList_init(CList* li, void (*des)())
{
  li->begin = li->end = NULL;
  li->size = 0;
  li->des = des;
}
