#pragma once
#include <stdlib.h>
#include <iostream>
#include <string>
#include "Header.h"
#include <iostream>
#include "string.h"
#include <fstream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
using namespace std;
const int n_max = 10;
const int m_max = 5;
const int n_vect = 60;
const int h_max = 500;

typedef struct T_instance {
	int n;
	int m;
	int machine[n_max+5][m_max+5];
	int p[n_max+1][m_max+5];
}T_instance;


typedef struct T_pere {
	int piece;
	int col;
}T_pere;


typedef struct T_solution {
	int co=0;
	int s[n_max+5][m_max+5];
	int vect[n_vect]={0};
	T_pere pere[n_max + 5][m_max + 5];
	
	
}T_solution;




void lire_inst(string nom, T_instance& ins);
void gen_vect(T_solution & s);
int cherche_pos(T_solution& s, int i, int j);
void permutation(T_solution& s1, int i, int j, T_solution& s);
void evaluer(T_solution& s, T_instance& ins);

void recherche_local(T_solution& s, T_instance ins, int n_max_itre);

int hachge(T_solution s);
void Grasp(T_solution& s, T_instance &ins, int nb_max);