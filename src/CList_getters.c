#include	"CList.h"

size_t		CList_size (CList const* li)           { return li ? li->size  : 0;             }
int		CList_empty(CList const* li)           { return li ? !li->size : 1;             }
CLink*		CList_begin(CList const* li)           { return li ? li->begin : NULL;          }
CLink*		CList_end  (CList const* li)           { return li ? li->end   : NULL;          }
CLink*          CList_next (CList const* li, size_t n) { return CLink_next(CList_begin(li), n); }
CLink*          CList_prev (CList const* li, size_t n) { return CLink_prev(CList_end(li), n);   }
