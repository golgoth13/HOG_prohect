*******************************************************************************
** Hans Julien, Perraud Frédéric
*******************************************************************************

**Résumé :

	Fichiers C++ permettant de traiter et visualiser le traitement d'image 
pgm contenus dans le répertoire ../img avec l'algorithme Histogram Of Gradient. 
L'execution du programme place les résultats dans le répertoire ../res : la 
première image est l'image originale, la deuxième est celle obtenue avec 
l'algorithme avec approximation linéaire sur des entiers et la dernière celle 
obtenue. Par ailleurs un certain nombre d'autre fonctions sont également 
implantées en début du programme main() (voir plus bas) pour donner le degré
de précision des approximations linéaires.

**Utlisation :
	 
	Pour utiliser la fonction, utiliser le Makefile et executer le binaire
./exec_cpp. Les fichiers spécifiés ligne 146 (et présent dans le répertoire 
../img) du main.cpp seront traités et le résultat sauvegardé dans le répertoire
../res.
	Pour visualiser (dans la console) le résultat de la comparaison entre le
calcul flottant double précision et l'approximation linéaire décommenter les
lignes à partir de la ligne 105 de main.cpp puis recompiler.

       Pour éffacer les fichiers objets et l'excutable, éxecuter make clean. Si
vous souhaiter effacer en plus les fichiers *.*~ et les fichiers résultats 
(../res/*_histo.pgm) : make clean-all.

**Contenu détaillé :
TODO
