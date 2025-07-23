#pragma once

using namespace std;
#include <string>

class Book {
private:
	// skapar privata variabler f�r bokens titel, f�rfattare och �rtal
	string title;
	string author;
	int year;
public:
	// Konstruktor f�r att initiera en bok med titel, f�rfattare och �rtal
	Book(string t, string a, int y);

	// Getter-funktioner f�r att h�mta bokens titel, f�rfattare och �rtal
	string getTitle() const;
	string getAuthor() const;
	int getYear() const;
};