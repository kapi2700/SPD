// SPD5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "RandomNumberGenerator.h"

using namespace std;

/*************************
* struktury
*************************/

struct instancja
{
    int n = 0;
    int m = 0;
    int seed = 0;
    int size = 0;
    vector<vector<int>> p;
    vector<vector<int>> u;
    vector<int> o;
};

struct permutacja
{
    vector<int> pi;
    vector<vector<int>> C;
    int cmax;
};

/*************************
* zmienne globalne
*************************/
instancja inst;
permutacja nat, INSA;


/*************************
* funkcje
*************************/


void swap(int& a, int& b)
{
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
}

void generuj()
{
    RandomNumberGenerator generator(inst.seed);
    vector<int> pom;        //zmienna wykorzystywana przy pushback, do instancji
    int x = floor(inst.m * 1.2);

    for (int i = 0; i < inst.n; i++)
    {
        inst.o.push_back(generator.nextInt(1, x));
        for (int j = 0; j < inst.o[i]; j++)
        {
            pom.push_back(generator.nextInt(1, 29));
        }
        inst.p.push_back(pom);
        pom.clear();
    }
    for (int i = 0; i < inst.n; i++)
    {
        for (int j = 0; j < inst.o[i]; j++)
        {
            pom.push_back(generator.nextInt(1, inst.m));
        }
        inst.u.push_back(pom);
        pom.clear();
    }
    inst.size = 0;
    for (int i = 0; i < inst.o.size(); i++)
    {
        inst.size += inst.o[i];
    }
}

void wyswietl()
{
    int* zad = new int[inst.size];
    int* miejsce = new int[inst.size];
    int k = 0;

    for (int i = 0; i < inst.n; i++)
    {
        for (int j = 0; j < inst.o[i]; j++)
        {
            zad[k] = i;
            miejsce[k] = j;
            k++;
        }
    }


    //Instancja
    cout << "p: [";
    for (int i = 0; i < inst.n; i++)
    {
        cout << "[";
        for (int j = 0; j < inst.p[i].size(); j++)
        {
            cout << inst.p[i][j];
            if (j == inst.p[i].size() - 1)
            {
                cout << "]";
            }
            else
            {
                cout << ", ";
            }
        }
        if (i == inst.n - 1)
        {
            cout << "]";
        }
        else
        {
            cout << ", ";
        }
    }
    cout << endl;

    cout << "u: [";
    for (int i = 0; i < inst.n; i++)
    {
        cout << "[";
        for (int j = 0; j < inst.u[i].size(); j++)
        {
            cout << inst.u[i][j];
            if (j == inst.u[i].size() - 1)
            {
                cout << "]";
            }
            else
            {
                cout << ", ";
            }
        }
        if (i == inst.n - 1)
        {
            cout << "]";
        }
        else
        {
            cout << ", ";
        }
    }
    cout << endl;

    //Permutacja naturalna
    cout << "permutacja naturalna" << endl;
    cout << "pi: [";
    for (int i = 0; i < inst.size; i++)
    {
        cout << (nat.pi[i] + 1);
        if (i == inst.size - 1)
        {
            cout << "]";
        }
        else
        {
            cout << ", ";
        }
    }
    cout << endl;

    cout << "C: [";
    for (int i = 0; i < inst.n; i++)
    {
        cout << "[";
        for (int j = 0; j < nat.C[i].size(); j++)
        {
            cout << nat.C[i][j];
            if (j == nat.C[i].size() - 1)
            {
                cout << "]";
            }
            else
            {
                cout << ", ";
            }
        }
        if (i == inst.n - 1)
        {
            cout << "]";
        }
        else
        {
            cout << ", ";
        }
    }
    cout << endl;
    cout << "Cmax: " << nat.cmax;
    cout << endl;

    //Algorytm INSA
    cout << "Algorytm INSA" << endl;
    cout << "pi: [";
    for (int i = 0; i < inst.size; i++)
    {
        cout << (INSA.pi[i] + 1);
        if (i == inst.size - 1)
        {
            cout << "]";
        }
        else
        {
            cout << ", ";
        }
    }
    cout << endl;

    cout << "C: [";
    for (int i = 0; i < inst.size; i++)
    {
        cout << (INSA.C[zad[INSA.pi[i]]][miejsce[INSA.pi[i]]]);
        if (i == inst.size - 1)
        {
            cout << "]";
        }
        else
        {
            cout << ", ";
        }
    }
    cout << endl;
    cout << "Inny sposob wyswietlenia C\n";
    cout << "C: [";
    for (int i = 0; i < inst.n; i++)
    {
        cout << "[";
        for (int j = 0; j < INSA.C[i].size(); j++)
        {
            cout << INSA.C[i][j];
            if (j == INSA.C[i].size() - 1)
            {
                cout << "]";
            }
            else
            {
                cout << ", ";
            }
        }
        if (i == inst.n - 1)
        {
            cout << "]";
        }
        else
        {
            cout << ", ";
        }
    }
    cout << endl;
    cout << "Cmax: " << INSA.cmax;
    cout << endl;
}

