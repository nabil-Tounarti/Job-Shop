#include "Header.h"

//la fonction pour lire le fichier
void lire_inst(string nom, T_instance& ins) {
	std::ifstream file(nom); //Ouvrir le fichier
	int nb_piece = -1;
	file >> nb_piece;
	int nb_machine = -1;
	file >> nb_machine;
	//Récupérer le nombre de machines et des pièces
	ins.n = nb_piece;
	ins.m = nb_machine;
	
	for (int i = 1; i <= nb_piece; i++) {
		for (int j = 1; j <= nb_machine; j++) {
			int n_machine = -1;
			int duree = -1;
			file >> n_machine; 
			n_machine++; //les machines commencent de 0, on doit ajouter 1
			file >> duree;
			ins.machine[i][j] = n_machine; //Récupérer la machine 
			ins.p[i][j] = duree; //Récupérer le pouce
		}
	}

}

//Générer un vecteur de bierwith
void gen_vect(T_solution& s) {
	int pos[n_max] = { 1,2,3,4,5,6,7,8,9,10 }; //Initialisation de tableau des positions
	int cont[n_max] = { m_max ,m_max ,m_max ,m_max ,m_max ,m_max ,m_max ,m_max ,m_max ,m_max }; //Initialisation des compteurs 
	int c = n_max;
	srand(time(NULL));
	int rnd = 0;
	for (int i = 1; i <= 50; i++) {
		rnd = (rand() % c); //Nombre aléatoire entre 0 et c-1 qui est le nombre des pièces encore à traité
		s.vect[i] = pos[rnd];
		cont[rnd]--; //Décrémente le compteur. 
		if (cont[rnd] == 0) {
			cont[rnd] = cont[c - 1];
			pos[rnd] = pos[c - 1];
			c--; //Décrémenter le nombre des pièces à traité
		}

	}
}

//Calculer le coût et le plus long chemin
void evaluer(T_solution& s, T_instance& ins) {
	T_pere pm[m_max+2];
	int j = -1;
	int counter[n_max + 1];
	int mach = 1;
	//Indianisation du vecteur de bierwith
	for (int i = 1; i <= m_max+1; i++) {
		pm[i].piece = 0;
		pm[i].col = 0;
	}
	//Indianisation de la list des pères
	for (int i = 1; i <= 12; i++) {
		s.pere[i][1].piece = 0;
		s.pere[i][1].col = 0;
	}
	//Indianisation de la liste des compteurs
	for (int i = 1; i <= n_max; i++) {
		counter[i] = 0;
	}
	//Indianisation du tableau des dates 
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 5; j++) {
			s.s[i][j] = 0;
		}

	}
	
	for (int i = 1; i <= n_max * m_max; i++) {
		j = s.vect[i];
		counter[j]++;
		
		int tmp = 0;
		if (counter[j] > 1) {
			tmp = s.s[j][counter[j] - 1];
			if ((tmp + ins.p[j][(counter[j] - 1)]) > s.s[j][counter[j]]) {
				s.s[j][counter[j]] = tmp + ins.p[j][(counter[j] - 1)]; //Mis à jour du tableau des dates

				s.pere[j][counter[j]].piece = counter[j] - 1; //Mis à jour du père
				s.pere[j][counter[j]].col = j;
			}
		}
		
		int p=0, q=0, date =0;
		mach = ins.machine[j][counter[j]]; //Récupérer le numéro de la machine
		if ( ( pm[mach].piece != 0) && (pm[mach].col != 0 )) {
			
			p = pm[mach].piece;
			q = pm[mach].col;
			
			date = s.s[p][q];
			if ( date + ins.p[p][q] > s.s[j][counter[j]]) {
				s.s[j][counter[j]] = date + ins.p[p][q]; //Mis à jour du tableau des dates
				s.pere[j][counter[j]].piece = q; //Mis à jour du père
				s.pere[j][counter[j]].col = p;

			}
		}
		pm[mach].piece = j;
		pm[mach].col = counter[j];
	}
	//Fin fictive et calcul du coût
	for (int i = 1; i <= 10; i++) {
		if (s.s[i][5] + ins.p[i][5] > s.co) {
			s.co = s.s[i][5] + ins.p[i][5];	
			s.pere[12][6].piece=5;
			s.pere[12][6].col = i;
		}
	}
	
	
	
}

