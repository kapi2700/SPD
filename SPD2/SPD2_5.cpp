#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#include <limits>
#include "RandomNumberGenerator.h"

using namespace std;

int seed, n, C_max;

/**************************** STRUKTURY *******************************/

struct Zadanie {
    int pi, p, r, q, S, C, Cq;
};

struct Porownaj_r
{
    bool operator ()(const Zadanie& z1, const Zadanie& z2)
    {
        //rosnąco
        if (z1.r > z2.r) return true;
        else return false;
    }
};

struct Porownaj_q
{
    bool operator ()(const Zadanie& z1, const Zadanie& z2)
    {
        //malejaco
        if (z1.q < z2.q) return true;
        else return false;
    }
};


/************************************ FUNKCJE ***********************************/


void Wyswietl1(vector<Zadanie> J) {
    cout << "nr: [";
    for (int i = 1; i <= J.size(); i++) {
        cout << J[i - 1].pi;
        if (i != J.size())
            cout << ",";
    }
    cout << "]\n";

    cout << "r: [";
    for (int i = 1; i <= J.size(); i++) {
        cout << J[i - 1].r;
        if (i != J.size())
            cout << ",";
    }
    cout << "]\n";

    cout << "p: [";
    for (int i = 1; i <= J.size(); i++) {
        cout << J[i - 1].p;
        if (i != J.size())
            cout << ",";
    }
    cout << "]\n";

    cout << "q: [";
    for (int i = 1; i <= J.size(); i++) {
        cout << J[i - 1].q;
        if (i != J.size())
            cout << ",";
    }
    cout << "]\n";

    cout << endl;
}

void Wyswietl2(vector<Zadanie> J) {
    cout << "pi: [";
    for (int i = 1; i <= J.size(); i++) {
        cout << J[i - 1].pi;
        if (i != J.size())
            cout << ",";
    }
    cout << "]\n";

    cout << "S: [";
    for (int i = 1; i <= J.size(); i++) {
        cout << J[i - 1].S;
        if (i != J.size())
            cout << ",";
    }
    cout << "]\n";

    cout << "C: [";
    for (int i = 1; i <= J.size(); i++) {
        cout << J[i - 1].C;
        if (i != J.size())
            cout << ",";
    }
    cout << "]\n";

    cout << "Cq: [";
    for (int i = 1; i <= J.size(); i++) {
        cout << J[i - 1].Cq;
        if (i != J.size())
            cout << ",";
    }
    cout << "]\n";
}

int Znajdz_Cmax(vector<Zadanie> J) {
    int C_max = 0;
    for (int i = 0; i < J.size(); i++) {
        C_max = max(C_max, J[i].Cq);
    }
    return C_max;
}

int CALCULATE(vector<Zadanie>& J) {
    if (J.size() > 0) {
        J[0].S = J[0].r;
        J[0].C = J[0].S + J[0].p;
        J[0].Cq = J[0].C + J[0].q;
        int C_max = J[0].Cq;
        for (int i = 1; i < J.size(); i++) {
            J[i].S = max(J[i].r, J[i - 1].C);
            J[i].C = J[i].S + J[i].p;
            J[i].Cq = J[i].C + J[i].q;
            C_max = max(C_max, J[i].Cq);
        }
        return C_max;
    }
    else {
        return INT_MAX;
    }
}

void Init(vector<Zadanie>& J, int seed, int n) {
    RandomNumberGenerator generator(seed);
    int A = 0, X;

    for (int i = 0; i < n; i++)
    {
        Zadanie tmp;
        tmp.p = generator.nextInt(1, 29);
        J.push_back(tmp);
        A += J[i].p;
        J[i].pi = i + 1;
    }
    //X = 29;
    X = A;
    for (int i = 0; i < n; i++)
    {
        J[i].r = generator.nextInt(1, A);
    }
    for (int i = 0; i < n; i++)
    {
        J[i].q = generator.nextInt(1, X);
    }
}

vector<Zadanie> SCHRAGE(vector<Zadanie> J) {
    priority_queue<Zadanie, vector<Zadanie>, Porownaj_r> N;
    priority_queue<Zadanie, vector<Zadanie>, Porownaj_q> G;
    vector<Zadanie> kolejnosc;
    int t;
    for (int i = 0; i < J.size(); i++) {
        N.push(J[i]);
    }
    t = N.top().r;
    while (!G.empty() || !N.empty()) {
        while (!N.empty() && N.top().r <= t) {
            G.push(N.top());
            N.pop();
        }
        if (!G.empty()) {
            kolejnosc.push_back(G.top());
            t = t + G.top().p;
            G.pop();
        }
        else {
            t = N.top().r;
        }
    }
    return kolejnosc;
}

