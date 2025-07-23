#include <iostream>
#include <vector>
#include <Windows.h>
#include "Book.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

// Anropa denna funktion f�r att enkelt kunna f� ��� r�tt utskriva:
void setWesternEuropeanCodePage() {
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    

}
using namespace std;


// Struct BokLista anv�nds f�r att representera en hel bokfil och dess inneh�ll
struct BokLista {
    string filnamn;  // Namnet p� filen som l�stes in (t.ex. "b1.txt")
    string rapportor; // Namnet p� personen som rapporterat (fr�n f�rsta raden i filen)
    string datum; // Datum n�r listan skapades (fr�n f�rsta raden i filen)
    vector<Book> books; // En lista (vector) med alla b�cker fr�n filen
};

void LasInBokFil(string filnamn, BokLista& lista) {
    lista.filnamn = filnamn; // vi sparar v�r filnamn och l�gger in den i v�r struct filnamn
    ifstream fil(filnamn); // �ppnar v�r fil d� med filnamn som vi anger 

	if (!fil) { // Om filen inte kunde �ppnas, skriv ut ett felmeddelande
        cout << "Kunde inte �ppna filen: " << filnamn << endl;
        return;
    }


    // --- L�ser f�rsta raden (rapport�r och datum) ---
	string firstLine;
	getline(fil, firstLine); // L�s f�rsta raden som �r rapport�r och datum
	stringstream ss(firstLine);// G�r raden till en stringstream f�r att enkelt dela upp den
    


    // Dela upp f�rsta raden i tv� delar (rapport�r och datum), separerade med ';'
	getline(ss, lista.rapportor, ';'); // Spara rapport�r i structen
	getline(ss, lista.datum, ';');// Spara datum i structen
     
    
    
    string line;
    while (getline(fil, line)) // Loopar s� l�nge det finns fler rader i filen
    {
		stringstream ss(line); // G�r om raden till en stringstream
        //variabler f�r datan
        string title, author, yearStr;
		getline(ss, title, ';'); // L�s titel
		getline(ss, author, ';'); // L�s f�rfattare
		getline(ss, yearStr, ';'); // L�s �rtal
		int year = stoi(yearStr); // Konvertera �rtal fr�n string till int
		lista.books.push_back(Book(title, author, year)); // Skapa en ny Book och l�gg till den i vector listan
        


    }
   
    

}
void laggTillBokfil(vector<BokLista>& filer, int& antalFiler, int& antalBocker) {

	//Fr�ga anv�ndaren efter filnamn
    string filnamn;
    cout << "Ange filnamn: " << endl;
    cin >> filnamn;

    // R�kna antal b�cker innan inl�sning
    int innan = 0;
    for (int i = 0; i < filer.size(); i++) {
        innan += filer[i].books.size();
    }

	// skapa en boklista som ska respresentera den nya filen
	BokLista nyLista;
    // L�s in filen och fyll v�r nya BokLista med data
    LasInBokFil(filnamn, nyLista);
    // L�gg till den nya BokLista i vektorn som inneh�ller ALLA filer
    filer.push_back(nyLista);

    int efter = 0;//R�kna hur m�nga b�cker som finns EFTER inl�sning
	for (int i = 0; i < filer.size(); i++) {
		efter += filer[i].books.size();
	}
    // Ber�kna skillnaden = hur m�nga nya b�cker vi l�ste in
	int nyaBocker = efter - innan;

    // Skriv ut resultat
    cout << "Rapport�r: " << nyLista.rapportor << endl;
    cout << "Datum: " << nyLista.datum << endl;
    cout << "L�ste in: " << nyaBocker << " b�cker.\n";

    //Uppdatera r�knare i huvudprogrammet via referenser
	antalFiler++;
	antalBocker = efter; // Uppdatera totalt antal b�cker
}

