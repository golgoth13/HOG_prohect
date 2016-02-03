*******************************************************************************
** Hans Julien, Perraud Frédéric                       3A SLE ENSIMAG 2015-2016
*******************************************************************************
	
**Résumé :
	
	Fichiers de configuration Catapult C pour la mise en oeuvre de 
l'algorithme HOG (Histogram Of Gradient). Ce répertoire contient également un 
fichier de test bench servant à la simulation ModelSim dans Catapult C et à 
l'exécution hors ligne du programme grace au Makefile.

**Utlisation :
	
	Pour utiliser les fichiers dans Catapult C, il suffit d'ajouter dans un
nouveau projet tout les fichier *.cpp et *.h en précisant d'ignorer tb_Main.cpp.
Pour ce projet, les contraintes à préciser sont pour l'architecture :
     - TODO mettre se qui va bien     
     -
     -
        Pour effectuer une simulation dans Catapult C, il faudra cocher dans les
options "sc_verify" en précisant les répertoires /li64 et /usr/gnu... dans ...
Il faudra également copier les répertoire ../img et ../res dans le répertoire 
de travail de Catapult C pour que l'image soit réellement chargée. Par défaut
Catapult C chargera une image noire.

        Pour simuler le fonctionnement de l'algorithme, il suffit compiler le 
projet avec le Makefile fournit : on peut choisir d'utiliser la librairie ac_int
de Catapult C ou celle fournie (ligne 7 du Makefile). Ce dernier utilise le 
fichier tp_Main.cpp pour charger en mémoire une image 320x240 au format pgm 
contenue dans le répertoire ../img. On peut préciser celle désirée dans le 
fichier tp_Main.cpp (ligne 51) et le résultat sera stocké dans le répertoire
../res (pour une éventuelle comparaison avec l'algorithme natif).
       Pour effacer les fichiers objet, l'executable : make clean. Pour 
également effacer les fichiers résultats et *.*~ : make clean-all.
	     
**Contenu détaillé :

	-Makefile : permet la compilation du projet pour en vérifier le bon 
fonctionnement et le débuggage.
	-Répertoire obj/ : stocke les fichiers objets compilés
	-tb_Main.cpp : sert à la compilation "hors ligne" et à la simulation
ModelSim via Catapult C.
	-Mem_Ram.h : contient toutes les constantes et les tableaux de valeurs 
nécessaires aux approximations linéaires.
	-HOG_Gradient : contient les fonctions calculant le gradient vertical et
horizontal d'un pixel.
	-HOG_Histogram : contient les fonctions calculant la norme et l'argument
d'un pixel
	-Main_HOG : fonction principale implémentant l'algorithme HOG et le
affiche résultat. L'argument "mode" permet de choisir le résultat de la sortie :
avec l'algorithme ou la simple copie de l'image d'entrée. 
