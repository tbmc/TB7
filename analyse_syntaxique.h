#ifndef ANALYSESYNTAXIQUE
#define ANALYSESYNTAXIQUE

#include "common.h"
#include "erreur.h"

Arbre analyseSyntaxique(Lexem lexem, int *error);

// Uniquement pour le debug
void debugArbre(Arbre arbre);
void afficheLexem(Lexem l, int size);
void debugArbre(Arbre arbre);
void debugArbreVu(Arbre arbre);

#endif // ANALYSESYNTAXIQUE

