#include <iostream>
#include <vector>
#include <Windows.h>
#include "Book.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

// Anropa denna funktion för att enkelt kunna få åäö rätt utskriva:
void setWesternEuropeanCodePage() {
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    

}
using namespace std;


// Struct BokLista används för att representera en hel bokfil och dess innehåll
struct BokLista {
    string filnamn;  // Namnet på filen som lästes in (t.ex. "b1.txt")
    string rapportor; // Namnet på personen som rapporterat (från första raden i filen)
    string datum; // Datum när listan skapades (från första raden i filen)
    vector<Book> books; // En lista (vector) med alla böcker från filen
};

void LasInBokFil(string filnamn, BokLista& lista) {
    lista.filnamn = filnamn; // vi sparar vår filnamn och lägger in den i vår struct filnamn
    ifstream fil(filnamn); // öppnar vår fil då med filnamn som vi anger 

	if (!fil) { // Om filen inte kunde öppnas, skriv ut ett felmeddelande
        cout << "Kunde inte öppna filen: " << filnamn << endl;
        return;
    }


    // --- Läser första raden (rapportör och datum) ---
	string firstLine;
	getline(fil, firstLine); // Läs första raden som är rapportör och datum
	stringstream ss(firstLine);// Gör raden till en stringstream för att enkelt dela upp den
    


    // Dela upp första raden i två delar (rapportör och datum), separerade med ';'
	getline(ss, lista.rapportor, ';'); // Spara rapportör i structen
	getline(ss, lista.datum, ';');// Spara datum i structen
     
    
    
    string line;
    while (getline(fil, line)) // Loopar så länge det finns fler rader i filen
    {
		stringstream ss(line); // Gör om raden till en stringstream
        //variabler för datan
        string title, author, yearStr;
		getline(ss, title, ';'); // Läs titel
		getline(ss, author, ';'); // Läs författare
		getline(ss, yearStr, ';'); // Läs årtal
		int year = stoi(yearStr); // Konvertera årtal från string till int
		lista.books.push_back(Book(title, author, year)); // Skapa en ny Book och lägg till den i vector listan
        


    }
   
    

}
void laggTillBokfil(vector<BokLista>& filer, int& antalFiler, int& antalBocker) {

	//Fråga användaren efter filnamn
    string filnamn;
    cout << "Ange filnamn: " << endl;
    cin >> filnamn;

    // Räkna antal böcker innan inläsning
    int innan = 0;
    for (int i = 0; i < filer.size(); i++) {
        innan += filer[i].books.size();
    }

	// skapa en boklista som ska respresentera den nya filen
	BokLista nyLista;
    // Läs in filen och fyll vår nya BokLista med data
    LasInBokFil(filnamn, nyLista);
    // Lägg till den nya BokLista i vektorn som innehåller ALLA filer
    filer.push_back(nyLista);

    int efter = 0;//Räkna hur många böcker som finns EFTER inläsning
	for (int i = 0; i < filer.size(); i++) {
		efter += filer[i].books.size();
	}
    // Beräkna skillnaden = hur många nya böcker vi läste in
	int nyaBocker = efter - innan;

    // Skriv ut resultat
    cout << "Rapportör: " << nyLista.rapportor << endl;
    cout << "Datum: " << nyLista.datum << endl;
    cout << "Läste in: " << nyaBocker << " böcker.\n";

    //Uppdatera räknare i huvudprogrammet via referenser
	antalFiler++;
	antalBocker = efter; // Uppdatera totalt antal böcker
}

