#include "Header.h"




int main()
{
    T_instance ins;
    T_solution S;
    T_solution s1;

  
    lire_inst("la01.txt", ins);
    gen_vect(S);
    cout << endl;
    cout << "Le vecteur cree par la fonction gen_vect() est :" << endl;
    for (int h = 1; h <= 50; h++) {
        cout << S.vect[h] << " ";
    }

    evaluer( S, ins);
    
    //la solution
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "Apres l'evaluation de le vecteur precedente, on a trouve que le tableau des dates et le suivant :" << endl;
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 5; j++) {
            cout << S.s[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "Et le tableau des peres et le suivant :" << endl;
    //péres
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 5; j++) {
            cout << S.pere[i][j].piece << "|"<< S.pere[i][j].col << "  ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "et le cout est le suivant" << "Coût:" << S.co << endl;
    cout   << endl;


    recherche_local(S, ins, 7);
    cout << endl;
    cout << "Apres l'execution de la recherche local le coût est" << "Coût:" << S.co << endl;
   
    Grasp(S, ins,50);
    cout << endl;
    cout << "Apres l'exécution de la fonction Grasp le coût est" << "Coût:" << S.co << endl;
    
    
    
    
}


