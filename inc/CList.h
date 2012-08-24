#ifndef			CLIST_H
#define			CLIST_H

#include		<stddef.h>

/* ForEach's value */
enum
{
  CLIST_NEXT,  /* Une maniere de ne rien faire   */
  CLIST_STOP,  /* On stoppe la boucle (un break) */
  CLIST_ERASE  /* On supprime le maillon actuel  */
};

typedef	struct CLink	CLink;
typedef	struct CList	CList;

struct			CLink
{
  CLink*		prev;
  CLink*		next;
  void*			data;
  void			(*free)();
};

struct			CList
{
  CLink*		begin;
  CLink*		end;
  size_t		size;
  void			(*free)();
};

/* Init & destroy */
void			CList_init(CList*, void (*destr)());
void			CList_clear(CList*);

/* CLink* [gs]etters */
CLink*			CLink_prev(CLink const*);
CLink*			CLink_next(CLink const*);
void*			CLink_data(CLink const*);
void			(*CLink_free(CLink const*))();

/* CList* [gs]etters */
CLink*			CList_begin(CList const*);
CLink*			CList_end(CList const*);
size_t			CList_size(CList const*);
int			CList_empty(CList const*);

/* Add */
CLink*			CList_push_back(CList*, void* data, size_t, void (*destr)());
CLink*			CList_push_front(CList*, void* data, size_t, void (*destr)());

/* Delete */
CLink*			CList_erase(CList*, CLink*);
CLink*			CList_pop_back(CList*);
CLink*			CList_pop_front(CList*);

/* Treatement */
void			CList_foreach(CList*, int (*fun)());

/* Find */
CLink*			CList_find_back(CList const*, void const*);
CLink*			CList_find_front(CList const*, void const*);
CLink*			CList_find_after(CLink const*, void const*);
CLink*			CList_find_before(CLink const*, void const*);

/* Merge */
CList*			CList_merge_back(CList*, CList*);
CList*			CList_merge_front(CList*, CList*);
CList*			CList_merge_after(CList*, CLink*, CList*);
CList*			CList_merge_before(CList*, CLink*, CList*);

CList*			CList_cut_after(CList*, CLink const*, size_t); /* TODO */

#endif
