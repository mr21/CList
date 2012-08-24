**CList**
=========================================================================================================

CList est mon système de liste chaînée générique en C (d'ou **C**List (j'ai pas cherché vraiment loin...).  
J'essaye de faire en sorte qu'il puisse satisfaire tous les projets et inimaginable (faut reussir à penser à tout, ce n'est pas fort simple, m'enfin..) !  

Donc voici un mode d'emploi (**dont l'écriture n'est pas fini**) pour comment l'utiliser comme il faut toussa toussa.  


Delete / Erase / Pop
---------------------------------------------------------------------------------------------------------
Comment faire pour supprimer un maillon d'une liste ?  
Il y a plusieurs methodes pour ça :

    /* Delete */
    CLink*                  CList_erase(CList*, CLink*);
    CLink*                  CList_pop_back(CList*);
    CLink*                  CList_pop_front(CList*);

Si il s'agit de supprimer un maillon que nous avons en pointeur alors c'est **CList_erase** qu'il nous faut !  
Elle prend en paramètre la liste et le maillon à supprimer.  
Elle retourne systematiquement le maillon suivant (ou _NULL_ si c'etait le dernier de la chaîne).  

Dans d'autres cas (qui arrivent très très souvent) vous pourrez avoir besoin de supprimer le premier ou le dernier maillon d'une liste, pour cela il y a : **CList_pop_back** et **CList_pop_front**.  
Ces fonctions ne prennent, quant-à elle qu'un seul paramètre : la liste en question (__CList*__).  
Elles renverront toujours le maillon qui est à l'extrémités de cette liste : **CList_pop_back** renverra toujours le dernier maillon (ou _NULL_ si la liste est vide) est vice versa (**CList_pop_front** le premier).  

Notons qu'il est également possible de supprimer plusieurs maillon d'un coup via **CList_foreach**.

Find
---------------------------------------------------------------------------------------------------------
Pour rechercher un maillon dans toute une liste j'ai écris huit fonctions que voici (ça devrait suffir je pense) :

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

Revenons sur le cas de _**f**find_, la fonction que l'on envoie aux fonctions du genre : **CList_ffind_back** est de type : __int (*f)()__  
Pourquoi int ? tout simplement pour savoir quand s'arrêter :P  
Voici un exemple :

    int         recherche(Personne* pers)
    {
        if (strcmp(pers->name, "Thomas") == 0 && pers->age == 22)
            return CLIST_BREAK;
        return CLIST_CONTINUE;
    }

Ici j'ai une fonction qui me permet de faire une recherche bien précise sur une liste de personne.  
Les deux valeurs possibles à renvoyer sont : **CLIST_BREAK** (on a trouve !) et **CLIST_CONTINUE** (on cherche encore...).  

Et évidemment, chaque fonction returnera _NULL_ si le maillon est introuvable.
