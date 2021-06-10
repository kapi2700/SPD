#include <iostream>
#include <algorithm>
#include "RandomNumberGenerator.h"
#include <vector>
#include <chrono>
#include <cmath>

using namespace std;

/********************************* ZMIENNNE I STRUKTURY ***************************************/

int n, m, seed;


struct Operacja {
    int p, C, S, nr_maszyny;
};

struct Zadanie {
    vector <Operacja> Maszyny;
    int nr_zadania;
};

vector<Zadanie> permutacja;
volatile int UB = INT_MAX;
static vector<Zadanie> perm;
static vector<int> min_p;


/********************************* FUNKCJE ***************************************/

void Init(vector<Zadanie>& J, int seed, int n, int m) {
    Operacja o;
    Zadanie z;
    RandomNumberGenerator generator(seed);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            o.p = generator.nextInt(1, 29);
            o.nr_maszyny = j;
            z.Maszyny.push_back(o);
        }
        z.nr_zadania = i;
        J.push_back(z);
        z.Maszyny.clear();
    }
}

int CALCULATE(vector<Zadanie>& J) {
    for (int i = 0; i < J.size(); ++i) {
        for (int j = 0; j < J[i].Maszyny.size(); ++j) {
            if (i == 0 && j == 0)
                J[i].Maszyny[j].C = J[i].Maszyny[j].p;
            else if (j != 0 && i != 0)
                J[i].Maszyny[j].C = max(J[i].Maszyny[j - 1].C, J[i - 1].Maszyny[j].C) + J[i].Maszyny[j].p;
            else if (i == 0)
                J[i].Maszyny[j].C = J[i].Maszyny[j - 1].C + J[i].Maszyny[j].p;
            else if (j == 0)
                J[i].Maszyny[j].C = J[i - 1].Maszyny[j].C + J[i].Maszyny[j].p;
        }
        if (i == J.size() - 1) { return  J[i].Maszyny[J[i].Maszyny.size() - 1].C; }
    }

}


void Wyswietl1(vector<Zadanie> J) {
    cout << "p: [";
    for (int i = 0; i < J.size(); ++i) {
        cout << "[";
        for (int j = 0; j < J[i].Maszyny.size(); ++j) {
            cout << J[i].Maszyny[j].p;
            if (j != J[i].Maszyny.size() - 1)
                cout << ",";
        }
        cout << "]";
        if (i != J.size() - 1)
            cout << ",";
    }
    cout << "]\n";
}

void Wyswietl2(vector<Zadanie> J) {
    cout << "pi: [";
    for (int i = 0; i < J.size(); ++i) {
        cout << J[i].nr_zadania;
        if (i != J.size() - 1)
            cout << ",";
    }
    cout << "]\n";
    cout << "C: [";
    for (int i = 0; i < J.size(); ++i) {
        cout << "[";
        for (int j = 0; j < J[i].Maszyny.size(); ++j) {
            cout << J[i].Maszyny[j].C;
            if (j != J[i].Maszyny.size() - 1)
                cout << ",";
        }
        cout << "]";
        if (i != J.size() - 1)
            cout << ",";
        else
            cout << "]\n" << "Cmax: " << J[i].Maszyny[J[i].Maszyny.size() - 1].C << endl;
    }

}

vector<Zadanie> Johnson(vector<Zadanie> J) {
    int l = 0, k = 0, nr = -1;
    vector<Zadanie> N = J, pi;

    while (!N.empty()) {
        int min = INT_MAX;
        for (int i = 0; i < N.size(); ++i) {
            for (int j = 0; j < N[i].Maszyny.size(); ++j) {
                if (min > N[i].Maszyny[j].p) {
                    min = N[i].Maszyny[j].p;
                    nr = i;
                }
            }
        }
        if (N[nr].Maszyny[0].p < N[nr].Maszyny[1].p) {
            pi.insert(pi.begin() + l, N[nr]);
            ++l;
        }
        else {
            pi.insert(pi.end() - k, N[nr]);
            ++k;
        }
        N.erase(N.begin() + nr);
    }
    return pi;
}

vector<Zadanie> Johnson_mod(vector<Zadanie> J) {
    int l = 0, k = 0, nr = -1;
    int ostatnia_maszyna = J[0].Maszyny.size() - 1;
    vector<Zadanie> N = J, pi;

    while (!N.empty()) {
        int min = INT_MAX;
        for (int i = 0; i < N.size(); ++i) {
            for (int j = 0; j < N[i].Maszyny.size(); j += ostatnia_maszyna) {
                if (min > N[i].Maszyny[j].p) {
                    min = N[i].Maszyny[j].p;
                    nr = i;
                }
            }
        }
        if (N[nr].Maszyny[0].p < N[nr].Maszyny[ostatnia_maszyna].p) {
            pi.insert(pi.begin() + l, N[nr]);
            ++l;
        }
        else {
            pi.insert(pi.end() - k, N[nr]);
            ++k;
        }
        N.erase(N.begin() + nr);
    }
    return pi;
}

