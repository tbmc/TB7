#include "Graph.h"
#include "affichage.h"
#include "common.h"
#include "analyse_lexicale.h"
#include "analyse_syntaxique.h"
#include "eval.h"

int main(int argc, char **argv)
{
    InitGraph(argc, argv, "Grapher", 640, 480, renderScene, keyEvent, mouseEvent, motionEvent, initOpenGL, wheelEvent, reshapeEvent);

    /*char in[] = "5x+1";
    float x = 3;
    printf("%s\n", in);
    int error = 0;
    Lexem l = AnalyseLexicale(in, &error);
    printf("Test : %d\n", getLexemSize(l));
    Arbre a = analyseSyntaxique(l, &error);
    float b = evaluation_arbre(a, x, &error);
    printf("Résultat: %f\n", b);*/

    return 0;
}

