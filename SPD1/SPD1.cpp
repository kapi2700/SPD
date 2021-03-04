// SPD1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "RandomNumberGenerator.h"

using namespace std;


int main()
{
    RandomNumberGenerator generator(1);
    int seed, n, czas=0;
    int p[1000], r[1000], S[1000], C[1000];
    int suma = 0;
    int temp;
    int pi[1000];

    while (1)
    {
        suma = 0;
        czas = 0;
        cout << "Wprowadz zrodlo losowania: ";
        cin >> seed;
        cout << "Wprowadz rozmiar problemu: ";
        cin >> n;

        generator = seed;

        cout << "n: " << n << endl << endl;
        for (int i = 0; i < n; i++)
        {
            p[i] = generator.nextInt(1, 29);
            suma += p[i];
            pi[i] = i + 1;
        }
        for (int i = 0; i < n; i++)
        {
            r[i] = generator.nextInt(1, suma);
        }


        cout << "nr: [";
        for (int i = 1; i <= n; i++) {
            cout << i;
            if (i != n)
                cout << ",";
        }
        cout << "]\n";


        cout << "r: [";
        for (int i = 1; i <= n; i++) {
            cout << r[i - 1];
            if (i != n)
                cout << ",";
        }
        cout << "]\n";

        cout << "p: [";
        for (int i = 1; i <= n; i++) {
            cout << p[i - 1];
            if (i != n)
                cout << ",";
        }
        cout << "]\n";

        cout << endl;


        for (int i = 0; i < n; i++)
        {
            if (i == 0)
                S[i] = r[i];
            else
            {
                if (r[i] < C[i - 1])
                {
                    S[i] = C[i - 1];
                }
                else
                {
                    S[i] = r[i];
                }
            }
            C[i] = S[i] + p[i];
        }




        cout << "pi: [";
        for (int i = 1; i <= n; i++) {
            cout << pi[i - 1];
            if (i != n)
                cout << ",";
        }
        cout << "]\n";

        cout << "C: [";
        for (int i = 1; i <= n; i++) {
            cout << C[i - 1];
            if (i != n)
                cout << ",";
        }
        cout << "]\n";

        cout << endl;




        for (int i = 0; i < n; i++)
            for (int j = 1; j < n - i; j++) 
                if (r[j - 1] > r[j])
                {
                    temp = r[j - 1];
                    r[j - 1] = r[j];
                    r[j] = temp;

                    temp = p[j - 1];
                    p[j - 1] = p[j];
                    p[j] = temp;

                    temp = pi[j - 1];
                    pi[j - 1] = pi[j];
                    pi[j] = temp;
                }



        for (int i = 0; i < n; i++)
        {
            if (i == 0)
                S[i] = r[i];
            else
            {
                if (r[i] < C[i - 1])
                {
                    S[i] = C[i - 1];
                }
                else
                {
                    S[i] = r[i];
                }
            }
            C[i] = S[i] + p[i];
        }




        cout << "pi: [";
        for (int i = 1; i <= n; i++) {
            cout << pi[i-1];
            if (i != n)
                cout << ",";
        }
        cout << "]\n";

        cout << "C: [";
        for (int i = 1; i <= n; i++) {
            cout << C[i - 1];
            if (i != n)
                cout << ",";
        }
        cout << "]\n";

        cout << endl;
    }
}