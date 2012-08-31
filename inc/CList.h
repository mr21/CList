#ifndef			CLIST_H
#define			CLIST_H

#include		<stddef.h>

/* ForEach's value */
enum
{
  CLIST_CONTINUE,  /* Une maniere de ne rien faire  */
  CLIST_BREAK,     /* On stoppe la boucle           */
  CLIST_ERASE,     /* On supprime le maillon actuel */
  CLIST_ERASE_STOP /* On supprime et on s'arrete    */
};

typedef	struct CLink	CLink;
typedef	struct CList	CList;

struct			CLink
{
  CList*		list;
  CLink*		prev;
  CLink*		next;
  void			(*free)();
  void*			data; /* "data" doit TOUJOURS etre en dernier! */
};

struct			CList
{
  CLink*		begin;
  CLink*		end;
  size_t		size;
};

/* Init & destro */
void			CList_init (CList*);
void			CList_clear(CList*);

/* CLink* [gs]etters */
CList*			CLink_list  (CLink const*);
CLink*			CLink_prev  (CLink const*, size_t);
CLink*			CLink_next  (CLink const*, size_t);
void*			CLink_data  (CLink const*);
void			(*CLink_free(CLink const*))();

/* CList* [gs]etters */
CLink*			CList_begin(CList const*);
CLink*			CList_end  (CList const*);
size_t			CList_size (CList const*);
int			CList_empty(CList const*);
CLink*			CList_prev (CList const*, size_t);
CLink*			CList_next (CList const*, size_t);

/* Add */
CLink*			CList_push_back (CList*, void* data, size_t, void (*destr)());
CLink*			CList_push_front(CList*, void* data, size_t, void (*destr)());

/* Delete */
CLink*			CList_erase    (CLink*);
CLink*			CList_pop_back (CList*);
CLink*			CList_pop_front(CList*);

/* Treatement */
void			CList_foreach(CList*, int (*f)());

/* Find...            */
/*     ...by pointer  */
CLink*			CList_pfind_back  (CList const*, void const*);
CLink*			CList_pfind_front (CList const*, void const*);
CLink*			CList_pfind_after (CLink const*, void const*);
CLink*			CList_pfind_before(CLink const*, void const*);
/*     ...by function */
CLink*			CList_ffind_back  (CList const*, int (*f)());
CLink*			CList_ffind_front (CList const*, int (*f)());
CLink*			CList_ffind_after (CLink const*, int (*f)());
CLink*			CList_ffind_before(CLink const*, int (*f)());

/* Merge */
CList*			CList_merge_back  (CList* li, CList* la);
CList*			CList_merge_front (CList* li, CList* la);
CList*			CList_merge_after (CLink* ln, CList* la);
CList*			CList_merge_before(CLink* ln, CList* la);

/* Cut */
CList*			CList_cut      (CLink*, CLink*);
CList*			CList_cut_back (CLink*);
CList*			CList_cut_front(CLink*);

/* Move !!TODO!! */
CList*			CList_move_back  (CLink* lna, CLink* lnb, CList* la);
CList*			CList_move_front (CLink* lna, CLink* lnb, CList* la);
CList*			CList_move_after (CLink* lna, CLink* lnb, CLink* lnc);
CList*			CList_move_before(CLink* lna, CLink* lnb, CLink* lnc);

#endif
