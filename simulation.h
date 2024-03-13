#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void lecture(char * nom_fichier);
void decodage_ligne(string line);

// traite le fichier ligne par ligne.  
void lecture(char * nom_fichier)
{
    string line;
    ifstream fichier(nom_fichier); 

    // l’appel de getline filtre aussi les séparateurs
    while(getline(fichier >> ws, line)) 
    {
        // ligne de commentaire à ignorer, on passe à la suivante
        if(line[0]=='#' or line[0]=='\n' or line[0]=='\r')  continue; 
        decodage_ligne(line);

    }
    cout << "fin de la lecture" << endl;

}

void decodage_ligne(string line){

    istringstream data(line);


}