void BruteForce(Zadanie z, vector<Zadanie> N, vector<Zadanie> pi) {
    pi.push_back(z);
    for (int i = 0; i < N.size(); ++i) {
        if (N[i].nr_zadania == z.nr_zadania) {
            N.erase(N.begin() + i);
        }
    }
    if (N.empty()) {
        int Cmax = CALCULATE(pi);
        if (Cmax < UB) {
            UB = Cmax;
            perm = pi;
        }
    }
    else {

        for (int i = 0; i < N.size(); ++i) {
            BruteForce(N[i], N, pi);
        }
    }
}

void znajdz_min(vector<Zadanie> J) {
    int m = J[0].Maszyny.size() - 1;
    min_p.clear();
    for (int i = 0; i <= m; ++i) {
        int min = INT_MAX;
        for (int j = 0; j < J.size(); ++j) {
            if (min > J[j].Maszyny[i].p) min = J[j].Maszyny[i].p;
        }
        min_p.push_back(min);
    }
}

int BOUND(vector<Zadanie> pi, vector<Zadanie> N) {
    int suma = 0, Cmx = 0, m = N[0].Maszyny.size() - 1;
    Cmx = CALCULATE(pi);
    for (int i = 0; i < N.size(); ++i) {
        suma += N[i].Maszyny[m].p;
    }
    return Cmx + suma;
}

int BOUND1(vector<Zadanie> pi, vector<Zadanie> N) {
    int suma, max = 0, Cix = 0, x = pi.size() - 1, m = N[0].Maszyny.size() - 1;
    CALCULATE(pi);
    for (int i = 0; i <= m; ++i) {
        suma = 0;
        Cix = pi[x].Maszyny[i].C;
        for (int j = 0; j < N.size(); ++j) {
            suma += N[j].Maszyny[i].p;
        }
        if (max < Cix + suma) max = Cix + suma;
    }
    return max;
}

int BOUND2(vector<Zadanie> pi, vector<Zadanie> N) {
    int suma, suma_min, max = 0, Cix = 0, x = pi.size() - 1, m = N[0].Maszyny.size() - 1;
    CALCULATE(pi);
    for (int i = 0; i <= m; ++i) {
        suma = 0, suma_min = 0;
        Cix = pi[x].Maszyny[i].C;
        for (int j = 0; j < N.size(); ++j) {
            suma += N[j].Maszyny[i].p;
        }
        for (int k = i + 1; k <= m; ++k) {
            suma_min += min_p[k];
        }
        if (max < Cix + suma + suma_min) max = Cix + suma + suma_min;
    }
    return max;
}

int BOUND3(vector<Zadanie> pi, vector<Zadanie> N) {
    int suma, suma_min, max = 0, Cix = 0, x = pi.size() - 1, m = N[0].Maszyny.size() - 1;
    CALCULATE(pi);
    znajdz_min(N);
    for (int i = 0; i <= m; ++i) {
        suma = 0, suma_min = 0;
        Cix = pi[x].Maszyny[i].C;
        for (int j = 0; j < N.size(); ++j) {
            suma += N[j].Maszyny[i].p;
        }
        for (int k = i + 1; k <= m; ++k) {
            suma_min += min_p[k];
        }
        if (max < Cix + suma + suma_min) max = Cix + suma + suma_min;
    }
    return max;
}

int BOUND4(vector<Zadanie> pi, vector<Zadanie> N) {
    int suma, suma_min, min, max = 0, Cix = 0, x = pi.size() - 1, m = N[0].Maszyny.size() - 1;
    CALCULATE(pi);
    for (int i = 0; i <= m; ++i) {
        suma = 0, min = INT_MAX;
        Cix = pi[x].Maszyny[i].C;
        for (int j = 0; j < N.size(); ++j) {
            suma_min = 0;
            suma += N[j].Maszyny[i].p;
            for (int k = i + 1; k <= m; ++k) {
                suma_min += N[j].Maszyny[k].p;
            }
            if (min > suma_min) min = suma_min;
        }
        if (max < Cix + suma + min) max = Cix + suma + min;
    }
    return max;
}

void BNB(Zadanie z, vector<Zadanie> N, vector<Zadanie> pi) {
    pi.push_back(z);
    for (int i = 0; i < N.size(); ++i) {
        if (N[i].nr_zadania == z.nr_zadania) {
            N.erase(N.begin() + i);
        }
    }
    if (!N.empty()) {
        int LB = BOUND4(pi, N);  //  <--------   zmiana metody liczenia LB
        if (LB < UB) {
            for (int i = 0; i < N.size(); ++i) {
                BNB(N[i], N, pi);
            }
        }
    }
    else {
        int Cmax = CALCULATE(pi);
        if (Cmax < UB) {
            UB = Cmax;
            perm = pi;
        }
    }
}


