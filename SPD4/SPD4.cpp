// SPD4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "RandomNumberGenerator.h"
#include <vector>
#include <chrono>
#include <algorithm>


using namespace std;

/********************************* ZMIENNNE I STRUKTURY ***************************************/

struct zadanie
{
    int Pi;
    int S;
    int C;
    int T;
    int wT;
};


vector<int> p;
vector<int> w;
vector<int> d;
int n = 0, z = 0;



/********************************* FUNKCJE ***************************************/
int max(int a, int b)           //max pomiedzy dwoma liczbami
{
    if (a > b)
        return a;
    else
        return b;
}

int min(vector<int> a)          //min w vectorze int
{
    int min = INT_MAX;
    for (int i = 0; i < a.size(); i++)
    {
        if (min > a[i])
            min = a[i];
    }
    return min;
}

int minN(vector<int> a)          //min w vectorze int
{
    int min = INT_MAX;
    int n = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (min > a[i])
        {
            min = a[i];
            n = i;
        }
    }
    return n;
}





void generujInstancje()                              //Funkcja generuj¹ca instancjê
{
    RandomNumberGenerator gen(z);
    int a=0;
    int x = 29;


    for (int i = 0; i < n; i++)
    {
        p.push_back(gen.nextInt(1, 29));
        a += p[i];
        
    }

    //x = a;                  // Do zakomentowania w celu sprawdzenia innego zakresu
    for (int i = 0; i < n; i++)
        w.push_back(gen.nextInt(1, 9));

    for (int i = 0; i < n; i++)
        d.push_back(gen.nextInt(1, x));
}


void wyswietl()                                       //Funkcja wyœwietlaj¹ca wygenerowan¹ instancjê
{
    cout << "nr: [";
    for (int i = 1; i <= n; i++)
    {
        if (i != n)
            cout << i << ", ";
        else
            cout << i << "]" << endl;
    }

    cout << "p: [";
    for (int i = 0; i < n; i++)
    {
        if (i != n-1)
            cout << p[i] << ", ";
        else
            cout << p[i] << "]" << endl;
    }

    cout << "w: [";
    for (int i = 0; i < n; i++)
    {
        if (i != n-1)
            cout << w[i] << ", ";
        else
            cout << w[i] << "]" << endl;
    }

    cout << "d: [";
    for (int i = 0; i < n; i++)
    {
        if (i != n-1)
            cout << d[i] << ", ";
        else
            cout << d[i] << "]" << endl;
    }
}

void wylicz(vector<zadanie>& permutacja, int& sum)    //Funkcja pozwalaj¹ca na wyliczenie C, T, wT oraz sumy wT na podstawie danej permutacji
{
    int opoznienie;

    sum = 0;

    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            permutacja[i].S = 0;
            permutacja[i].C = p[permutacja[i].Pi - 1];
        }
        else
        {
            permutacja[i].S = permutacja[i - 1].C;
            permutacja[i].C = p[permutacja[i].Pi - 1] + permutacja[i].S;
        }

        opoznienie = permutacja[i].C - d[permutacja[i].Pi - 1];
        if (opoznienie > 0)
            permutacja[i].T = opoznienie;
        else
            permutacja[i].T = 0;

        permutacja[i].wT = permutacja[i].T * w[permutacja[i].Pi - 1];
        sum += permutacja[i].wT;
    }
}

void wyswietlRozw(vector<zadanie> permutacja, int suma)       //Funkcja wyœwietlaj¹ca rozwi¹zanie na podstawie wczesniej wyliczonej permutacji, za pomoc¹ funkcji "wylicz"
{
    cout << "pi: [";
    for (int i = 0; i < n; i++)
    {
        if (i != n-1)
            cout << permutacja[i].Pi << ", ";
        else
            cout << permutacja[i].Pi << "]" << endl;
    }

    cout << "C: [";
    for (int i = 0; i < n; i++)
    {
        if (i != n - 1)
            cout << permutacja[i].C << ", ";
        else
            cout << permutacja[i].C << "]" << endl;
    }

    cout << "T: [";
    for (int i = 0; i < n; i++)
    {
        if (i != n - 1)
            cout << permutacja[i].T << ", ";
        else
            cout << permutacja[i].T << "]" << endl;
    }

    cout << "wT: [";
    for (int i = 0; i < n; i++)
    {
        if (i != n - 1)
            cout << permutacja[i].wT << ", ";
        else
            cout << permutacja[i].wT << "]" << endl;
    }
    cout << "wiTi sum: " << suma << endl;
}


void nat(vector<zadanie>& natural, int& suma)       //rozwi¹zanie z permutacj¹ naturaln¹, razem z wyœwietleniem
{
    zadanie pom;
    cout << "natural pi" << endl;
    for (int i = 0; i < n; i++)
    {
        pom.Pi = i + 1;
        natural.push_back(pom);
    }
    wylicz(natural, suma);
    wyswietlRozw(natural, suma);
}


