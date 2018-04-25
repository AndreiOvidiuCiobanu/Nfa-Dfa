#include<iostream>
#include<fstream>
#include <vector>
#include <list>
#include <utility>
#include<cstring>
#include <string>
#include<queue>

using namespace std;

int main()
{
	ifstream fin("fisier.in");
	unsigned int n;
	cout << "Cate stari sunt?";
	cout << endl;
	fin >> n; //citirea numarului de stari
	cout << "n=" << n;
	int i, j, flag = 0, k = 0, nr = 0, contor = 0;
	char c, x, y;
	cout << endl;
	cout<<"Care este starea initiala?"<<endl;
	fin>>c;
	cout<<"Cate drumuri sunt?"<<endl;
	cout<<c<<endl;
	cout << "Cate stari finale sunt?" << endl;
	fin>>k;
	vector<int> drum;

	for(int i=0;i<k;i++)
    {
     fin>>nr;
     drum.push_back(nr);
    }
	fin >> n; //citirea numarului de stari finale
	vector <int> final; //vectorul in care se vor stoca starile finale

	for (i = 0; i < n; i++)
	{
		cout << "O stare finala este" << endl;
		fin >> x;
		final.push_back(x); //adaugarea in vector a starilor finale
		nr++;
	}
	cout << endl;
	cout << "Cate perechi sunt" << endl;
	fin >> n; //citirea numarului de limbaje

	struct NFA
	{
		char exi;
		char exf;
		char drum;
	}; //unde voi stoca informatiile

	contor = n; //copierea informatiilor referitoare la nr de stari finale
	struct NFA v[101];
	char t;

	for (i = 0; i < n; i++)
	{
        fin >>v[i].exi;
        cout<<v[i].exi<<" ";
        fin>>v[i].drum;
        cout<<v[i].drum<<" ";
        fin>>t;
        v[i].exf=t;
        cout<<v[i].exf<<endl;
	}
	for (i = 0; i < n; i++)
	{
		cout << "Starile sunt:" << endl;
		cout << v[i].exi <<" "<< v[i].drum<<" "<<v[i].exf<<" "<<endl;
	}
	for( i=0;i<n-1;i++)
		for( j=i+1;j<n;j++)
			if (v[i].exi > v[j].exi)
			{
				struct NFA aux;
				aux = v[i];
				v[i] = v[j];
				v[j] = aux; //sa am toate drumurile care pleaca din acelasi nod consecutive
			}
	for (i = 0; i < n; i++)
	{
		cout << "Starile sunt:" << endl;
		cout << v[i].exi <<" "<< v[i].exf<<" "<< v[i].drum << endl; //citirea starilor
	}
	cout << endl;
	fin.close();
    string a[101][k+1];
    a[0][0]=c;

	struct DFA
	{
		string exi;
		string exf;
		string drum;
	};
	DFA w[101];
    //cout<<k+1<<endl;
    cout<<n<<endl;
    queue<string>myqueue;
    myqueue.push(a);
    int ap[33]={0};
    for(int i=0;i<n;i++)
        if(v[i].exi==c)
          {
              int y=v[i].drum;
              y++;
			  char q = v[i].exf;
			  a[0][y - '0'] += v[i].exf;

           }
    int dim=1;
    for(int i=0;i<k;i++)
        a[i+1][0]=a[0][i+1];

    for(int i=0;i<3;i++)
        for(j=0;j<k+1;j++)
            cout<<a[i][j]<<" ";

    dim=k+1;
    nr=1;
    int fg=k;
    for(j=nr;j<dim;j++)
        {
        for(i=0;i<n;i++)
            for(k=0;k<a[j][0].size();k++)
            { c=a[j][0][k];
                if(v[i].exi==c)
                {
                    flag=0;
                    int y=v[i].drum;
                    y++;
                    char q=v[i].exf;
                    for(int u=0;u<a[j][y-'0'].size();u++)
                        if(a[j][y-'0'][u]==q)
                            flag++;
                    if(flag==0)
                        a[j][y-'0']+=q;
                }
            }
            nr++;
            for(int f=dim;f<dim+fg;f++)
                for(int b=1;b<fg+1;b++)
            {
                a[f][0]=a[j][b];}
            dim=dim+fg;
        }
        cout<<"@@@@"<<endl;
    for(int i=0;i<dim;i++)
    {
        for(int j=0;j<3;j++)
            cout<<a[i][j]<<" ";
        cout<<endl;}

return 0;
}
