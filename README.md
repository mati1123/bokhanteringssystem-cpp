📚 Bokhanteringssystem (C++)
🔍 Översikt
Detta är ett konsolbaserat bokhanteringssystem skrivet i C++.
Programmet låter dig läsa in boklistor från textfiler, visa böcker från en specifik fil eller visa alla böcker.
Projektet demonstrerar:

Klasser och objekt (OOP)

Filhantering (ifstream, stringstream)

Dynamiska datastrukturer med vector

Strukturering av kod med header- och cpp-filer

✅ Funktioner
Lägg till bokfiler och lagra dem i minnet

Visa böcker från en vald fil

Visa alla böcker från alla filer

Räknar totalt antal filer och böcker


📂 Projektstruktur
BookDatabase/
├── Bookdatabase.cpp   # Huvudprogram med meny och logik
├── Book.h             # Headerfil för Book-klassen
├── Book.cpp           # Implementation av Book-klassen
├── b1.txt             # Exempelfil
├── b2.txt
├── b3.txt
└── b4.txt


📜 Filformat
Första raden i filen innehåller rapportör och datum:
Rapportör;Datum
Efterföljande rader innehåller:
Titel;Författare;År

Exempel:
Anna;2023-05-01
Harry Potter;J.K. Rowling;1997
Sagan om Ringen;J.R.R. Tolkien;1954

🖥 Meny
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~  Bokhanteraren  ~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Totalt antal bokfiler: 0
 Totalt antal böcker: 0
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
1. Lägg till bokfil
2. Visa en boklista
3. Visa alla böcker
4. Avsluta
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Ange ditt val:

 
 
📌 Vad du lär dig
Strukturera ett C++-projekt med header- och implementeringsfiler

Skapa och använda klasser, structar och referenser (&) för att organisera och uppdatera data

Använda vector för dynamisk datalagring

Filinläsning med ifstream och stringstream

Skapa menybaserade konsolprogram




