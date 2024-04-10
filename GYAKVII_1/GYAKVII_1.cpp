#include <string>
#include <fstream>
#include <ctime>
#include <iostream>
#include <iomanip>

using namespace std;

struct dolgozo
{
	string nev;
	int fizetes;
	int szuletesi_ev;
	int ledolgozott_orak;
};

int beolvasdb(char *t);
void beolvas(dolgozo* dolgozok, int db, char* t);
void kiiratas(dolgozo* dolgozok, int db);
int ledolgozott_orak(dolgozo* dolgozok, int db);
void legoregebb(dolgozo* dolgozok, int db);
int szaznaltobb(dolgozo* dolgozok, int db);
void rendez_mentes(dolgozo* dolgozok, int db);

int main()
{
	const int maxchar = 80;
	char t[maxchar] = "majus.txt";
	srand((unsigned)time(NULL));
	int db =  beolvasdb(t);
	cout << "A dolgozok szama:" << db << endl;
	dolgozo* dolgozok = new dolgozo[db];
	beolvas(dolgozok, db, t);
	system("cls");
	kiiratas(dolgozok, db);
	cout << "A dolgozok osszesen " << ledolgozott_orak(dolgozok, db) << " orat dolgoztak." << endl;
	legoregebb(dolgozok, db);
	cout << "A 100 orat ledolgozott dolgozok szama majusban: " << szaznaltobb(dolgozok, db) << endl;
	rendez_mentes(dolgozok, db);
	delete[] dolgozok;
	system("pause");
	return 0;
}

int beolvasdb(char* t) {
	int db = 0;
	string name;
	fstream file(t);
	if (!file.is_open()) {
		cerr << "Nem sikerult megnyitni a fajlt!" << endl;
		return -1;
	}
	else {
		while (!file.eof())
		{
			file >> name;
			db++;
		}
	}
	file.close();
	return db;
}

void beolvas(dolgozo* dolgozok, int db, char* t) {
	fstream file(t);
	if (!file.is_open()) {
		cerr << "Nem sikerult megnyitni a fajlt!" << endl;
	}
	else {
		for (int i = 0; i < db; i++)
		{
			file >> dolgozok[i].nev;

			do {
				cout << "Adja meg a "<< dolgozok[i].nev <<" dolgozo szuletesi evet! ";
				cin >> dolgozok[i].szuletesi_ev;
				if (dolgozok[i].szuletesi_ev < 1957 || dolgozok[i].szuletesi_ev > 2004) {
					cout << "Hibas szuletesi ev! Adja meg ujra!" << endl;
				}
			
			} while (dolgozok[i].szuletesi_ev < 1957 || dolgozok[i].szuletesi_ev > 2004);
			
			dolgozok[i].ledolgozott_orak = rand() % 160 + 1;
			dolgozok[i].fizetes = dolgozok[i].ledolgozott_orak*2800;

			
		}
	}
	file.close();
}

void kiiratas(dolgozo* dolgozok, int db) {
	for (int i = 0; i < db; i++)
	{
		cout << setw(5) << dolgozok[i].nev << " " << dolgozok[i].szuletesi_ev << " " << dolgozok[i].ledolgozott_orak << " " << dolgozok[i].fizetes << endl;
	}
}

int ledolgozott_orak(dolgozo* dolgozok, int db) {
	int osszeg = 0;
	for (int i = 0; i < db; i++)
	{
		osszeg += dolgozok[i].ledolgozott_orak;
	}
	return osszeg;
}

void legoregebb(dolgozo* dolgozok, int db) {
	int max = dolgozok[0].szuletesi_ev;
	int index = 0;
	for (int i = 0; i < db; i++)
	{
		if (dolgozok[i].szuletesi_ev > max) {
			max = dolgozok[i].szuletesi_ev;
			index = i;
		}
	}
	cout << "A legoregebb dolgozo: " << dolgozok[index].nev << endl;
}

int szaznaltobb(dolgozo* dolgozok, int db) {
	int db2 = 0;
	for (int i = 0; i < db; i++)
	{
		if (dolgozok[i].ledolgozott_orak > 100) {
			db2++;
		}
	}
	return db2;
}

void rendez_mentes(dolgozo* dolgozok, int db) {
	dolgozo temp;
	for (int i = 0; i < db - 1; i++)
	{
		for (int j = i + 1; j < db; j++)
		{
			if (dolgozok[i].nev < dolgozok[j].nev) {
				temp = dolgozok[i];
				dolgozok[i] = dolgozok[j];
				dolgozok[j] = temp;
			}
		}
	}
	fstream file("majus_teljes.txt", ios::out);
	if (!file.is_open()) {
		cerr << "Nem sikerult megnyitni a fajlt!" << endl;
	}
	else {
		for (int i = 0; i < db; i++)
		{
			file << dolgozok[i].nev 
				<< " " << dolgozok[i].szuletesi_ev
				<< " " << dolgozok[i].ledolgozott_orak 
				<< " " << dolgozok[i].fizetes << endl;
		}
	}
	file.close();
}