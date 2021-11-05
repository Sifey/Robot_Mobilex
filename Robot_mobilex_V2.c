/*===============================================================
// Nom du fichier :Robot_Mobilex_V2
// Auteurs : J.BAYLE & A.AMIL
// Date de création : Mars 2020
// Version : V2.1
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Description :
// Robot Mobilex commandable via la telecommande sans fil, peut 
// être commande manuellement ou se gare automatiquement 
// parallelement a un mur.
// --------------------------------------------------------------
// A noter :
// mode 0 = à l'arret
// mode 1 = fonctionnement manuel
// mode 2 = fonctionnement automatique
// mode 3 = fin du programme
// N'ayant pas pu faire de test pour connaitre les distances reels,
// pour une puissance et une direction donnée, les distances 
// affiché sont a titre d'exemple afin de montrer le fonctionnement
// de notre systeme.
// **************************************************************

--------------MANUEL D'UTILISATION DU ROBOT MOBILEX--------------

-Preparation: 
	-Brancher le capteur infrarouge sur la sortie S1
	-Brancher le capteur ultrason sur la sortie S4
	-Brancher le moteur droit sur la sortie C
	-Brancher le moteur gauche sur la sortie A
	-Placer le capteur ultrason suffisamment haut 
	pour qu'il ne soit pas gener par des obstacles

-Demarrage:
	Lorsque le programme demarre , il entre dans le mode 0 qui permet le 
	choix entre le mode manuel (presse du bouton gauche de la brique) ou 
	le mode automatique (presse du bouton droit de la brique)

-Mode manuel (le robot se controle a distance via la telecommande sans fil):
	-Marche Avant : Haut rouge et haut bleu appuye simultanement
	-Marche Arrière : Bas rouge et bas bleu appuye simultanement
	-Tourner à Droite : Haut bleu appuye
	-Tourner à Gauche : Haut rouge appuye 
	-Klaxonner : Haut bleu et bas rouge appuye
	
-Mode automatique:
	Lors du lancement de ce mode, le robot avance tout droit jusqu’a detecter un 
	mur, puis il se gare parallelement a celui-ci.

-Changement de mode:
	Il est possible de passer d’un mode a un autre en appuyant sur le bouton bas 
	de la brique, on peut choisir de passer au mode manuel ou automatique mais aussi 
	d’éteindre le programme (les boutons sur lesquels appuyer sont affiché sur la brique).
	Le robot passe automatiquement en mode automatique a l'approche d'un mur

-Fin du programme: 
	La brique affiche la distance parcouru et un message de fin de programme pendant 
	8 secondes puis le programme s'éteint.
//=====================================================================================*/

//Fonction pour klaxonner en appuyant sur haut bleu et bas rouge
void klaxonne()
{
	if (getIRRemoteButtons(S1)==11)
	{
		PlaySoundFile("klaxon.rso");
	}
}

