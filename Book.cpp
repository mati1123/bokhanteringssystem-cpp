#include "Book.h"

Book::Book(string t, string a, int y)
	{
	title = t; // Värdet vi kommer då skicka in för titel
	author = a; // värder vi skickar in för författare
	year = y; // värdet vi skickar in för årtal
}



//Dessa returnerar värdena från de privata variablerna.
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
