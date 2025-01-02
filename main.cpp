#include <iostream>
#include <time.h>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

void clearScreen(){
    std::cout << "\033[2J\033[1;1H";
}

class ClassificaGenerale
{
private:
    vector<string> giocatori;
    vector<int> punteggi;

    int numeroPunteggiRegistrati = 10;
    int size = 0;
    int MAX_SIZE = 10;

    void salvaClassificaGenerale()
    {
        ofstream file("classificaGenerale.txt", ios::out);
        if (!file)
        {
            cout << "Errore apertura del file" << endl;
            return;
        }
        for (int i = 0; i < giocatori.size(); i++)
        {
            file << punteggi[i] << " " << giocatori[i] << endl;
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

        while (file >> punteggio)
        {
            file >> giocatore;
            punteggi.push_back(punteggio);
            giocatori.push_back(giocatore);
        }
        file.close();
    }

    ~ClassificaGenerale(){
        salvaClassificaGenerale();
    }

    void aggiungiPunteggio(int punteggio, string giocatore)
    {
        giocatori.push_back(giocatore);
        punteggi.push_back(punteggio);
        salvaClassificaGenerale();
    }
    
    void stampaclassificaGenerale()
    {
        clearScreen();
        cout << "\n\n\n\n";
    cout << "-------------------- CLASSIFICA GENERALE -----------------------" << endl;
    cout << endl;
    if (giocatori.size() > MAX_SIZE){
        size = MAX_SIZE;
    }
    else{
        size = giocatori.size();   
    }

    for (int i = 0; i < size; i++){
        cout << i+1 << " Punteggio: " << punteggi[i] << " Giocatore: " << giocatori[i] << endl;
    }
    cout << "----------------------------------------------------------------" << endl;
    }
};

int menu()
{
    int scelta = -1;
    cout << "\n\n\n\n";
    cout << "----------------------------- MENU -----------------------------" << endl;
    cout << "1 - Gioca" << endl;
    cout << "2 - Classifica Generale" << endl;
    cout << "0 - Uscita" << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << "> ";
    cin >> scelta;
    return scelta;
}


int main()
{
    ClassificaGenerale classifica;
    srand(time(NULL));
    int contatore = 0;
    int numero = 0;
    int tentativo = -1;
    
    clearScreen();

    while (true)
    {
        switch (menu())
        {
        case 1:
            numero = rand() % 1000 + 1;
            cout << "Numero da indovinare " << numero << endl;
            cout << "Indovina il numero tra 1 e 1000" << endl;
            while (tentativo != numero)
            {
                contatore++;
                cout << "Inserisci il numero: ";
                cin >> tentativo;
                if (tentativo < numero)
                {
                    cout << "il numero da indovinare è maggiore! riprova" << endl;
                }
                else if (tentativo > numero)
                {
                    cout << "il numero da indovinare è minore! riprova" << endl;
                }
                else
                {
                    cout << "Hai indovinato!! in " << contatore << " volte" << endl;
                    cout << "Inserisci il tuo nome per la classifica generale!!" << endl;
                    string giocatore = "Anonimo";
                    cin >> giocatore;
                    classifica.aggiungiPunteggio(contatore, giocatore);
                    contatore = 0;
                    clearScreen();
                }
            }
            break;
        case 2:
            classifica.stampaclassificaGenerale();
            break;
        case 0:
            cout << "Gioco terminato, alla prossima partita!!\n";
            return 0;
        default:
            cout << "Scelta non valida\n";
            break;
        }
    }
}