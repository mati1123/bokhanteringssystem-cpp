#include "Book.h"

Book::Book(string t, string a, int y)
	{
	title = t; // V�rdet vi kommer d� skicka in f�r titel
	author = a; // v�rder vi skickar in f�r f�rfattare
	year = y; // v�rdet vi skickar in f�r �rtal
}



//Dessa returnerar v�rdena fr�n de privata variablerna.
string Book::getTitle() const
{
	return title;
}

string Book::getAuthor() const
{
	return author;
}

int Book::getYear() const
{
	return year;
}