int wylicz(permutacja& perm)
{
    int* zad = new int[inst.size];
    int* miejsce = new int[inst.size];
    int* maszyny = new int[inst.m];
    int n = 0;
    int akt_zad = 0;
    int akt_miejsce = 0;
    int max=0;
    
    int debug = inst.m;

    vector<int> pom;

    for (int i = 0; i < inst.m; i++)
    {
        maszyny[i] = 0;
    }

    for (int i = 0; i < inst.size; i++)
    {
        zad[i] = 0;
        miejsce[i] = 0;
    }

    for (int i = 0; i < inst.n; i++)
    {
        for (int j = 0; j < inst.o[i]; j++)
        {
            zad[n] = i;
            miejsce[n] = j;
            n++;

            pom.push_back(0);
        }
        perm.C.push_back(pom);
        pom.clear();
    }



    for (int i = 0; i < perm.pi.size(); i++)
    {
        akt_miejsce = miejsce[perm.pi[i]];
        akt_zad = zad[perm.pi[i]];
        if (i == 0)
        {
            perm.C[akt_zad][akt_miejsce]=(inst.p[akt_zad][akt_miejsce]);
            maszyny[inst.u[akt_zad][akt_miejsce] - 1] += inst.p[akt_zad][akt_miejsce];
        }
        else
        {
            if (akt_miejsce == 0)
            {
                maszyny[inst.u[akt_zad][akt_miejsce] - 1] += inst.p[akt_zad][akt_miejsce];
                perm.C[akt_zad][akt_miejsce] = maszyny[inst.u[akt_zad][akt_miejsce] - 1];
            }
            else
            {
                if (maszyny[inst.u[akt_zad][akt_miejsce] - 1] > perm.C[akt_zad][akt_miejsce - 1])
                {
                    maszyny[inst.u[akt_zad][akt_miejsce] - 1] += inst.p[akt_zad][akt_miejsce];
                    perm.C[akt_zad][akt_miejsce] = maszyny[inst.u[akt_zad][akt_miejsce] - 1];
                }
                else
                {
                    perm.C[akt_zad][akt_miejsce] = perm.C[akt_zad][akt_miejsce - 1] + inst.p[akt_zad][akt_miejsce];
                    maszyny[inst.u[akt_zad][akt_miejsce] - 1] = perm.C[akt_zad][akt_miejsce];
                }
            }
        }
        if (max < perm.C[akt_zad][akt_miejsce])
        {
            max = perm.C[akt_zad][akt_miejsce];
        }
       
    }
    perm.cmax = max;

    return perm.cmax;
}

void natural_alg()
{
    for (int i = 0; i < inst.size; i++)
    {
        nat.pi.push_back(i);
    }
    wylicz(nat);
}

void INSA_alg()
{
    vector<int> a;
    permutacja sprawdzana1, sprawdzana2;
    int  k = 0;
    int* zad = new int[inst.size];
    int* miejsce = new int[inst.size];
    int* maszyna = new int[inst.size];
    vector<int> w;
    vector<int> ktory;
    vector<int> pom;
    vector<vector<int>> pi2;
    int max = -1;
    int akt_zad = 0;
    int akt_miejsce = 0;
    int teraz = 0;
    int wczesniej = 0;


    for (int i = 0; i < inst.m; i++)
    {
        maszyna[i] = 0;
        zad[i] = 0;
        miejsce[i] = 0;
    }

    for (int i = 0; i < inst.n; i++)
    {
        for (int j = 0; j < inst.o[i]; j++)
        {
            zad[k] = i;
            miejsce[k] = j;
            maszyna[k] = inst.u[i][j];
            pom.push_back(k);
            k++;
        }
        pi2.push_back(pom);
        pom.clear();
    }




    for (int i = 0; i < inst.n; i++)
    {
        w.push_back(0);
        ktory.push_back(i);
        for (int l = 0; l < inst.o[i]; l++)
        {
            w[i] += inst.p[i][l];
        }
    }

    for (int i = 0; i < inst.n - 1; i++)
    {
        for (int j = 0; j < inst.n - i - 1; j++)
        {
            if (w[j] > w[j + 1])
            {
                swap(w[j], w[j + 1]);
                swap(ktory[j], ktory[j + 1]);
            }
        }
    }


    k = 1;
    while (!ktory.empty())
    {
        akt_zad = ktory.back();
        ktory.pop_back();

        wczesniej = -1;
        for (int j = 0; j < inst.o[akt_zad]; j++)
        {
            akt_miejsce = j;

            a.push_back(pi2[akt_zad][akt_miejsce]);
            teraz = a.size() - 1;
            for (int l = wczesniej + 1; l < a.size() - 1; l++) //sprawdzamy od miejsca jeden za ustalon¹ pozycj¹ poprzedniej operacji, z tego samego zadania
            {
                sprawdzana1.pi = a;
                sprawdzana2.pi = a;
                if (maszyna[l] == maszyna[teraz])
                {
                    sprawdzana1.pi.erase(sprawdzana1.pi.begin() + teraz);
                    sprawdzana1.pi.insert(sprawdzana1.pi.begin() + l, pi2[akt_zad][akt_miejsce]);
                    if (wylicz(sprawdzana1) < wylicz(sprawdzana2))
                    {
                        a = sprawdzana1.pi;
                        teraz = l;
                    }
                }
            }
            wczesniej = teraz;
            k++;
        }
    }


    INSA.pi = a;
    wylicz(INSA);
}

/*************************
* main
*************************/

int main()
{
    char buff;
    cout << "seed: ";
    cin >> inst.seed;
    cout << "rozmair: ";
    cin >> inst.n;
    cin >> buff;
    cin >> inst.m;

    generuj();
    natural_alg();
    INSA_alg();
    wyswietl();
}