void visaEnBoklista(vector<BokLista>& filer) {
	// kollar om det finns n�gra filer att visa
	if (filer.empty()) {
		cout << "Inga bokfiler tillg�ngliga." << endl;
		return;
	}
	// Visa en lista �ver alla filer som har l�sts in
    cout << "\nF�ljande filer har l�sts in:\n";
    for (int i = 0; i < filer.size(); i++) {
        cout << (i + 1) << ".    " << filer[i].filnamn << endl;
    }

	// Fr�ga anv�ndaren vilken fil de vill se
    int val;
	cout << "Vilken lista vill du se (1-" << filer.size() << ")? ";
     
    cin >> val;


	// Kontrollera att anv�ndarens val �r giltigt
    if (val < 1 || val > filer.size()) {
        cout << "Ogiltigt val!\n";
        return;
    }
    //H�mta filens data
	BokLista& valdFil = filer[val - 1];

	// Skriv ut information om vald fil
	cout << "Rapport�r: " << valdFil.rapportor << ", " << "Datum: " << valdFil.datum << ". " << "Antal B�cker: " << valdFil.books.size() << endl;
    // Skriv rubrik f�r tabellen
    cout << setw(45) << left << "Titel" << setw(25) << left << "F�rfattare" << "�r\n";
    cout << "------------------------------------------------------------------------------\n";
    //Loopa igenom alla b�cker i vald fil och skriv ut deras info mha getters
	for (int i = 0; i < valdFil.books.size(); i++) {
		cout << setw(45) << left << valdFil.books[i].getTitle()
			<< setw(25) << left << valdFil.books[i].getAuthor()
			<< valdFil.books[i].getYear() << endl;
	}
	
}

void visaAllaBocker(vector<BokLista>& filer, int antalBocker) {
	// Kollar om det finns n�gra filer
	if (filer.empty()) {
		cout << "Inga bokfiler tillg�ngliga." << endl;
		return;
	}

	// Skriv ut rubriker och total antal b�cker
    cout << "\n------------------------------------------------------------------------------\n";
    cout << "Visar alla b�cker fr�n alla filer!" << endl;
	cout << "Totalt antal b�cker: " << antalBocker<< endl;
	// Skriv rubriker f�r tabellen
    cout << setw(45) << left << "\nTitel" << setw(25) << left << "F�rfattare" << "�r\n";
    cout << "------------------------------------------------------------------------------\n";

    //G� igenom alla filer i vektor filer
    for (int i = 0; i < filer.size(); i++) {
        BokLista& lista = filer[i];
        //loopa igenom alla b�cker i filen
		for (int j = 0; j < lista.books.size(); j++) {
			cout << setw(45) << left << lista.books[j].getTitle()
				<< setw(25) << left << lista.books[j].getAuthor()
				<< lista.books[j].getYear() << endl;
		}
    }

  

}
 


int main() {
    setWesternEuropeanCodePage(); // F�r att hantera svenska tecken (�, �, �) i Windows-konsolen.
    vector<BokLista> filer; // Alla filer med sina b�cker
    // Varje element i denna vector �r en BokLista som inneh�ller b�cker + data (filnamn, rapport�r, datum).
    
    
	
    int val = 0; // Anv�ndarens menyval
    int antalFiler = 0; // Totalt antal bokfiler
    int antalBocker = 0; // totalt antal b�cker
   

    do {
        // menyn
        cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "~~~~~  Bokhanteraren  ~~~~~~~" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << " Totalt antal bokfiler: " << antalFiler << endl;
        cout << " Totalt antal b�cker: " << antalBocker << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "1. L�gg till bokfil" << endl;
        cout << "2. Visa en boklista" << endl;
        cout << "3. Visa alla b�cker" << endl;
        cout << "4. Avsluta" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Ange ditt val: " << endl;

		cin >> val; // tar in inputen

        // Hantera valet
        switch (val) {
        case 1:
			laggTillBokfil(filer, antalFiler, antalBocker); // L�gg till en bokfil 
            break;
        case 2:
			visaEnBoklista(filer); // Visa en specifik boklista
            break;
        case 3:
            
			visaAllaBocker(filer, antalBocker); // Visa alla b�cker fr�n alla filer
			break;
        case 4:
            cout << "Programmet avslutas..." << endl;
            break;
        default:
            cout << "Felaktigt val! F�rs�k igen." << endl;
        }

    } while (val != 4); // Upprepa tills anv�ndaren v�ljer 4

    return 0;


}
