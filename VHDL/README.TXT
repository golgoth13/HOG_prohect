*******************************************************************************
** Hans Julien, Perraud Frédéric                       3A SLE ENSIMAG 2015-2016
**
**VHDL
*******************************************************************************

**Résumé :

	Contient tout les éléments à ajouter ou modifier au projet "zybo_cam" de
ISE pour générer le bit-stream du projet HOG. 

**Utlisation :

	Copier et écraser les fichiers dans le répertoire du projet "zybo_cam" 
de ISE. Ajouter les fichiers correspondant aux points d'interrogations 
(mem_lum.ngc, Main_Hog.edf, etc. Recompiler le projet puis lancer le script 
bootgen : le fichier boot.bin généré peut etre copié directement sur la carte SD
et testé.

**Contenu détaillé :

	- camera_capture : IP de la caméra permettant l'écriture de l'image dans
la mémoire RAM vidéo.
   	- clk_pll.vhd : IP permettant l'adapatation de l'horloge originelle
(124MHz) vers une horloge adaptée à la cadence de la camera et du VGA
	- Main_HOG : IP générée via le plug-in Précision (black-box décrite dans
le système top) : la version *_roll.edf est non optimée mais la version 
*_unroll l'es. Renommer l'une des deux en Main_Hog.edf pour l'intégrée au projet
   	- mem_lum.ngc : IP des deux RAM utilisées (Vidéo et VGA) 320x240 8
bits. Black-box décrite dans le fichier mem_lum.vhd.
	- multiplexer_RGB : IP gérant l'activation du module VGA_generator, de 
l'affichage des mires de test et de l'envoi des coordonnées des pixels à lire
dans la RAM VGA.
     	- packageVGA : contient les constantes et la déclaration de structure
	- system_top : IP principale contient l'intégralité des IP du projet:
leurs déclaration, leurs mapping ainsi que quelques fonctions permettant son
bon fonctionnement.
	-VGA_generator : IP calculant les adresses mémoires en fonction des 
coordonnées d'un pixel
