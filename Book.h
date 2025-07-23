#pragma once

using namespace std;
#include <string>

class Book {
private:
	// skapar privata variabler för bokens titel, författare och årtal
	string title;
	string author;
	int year;
public:
	// Konstruktor för att initiera en bok med titel, författare och årtal
	Book(string t, string a, int y);

	// Getter-funktioner för att hämta bokens titel, författare och årtal
	string getTitle() const;
	string getAuthor() const;
	int getYear() const;
};