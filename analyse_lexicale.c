#include "analyse_lexicale.h"
#include <string.h>
#include "erreur.h"

void decaler (char* tab,int i) // supprime le caractere au rang i de la chaine de caractere en parametre en decalant tout les caracteres qui suivent
{
    for(;tab[i]!='\0';i++)
    {
        tab[i]=tab[i+1];
    }
}

void mise_en_forme(char* tab) // mets tout les caracteres en miniscules et supprime les espaces
{
    int i;
    for(i=0;tab[i]!='\0';i++)
    {
        while(tab[i]==' ')
        {
            decaler(tab,i);
        }
        if(tab[i]>='A' && tab[i]<='Z' )
        {
            tab[i]+=('a'-'A');
        }
    }
}

int comparer(const char* tab1,const char* tab2,int* avancement) //compare la chaine tab1 (a partirdu rang avancement) et tab2 et renvoit le nombre de caracteres en commun
{
    int i;
    for(i=0;tab1[i+(*avancement)]!= '\0' && tab2[i]!= '\0' && tab1[i+(*avancement)]==tab2[i];i++);
    return i;
}

float lire_chaine_value(char* tab, int* avancement,int* error) //renvoit le nombre dans la chaine de caractere
{
    float value=0;
    int virgule=0;
    for(;((tab[(*avancement)]<='9' && tab[(*avancement)]>='0'))|| tab[(*avancement)]==';' ||
        tab[(*avancement)]=='.' || tab[(*avancement)]==',';(*avancement)++)
    {
        if(tab[(*avancement)]==';' || tab[(*avancement)]=='.' || tab[(*avancement)]==',')
        {
            if(virgule==0)
            {virgule++;}
            else
            {
                *error=VIRGULE_EN_TROP;
                return 0;
            }
        }
        else
        {
            if(virgule==0)
            {
                value*=10;
                value+=((tab[(*avancement)]-'0'));
            }
            else
            {
                value+=((tab[(*avancement)]-'0')*pow(10,-virgule));
                virgule++;
            }
        }
    }
    return value;
}

TypeLexem lire_fonction(char* tab, int* avancement, int* error) // renvoit le lexem de la fonction dans le texte renvoit null si fonction inconnue
{
    int i, len;
    for(i = FIN; i < ((int)FIN_FONCTIONS) - ((int)SIN); i++)
    {
        len = strlen(tab_functions[i].n);
        if(comparer(tab, tab_functions[i].n, avancement) == len)
        {
            *(avancement) += len;
            return (TypeLexem)(i + SIN);
        }
    }
    /*
    if(comparer(tab,"sinh",avancement)==4)
    {
        *(avancement)+=4;
        return SINH;
    }
    else if(comparer(tab,"cosh",avancement)==4)
    {
        *(avancement)+=4;
        return COSH;
    }
    else if(comparer(tab,"tanh",avancement)==4)
    {
        *(avancement)+=4;
        return TANH;
    }
    else if(comparer(tab,"sin",avancement)==3)
    {
        *(avancement)+=3;
        return SIN;
    }
    else if(comparer(tab,"cos",avancement)==3)
    {
        *(avancement)+=3;
        return COS;
    }
    else if(comparer(tab,"tan",avancement)==3)
    {
        *(avancement)+=3;
        return TAN;
    }
    else if(comparer(tab,"ln",avancement)==2)
    {
        *(avancement)+=2;
        return LN;
    }
    else if(comparer(tab,"log",avancement)==3)
    {
        *(avancement)+=3;
        return LOG;
    }
    else if(comparer(tab,"sqrt",avancement)==4)
    {
        *(avancement)+=4;
        return SQRT;
    }
    else if(comparer(tab,"exp",avancement)==3)
    {
        *(avancement)+=3;
        return EXP;
    }
    else if(comparer(tab,"pi",avancement)==2)
    {
        *(avancement)+=2;
        return PI;
    }
    else if(comparer(tab,"abs",avancement)==3)
    {
        *(avancement)+=3;
        return ABS;
    }
    else if(comparer(tab,"asin",avancement)==4)
    {
        *(avancement)+=4;
        return ASIN;
    }
    else if(comparer(tab,"acos",avancement)==4)
    {
        *(avancement)+=4;
        return ACOS;
    }
    else if(comparer(tab,"atan",avancement)==4)
    {
        *(avancement)+=4;
        return ATAN;
    }
    else if(comparer(tab,"arrinf",avancement)==6)
    {
        *(avancement)+=6;
        return ARRINF;
    }
    else if(comparer(tab,"arrsup",avancement)==6)
    {
        *(avancement)+=6;
        return ARRSUP;
    }
    else */
    if(((tab[(*avancement)]<='9' && tab[(*avancement)]>='0'))|| tab[(*avancement)]==';' || tab[(*avancement)]=='.' || tab[(*avancement)]==',')
    {
        return VALUE;
    }
    else
    {
        *error=EXPRESSION_INCONNUE;
        return VALUE;
    }
}

