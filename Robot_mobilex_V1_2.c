/*===============================================================
// Nom du fichier :Robot_Mobilex_V1_2
// Auteurs : J.BAYLE & A.AMIL
// Date de création : Mars 2020
// Version : V1_2
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Description :
// programation des differents modes du robot, changement des mode via la brique.
// Peut etre controle manuellement via des capteurs de contact ou se gare 
// automatiquement parallelement a un mur. Peut klaxonner en mode manuel.
// --------------------------------------------------------------
// A noter :
// mode 0 = à l'arret
// mode 1 = fonctionnement manuel
// mode 2 = fonctionnement automatique
// mode 3 = fin du programme
//===============================================================*/

//Fonction pour klaxonner en appuyant sur les 3 capteurs de contact
void klaxonne()
{
	while (SensorValue[S1]==1 && SensorValue[S2]==1 && SensorValue[S3]==1)
	{
		PlaySoundFile("klaxon.rso");
	}
}

task main()
{
	float fDistance = 0;
	SensorType[S4] = sensorEV3_Ultrasonic;
	SensorType[S1] = sensorEV3_Touch;
	SensorType[S2] = sensorEV3_Touch;
	SensorType[S3] = sensorEV3_Touch;
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
	//Entrer dans une boucle qui permet de passer d'un mode à l'autre jusqu'a aller dans le mode 3
	while (mode != 3) {
		eraseDisplay();
		if (mode == 1) {
		//Dans le mode 1
			while (mode ==1) {
				displayCenteredBigTextLine(2, "Mode:");
				displayCenteredBigTextLine(4, "Manuel");
				//Avance lorsque le capteur central est presse 
				while (SensorValue[S1]==1 && SensorValue[S2]!=1 && SensorValue[S3]!=1){
					playSound(soundUpwardTones);
					setMotorSpeed(motorC,30);
					setMotorSpeed(motorA,30);
				}
				stopMotor(motorA);
				stopMotor(motorC);
				//Deplacement a droite lorsque le capteur droit est presse
				while (SensorValue[S2]==1 && SensorValue[S3]!=1 && SensorValue[S1]!=1){
					playSound(soundLowBuzzShort);
					setMotorSpeed(motorC,5);
					setMotorSpeed(motorA,30);
				}
				stopMotor(motorA);
				stopMotor(motorC);
				//Deplacement a gauche lorsque le capteur gauche est presse
				while (SensorValue[S3]==1 && SensorValue[S1]!=1 && SensorValue[S2]!=1){
					playSound(soundDownwardTones);
					setMotorSpeed(motorC,30);
					setMotorSpeed(motorA,5);
				}
				stopMotor(motorA);
				stopMotor(motorC);
				//Marche arriere lorsque les capteurs droit et gauche sont presse simultanement
				while (SensorValue[S3]==1 && SensorValue[S2]==1 && SensorValue[S1]!=1){
					playSound(soundShortBlip);
					setMotorSpeed(motorC,-30);
					setMotorSpeed(motorA,-30);
				}
				stopMotor(motorA);
				stopMotor(motorC);
				//klaxonne si tous les capteurs de contacts sont appuie
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
						sleep(5000);
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
			//Choix du mode
			if (getButtonPress(buttonLeft)==1) {
				mode = 1;
			} else {
				if (getButtonPress(buttonRight)==1) {
					mode = 2;
				} else {
					if (getButtonPress(buttonUp)==1) {
						mode = 3;
						}
				}
			}
		}
	}
	//Entrer dans le mode 3: Fin du programme
	eraseDisplay();
	displayCenteredBigTextLine(2, "Fin du");
	displayCenteredBigTextLine(5, "programme");
	sleep(5000);
}