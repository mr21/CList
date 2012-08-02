#include	"CList.h"

CList*		CList_list(CLink const* ln) { return ln ? ln->list : NULL; }
CLink*		CList_prev(CLink const* ln) { return ln ? ln->prev : NULL; }
CLink*		CList_next(CLink const* ln) { return ln ? ln->next : NULL; }
void*		CList_data(CLink const* ln) { return ln ? (void*)ln->ptr_data : NULL; }
