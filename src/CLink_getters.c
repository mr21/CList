#include	"CList.h"

CLink*		CLink_prev(CLink const* ln) { return ln ? ln->prev : NULL; }
CLink*		CLink_next(CLink const* ln) { return ln ? ln->next : NULL; }
void*		CLink_data(CLink const* ln) { return ln ? ln->data : NULL; }
