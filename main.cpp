#include <iostream>
#include <time.h>
#include <fstream>
#include <map>
#include <vector>
#include <chrono>

using namespace std;

void clearScreen()
{
    std::cout << "\033[2J\033[1;1H";
}

class ClassificaGenerale
{
private:
    vector<string> giocatori;
    vector<int> punteggi;
    vector<int> tempi;

    int size = 0;
    int MAX_SIZE = 9;

    void salvaClassificaGenerale()
    {
        ofstream file("classificaGenerale.txt", ios::out);
        if (!file)
        {
            cout << "Errore apertura del file" << endl;
            return;
        }
        int size;
        if (giocatori.size() > MAX_SIZE)
        {
            size = MAX_SIZE;
        }
        else
        {
            size = giocatori.size();
        }
        for (int i = 0; i < size; i++)
        {
            file << punteggi[i];
            file << " ";
            file << giocatori[i];
            file << " ";
            file << tempi[i];
            file << endl;
        }
        file.close();
    }

public:
    ClassificaGenerale()
    {
        ifstream file("classificaGenerale.txt");
        if (!file)
        {
            cout << "Errore nessuna classifica presente!!" << endl;
        }
        string giocatore;
        int punteggio;
        int tempo;

        while (file >> punteggio)
        {
            file >> giocatore;
            file >> tempo;
            punteggi.push_back(punteggio);
            giocatori.push_back(giocatore);
            tempi.push_back(tempo);
        }
        file.close();
    }

    ~ClassificaGenerale()
    {
        salvaClassificaGenerale();
    }

    void aggiungiPunteggio(int punteggio, string giocatore, int tempo)
    {
        // Meccanismo con vector vuoto
        if (punteggi.size() == 0)
        {
            punteggi.push_back(punteggio);
            giocatori.push_back(giocatore);
            tempi.push_back(tempo);
            return;
        }

        // Meccanismo che aggiunge il punteggio in posizione e fa scorrere il vector con gli altri elementi
        auto gt = giocatori.begin();
        auto tt = tempi.begin();

        for (auto it = punteggi.begin(); it != punteggi.end(); it++)
        {
            if (punteggio == *it)
            {
                if (tempo < *tt)
                {
                    punteggi.insert(it, punteggio);
                    giocatori.insert(gt, giocatore);
                    tempi.insert(tt, tempo);
                    return;
                }
            }
            else if (punteggio < *it)
            {
                punteggi.insert(it, punteggio);
                giocatori.insert(gt, giocatore);
                tempi.insert(tt, tempo);
                return;
            }

            gt++;
            tt++;
        }

        // Meccanismo che aggiunge in coda
        giocatori.push_back(giocatore);
        punteggi.push_back(punteggio);
        tempi.push_back(tempo);
    }

    void stampaclassificaGenerale()
    {
        clearScreen();
        cout << "\n\n\n";
        cout << "-------------------- CLASSIFICA GENERALE -----------------------" << endl;
        cout << endl;
        if (giocatori.size() > MAX_SIZE)
        {
            size = MAX_SIZE;
        }
        else
        {
            size = giocatori.size();
        }

        for (int i = 0; i < size; i++)
        {
            cout << i + 1 << "\tTentativi: " << punteggi[i] << "\tTempo: " << tempi[i] << "\tGiocatore: " << giocatori[i] << endl;
        }
        cout << "----------------------------------------------------------------" << endl;
    }
};

int menu()
{
    int scelta = -1;
    string stringaScelta = "";
    cout << "\n\n\n\n";
    cout << "----------------------------- MENU -----------------------------" << endl;
    cout << "1 - Gioca" << endl;
    cout << "2 - Classifica Generale" << endl;
    cout << "3 - Gioca con l'aiuto della IA" << endl;
    cout << "0 - Uscita" << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << "> ";
    cin >> stringaScelta;
    try
    {
        scelta = stoi(stringaScelta);
    }
    catch (invalid_argument &e)
    {
        cout << "Errore: non hai immesso un numero valido" << endl;
        return -1;
    }
    catch (out_of_range &e)
    {
        cout << "Errore: il numero è fuori dal range!!!" << endl;
        return -1;
    }
    return scelta;
}

