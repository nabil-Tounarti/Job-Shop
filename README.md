# Job-Shop
# objectif :
Organiser dans le temps le fonctionnement d'un atelier contient 5 machines et 10 pièces .pour utiliser au mieux les ressources humaines et matérielles disponibles dans le but de produire les quantités désirées dans le temps imparti en utilisant l'ordonnancement (Job Shop).


# Hypothèse(s) retenue(s) :
Les données de l'atelier sont stockées dans un fichier txt.
On utilise le vecteur de Bierwith pour créer le graphe.
Pour optimiser le graphe on fait une recherche locale sur le vecteur de Bierwith puis une recherche globale portant sur 10 séquences.

# Liste du matériel :
Visual Studio Code

# 1. Présentation des structures des données :

T_instance:
    • Nombre de machines   
    • Nombre de pièces
    • Tableau des machines                            
    • Tableau des poids




T_solution:
    • Cout
    • Tableau des dates d'entrée de la pièce i au machine j
    • Tableau des péres
    • Vecteur de Bierwith




T_pere:
    • pièce
    • colonne




# 2.Description des points nécessaires à l’optimisation d’un JS :

# a) évaluation d’un graphe:
Pour évaluer un graphe on va calculer le cout et le plus long chemin en utilisant la fonction évaluer qui prend en paramètre une séquence et une solution et retourne un tableau des dates d'entrée de chaque pièce et tableau des péres et le coût.
On va stocker la fin fictive dans la case [6,12] dans le tableau des pères.
À travers le tableau des pères, on peut récupérer le plus long chemin en partant de la fin fictive et en arrivant au début fictif
on peut calculer le coût en ajoutant le temps de traitement pour chaque machine existe dans le plus long chemin.




# b) génération d’un graphe à partir d’une séquence:
Pour créer le graphe on va géneré un vecteur de Bierwith à travers ce vecteur on va génerer le graphe en utilisant la fonction évaluer qui prend en paramétre une séquence et une  solution cette solution contient le vecteur de Bierwith. la fonction évaluer retourne le graphe.




# c) conception d’une recherche locale efficace:
la fonction recherche local prend en paramètre une séquence et une solution et le nombre d'itérations maximal.
Premièrement en prend la fin fictive et son père et on fait la permutation s'ils sont sur la même machine.
Dans chaque itération, on va vérifier s'il existe un plus long chemin de coût optimal si oui le vecteur V recoit V' , sinon on continue la permutation.




# d) conception d’un GRASP()
la fonction recherche local prend en paramètre une séquence et une solution et le nombre d'itérations maximal.
dans chaque itération on essayer de créer 10 séquences à partir d'une seul solution en permutant aléatoirement deux pièces puis on vérifier si le nouveau vecteur n'est pas encore traité en utilisant un tableau de hachage
On stocke les solutions dans un tableau puis on prend le vecteur qui a le plus petit coût et en refait le même travaille sur ce niveau vecteur jusqu'à la fin de nombre d'itérations.




# e) conception la fonction lire
la fonction lire prend en paramètre un fichier texte et une séquence le transformer en deux tableaux un pour les machines et l'autre pour les poids





# d) conception la fonction génerer vecteur 
la fonction prend en paramétre une solution et retourne un Vecteur de Bierwith 




# 2.Description algorithmique des points nécessaires à l’optimisation d’un JS:

# a) la procédure évaluer ():
ST[i][j] : Matrice des dattes d'entrer de chaque pièce dans une machine

pm[i] : Une liste de structures contient deux entiers (a, b) pour mémoriser le père de chaque machine.

C[i] : Une lise des compteurs qui compte le nombre de fois d'apparition d'une pièce

m : Nombre des machines

n : Nombre des pièces

V : Vecteur de Bierwith

P : Le temps de traitement pour chaque machine

INITIALISATION:
∀ (i,j)  ST[i][j]=0
∀ (i)  pm[i]=(0,0)
∀ (i)  C[i]=0

# Algo:
Pour i=1 à n*m faire :

         j=V[i]
         
         C[j]=C[j]+1
         
         Si ( C[j] > 1) alors
         
           |       m=ST[j][C[j]-1]
           
           |       Si ( m+P[i][C[j]-1] > ST[j][C[j]] ) alors 
           
           |         |            ST[j][C[j]=m+P[i][C[j]-1] 
           
           |       fsi
           
         fsi
         
         mach =m[j][C[j]]
         
         Si pm[mach] =! (0,0) alors 
         
          |         (p,q) = pm[mach]
          
          |         date = ST[p][q]
          
          |        Si (date + P[p][q] > ST[j][C[j]] ) alors
          
          |         |          ST[j][C[j]] = date + P[p][q]
          
          |        fsi
          
         fsi
         
         pm[mach]=(j,C[j])
         
Fpour


# b) la procédure recherche_locale():


# Algo:


évaluer(ST,pere,cout)

Stop =  0

i=*

j=pere(*)

c=0

Tant-que (Stop == 0) faire

          c++
          
          Si (machine de i = machine de j ) alors 
          
           |        chercher position de i (Droitr à gauche) 
           
           |        chercher position de j (Droitr à gauche) 
           
           |         V'= permutation(V,pos i ,pos j)
           
           |        évaluer(V')
           
           |         Si (cout de V'  >  cout de V ) alors 
           
           |          |          i=j
           
           |          |           j=pére(j)
           
           |         Sinon
           
           |          |           V=V'
           
           |          |            i=*
           
           |          |            j=pere(i)
           
           |         fsi
           
         Sinon
         
           |          i=j
           
           |          j=pere(i)
           
          fsi
          
          Si ( i ==0) ou (c = nmaxit) alors
          
           |            Stop =1
           
          fsi
          
Fintq

                   


# b) la procédure Grasp():

tab_s est un tableau contient dix solutions
tab_h est un tableau de hachage
s une solution
ins une instance
nb_max est le nombre maximal des élévations

# Algo:

recherche_local(s,ins,50)


pour i de 1 à nb_max faire:

    |       tab_s[1]=s
    
    |       pour j de 2 à 10 faire:
    
    |            |          s1=s
    
    |            |       a=random()%50
    
    |            |          b=random()%50
    
    |            |          permutation(s1,ins,50,s)
    
    |            |         recherche_local(s1,ins,50)
    
    |            |         si tab_h[s1] == 0 test > test_max
    
    |            |            |                    tab_h[s1]=1
    
    |            |            |                   tab_s[j]=s1
    
    |            |            |                  test=0
    
    |            |         sinon
    
    |            |             |                   j--
    
    |            |             |                  test++
    
    |            |           fsi
    
    |          fpour
    
    |          j_max=1
    
    |          pour i de 2 à 10 faire
    
    |           |       Si le cout de tab_s[i] < cout de tab_s[j_max] alors
    
    |           |        |                 j_max=i
    
    |           |       fsi
    
    |          fpour
    
    |          s=tab_s[j_max]
    
fpour