TypeLexem lire_chaine_type(char* tab, int* avancement, int* error) // renvoit l'operateur ou la fonction ecrite
{
    int i;
    for(i = FIN; i < (int)POW; i++)
    {
        if(tab[*avancement] == tab_operators[i])
        {
            (*avancement)++;
            return (TypeLexem)i;
        }
    }
    return lire_fonction(tab, avancement, error);
    /*
    switch(tab[(*avancement)])
    {
    case '+' :
    {
        (* avancement)++;
        return PLUS;
        break;
    }
    case 'x' :
    {
        (* avancement)++;
        return VARIABLE;
        break;
    }
    case '-' :
    {

        (* avancement)++;
        return MOINS;
        break;
    }
    case '*' :
    {
        (* avancement)++;
        return MULTIPLIER;
        break;
    }
    case '/' :
    {
        (* avancement)++;
        return DIVISER;
        break;
    }
    case '%' :
    {
        (* avancement)++;
        return MODULO;
        break;
    }
    case '!' :
    {
        (* avancement)++;
        return FACTORIELLE;
        break;
    }
    case '(' :
    {
        (* avancement)++;
        return PARENTHESE_OUVRANTE;
        break;
    }
    case ')' :
    {
        (* avancement)++;
        return PARENTHESE_FERMANTE;
        break;
    }
    case '^' :
    {
        (* avancement)++;
        return POW;
        break;
    }
    case '\0' :
    {
        (* avancement)++;
        return FIN;
        break;
    }
    default :
    {
        return lire_fonction(tab, avancement, error);
        break;
    }
    }*/
}

Lexem AnalyseLexicale(const char* tab, int* error) //
{
    if(tab==NULL)
    {
        *error=POINTEUR_NULL;
        return NULL;
    }
    else
    {
        // Creation chaine de caractere et copy de la saisie
        char* copy_tab = (char*) malloc((size_t)strlen(tab)+sizeof(char));
        if(tab==NULL)
        {
            *error=ECHEC_MALLOC;
            return NULL;
        }
        strcpy(copy_tab,tab);
        mise_en_forme(copy_tab);

        //Allocation de la memoire pour le retour
        Lexem retour=(Lexem) malloc((size_t)sizeof(struct Lexem)*MAX_LEXEM);
        if(retour==NULL)
        {
            *error=ECHEC_MALLOC;
            return NULL;
        }

        //Transformation de la formule en lexem
        int i=0,avancement=0;
        for(i=0;i<MAX_LEXEM && *error==0;i++)
        {
            if(copy_tab[avancement]!='\0')
            {
                retour[i].type=lire_chaine_type(copy_tab,&avancement,error);
                if(retour[i].type==VALUE)
                {
                    retour[i].value=lire_chaine_value(copy_tab,&avancement,error);
                }
                else if(retour[i].type==PI)
                {
                    retour[i].type=VALUE;
                    retour[i].value= 3.141592653589793;
                }
                else if(retour[i].type==MOINS)
                {
                    retour[i].type=PLUS;
                    if(i>MAX_LEXEM-2)
                    {
                        *error=FONCTION_TROP_LONGUE;
                    }
                    else
                    {
                        i++;
                        retour[i].type=VALUE;
                        retour[i].value=(-1.0);
                    }
                }
                else
                {
                    retour[i].value=0.;
                }
            }
            else
            {
                retour[i].value=0.;
                retour[i].type=FIN;
            }

        }

        //suppression de la copie de la chaine de caractere
        free(copy_tab);

        //Verification de la presence du FIN et retour
        if(*error==0 && retour[(i-1)*(i>0)].type==FIN && i>0)
        {
            return retour;
        }
        free(retour);
        retour=NULL;
        if(*error==0)
        {
            *error=FONCTION_TROP_LONGUE;
        }
        return retour;
    }
}