int main()
{
    ClassificaGenerale classifica;
    srand(time(NULL));
    int contatore = 0;
    int numero = 0;
    long long tentativo = -1;
    string stringaTentativo = "";

    int max = 1000;
    int min = 1;

    chrono::time_point<chrono::high_resolution_clock> inizio;
    chrono::time_point<chrono::high_resolution_clock> fine;
    int tempo;

    clearScreen();

    while (true)
    {
        switch (menu())
        {
        case 0:
            cout << "Gioco terminato, alla prossima partita!!\n";
            return 0;
        case 1:

            classifica.stampaclassificaGenerale();

            numero = rand() % 1000 + 1;

            // cout << "Numero da indovinare " << numero << endl;
            cout << "Indovina il numero tra 1 e 1000" << endl;
            inizio = chrono::high_resolution_clock::now();
            while (tentativo != numero)
            {
                contatore++;
                cout << "Inserisci il numero: ";
                cin >> stringaTentativo;
                try
                {
                    tentativo = stoll(stringaTentativo);
                }
                catch (invalid_argument &e)
                {
                    cout << "Errore: non hai immesso un numero valido" << endl;
                    break;
                }
                catch (out_of_range &e)
                {
                    cout << "Errore: il numero è fuori dal range!!!" << endl;
                    break;
                }

                if (tentativo < numero)
                {
                    cout << "Il numero da indovinare è maggiore! riprova" << endl;
                }
                else if (tentativo > numero)
                {
                    cout << "Il numero da indovinare è minore! riprova" << endl;
                }
                else
                {
                    fine = chrono::high_resolution_clock::now();
                    tempo = chrono::duration_cast<chrono::seconds>(fine - inizio).count();

                    if (contatore == 1)
                    {
                        cout << "Hai indovinato!! in " << contatore << " volta! OTTIMO, in " << tempo << " secondi" << endl;
                    }
                    else
                    {
                        cout << "Hai indovinato!! in " << contatore << " volte, in " << tempo << " secondi" << endl;
                    }

                    cout << "Inserisci il tuo nome per la classifica generale!! (Max 12 Lettere)" << endl;
                    string giocatore = "Anonimo";
                    cin >> giocatore;
                    try
                    {
                        int lunghezza = giocatore.length();
                        if (lunghezza > 12)
                        {
                            giocatore = giocatore.substr(0, 12);
                        }
                    }
                    catch (invalid_argument &e)
                    {
                        giocatore = "Anonimo";
                    }
                    catch (out_of_range &e)
                    {
                        giocatore = giocatore.substr(0, 12);
                    }

                    classifica.aggiungiPunteggio(contatore, giocatore, tempo);
                    contatore = 0;
                    clearScreen();
                }
            }
            break;

        case 2:
            classifica.stampaclassificaGenerale();
            break;

        case 3:
            classifica.stampaclassificaGenerale();

            numero = rand() % 1000 + 1;

            // cout << "Numero da indovinare " << numero << endl;
            cout << "Indovina il numero tra 1 e 1000" << endl;

            while (tentativo != numero)
            {
                contatore++;
                cout << "Inserisci il numero: ";
                cin >> stringaTentativo;
                try
                {
                    tentativo = stoll(stringaTentativo);
                }
                catch (invalid_argument &e)
                {
                    cout << "Errore: non hai immesso un numero valido" << endl;
                    break;
                }
                catch (out_of_range &e)
                {
                    cout << "Errore: il numero è fuori dal range!!!" << endl;
                    break;
                }
                if (tentativo < numero)
                {
                    cout << "Il numero da indovinare è maggiore! riprova" << endl;
                    if (tentativo >= 1 && tentativo <= 1000)
                    {
                        min = tentativo;
                    }
                    cout << "IA: ti suggerisco di inserire " << (max + min) / 2 << " " << endl;
                }
                else if (tentativo > numero)
                {
                    cout << "Il numero da indovinare è minore! riprova" << endl;
                    if (tentativo >= 1 && tentativo <= 1000)
                    {
                        max = tentativo;
                    }
                    cout << "IA: ti suggerisco di inserire " << (max + min) / 2 << " " << endl;
                }
                else
                {
                    if (contatore == 1)
                    {
                        cout << "Hai indovinato!! in " << contatore << " volta! OTTIMO" << endl;
                    }
                    else
                    {
                        cout << "Hai indovinato!! in " << contatore << " volte" << endl;
                    }

                    cout << "Hai usato l'IA non sarai iscritto in classifica generale!! Inserisci un carattere per continuare..." << endl;
                    string giocatore = "";
                    cin >> giocatore;

                    contatore = 0;
                    clearScreen();
                }
            }
            break;
        default:
            cout << "Scelta non valida\n";
            break;
        }
    }
}