void SimulatedAnnealing(vector<Zadanie> J) {
    vector<Zadanie> pi = J, pi_new;
    int T0 = CALCULATE(pi) * 11 / 10;
    double Tend = 0.1;
    int deltaT = T0 / 20;
    int L = pi.size()*(pi.size()-1)/4;
    int T = T0, i, j,C_new, C_old;
    double r;
    
    while (T > Tend) {
        for (int k = 0; k < L; ++k) {
            i = rand() % pi.size();
            j = rand() % pi.size();
            while (i == j) {
                j = rand() % pi.size();
            }
            pi_new = pi;
            swap(pi_new[i], pi_new[j]);
            C_new = CALCULATE(pi_new);
            C_old = CALCULATE(pi);
            if ( C_new > C_old ) {

               r= double(rand()) / (double(RAND_MAX));
               if (r >= exp(double(C_old-C_new)/(double(T)))) {
                   pi_new = pi;
               }

            }
            pi = pi_new;
            if (CALCULATE(pi) < CALCULATE(perm)) {
                perm = pi;
            }
        }
        T -= deltaT;
    }
}

void TabuSearch(vector<Zadanie> J,int it_Limit, int cadance) {
    int j2, k2;
    vector<Zadanie> pi = J, pi_new;
    vector < vector <int> > tabuList;
    for (int i = 0; i < pi.size(); ++i) {
        vector<int> tmp;
        for (int j = 0; j < pi.size(); ++j) {
            if (i == j) {
                tmp.push_back(INT_MAX);
            }
            else {
                tmp.push_back(-1);
            }
        }
        tabuList.push_back(tmp);
    }

    for (int it = 0; it < it_Limit ; ++it) {
        int Cbest = INT_MAX;
        for (int j = 0; j < pi.size()-1; ++j) {
            for (int k = j + 1; k < pi.size(); ++k) {
                if( tabuList[j][k]<it){
                    pi_new = pi;
                    swap(pi_new[j], pi_new[k]);
                    if (CALCULATE(pi_new) < Cbest) {
                        Cbest = CALCULATE(pi_new);
                        j2 = j;
                        k2 = k;
                    }
                }
            }
        }
        swap(pi[j2], pi[k2]);
        tabuList[j2][k2] = it + cadance;
        tabuList[k2][j2] = it + cadance;
        if (CALCULATE(pi) < CALCULATE(perm)) {
            perm = pi;
        }
    }




}



/********************************* MAIN *************************************/


int main()
{
    while (1)
    {
        vector<Zadanie> Z, permutacja,tmp;


        //INTERAKCJA Z UŻYTKOWNIKIEM
        cout << endl;
        cout << "Wprowadz zrodlo losowania: ";
        cin >> seed;
        cout << "Wprowadz ilosc zadan i maszyn: ";
        cin >> n;
        cin >> m;
        cout << endl << endl;


        //GENEROWANIE INSTANCJI

        Init(Z, seed, n, m);
        Wyswietl1(Z);
        CALCULATE(Z);
        cout << "permutacja naturalna" << endl;
        Wyswietl2(Z);


        //SIMULATED ANNEALING
        
        auto begin = chrono::high_resolution_clock::now();

        perm = Z;
        SimulatedAnnealing(Z);
        CALCULATE(perm);
       
        auto end = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);

        cout << "\nSymulowane wyzarzanie" << endl;
        Wyswietl2(perm);
        printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
        perm.clear();


        //TABU SEARCH

        begin = chrono::high_resolution_clock::now();

        perm = Z;
        TabuSearch(Z,20,4);
        CALCULATE(perm);

        end = chrono::high_resolution_clock::now();
        elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);

        cout << "\nPrzeszukiwanie z Zabronieniami" << endl;
        Wyswietl2(perm);
        printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
        perm.clear();


        //JOHNSON

        begin = chrono::high_resolution_clock::now();

        permutacja = Johnson_mod(Z);
        CALCULATE(permutacja);

        end = chrono::high_resolution_clock::now();
        elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);

        cout << "\nJohnson" << endl;
        Wyswietl2(permutacja);
        printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);


        //BRUTE FORCE

        begin = chrono::high_resolution_clock::now();

        vector<Zadanie> N = Z;
        UB = INT_MAX;
        perm.clear();
        permutacja.clear();
        for (int i = 0; i < N.size(); ++i) {
            BruteForce(N[i], N, permutacja);
        }
        CALCULATE(perm);

        end = chrono::high_resolution_clock::now();
        elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);

        cout << "\nBruteForce" << endl;
        Wyswietl2(perm);
        printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);


        //BRANCH AND BOUND

        begin = chrono::high_resolution_clock::now();

        //znajdz_min(Z);   // <----- do BOUND2 
        N = Z;
        UB = INT_MAX;

        permutacja.clear();
        permutacja = Johnson_mod(Z);            // <------ UB wyznaczone Johnsonem
        tmp = permutacja;
        UB = CALCULATE(permutacja);

        perm.clear();
        permutacja.clear();
        for (int i = 0; i < N.size(); ++i) {
            BNB(N[i], N, permutacja);
        }
        if (perm.size() == 0)perm = tmp;
        CALCULATE(perm);

        end = chrono::high_resolution_clock::now();
        elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);

        cout << "\nBranch and Bound" << endl;
        Wyswietl2(perm);
        printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

    }
}