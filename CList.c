#include	"CList.h"

size_t		CList_size (CList const* li)           { return li ? li->size  : 0;             }
int		CList_empty(CList const* li)           { return li ? !li->size : 1;             }
CLink*		CList_begin(CList const* li)           { return li ? li->begin : NULL;          }
CLink*		CList_end  (CList const* li)           { return li ? li->end   : NULL;          }
CLink*          CList_next (CList const* li, size_t n) { return CLink_next(CList_begin(li), n); }
CLink*          CList_prev (CList const* li, size_t n) { return CLink_prev(CList_end(li), n);   }
#include	"CList.h"

CList*		CList_move_back(CLink* lna, CLink* lnb, CList* li)
{
  CList		tmpli;

  CList_extract(lna, lnb, &tmpli);
  return CList_merge_back(li, &tmpli);
}

CList*		CList_move_front(CLink* lna, CLink* lnb, CList* li)
{
  CList		tmpli;

  CList_extract(lna, lnb, &tmpli);
  return CList_merge_front(li, &tmpli);
}

CList*		CList_move_after(CLink* lna, CLink* lnb, CLink* lnc)
{
  CList		tmpli;

  CList_extract(lna, lnb, &tmpli);
  return CList_merge_after(lnc, &tmpli);
}

CList*		CList_move_before(CLink* lna, CLink* lnb, CLink* lnc)
{
  CList		tmpli;

  CList_extract(lna, lnb, &tmpli);
  return CList_merge_before(lnc, &tmpli);
}
#include	<stdlib.h>
#include	"CList.h"

void		CList_init(CList* li)
{
  li->begin = li->end = NULL;
  li->size = 0;
}
#include	<stdlib.h>
#include	"CList.h"

CLink*		CList_pop_front(CList* li)
{
  CLink*	ln = li->begin;

  if (!ln)
    return NULL;
  --li->size;
  if (!(li->begin = ln->next))
    li->end = NULL;
  else
    li->begin->prev = NULL;
  if (ln->free)
    ln->free(ln->data);
  free(ln);
  return li->begin;
}

CLink*		CList_pop_back(CList* li)
{
  CLink*	ln = li->end;

  if (!ln)
    return NULL;
  --li->size;
  if (!(li->end = ln->prev))
    li->begin = NULL;
  else
    li->end->next = NULL;
  if (ln->free)
    ln->free(ln->data);
  free(ln);
  return li->end;
}

CLink*		CList_pop(CLink* ln)
{
  CList*	li = CLink_list(ln);
  CLink*	ln_ret;

  if (!li)
    return NULL;
  if (ln == li->begin)
    return CList_pop_front(li);
  if (ln == li->end)
    return CList_pop_back(li), NULL;
  ln->prev->next = ln_ret = ln->next;
  ln->next->prev = ln->prev;
  --li->size;
  if (ln->free)
    ln->free(ln->data);
  free(ln);
  return ln_ret;
}

CLink*		CList_popn(CLink* a, CLink* b)
{
  CList*	li = a->list;
  CLink*	ln = a, *tmp, *b_next = b->next;

  if (!a->prev)
    li->begin = b->next;
  else
    a->prev->next = b->next;
  if (!b->next)
    li->end = a->prev;
  else
    b->next->prev = a->prev;
  for (; ln != b_next; ln = tmp)
    {
      tmp = ln->next;
      if (ln->free)
        ln->free(ln->data);
      free(ln);
      --li->size;
    }
  return tmp;
}
#include	<stdlib.h>
#include	"CList.h"

void		CList_extract(CLink* lna, CLink* lnb, CList* newli)
{
  CList*	li = lna->list;

  newli->begin = lna;
  newli->end = lnb;
  newli->size = CList_count_n_li(lna, lnb, newli);
  li->size -= newli->size;
  if (lna->prev)
    lna->prev->next = lnb->next;
  else
    li->begin = lnb->next;
  if (lnb->next)
    lnb->next->prev = lna->prev;
  else
    li->end = lna->prev;
  lna->prev = lnb->next = NULL;
}

CList*		CList_cut(CLink* lna, CLink* lnb)
{
  CList*	la = malloc(sizeof *la);

  if (la)
    CList_extract(lna, lnb, la);
  return la;
}

CList*		CList_cut_back(CLink* ln)  { return CList_cut(ln, ln->list->end);   }
CList*		CList_cut_front(CLink* ln) { return CList_cut(ln->list->begin, ln); }
#include	<stdlib.h>
#include	"CList.h"

void		CList_clear(CList* li)
{
  CLink*	ln = li->begin;
  CLink*	tmp;

  for (; ln; ln = tmp)
    {
      tmp = ln->next;
      if (ln->free)
	ln->free(ln->data);
      free(ln);
    }
  li->begin = li->end = NULL;
  li->size = 0;
}
#include	"CList.h"

void		CList_foreach(CList* li, int (*f)())
{
  CLink*	ln = CList_begin(li);

  while (ln)
    switch (f(ln->data))
      {
      case CLIST_CONTINUE:	ln = ln->next;		break;
      case CLIST_ERASE:		ln = CList_pop(ln);	break;
      case CLIST_ERASE_STOP:	CList_pop(ln);
      default:			return;
      }
}
#include	"CList.h"

CLink*		CList_pfind_after(CLink const* ln, void const* data)
{
  for (; ln && ln->data != data; ln = ln->next);
  return (CLink*)ln;
}

CLink*		CList_pfind_before(CLink const* ln, void const* data)
{
  for (; ln && ln->data != data; ln = ln->prev);
  return (CLink*)ln;
}

