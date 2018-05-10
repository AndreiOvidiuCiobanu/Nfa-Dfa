#include<iostream>
#include<fstream>
#include <vector>
#include <list>
#include <utility>
#include<cstring>
#include <string>
#include<queue>
using namespace std;

void setcolor(unsigned short color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}

int main()
{
	ifstream fin("fisier.in");
	unsigned int nrstari;
	fin >> nrstari; ///citirea numarului de stari
	int i, j, flag = 0, k = 0, nr = 0, contor = 0,nrstarifinale,nrlimbaje;
	char c, x, y;
	fin >> c; ///starea initiala
	fin >> k; ///nr de drumuri
	
	vector<int> drum;
	for (int i = 0; i<k; i++)
	{
		fin >> nr;
		drum.push_back(nr);
	}

	fin >> nrstarifinale; ///citirea numarului de stari finale
	

	vector <char> final; ///vectorul in care se vor stoca starile finale
	vector <char>::iterator iterat;

	for (i = 0; i < nrstarifinale; i++)
	{
		fin >> x;
		final.push_back(x); ///adaugarea in vector a starilor finale
		nr++;

	}

	fin >> nrlimbaje; ///citirea numarului de limbaje


	struct NFA
	{
		char exi;
		char exf;
		char drum;
	}; ///unde voi stoca informatiile

	contor = nrstarifinale; ///copierea informatiilor referitoare la nr de stari finale

	struct NFA v[101];
	char t;


	for (i = 0; i < nrlimbaje; i++)
	{
		fin >> v[i].exi;
		
		fin >> v[i].drum;
		
		fin >> t;
		v[i].exf = t;

	}///citire NFA

	
	for (i = 0; i<nrlimbaje - 1; i++)
		for (j = i + 1; j<nrlimbaje; j++)
			if (v[i].exi > v[j].exi)
			{
				struct NFA aux;
				aux = v[i];
				v[i] = v[j];
				v[j] = aux; ///sa am toate drumurile care pleaca din acelasi nod consecutive
			}

	fin.close();
	string a[101][101];
	a[0][0] = c;
	

	struct DFA
	{
		string exi;
		string exf;
		string drum;
	};
	DFA w[101];
	
	vector<string>myvector;
	vector<string>::iterator it;
	myvector.push_back(a[0][0]);

	int ap[33] = { 0 }; 
	for (int i = 0; i<nrlimbaje; i++)
		if (v[i].exi == c)
		{
			int y = v[i].drum;
			y++;
			char q = v[i].exf;
			a[0][y - '0'] += v[i].exf; ///pentru a[0][0](starea initiala) verific in ce noduri se duce cu toate drumurile

		}
	int dim = 1;
	for (int i = 0; i < k; i++)
	{
		a[i + 1][0] = a[0][i + 1];
		myvector.push_back(a[0][i+1]); ///in vectorul de "vizitari" adaug noile stari in care merge stare intiala
	}


	int nrdrumuri = k + 1;

	dim = k + 1; ///nrdrumuri
	nr = 2;
	int m = k + 1;
	int fg = k;
	int inceput=1;
	
	for (j =inceput ; j<101; j++)
	{

		for (i = 0; i<nrlimbaje; i++)
			for (k = 0; k<a[j][0].size(); k++)
			{
				c = a[j][0][k]; ///iau litera cu litera a starilor noi 

				if (v[i].exi == c) ///verific ce drumuri exista din acea stare 
				{
					int y = v[i].drum;
					y++;
					char q = v[i].exf;
		
					if (a[j][y - '0'].find(q) > a[j][y - '0'].size()|| a[j][y - '0'].find(q)<0)
						a[j][y-'0'] += q; ///daca starea finala nu apartine noilor stari, adaug
				}

			}

			for (int r = 1; r <nrdrumuri; r++)
			{
				flag = 0;
				for (it = myvector.begin(); it != myvector.end(); it++)
					if ((a[j][r].compare(*it))==0)
						flag++;

				if (flag == 0)
				{
					a[dim][0] = a[j][r]; ///adaug norile stari in care se ajunge din nodul curent 
					dim++;
				}

			}
		
		int ri;
		for (ri = 0; ri < nrdrumuri; ri++)
		{

			flag = 0;
			for (it = myvector.begin(); it != myvector.end(); it++)
			{
				if (a[j][ri].compare(*it) == 0)
					flag++;
				
			}
			if (flag == 0)
				myvector.push_back(a[j][ri]);
		}
		inceput++;
	}
	 setcolor(10); cout<< "NFA transformat in DFA:" << endl;
	string vid;

	for (int i = 0; i<dim; i++)
	{
		for (int j = 0; j < nrdrumuri; j++)
			if (j == 0)
				if (a[i][j].compare(vid) != 0)
					cout << "Sigma=" << a[i][j] << " ;";
				else
					cout << "Sigma= * ;"; 
			else
				if (a[i][j].compare(vid) != 0)
					cout << "Cu drumul " << j << " in " << a[i][j] << " ;";
				else
					cout << "Cu drumul " << j << " in *; ";
		cout << endl;
	}

	cout << "SFARSIT" << endl;
	cout << endl << endl << endl;
	
	setcolor(100);

	cout <<"Starea initiala este:" <<a[0][0] << endl<<endl<<endl<<endl;

	vector<string> afisari;
	vector <string>::iterator yi;
	
	setcolor(70);
		for (it = myvector.begin(); it != myvector.end(); it++)
		{
			flag = 0;
			for (iterat = final.begin(); iterat != final.end(); iterat++)
				if ((*it).find(*iterat) >= 0 && (*it).find(*iterat) <= (*it).size())
					flag++;
			if (flag != 0)
				cout << "Stare finala:" << *it << endl;
		}
	return 0;
}
