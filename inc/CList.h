#ifndef			CLIST_H
#define			CLIST_H

#include		<stddef.h>

/* Valeur de retour pour le foreach : */
enum
{
  CLIST_NEXT,  /* Une maniere de ne rien faire   */
  CLIST_STOP,  /* On stoppe la boucle (un break) */
  CLIST_ERASE  /* On supprime le maillon actuel  */
};

typedef	struct CLink	CLink;
typedef	struct CList	CList;

struct			CList
{
  CLink*		begin;
  CLink*		end;
  size_t		size;
  void			(*des)();
};

struct			CLink
{
  CList*		list;
  CLink*		prev;
  CLink*		next;
  void*			data;
};

/* Init & destroy */
void			CList_init(CList*, void (*des)());
void			CList_clear(CList*);

/* CLink* [gs]etters */
CList*			CList_list(CLink const*);
CLink*			CList_prev(CLink const*);
CLink*			CList_next(CLink const*);
void*			CList_data(CLink const*);

/* CList* [gs]etters */
CLink*			CList_begin(CList const*);
CLink*			CList_end(CList const*);
size_t			CList_size(CList const*);
int			CList_empty(CList const*);

/* Add */
CLink*			CList_push_back(CList*, void* data, size_t);
CLink*			CList_push_front(CList*, void* data, size_t);

/* Delete */
CLink*			CList_erase(CLink*);
CLink*			CList_pop_back(CList*);
CLink*			CList_pop_front(CList*);

/* Treatement */
void			CList_foreach(CList const*, int (*fun)());

/* Find */
CLink*			CList_find_front(CList const*, void const*);
CLink*			CList_find_back(CList const*, void const*);
CLink*			CList_find_after(CLink const*, void const*);
CLink*			CList_find_before(CLink const*, void const*);

/* CList* & CList* */
/*todooo*/CList*			CList_cut_after(CList*, CLink const*, size_t);
/*totest*/CList*			CList_merge_back(CList*, CList*);
/*totest*/CList*			CList_merge_front(CList*, CList*);

#endif