CLink*		CList_pfind_front(CList const* li, void const* data)
{
  return CList_pfind_after(CList_begin(li), data);
}

CLink*		CList_pfind_back(CList const* li, void const* data)
{
  return CList_pfind_before(CList_end(li), data);
}

CLink*          CList_ffind_after(CLink const* ln, int (*f)())
{
  for (; ln && f(ln->data) == CLIST_CONTINUE; ln = ln->next);
  return (CLink*)ln;
}

CLink*          CList_ffind_before(CLink const* ln, int (*f)())
{
  for (; ln && f(ln->data) == CLIST_CONTINUE; ln = ln->prev);
  return (CLink*)ln;
}

CLink*		CList_ffind_front(CList const* li, int (*f)())
{
  return CList_ffind_after(CList_begin(li), f);
}

CLink*		CList_ffind_back(CList const* li, int (*f)())
{
  return CList_ffind_before(CList_end(li), f);
}
#include	<stdlib.h>
#include	"CList.h"

static void	add(CList* li, CList* la)
{
  CLink*	ln = li->begin;

  for (; ln; ln = ln->next)
    ln->list = li;
  li->size += la->size;
  CList_init(la);
}

CList*		CList_merge_back(CList* li, CList* la)
{
  if (li != la && la && la->size)
    {
      if (li->size)
	li->end->next = la->begin;
      else
	li->begin = la->begin;
      la->begin->prev = li->end;
      li->end = la->end;
      add(li, la);
    }
  return li;
}

CList*		CList_merge_front(CList* li, CList* la)
{
  if (li != la && la && la->size)
    {
      if (li->size)
	li->begin->prev = la->end;
      else
	li->end = la->end;
      la->end->next = li->begin;
      li->begin = la->begin;
      add(li, la);
    }
  return li;
}

CList*		CList_merge_after(CLink* ln, CList* la)
{
  CList*	li = CLink_list(ln);

  if (li && ln == li->end)
    return CList_merge_back(li, la);
  if (li != la && la && la->size && ln)
    {
      la->begin->prev = ln;
      la->end->next = ln->next;
      ln->next->prev = la->end;
      ln->next = la->begin;
      add(li, la);
    }
  return li;
}

CList*		CList_merge_before(CLink* ln, CList* la)
{
  CList*	li = CLink_list(ln);

  if (li && ln == li->begin)
    return CList_merge_front(li, la);
  if (li != la && la && la->size && ln)
    {
      la->begin->prev = ln->prev;
      la->end->next = ln;
      ln->prev->next = la->begin;
      ln->prev = la->end;
      add(li, la);
    }
  return li;
}
#include	"CList.h"

CList*		CLink_list(CLink const* ln)      { return ln ? ln->list : NULL; }
void*		CLink_data(CLink const* ln)      { return ln ? ln->data : NULL; }
void		(*CLink_free(CLink const* ln))() { return ln ? ln->free : NULL; }

CLink*		CLink_prev(CLink const* ln, size_t n)
{
  for (; ln && n; ln = ln->prev, --n);
  return (CLink*)ln;
}

CLink*		CLink_next(CLink const* ln, size_t n)
{
  for (; ln && n; ln = ln->next, --n);
  return (CLink*)ln;
}
#include	<stdlib.h>
#include	<string.h>
#include	"CList.h"

static CLink*	newLink(CList* li, void* data, size_t sz, void (*destr)())
{
  CLink*	new = malloc(sizeof(*new) + sz);

  if (new)
    {
      new->list = li;
      new->free = destr;
      new->prev = new->next = NULL;
      if (!sz)
	new->data = data;
      else
	{
	  new->data = &new->data + 1;
	  data ? memcpy(new->data, data, sz) :
	    memset(new->data, 0, sz);
	}
      if (++li->size == 1)
	li->begin = li->end = new;
    }
  return new;
}

CLink*		CList_push_front(CList* li, void* data, size_t sz, void (*destr)())
{
  CLink*	new = newLink(li, data, sz, destr);

  if (new && li->size > 1)
    {
      new->next = li->begin;
      li->begin->prev = new;
      li->begin = new;
    }
  return new;
}

CLink*		CList_push_back(CList* li, void* data, size_t sz, void (*destr)())
{
  CLink*	new = newLink(li, data, sz, destr);

  if (new && li->size > 1)
    {
      new->prev = li->end;
      li->end->next = new;
      li->end = new;
    }
  return new;
}

CLink*		CList_push_after(CLink* ln, void* data, size_t sz, void (*destr)())
{
  CList*	li = ln->list;
  CLink*	new;

  if (ln == li->end)
    return CList_push_back(li, data, sz, destr);
  if ((new = newLink(li, data, sz, destr)))
    {
      new->prev = ln;
      new->next = ln->next;
      ln->next->prev = new;
      ln->next = new;
    }
  return new;
}

CLink*		CList_push_before(CLink* ln, void* data, size_t sz, void (*destr)())
{
  CList*	li = ln->list;
  CLink*	new;

  if (ln == li->begin)
    return CList_push_front(li, data, sz, destr);
  if ((new = newLink(li, data, sz, destr)))
    {
      new->prev = ln->prev;
      new->next = ln;
      ln->prev->next = new;
      ln->prev = new;
    }
  return new;
}
#include	"CList.h"

size_t		CList_count(CLink const* a, CLink const* b)
{
  size_t	n = 1;

  for (; a && a != b; a = a->next)
    ++n;
  return n;
}

size_t		CList_count_n_li(CLink* a, CLink* b, CList const* li)
{
  size_t	s = 0;

  do
    ++s, a->list = (CList*)li;
  while (a != b && (a = a->next));
  return s;
}