//Chercher la position de la pièce i dans la machine j
int cherche_pos(T_solution &s,  int i,int j) {
	int k = 5; //Nombre des machines
	int p = 50;
	while (k >= j) {
		if (s.vect[p] == i) { //Vérifier le numéro de la pièce
			k--;
		}
		p--;
	}
	return p+1;
}

//permuter i et j
void permutation(T_solution& s1, int i, int j, T_solution& s) {

	for (int k = 1; k <= 50; k++) {
		s1.vect[k] = s.vect[k];
	}
	int a= s.vect[j];
	int b = s.vect[i];;
	s1.vect[i] = a;//Permuter i et j
	s1.vect[j] = b;
}

//faire la recherche local 
void recherche_local(T_solution &s,T_instance ins,int n_max_itre){
	int c = 0;int a = 0;int b = 0;
	T_solution s1;
	bool stop = false;
	//Initialise le vecteur de bierwith de la solution s1 par le vecteur de bierwith de la solution s
	for (int h = 1; h <= 50; h++) {
		s1.vect[h] = s.vect[h];
	}
	
	evaluer(s, ins); //pour calculer le cout 
	
	
	T_pere p = s.pere[12][6]; //la  fin fictive
	T_pere q = s.pere[p.col][p.piece]; // le pére de la fin fictive
	
	
	while (!stop) {
		c++;	
		//Tester si p et q sont sur la même machine
		if (ins.machine[p.col][p.piece] == ins.machine[q.col][q.piece]) { 
			//si oui, on permute p et q pour trouver s1
			a=cherche_pos(s, p.col, p.piece);
			b= cherche_pos(s, q.col, q.piece);
			permutation(s1, a, b, s);
			evaluer(s1, ins);
			
			//si le coût de s1 est plus grand que le coût de s
			if (s1.co > s.co) {
				//si oui on continue 
				p = q;
				q = s.pere[q.col][q.piece];
			}
			else {
				//sinon V=V' <--> s=s1
				for (int h = 1; h <= 50; h++) {
					s.vect[h]=s1.vect[h] ;
				}
				s.co = s1.co;
				p = s.pere[12][6];
				q = s.pere[p.col][p.piece];
			}

		}
		else {
			//Sinon on continue le parcours de le plus long chemin
			p = q;
			q = s.pere[p.col][p.piece];
		}
		//si on est arrivé à la fin
		if ( p.col == 0 || c == n_max_itre) {
			stop = true;
		}
		
	}
	evaluer(s, ins);//pour calculer le cout final
}

//la fonction de hachage 
int hachge(T_solution s) {
	int m = 0;
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 5; j++) {
			m = m + (s.s[i][j])* (s.s[i][j]);//fonction de hachage 
		}
	}
	return (m%h_max);
}

//la fonction grasp()
void Grasp(T_solution& s, T_instance& ins, int nb_max) {
	srand(time(NULL));
	int a = 0, b = 0,test=0,test_max=20;
	T_solution tab_s[11];
	int tab_h[h_max];
	//inisialiser le tableau de hachage à des zéros
	for (int i = 0; i < h_max; i++) {
		tab_h[i] = 0;
	}

	recherche_local(s, ins, 50);

	for (int i = 0; i < nb_max; i++) {
		tab_s[1] = s;//sauvgarder le vecteur s
		//On va générer 9 solutions à partir de s.
		for (int j = 2; j <= 10; j++) {
			T_solution s1 = s;
			a = (rand() % 50) + 1;//Nombre aléatoire
			b = (rand() % a) + (rand()%(50-a+ 1))+1;//Nombre aléatoire défère de a
			permutation(s1, a, b, s);//permuter a et b
			recherche_local(s1, ins, 50);
			//si le vecteur n'est jamais traité
			if (tab_h[hachge(s1)] == 0 || test > test_max) {
				//j'ai ajouté le test parce qu'il'y a une possibilité de boucle infinie si la table de hachage est plein
				tab_h[hachge(s1)] = 1;
				tab_s[j] = s1;
				test = 0;
			}
			else {
				j--;
				test++;
			}
			
		}
		int j_max = 1;
		//Récupérer la solution de cout minimal
		for (int i = 2; i <= 10; i++) {
			if (tab_s[i].co < tab_s[j_max].co) {
				j_max = i;
			}
		}
		s = tab_s[j_max];
		
	}
}