#include <stdio.h>
#include <stdlib.h>

typedef int element;

struct cellule
{
    element contenu;
    struct cellule* suivant;
};

typedef struct cellule cellule;

typedef struct
{
    cellule* tete;
    cellule* fin;
}file_list;

void initFile(file_list *f)
{
    f->tete=NULL;
    f->fin=NULL;
}

int fileVide(file_list f)
{
    return(f.tete==NULL && f.fin==NULL);
}

void ajouteFile(file_list *f,element valeur)
{
    cellule *p;
    p=(cellule*)malloc(sizeof(cellule));
    p->contenu=valeur;
    p->suivant=NULL;
    if(fileVide(*f))
    {
        f->tete=p;
        f->fin=p;
    }
    else
    {
        f->fin->suivant=p;
        f->fin=p;
    }
}

element retirerFile(file_list *f)
{
    if(fileVide(*f))
    {
        printf("Hang doi trong!");
        exit;
    }
    else
    {
        element valeur;
        if(f->tete==f->fin)
        {
            valeur=f->tete->contenu;        
            f->tete=NULL;
            f->fin=NULL;
        }
        else
        {
            cellule *q;
            q=f->tete;
            valeur=f->tete->contenu;
            f->tete=q->suivant;
            free(q);
        }
        return valeur;
    }
}


