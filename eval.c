#include "eval.h"

float evaluation_arbre(Arbre arbre, float x, int *error)
{
    if(arbre == NULL)
        return 0;
    float gauche, droite, n;
    gauche = evaluation_arbre(arbre->filsGauche, x, error);
    if(*error != 0)
        return 0;
    droite = evaluation_arbre(arbre->filsDroit, x, error);
    if(*error != 0)
        return 0;


    TypeLexem type = arbre->lexem->type;
    int t = type;

    if(type == FIN)
        return 0;

    if(type == VALUE)
    {
        return arbre->lexem->value;
    }
    else if(type == VARIABLE)
    {
        return x;
    }
    else
    {
        if(arbre->filsGauche == FIN)
        {
            if(((int)SIN) <= t && t < ((int)FIN_FONCTIONS))
                n = fonction(t, droite, error);
        }
        else
        {
            if(((int)PLUS) <= t && t <= ((int)POW))
                n = operation_eval(type, gauche, droite, error);
        }
        if(*error != 0)
            return 0;
        return n;
    }

    return 0;
}

float operation_eval(TypeLexem type, float a, float b, int *error)
{
    switch(type)
    {
    case PLUS:
        return a + b;
    case MOINS:
        return a - b;
    case MULTIPLIER:
        return a * b;
    case DIVISER:
        if(b == 0)
        {
            *error = DivisionPar0;
            return 0;
        }
        return a / b;
    case MODULO:
        if(b == 0)
        {
            *error = ModuloPar0;
            return 0;
        }
        if(!(ceilf(a)-a == 0 && ceilf(b)-b==0))
        {
            *error = ModuloVirgule;
            return 0;
        }
        return ((int)a) % (int)b;
    case POW:
        return (float)pow(a, b);
    default:
        *error = ErreurType;
        return 0;
    }
    return 0;
}

float fonction(int type, float a, int *error)
{
    double (*f)(double) = tab_functions[type - ((int)SIN)].f;
    if(f == sqrt && a < 0)
        *error = ErreurRacineCarre;
    else if((f == log || f == log10) && (a <= 0))
        *error = ErreurLN;
    else if(f == asin && -1 <= a && a <= 1)
        *error = ErreurASIN;
    else if(f == acos && -1 <= a && a <= 1)
        *error = ErreurACOS;
    else if(f == factoriel && a < 0)
        *error = ErreurFactoriel;
    if(*error != 0)
        return 0;
    return (float)(f(a));
}

Point eval(Arbre arbre, float x, int *error)
{
    Point p;
    p.x = x;
    p.y = evaluation_arbre(arbre, x, error);
    return p;
}