void greed(vector<zadanie>& greedy, int& suma)      //rozwi¹zanie za pomoc¹ algorytmu zach³annego, razem z wyœwietleniem
{
    int min=99999;
    int k=0;
    zadanie pom;
    vector<int> deadline, nr;
    
    cout << "greedy" << endl;

    auto begin = chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++)  //zape³nienie danych do sortowania
    {
        deadline.push_back(d[i]);
        nr.push_back(i + 1);
    }


    for (int i = 0; i < n; i++)
    {
        min = 99999;
        k = 0;
        for (int j = 0; j < n-i; j++)
        {
            if (min > deadline[j])
            {
                min = deadline[j];
                k = j;
            }
            
        }
        deadline.erase(deadline.begin() + k);
        pom.Pi = nr[k];
        nr.erase(nr.begin() + k);
        greedy.push_back(pom);
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - begin;

    wylicz(greedy, suma);
    wyswietlRozw(greedy, suma);
    cout << "czas dzialania: " << elapsed.count() << " s" << endl;
}


void bruteForce(vector<zadanie>& brute, int& suma)      //rozwi¹zanie za pomoc¹ algorytmu brute force, razem z wyœwietleniem
{
    zadanie pom;
    int* sprPi = new int[n];
    vector<zadanie> testowe;
    int sumTest;
    int min=9999999;
    cout << "brute force" << endl;

    auto begin = chrono::high_resolution_clock::now();


    for (int i = 0; i < n; i++)
    {
        sprPi[i] = i+1;
    }


    do {
        for (int i = 0; i < n; i++)
        {
            pom.Pi = sprPi[i];
            testowe.push_back(pom);
        }
        wylicz(testowe, sumTest);
        if (sumTest < min)
        {
            min = sumTest;
            suma = min;
            brute = testowe;
        }
        testowe.clear();
    } while (next_permutation(sprPi, sprPi + n));

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - begin;

    //wylicz(brute, suma); pomijamy, poniewaz zostalo juz obliczone podczas wykonywania algorytmu
    wyswietlRozw(brute, suma);
    cout << "czas dzialania: " << elapsed.count() << " s" << endl;

    delete[] sprPi;
}



void dynamicProgramming(vector<zadanie>& dynamic, int& suma)        //rozwi¹zanie za pomoc¹ programowania dynamicznego, razem z wyœwietleniem
{
    zadanie pom;
    int wielkosc=pow(2,n);
    int* mem = new  int[wielkosc];
    int sum=0;
    int temp;
    int y, z; //wykorzystywane podczas znajdowania najlepszej kolejnosci, po algorytmie
    int* pi2 = new int[n];
    vector<int> x, kol;

    cout << "dynamic programing" << endl;

    auto begin = chrono::high_resolution_clock::now();



    for (int i = 0; i < wielkosc; i++)
        mem[i] = -1;
    
    mem[0] = 0;
    for (int i = 1; i < wielkosc; i++)
    {
        sum = 0;
        x.clear();

        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j))
            {
                sum += p[j];
            }
        }

        for (int j = 0; (j < n); j++)
        {
            if (i & (1 << j))
            {
                temp = ((max(sum - d[j], 0) * w[j]) + mem[(i ^ (1 << j))]);
                x.push_back(temp);
            }
        }
        mem[i] = min(x);
    }                       //zakoñczenie znajdowania sumy wiTi
    
    //auto end = chrono::high_resolution_clock::now();          //do odkomentowania, jeœli chcemy obliczyæ czas wyznaczania samej sumy
        

    y = minN(x);            //szukanie kolejnoœci najlepszego rozwi¹zania
    pi2[0] = y + 1;
    z = ((wielkosc - 1) ^ (1 << y));        //usuniêcie pierwszej (ostatniej) liczby

    for (int k = 1; k < n; k++)
    {
        sum = 0;
        x.clear();
        kol.clear();

        for (int j = 0; j < n; j++)
        {
            if (z & (1 << j))
            {
                sum += p[j];
            }
        }

        for (int j = 0; (j < n); j++)
        {
            if (z & (1 << j))
            {
                temp = ((max(sum - d[j], 0) * w[j]) + mem[(z ^ (1 << j))]);
                x.push_back(temp);
                kol.push_back(j);
            }
        }
        y = minN(x);
        pi2[k] = kol[y] + 1;
        z = (z ^ (1 << kol[y]));            //usuwanie kolejnych liczb
    }
    
    for (int i = n - 1; i >= 0; i--)    //odwracanie kolejnoœci
    {
        pom.Pi = pi2[i];
        dynamic.push_back(pom);
    }
    auto end = chrono::high_resolution_clock::now();            //do zakomentowania, jeœli chcemy obliczyæ czas wyznaczania samej sumy
    chrono::duration<double> elapsed = end - begin;     

    wylicz(dynamic, suma);
    wyswietlRozw(dynamic, suma);
    cout << "czas dzialania: " << elapsed.count() << " s" << endl;

    delete[] mem;
}




/********************************* MAIN *************************************/

int main()
{
    vector<zadanie> natural, greedy, brute, dynamic;
    int sumN = 0, sumG = 0, sumB = 0, sumD = 0;

    

    cout << "Wprowadz zrodlo losowania: ";
    cin >> z;
    cout << "Wprowadz rozmiar problemu: ";
    cin >> n;
    cout << "n: ";
    cout << n;
    cout << endl << endl;

    generujInstancje();
    wyswietl();
    nat(natural, sumN);
    greed(greedy, sumG);
    bruteForce(brute, sumB);
    dynamicProgramming(dynamic, sumD);
}