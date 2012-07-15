#include	<stdlib.h>
#include	"CList.h"

void		CList_init(CList* li, void (*des)())
{
  li->first = li->last = NULL;
  li->length = 0;
  li->des = des;
}
