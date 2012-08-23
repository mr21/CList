#include	<stdlib.h>
#include	"CList.h"

void		CList_init(CList* li, void (*destr)())
{
  li->begin = li->end = NULL;
  li->size = 0;
  li->free = destr;
}
