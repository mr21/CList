**CList**
=====


Find
----
Pour rechercher un maillon dans toute une chaîne j'ai écris huit fonctions que voici (ça devrait suffir je pense) :

    /* Find...            */
    /*     ...by pointer  */
    CLink*                  CList_pfind_back(CList const*, void const*);
    CLink*                  CList_pfind_front(CList const*, void const*);
    CLink*                  CList_pfind_after(CLink const*, void const*);
    CLink*                  CList_pfind_before(CLink const*, void const*);
    /*     ...by function */
    CLink*                  CList_ffind_back(CList const*, int (*f)());
    CLink*                  CList_ffind_front(CList const*, int (*f)());
    CLink*                  CList_ffind_after(CLink const*, int (*f)());
    CLink*                  CList_ffind_before(CLink const*, int (*f)());

Ces huit fonctions se séparent en deux groupes :  
* Rechercher un maillon via son **p**ointeur : _**p**find_
* Rechercher un maillon via une **f**onction spécialement écrite pour cette recherche : _**f**find_

Ces deux groupes peuvent eux-mêmes se diviser en deux parties :
* Rechercher depuis les extrémités d'une liste (__CList const*__) : _back_ ou _front_
* Rechercher à partir d'un maillon (__CLink const*__) : _before_ ou _after_

Chaque fonction returne _NULL_ si le maillon n'a pas été trouvé évidemment.
