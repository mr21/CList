**CList**
=========================================================================================================

CList est mon système de liste chaînée en C (d'où **C**List (j'ai pas vraiment cherché loin...)).  
J'ai essayé de faire en sorte que cette lib' puisse satisfaire n'importe quel type de projets !  

Pour simplifier l'utilisation, j'ai rassemblé tous les fichiers sources en un seul et unique .c via :  
`cat ``find sources/src/ -name '*.c'`` > CList.c`  


**Mode d'emploi** :  

* [Init / Clear](#init--clear)
* [Push](#push)
* [Pop](#pop)
* [Find](#find)
* [Merge](#merge)
* [Cut](#cut)
* [Move](#move)


Init / Clear
---------------------------------------------------------------------------------------------------------
Les deux fonctions de bases à connaitre sont celles qui initialisent et detruisent une liste (`CList*`).  

    void                    CList_init (CList*);
    void                    CList_clear(CList*);

Aucun malloc n'est fait dans `CList_init`, elle ne fait qu'initialiser les variables à 0.  
`CList_clear` libère chaque maillon de la liste en appellant leur destructeur respectif, et fait un free sur le maillon lui-même. La taille de la liste sera donc remise à 0 etc.  

Push
---------------------------------------------------------------------------------------------------------
L'action la plus élémentaire est celle d'ajouter un maillon à une liste, c'est pourtant la plus complexe à bien comprendre... :S  

    CLink*      CList_push_back  (CList* list, void* data, size_t size, void (*destr)());
    CLink*      CList_push_front (CList* list, void* data, size_t size, void (*destr)());
    CLink*    	CList_push_after (CLink* link, void* data, size_t size, void (*destr)());
    CLink*		CList_push_before(CLink* link, void* data, size_t size, void (*destr)());

D'une manière générale les nouveaux maillons se mettent à la fin ou au début de la liste, c'est pourquoi nous avons : _front_ et _back_.  
Ces deux fonctions ont le même comportement et reçoivent chacune quatre arguments :  
* __*list*__ : un pointeur vers la liste dans laquelle nous voulons mettre un nouveau maillon.
* __*data*__ : un pointeur vers les données du nouveau maillon.
* __*size*__ : le *sizeof* des données, mais **uniquement** si l'on souhaite que les data soient **ancrées** dans le maillon. Dans le cas le plus courant qui consiste à passer le retour d'un malloc, il faut mettre `0`. Tout ce système complexe a été conçu pour se passer d'un malloc par maillon dans certain cas.
* __*destr*__ : le destructeur, chaque maillon possède un pointeur vers un destructeur (pratique pour les merges de liste), dans le cas où vous envoyez le retour d'un malloc il vous suffit de mettre `free`. Si vous ne voulez pas de destructeur pour votre maillon passez-lui `NULL` (très utile dans le cas où vous ancrez les data directement dans le maillon).  

Ceci dit il est possible de vouloir rajouter un maillon à un endroit bien précis dans la liste, pour ceci il y a _after_ et _before_ :  
Elles ont exactement le même prototype que celui expliqué au dessus, sauf qu'elles prennent un maillon (`CLink*`) et non une liste en paramètre.  

En résumé voici les deux exemples :  

    int         main(void)
    {
        CList   li;
        Objet*  obj_0 = malloc(sizeof *obj);
        Objet   obj_1;
    
        CList_init(&li);
    
        CList_push_back(&li, obj_0, 0, free);
        CList_push_back(&li, &obj_1, sizeof obj_1, NULL);
    
        CList_clear(&li);
        return 0;
    }


Pop
---------------------------------------------------------------------------------------------------------
Comment faire pour supprimer un maillon d'une liste ?  
Il y a plusieurs methodes pour ça :

    CLink*      CList_pop      (CLink*);
    CLink*      CList_pop_back (CList*);
    CLink*      CList_pop_front(CList*);

Si il s'agit de supprimer un maillon que nous avons en pointeur alors c'est `CList_pop` qu'il nous faut !  
Elle retourne systematiquement le maillon suivant (ou `NULL` si c'etait le dernier de la liste).  

Dans d'autres cas (qui arrivent très souvent) vous pourrez avoir besoin de supprimer le premier ou le dernier maillon d'une liste, pour cela il y a : `CList_pop_back` et `CList_pop_front`.  
Ces fonctions prennent la liste en paramètre (`CList*`).  
Elles renverront toujours le maillon qui est à l'extrémités de cette liste : `CList_pop_back` renverra toujours le dernier maillon (ou `NULL` si la liste est vide) est vice versa (`CList_pop_front` le premier).  

Notons qu'il est également possible de supprimer plusieurs maillon d'un coup via `CList_foreach`.

Find
---------------------------------------------------------------------------------------------------------
Pour rechercher un maillon dans toute une liste j'ai écris huit fonctions que voici (ça devrait suffir je pense) :

    CLink*      CList_pfind_back  (CList const*, void const*);
    CLink*      CList_pfind_front (CList const*, void const*);
    CLink*      CList_pfind_after (CLink const*, void const*);
    CLink*      CList_pfind_before(CLink const*, void const*);
    
    CLink*      CList_ffind_back  (CList const*, int (*f)());
    CLink*      CList_ffind_front (CList const*, int (*f)());
    CLink*      CList_ffind_after (CLink const*, int (*f)());
    CLink*      CList_ffind_before(CLink const*, int (*f)());

Ces huit fonctions se séparent en deux groupes :  
* Rechercher un maillon via son **p**ointeur : _**p**find_
* Rechercher un maillon via une **f**onction spécialement écrite pour cette recherche : _**f**find_

Ces deux groupes peuvent eux-mêmes se diviser en deux parties :
* Rechercher depuis les extrémités d'une liste (`CList const*`) : _back_ ou _front_
* Rechercher à partir d'un maillon (`CLink const*`) : _before_ ou _after_

Revenons sur le cas de _**f**find_, la fonction que l'on envoie aux fonctions du genre : `CList_ffind_back` est de type : `int (*f)()`  
Pourquoi int ? tout simplement pour savoir quand s'arrêter :P  
Un exemple :

    int         recherche(Personne* pers)
    {
        if (strcmp(pers->name, "Thomas") == 0 && pers->age == 22)
            return CLIST_BREAK;
        return CLIST_CONTINUE;
    }

Ici j'ai une fonction qui me permet de faire une recherche précise sur une liste de personne.  
Les deux valeurs possibles à renvoyer sont : `CLIST_BREAK` (on a trouvé !) et `CLIST_CONTINUE` (on cherche encore...).  

Et évidemment, chaque fonction returnera `NULL` si le maillon est introuvable.

Merge
---------------------------------------------------------------------------------------------------------
Il est possible de merger une liste avec une autre (ou **dans** une autre), via quatres fonctions.  

    CList*      CList_merge_back  (CList* li, CList* la);
    CList*      CList_merge_front (CList* li, CList* la);
    CList*      CList_merge_after (CLink* ln, CList* la);
    CList*      CList_merge_before(CLink* ln, CList* la);

Premièrement ces fonctions `return` la liste _*li_ (en d'autre terme la liste retournée est celle qui se voit agrandit par l'ajout de l'autre).  
Deuxièmement il n'y a **aucune copie** dans ces opérations. Ce qui insinu que la liste _*la_ deviendra totalement vide, elle sera dans le même état qu'elle l'a été au moment de son initialisation : `CList_init(&la);`.  

`CList_merge_back` va souder la liste _*la_ à la fin de la liste _*li_.  
`CList_merge_front` va souder la liste _*la_ au début de la liste _*li_.  

Cependant il est possible que vous ayez envie de placer la liste _*la_ **dans** la liste _*li_ et non à l'une de ses extrèmités. Pour cela il y a :  
`CList_merge_after` qui mettra la liste _*la_ juste **après** le maillon _*ln_ (appartenant à la liste _*ln->list_).
`CList_merge_before` qui mettra la liste _*la_ juste **avant** le maillon _*ln_ (appartenant à la liste _*ln->list_).

**Note** : Tout plantera si l'on souhaite _merger_ la liste dans elle même...  

Cut
---------------------------------------------------------------------------------------------------------
On peut voir **cut** comme l'inverse de **merge**.  
**cut** permet de couper une liste en deux, les trois fonctions ci-dessous vont créer une nouvelle liste (`CList*`) qu'il sera necéssaire de `free` par la suite.  

    CList*    	CList_cut      (CLink* lna, CLink* lnb);
    CList*		CList_cut_back (CLink*);
    CList*		CList_cut_front(CLink*);

Pour les trois fonctions tous les maillons (`CLink*`) seront compris dans la nouvelle liste (`CList*`) créée.  
Prenons par exemple cette liste :  

    CList* li = 0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9

Si nous faisons `CList* la = CList_cut_back(CList_ffind_front(&li, find_4));` Nous nous retronverons avec :  

    CList* li = 0 - 1 - 2 - 3
    CList* la = 4 - 5 - 6 - 7 - 8 - 9

Si nous reprenons la liste _*li_ initiale sur laquelle j'applique `CList* la = CList_cut_front(CList_ffind_front(&li, find_6));` nous aurons :  

    CList* li = 7 - 8 - 9
    CList* la = 0 - 1 - 2 - 3 - 4 - 5 - 6

On voit bien que c'est exactement comme si je donnais un coup de ciseau dans la liste !  
Mais admettons cette fois-ci que je veuille découper un bout qui soit au milieu de la liste et non à ses extremités. C'est maintenant que rentre en jeu `CList_cut`.  

Reprenons de nouveau la liste de départ, avec cette ligne `CList* la = CList_cut(&li, CList_ffind_front(&li, find_4), CList_ffind_front(&li, find_6));` le résultat sera :  

    CList* li = 0 - 1 - 2 - 3 - 7 - 8 - 9
    CList* la = 4 - 5 - 6

Le maillon 3 et 7 de la liste _*li_ se sont raccrochés.  

**Rappel** : Les trois fonctions expliquées ci-dessus font un `malloc`, il faudra donc `free` leurs retours systématiquement.  
**Note** : Actuellement, Il est impératif à ce que le maillon `lna` se trouve avant `lnb` pour `CList_cut`.  
**Note** : Toutes les mini-fonction *find_4; find_6;* etc. n'existe évidemment pas, il faut les coder vous-même.  

Move
---------------------------------------------------------------------------------------------------------

Les fonctions **move** servent à déplacer un ensemble de maillons contigus à un autre endroit dans la liste ou dans une liste différente !  

    CList*    		CList_move_back  (CLink* lna, CLink* lnb, CList* la);
    CList*			CList_move_front (CLink* lna, CLink* lnb, CList* la);
    CList*			CList_move_after (CLink* lna, CLink* lnb, CLink* lnc);
    CList*			CList_move_before(CLink* lna, CLink* lnb, CLink* lnc);

Exemples prenons deux listes (li et la) :  

    CList* li = 0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9
    CList* la = 

    CList_move_back(CList_ffind_front(li, find_3), CList_ffind_front(li, find_6), la);

    CList li = 0 - 1 - 2 - 7 - 8 - 9
    CList la = 3 - 4 - 5 - 6

    CList_move_front(CList_ffind_front(li, find_2), CList_ffind_front(li, find_8), li);

    CList li = 2 - 7 - 8 - 0 - 1 - 9
    CList la = 3 - 4 - 5 - 6

    CList_move_back(CList_begin(la), CList_begin(la), la);

    CList li = 2 - 7 - 8 - 0 - 1 - 9
    CList la = 4 - 5 - 6 - 3

    CList_move_after(CList_ffind_front(li, find_0), CList_ffind_front(li, find_9), CList_ffind_front(la, find_5));

    CList li = 2 - 7 - 8
    CList la = 4 - 5 - 0 - 1 - 9 - 6 - 3

    CList_move_front(CList_begin(la), CList_end(la), li);

    CList li = 4 - 5 - 0 - 1 - 9 - 6 - 3 - 2 - 7 - 8
    CList la = 

Voilà je pense que ces quelques exemples sont bien plus parlant qu'autre chose ^^  
Ah oui, il ne faut surtout pas oublier que chaque maillon sait dans quelle liste il se trouve. C'est pour ça que toutes ces fonctions prennent très peu d'argument.  

Bon cependant ces fonctions sont un peu casse gueule dans le sens ou il faut que les deux premiers maillons (`*lna` et `*lnb`) soient de la même liste ET qu'ils soient dans le bon ordre (`*lna` avant `*lnb`). Il faut aussi que `*lnc` ne soit pas entre `*lna` et `*lnb`.  

Je compte plus tard faire des fonctions avec un suffixe `_secure` qui feront attention à tout ça.  
Exemple : `CList_move_after_secure` etc.

Bref, voilà je pense avoir fini :)  

Bisous <3