task main()
{
	float fDistance = 0;
	SensorType[S4] = sensorEV3_Ultrasonic;
	SensorType[S1] = sensorEV3_IRSensor;
	int mode = 0;
	int compteur = 0;

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
				displayCenteredBigTextLine(2, "Mode:");
				displayCenteredBigTextLine(4, "Manuel");
				//Avance lorsque les bouton haut bleu et rouge sont appuye 
				while (getIRRemoteButtons(S1)==5 || mode != 2){
					playSound(soundLowBuzzShort);
					setMotorSpeed(motorC,30);
					setMotorSpeed(motorA,30);
					sleep(50);
					// a chaque bloucle le robot avance de 5 cm
					compteur = compteur + 5;
					if (fDistance <= 25) {
						mode = 2;
					}
				}
				stopMotor(motorA);
				stopMotor(motorC);
				//Deplacement a droite lorsque le bouton haut bleu est appuye
				while (getIRRemoteButtons(S1)==3 || mode != 2){
					playSound(soundLowBuzzShort);
					setMotorSpeed(motorC,5);
					setMotorSpeed(motorA,30);
					sleep(50);
					// a chaque bloucle le robot avance de 1 cm
					compteur = compteur + 1;
					if (fDistance <= 25) {
						mode = 2;
					}
				}
				stopMotor(motorA);
				stopMotor(motorC);
				//Deplacement a gauche lorsque le bouton haut rouge est appuye
				while (getIRRemoteButtons(S1)==1 || mode != 2){
					playSound(soundDownwardTones);
					setMotorSpeed(motorC,30);
					setMotorSpeed(motorA,5);
					sleep(50);
					// a chaque bloucle le robot avance de 1 cm
					compteur = compteur + 1;
					if (fDistance <= 25) {
						mode = 2;
					}
				}
				stopMotor(motorA);
				stopMotor(motorC);
				//Marche arriere lorsque les boutons bas rouge et bleu sont appuye
				while (getIRRemoteButtons(S1)==8 || mode != 2){
					playSound(soundShortBlip);
					setMotorSpeed(motorC,-30);
					setMotorSpeed(motorA,-30);
					sleep(50);
					// a chaque bloucle le robot avance de 5 cm
					compteur = compteur + 5;
					if (fDistance <= 25) {
						mode = 2;
					}
				}
				stopMotor(motorA);
				stopMotor(motorC);
				//Possibilite de klaxonner si les boutons haut bleu et bas rouge sont appuye
				klaxonne();
				//test pour changer de mode
				if (getButtonPress(buttonDown)==1) {
					mode = 0;
				}
			}
		} else {
			//Entrer dans le mode 2
			if (mode == 2 ) {
				while (mode == 2) {
					//il avance tout droit a 20% de la puissance de chaque moteur
					setMotorSpeed(motorC,20);
					setMotorSpeed(motorA,20);
					sleep(50);
					// a chaque bloucle le robot avance de 3 cm
					compteur = compteur + 3;
					displayCenteredBigTextLine(2, "Mode:");
					displayCenteredBigTextLine(4, "Automatique");
					// S'arrete lorsque qu'il est a 16cm ou moins d'un mur puis se gare parallelement au mur
					fDistance = getUSDistance(S4);
					if (fDistance <= 16) {
						stopMotor(motorA);
						stopMotor(motorC);
						sleep(1000);
						setMotorSpeed(motorC,1);
						setMotorSpeed(motorA,10);
						sleep(4500);
						// a chaque bloucle le robot avance de 15 cm
						compteur = compteur + 15;
						mode = 0;
					}
					//test pour changer de mode
					if (getButtonPress(buttonDown)==1) {
						mode = 0;
					}
				}
				//Entrer dans le mode 0
				stopMotor(motorA);
				stopMotor(motorC);
			}
		}

		eraseDisplay();
		while (mode == 0) {

		//affiche sur la brique les options pour choisir un mode
			displayCenteredBigTextLine(2, "Bouton gauche:");
			displayCenteredTextLine(5, "fonctionnement manuel");
			displayCenteredBigTextLine(9, " Bouton droit: ");
			displayCenteredTextLine(11, "Foncionnement automatique");
			displayCenteredBigTextLine(13, " Bouton haut: ");
			displayCenteredTextLine(16, "Fin du programme");
			//Choix du mode 1
			if (getButtonPress(buttonLeft)==1) {
				mode = 1;
			} else {
				//choix du mode 2
				if (getButtonPress(buttonRight)==1) {
					mode = 2;
				} else {
				//choix du mode 3
						if (getButtonPress(buttonUp)==1) {
							mode = 3;
						}
				}
			}
		}
	}
	//Entrer dans le mode 3: Fin du programme et affichage de la distance parcouru
	eraseDisplay();
	displayCenteredBigTextLine(2, "Fin du");
	displayCenteredBigTextLine(5, "programme");
	displayCenteredTextLine(12, "Distance parcouru: %d cm", compteur);
	sleep(8000);
}