void visaEnBoklista(vector<BokLista>& filer) {
	// kollar om det finns några filer att visa
	if (filer.empty()) {
		cout << "Inga bokfiler tillgängliga." << endl;
		return;
	}
	// Visa en lista över alla filer som har lästs in
    cout << "\nFöljande filer har lästs in:\n";
    for (int i = 0; i < filer.size(); i++) {
        cout << (i + 1) << ".    " << filer[i].filnamn << endl;
    }

	// Fråga användaren vilken fil de vill se
    int val;
	cout << "Vilken lista vill du se (1-" << filer.size() << ")? ";
     
    cin >> val;


	// Kontrollera att användarens val är giltigt
    if (val < 1 || val > filer.size()) {
        cout << "Ogiltigt val!\n";
        return;
    }
    //HÄmta filens data
	BokLista& valdFil = filer[val - 1];

	// Skriv ut information om vald fil
	cout << "Rapportör: " << valdFil.rapportor << ", " << "Datum: " << valdFil.datum << ". " << "Antal Böcker: " << valdFil.books.size() << endl;
    // Skriv rubrik för tabellen
    cout << setw(45) << left << "Titel" << setw(25) << left << "Författare" << "År\n";
    cout << "------------------------------------------------------------------------------\n";
    //Loopa igenom alla böcker i vald fil och skriv ut deras info mha getters
	for (int i = 0; i < valdFil.books.size(); i++) {
		cout << setw(45) << left << valdFil.books[i].getTitle()
			<< setw(25) << left << valdFil.books[i].getAuthor()
			<< valdFil.books[i].getYear() << endl;
	}
	
}

void visaAllaBocker(vector<BokLista>& filer, int antalBocker) {
	// Kollar om det finns några filer
	if (filer.empty()) {
		cout << "Inga bokfiler tillgängliga." << endl;
		return;
	}

	// Skriv ut rubriker och total antal böcker
    cout << "\n------------------------------------------------------------------------------\n";
    cout << "Visar alla böcker från alla filer!" << endl;
	cout << "Totalt antal böcker: " << antalBocker<< endl;
	// Skriv rubriker för tabellen
    cout << setw(45) << left << "\nTitel" << setw(25) << left << "Författare" << "År\n";
    cout << "------------------------------------------------------------------------------\n";

    //Gå igenom alla filer i vektor filer
    for (int i = 0; i < filer.size(); i++) {
        BokLista& lista = filer[i];
        //loopa igenom alla böcker i filen
		for (int j = 0; j < lista.books.size(); j++) {
			cout << setw(45) << left << lista.books[j].getTitle()
				<< setw(25) << left << lista.books[j].getAuthor()
				<< lista.books[j].getYear() << endl;
		}
    }

  

}
 


int main() {
    setWesternEuropeanCodePage(); // För att hantera svenska tecken (å, ä, ö) i Windows-konsolen.
    vector<BokLista> filer; // Alla filer med sina böcker
    // Varje element i denna vector är en BokLista som innehåller böcker + data (filnamn, rapportör, datum).
    
    
	
    int val = 0; // Användarens menyval
    int antalFiler = 0; // Totalt antal bokfiler
    int antalBocker = 0; // totalt antal böcker
   

    do {
        // menyn
        cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "~~~~~  Bokhanteraren  ~~~~~~~" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << " Totalt antal bokfiler: " << antalFiler << endl;
        cout << " Totalt antal böcker: " << antalBocker << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "1. Lägg till bokfil" << endl;
        cout << "2. Visa en boklista" << endl;
        cout << "3. Visa alla böcker" << endl;
        cout << "4. Avsluta" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Ange ditt val: " << endl;

		cin >> val; // tar in inputen

        // Hantera valet
        switch (val) {
        case 1:
			laggTillBokfil(filer, antalFiler, antalBocker); // Lägg till en bokfil 
            break;
        case 2:
			visaEnBoklista(filer); // Visa en specifik boklista
            break;
        case 3:
            
			visaAllaBocker(filer, antalBocker); // Visa alla böcker från alla filer
			break;
        case 4:
            cout << "Programmet avslutas..." << endl;
            break;
        default:
            cout << "Felaktigt val! Försök igen." << endl;
        }

    } while (val != 4); // Upprepa tills användaren väljer 4

    return 0;


}
