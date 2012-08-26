#include	<stdlib.h>
#include	"CList.h"

void		CList_init(CList* li)
{
  li->begin = li->end = NULL;
  li->size = 0;
}
