#include	"CList.h"

CLink*		CList_begin(CList const* li) { return li ? li->first : NULL; }
CLink*		CList_end(CList const* li)   { return li ? li->last  : NULL; }
size_t		CList_size(CList const* li)  { return li ? li->size  : 0; }
int		CList_empty(CList const* li) { return li ? !li->size : 1; }
