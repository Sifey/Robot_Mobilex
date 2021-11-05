/*===============================================================
// Nom du fichier :Robot_Mobilex_V1_1
// Auteur : J.BAYLE & A.AMIL
// Date de création : Mars 2020
// Version : V1.1
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Description :
// Codage des differents mode du robot pour pouvoir passer d'un 
// mode a l'autre 
// --------------------------------------------------------------
// A noter :
// mode 0 = à l'arret
// mode 1 = fonctionnement manuel
// mode 2 = fonctionnement automatique
//===============================================================*/

task main()
{
	int mode = 0;

	//Entrer dans le mode 0, choix du mode 1 ou du mode 2.
	while (mode != 1 && mode !=2) {

		//afficher sur la brique les options pour choisir un mode
		displayCenteredBigTextLine(2, "Bouton gauche:");
		displayCenteredTextLine(5, "fonctionnement manuel");
		displayCenteredBigTextLine(9, " Bouton droit: ");
		displayCenteredTextLine(11, "Foncionnement automatique");
			//Choix du mode
			if (getButtonPress(buttonLeft)==1) {
			mode = 1;
			} else {
				if (getButtonPress(buttonRight)==1) {
				mode = 2;
			}
		}
	}
	while (mode != 3) {
			eraseDisplay();
		if (mode == 1) {
		//Dans le mode 1
			while (mode ==1) {
				displayCenteredBigTextLine(2, "Mode 1");
				//test pour changer de mode
				if (getButtonPress(buttonDown)==1) {
					mode = 0;
				}
			}
		} else {
			//Dans le mode 2
			if (mode == 2) {
				while (mode == 2) {
				displayCenteredBigTextLine(2, "Mode 2");
				//test pour changer de mode
					if (getButtonPress(buttonDown)==1) {
						mode = 0;
					}
				}
			}
		}

		eraseDisplay();
		while (mode == 0) {

		//afficher sur la brique les options pour choisir un mode
			displayCenteredBigTextLine(2, "Bouton gauche:");
			displayCenteredTextLine(5, "fonctionnement manuel");
			displayCenteredBigTextLine(9, " Bouton droit: ");
			displayCenteredTextLine(11, "Foncionnement automatique");
			displayCenteredBigTextLine(13, " Bouton haut: ");
			displayCenteredTextLine(16, "Fin du programme");
			//Choix du mode
			if (getButtonPress(buttonLeft)==1) {
				mode = 1;
			} else {
				if (getButtonPress(buttonRight)==1) {
					mode = 2;
				} else {
				//Appuie sur le bouton bas pour aller mode 0
						if (getButtonPress(buttonUp)==1) {
							mode = 3;
						}
				}
			}
		}
	}
	eraseDisplay();
	displayCenteredBigTextLine(2, "Mode 3");
	sleep(5000);
}
