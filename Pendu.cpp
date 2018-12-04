#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

const int NOMBRE_ESSAIES_MAX = 10;

string melangerLettres(string mot) {
	string melange;
	int position(0);

	//Tant qu'on n'a pas extrait toutes les lettres du mot
	while (mot.size() != 0) {
		//On choisit un numéro de lettre au hasard dans le mot
		position = rand() % mot.size();
		//On ajoute la lettre dans le mot mélangé
		melange += mot[position];
		//On retire cette lettre du mot mystère
		//Pour ne pas la prendre une deuxième fois
		mot.erase(position, 1);
	}

	//On renvoie le mot mélangé
	return melange;
}

void jouezADeux() {
	string motMystere, motMelange, motUtilisateur;
	char choix = (char) 0;
	while (choix != 'N') {
		choix = (char) 0;
		int nombreEssaies = 0;
		//Initialisation des nombres aléatoires
		srand(time(0));

		//1 : On demande de saisir un mot
		cout << "Saisissez un mot" << endl;
		cin >> motMystere;

		//2 : On récupère le mot avec les lettres mélangées dans motMelange
		motMelange = melangerLettres(motMystere);

		// cache le mot mystère entré
		cout
				<< "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
				<< endl;

		//3 : On demande à l'utilisateur quel est le mot mystère
		do {
			cout << endl << "Quel est ce mot ? " << motMelange << endl;
			cin >> motUtilisateur;

			if (motUtilisateur == motMystere) {
				cout << "Bravo !" << endl;
			} else {
				cout << "Ce n'est pas le mot !" << endl;
				nombreEssaies++;
			}
		} while (motUtilisateur != motMystere
				&& nombreEssaies < NOMBRE_ESSAIES_MAX);
		//On recommence tant qu'il n'a pas trouvé
		if (nombreEssaies >= NOMBRE_ESSAIES_MAX) {
			cout
					<< "vous avez atteint le nombre d'essaies maximals, le mot a trouvé est : "
					<< motMystere << endl;
		}
		while (choix != 'N' && choix != 'o') {
			cout << "Voulez-vous continuer (o/N)" << endl;
			cin >> choix;
		}
	}
}

string motDuDictionnaire() {
	//Initialisation des nombres aléatoires
	srand(time(0));
	const string cheminFichierDico = ".\\dico.txt"; // chemin relatif par rapport à l'exécutable ou chemin absolu
	ifstream dico(cheminFichierDico.c_str()); //Ouverture d'un fichier en lecture
	int ligneSelectionne;
	string motChoisie;
	if (dico) {
		string ligne;
		int i = 0;
		while (getline(dico, ligne)) {
			i++;
		}
		dico.close();
		ifstream dico(cheminFichierDico.c_str());
		ligneSelectionne = rand() % i;
		i = 0;
		while (getline(dico, ligne)) {
			if (ligneSelectionne == i) {
				// suppression du \n à la fin de la ligne
				motChoisie = ligne.erase(ligne.length() - 1, ligne.length());
				break;
			}
			i++;
		}
	} else {
		cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
	}
	dico.close();
	return motChoisie;
}

void jouezSeul() {
	char choix;
	int nombreEssaies;
	string motUtilisateur, motMelange, motMystere;
	while (choix != 'N') {
		choix = (char) 0;
		nombreEssaies = 0;
		motMystere = motDuDictionnaire();
		//2 : On récupère le mot avec les lettres mélangées dans motMelange
		motMelange = melangerLettres(motMystere);

		//3 : On demande à l'utilisateur quel est le mot mystère
		do {
			cout << endl << "Quel est ce mot ? " << motMelange << endl;
			cin >> motUtilisateur;

			if (motUtilisateur == motMystere) {
				cout << "Bravo !" << endl;
			} else {
				cout << "Ce n'est pas le mot !" << endl;
				nombreEssaies++;
				cout << "Il vous reste : " << NOMBRE_ESSAIES_MAX - nombreEssaies
						<< " essaies" << endl;
			}
		} while (motUtilisateur != motMystere
				&& nombreEssaies < NOMBRE_ESSAIES_MAX);
		//On recommence tant qu'il n'a pas trouvé
		if (nombreEssaies >= NOMBRE_ESSAIES_MAX) {
			cout
					<< "vous avez atteint le nombre d'essaies maximals, le mot a trouvé est : "
					<< motMystere << endl;
		}
		while (choix != 'N' && choix != 'o') {
			cout << "Voulez-vous continuer (o/N)" << endl;
			cin >> choix;
		}
	}
}

int main() {
	char choix((char) 0);
	do {
		cout << "Voulez-vous jouez seul(o/N) ?" << endl;
		cin >> choix;
	} while (choix != 'N' && choix != 'o');
	if (choix == 'o') {
		jouezSeul();
	} else {
		jouezADeux();
	}
	return 0;
}
