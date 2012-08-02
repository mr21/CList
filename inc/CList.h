#ifndef			CLIST_H
#define			CLIST_H

#include		<stddef.h>

typedef	struct CLink	CLink;
typedef	struct CList	CList;

struct			CList
{
  CLink*		first;
  CLink*		last;
  unsigned		size;
  void			(*des)();
};

struct			CLink
{
  CList*		list;
  CLink*		prev;
  CLink*		next;
  void const*		ptr_data;
  void const*		data;
};

CLink*			CList_begin(CList const*);
void			CList_clear(CList*);
int			CList_empty(CList const*);
CLink*			CList_end(CList const*);
CLink*			CList_erase(CLink*);
CLink*			CList_find_data(CList const*, void const* data);
unsigned		CList_find_n_destroy(CList*, void const* data);
void			CList_foreach(CList const*, void (*fun)());
void			CList_init(CList*, void (*des)());
CLink*			CList_pop_back(CList*);
CLink*			CList_pop_front(CList*);
CLink*			CList_push_back(CList*, void const* data, size_t);
CLink*			CList_push_front(CList*, void const* data, size_t);
unsigned		CList_size(CList const*);

#endif
