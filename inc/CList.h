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
void			CList_clear(CList*);
void			CList_foreach(CList*, void (*f)());

int			CList_push_front(CList*, void* data);
int			CList_push_back(CList*, void* data);

/* Delete */
void			CList_pop_front(CList*);
void			CList_pop_back(CList*);
CLink*			CList_erase(CLink*);

/* Find */
unsigned		CList_find_n_destroy(CList*, void* data);
CLink*			CList_find_data(CList*, void* data);

/* Debugs */
void			CList_print(CList*);
void			CList_print_rev(CList*);

#endif
