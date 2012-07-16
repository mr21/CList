#ifndef			CLIST_H
# define		CLIST_H

typedef	struct CLink	CLink;
typedef	struct CList	CList;

struct			CLink
{
  CList*		list;
  CLink*		prev;
  CLink*		next;
  void*			data;
};

struct			CList
{
  CLink*		first;
  CLink*		last;
  unsigned		length;
  void			(*des)();
};

void			CList_init(CList*, void (*des)());

unsigned		CList_size(CList*);
int			CList_empty(CList*);

void			CList_clear(CList*);
CLink*			CList_pop_front(CList*);
CLink*			CList_pop_back(CList*);
CLink*			CList_erase(CLink*);

CLink*			CList_push_front(CList*, void* data);
CLink*			CList_push_back(CList*, void* data);

void			CList_foreach(CList*, void (*f)());
unsigned		CList_find_n_destroy(CList*, void* data);
CLink*			CList_find_data(CList*, void* data);

#endif
