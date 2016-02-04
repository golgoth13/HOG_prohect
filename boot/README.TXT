*******************************************************************************
** Hans Julien, Perraud Frédéric                       3A SLE ENSIMAG 2015-2016
*******************************************************************************

**Résumé :

	Contient les bit stream du projet après le passage dans ISE.
 
**Utlisation :

	Copier un des fichier sur la carte SD de la carte ZYBO en le renommant
boot.bin et mettre sous tension. Les fonctionnalités sont les suivantes :

	- switch 0 : permet d'activer ou non le module multiplexer_VGA. On peut 
soit choisir de le laisser activer (recopie du contenue de la RAM vers le 
périphérique VGA) soit en appuyant sur le bouton 1 ou 2 afficher les mires
verticales ou horizontales.

	- switch 1 : permet de choisir le mode fonctionnement du module HOG.
Soit ce dernier fait une simple copie de la mémoire d'entrée, soit il réalise
l'algorithme HOG et affiche le résultat.

	- switch 2 : bypass hardware pour la RAM VGA. Soit c'est le contenu de
la mémoire "caméra" qui est lue, soit c'est celle de la "RAM HOG"

	- switch 3 : permet d'activer ou désactiver le module VGA. Cela permet
notamment de freezer l'image VGA (le contenue de la RAM de sortie n'est plus
mis à jour.

**Contenu détaillé :

	- boot_roll.bin : projet compilé sans optimisation (déroulement des 
boucles)
	- boot_unroll.bin : projet optimisé avec déroulement de certaines 
boucles : performances accrues