vector<Zadanie> SCHRAGEPMTN(vector<Zadanie> J) {

    priority_queue<Zadanie, vector<Zadanie>, Porownaj_r> N;
    priority_queue<Zadanie, vector<Zadanie>, Porownaj_q> G;
    vector<Zadanie> kolejnosc;
    int t;
    for (int i = 0; i < J.size(); i++) {
        N.push(J[i]);
    }
    t = N.top().r;
    while (!G.empty() || !N.empty()) {
        while (!N.empty() && N.top().r <= t) {
            G.push(N.top());
            N.pop();
        }
        if (!G.empty()) {
            Zadanie tmp = G.top();
            G.pop();
            tmp.S = t;
            if (!N.empty()) {
                //brak przerwania
                if (N.top().r >= t + tmp.p) {
                    t = t + tmp.p;
                }
                //przerwanie
                else {
                    tmp.p = tmp.p - (N.top().r - t);
                    t = N.top().r;
                    G.push(tmp);
                }
            }
            else {
                t = t + tmp.p;
            }
            tmp.C = t;
            tmp.Cq = tmp.C + tmp.q;
            if (kolejnosc.size() > 0) {
                if (tmp.pi == kolejnosc[kolejnosc.size() - 1].pi) {
                    kolejnosc.pop_back();
                }
            }
            kolejnosc.push_back(tmp);

        }
        else {
            t = N.top().r;
        }
    }
    return kolejnosc;
}

static int UB = INT_MAX;
static vector<Zadanie> pi2;
vector<Zadanie> CARLIER (vector<Zadanie> J) {
    vector<Zadanie> pi1= SCHRAGE(J), pi3, K;
    int U = CALCULATE(pi1), LB;
    int a=0, b=0, c=-1, p=0, r=INT_MAX, q=INT_MAX, tmp;
    if (U < UB) {
        UB = U;
        pi2 = pi1;
    }
    for (int i = 0; i < pi1.size(); i++) {
        if (U == pi1[i].Cq) {
            b = i;
        }
    }
    for (int i = b, suma=0; i >0; i--) {
        suma += pi1[i].p;
        if (U == pi1[i].r + suma + pi1[i].q) {
            a = i;
        }
    }
    for (int i = a; i < b; i++) {
        if (pi1[i].q < pi1[b].q) {
            c = i;
        }
    }
    if (c == -1) { return pi2; }
    for (int i = c+1; i <= b; i++) {
        K.push_back(pi1[i]);
    }
    for (int i = 0; i < K.size(); i++) {
        if (r > K[i].r) {
            r = K[i].r;
        }
    }
    for (int i = 0; i < K.size(); i++) {
        if (q > K[i].q) {
            q = K[i].q;
        }
    }
    for (int i = 0; i < K.size(); i++) {
        p += K[i].p;
    }
    tmp = pi1[c].r;
    pi1[c].r = max(pi1[c].r, r + p);
    pi3 = SCHRAGEPMTN(J);
    LB = Znajdz_Cmax(pi3);
    if (LB < UB) {
        CARLIER(pi1);
    }
    pi1[c].r = tmp;
    tmp = pi1[c].q;
    pi1[c].q = max(pi1[c].q, q + p);
    pi3 = SCHRAGEPMTN(J);
    LB = Znajdz_Cmax(pi3);
    if (LB < UB) {
        CARLIER(pi1);
    }
    pi1[c].q = tmp;
    return pi2;
}



/******************************  MAIN *****************************/

int main()
{

    while (1)
    {
        vector<Zadanie> Z, permutacja;


        //INTERAKCJA Z UŻYTKOWNIKIEM
        cout << "Wprowadz zrodlo losowania: ";
        cin >> seed;
        cout << "Wprowadz rozmiar problemu: ";
        cin >> n;
        cout << "n: " << n << endl << endl;


        //GENEROWANIE P R Q

        Init(Z, seed, n);

        //WYŚWIETLANIE

        Wyswietl1(Z);

        //LICZENIE WARTOŚCI FUNKCJI CELU

        C_max = CALCULATE(Z);

        //WYŚWIETLANIE

        cout << "permutacja naturalna" << endl;
        Wyswietl2(Z);
        cout << "Cmax: " << C_max << endl << endl;

        //ALGORYTM SCHRAGE

        permutacja = SCHRAGE(Z);

        //GENEROWANIE NOWYCH Cq i Cmax

        C_max = CALCULATE(permutacja);

        //WYŚWIETLANIE

        cout << "permutacja po alg Schrage" << endl;
        Wyswietl2(permutacja);
        cout << "Cmax: " << C_max << endl << endl;

        //ALGORYTM SCHRAGE PTMN

        permutacja = SCHRAGEPMTN(Z);

        //GENEROWANIE NOWYCH Cq i Cmax

        C_max = Znajdz_Cmax(permutacja);

        //WYŚWIETLANIE

        cout << "permutacja po alg SchragePMTN" << endl;
        Wyswietl2(permutacja);
        cout << "Cmax: " << C_max << endl << endl;

        //ALGORYTM SCHRAGE PTMN
        pi2 = Z;
        permutacja = CARLIER(Z);

        //GENEROWANIE NOWYCH Cq i Cmax

        C_max = Znajdz_Cmax(permutacja);

        //WYŚWIETLANIE

        cout << "permutacja po alg Carlier" << endl;
        Wyswietl2(permutacja);
        cout << "Cmax: " << C_max << endl << endl;



    }
}