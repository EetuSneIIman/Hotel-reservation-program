
/*  
    Versio 1.0
    C++
    Eetu Snellman
    Hotellivarausjärjestelmä
*/

// Lisätään tarvittavat kirjastot
#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <windows.h>
#include <iomanip>

// Lisätään kirjastoista teksin järjestelyyn tarvittavia funktioita
using namespace std;
using std::cout;
using std::left;
using std::setw;

// Määritetään funktio joka tarkistaa varatut huoneet ja palauttaa 1 / 0
bool Huonevarattu(int, vector<int> varatuthuoneet1);

// Luodaan struct varauksen sisällölle
struct Varaus
{
    string varaajan_nimi; // Nimi
    int varausid;         // Arvottu varaus id
    int huoneen_koko;     // Huoneen koko 1-3 huonetta
    int oiden_maara;      // Varattavien öiden määrä
    float hinta;          // Varauksen hinta
    int huoneennumero;    // Arvottu huoneen numero
    int varaus;           // Varauksen järjestysnumero
};

int main()
{
    int arvotutHuoneet = 30; // Arvottu huoneiden määrä
    int valmiiksiVaratut;    // Muuttuja joka lisää varattujen listalle arvotun huonenumeron
    int varattujenMaara;     // Muuttuja valmiiksi varattujen huoneiden määrälle
    int arvotutHuoneetMax;   // Arvottu lisättävien varattujen huoneiden määrä
    float yhteinenHinta = 0; // Varauksien kokonaishinta

    int poistetaan; // Muuttuja huoneen poistamiselle

    string userInput; // Muuttuja käyttäjän vastauksille menussa

    // Luodaan vector listat
    vector<int> varatuthuoneet; // Vectori varatuille huoneille

    vector<Varaus> v; // Vectori käyttäjän varauksille

    arvotutHuoneetMax = rand() % 70 + 0; // Arvotaan luku väliltä 0-70
    valmiiksiVaratut = rand() % 30 + 5;  // Arvotaan valmiiksi varattujen määrä väliltä 5-30

    arvotutHuoneet = arvotutHuoneet + arvotutHuoneetMax; // Lisätään arvottu luku huoneiden määrään (Max 100)

    // Asetetaan arvotut arvot varatuista huoneista
    for (int i = 1; i < valmiiksiVaratut; i++) // for loop joka lisää huoneen "varatuthuoneet" vectoriin kunnes arvottujen huoneiden raja tulee vastaan
    {
        int varataan; // Luodaan muuttuja varattavan huoneen numerolle

        varataan = rand() % 100 + 5; // Arvotaan, että mikä huone varataan väliltä 5 - 100 (Huoneiden määrä)

        varatuthuoneet.insert(varatuthuoneet.end(), varataan);
    }

    cout << "Tervetuloa hotellivarausjarjestelmaan \n\n"; // Tervetulo toivotus käyttäjälle. Näytetään vain kerran ohjelman alussa

menu: // tag menu

    while (true) // Menun loop
    {
        // Menu rakenne jossa 4 vastausta
        cout << "\n\nValitse toiminto seuraavista vaihtoehdoista (numerovalinta 1-4) \n\n";
        cout << "\n1: Varaa huone";
        cout << "\n2: Tarkista varaamasi huoneet";
        cout << "\n3: Poista varaus";
        cout << "\n4: Lopetus\n";

        // Käyttäjän vastaus
        cout << "\nValinta: ";
        cin >> userInput;

        cout << "\n\n--------------------------------------------------------------------------------------------------------------------\n\n";

        if (userInput == "1") // Jos käyttäjä vastaa "1" siirretään käyttäjä varausmenuun
        {
            goto varausmenu;
        }

        if (userInput == "2") // Jos käyttäjä vastaa "2" siirretään käyttäjä varattujenhuoneiden listaan
        {
            goto varausLista;
        }

        if (userInput == "3") // Jos käyttäjä vastaa "3" siirretään käyttäjä poistettavan varauksen menuun
        {
            goto varauksenPoisto;
        }

        if (userInput == "4") // Jos käyttäjä vastaa "4" ohjelma sammuu
        {
            cout << "\nOhjelma sammutettu" << endl;

            return 0;
        }

        else // Jos käyttäjä vastaa yli neljän tai tekstillä, annetaan virheilmoitus ja siirretään takaisin menun alkuun
        {
            cout << "\nVirheellinen vastaus" << endl;

            cout << "\n\n--------------------------------------------------------------------------------------------------------------------\n\n";

            goto menu;
        }
    }

    // -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

varausmenu: // Tag varauslistalle

    if (varatuthuoneet.size() >= arvotutHuoneet) // Jos varattujen huoneiden määrä on sama kuin huoneiden määrä, ilmoitetaan käyttäjälle, että kaikki huoneet varattu ja palautetaan menuun
    {
        cout << endl
             << "Kaikki huoneet varattu. Palautetaan kayttaja menuun" << endl;
    }

    while (true) // varauksen loop
    {
        int varausid;          // arvottava varaus id
        int huoneennumero;     // arvottava huoneen numero
        int varaus = v.size(); // Varauksen järjestysnumero joka on listan koko +1
        string nimi;           // Varaajan nimen muuttuja
        int huoneen_koko1;     // Huoneen koko
        int oiden_maara1;      // Varattavien öiden määrä
        float hinta1;          // Muuttuja hinnalle
        float alennus;         // Muuttuja hinnan alennukselle
        char varausVastaus;    // Muuttuja käyttäjän vastaukselle menussa

        varausid = rand() % 99999 + 10000;           // Arvotaan varaukselle id
        huoneennumero = rand() % arvotutHuoneet + 5; // Arvotaan huoneelle numero 5 - arvottujen huoneiden määrä

        varaus = varaus + 1; // Lisätään järjestysnumeroon +1, jotta järjestysnumero on yhden suurempi kuin listan koko

        while (true) // loop varatun huoneen tarkistukselle
        {
            if (Huonevarattu(huoneennumero, varatuthuoneet)) // Kutsutaan muuttuja joka tarkistaa onko huone varattu. Parametrit (huoneen numero, varattujen huoneiden lista)
            {
                huoneennumero = rand() % arvotutHuoneet + 5; // Jos huone varattu, arvotaan huone uudelleen ja tarkistetaan uudelleen
            }
            else
            {
                break; // Lopetetaan loop koska huone ei ole varattu ja mennään ohjelmassa eteenpäin
            }
        }

        cin.ignore(); // Tyhjennetään cin, jotta getline komento voidaan käyttää

        cout << "Varaajan nimi: "; // Kysytään varaajan nimi
        getline(cin, nimi);

        nimi = nimi.substr(0, 29); // Rajoitetaan nimi 29 merkkiin

    huoneenKoko: // Tag joka palauttaa huoneen koko kysymykseen

        // Kysytään haluttu huoneen koko väliltä 1-3
        cout << "Huoneen koko (1-3) huonetta: ";
        cin >> huoneen_koko1;

        // Jos vastaus ei ole numero, annetaan virheilmoitus
        if (cin.fail())
        {
            cout << "Virheellinen vastaus! Vastaa huoneen koko valilta (1-3) huonetta" << endl;
            huoneen_koko1 = 0; // Palautetaan arvo huoneen koko muuttujaan

            // Tyhjennetään vastaus
            cin.clear();
            cin.ignore(256, '\n');

            goto huoneenKoko; // Mennään takaisin huoneen koko tagille
        }

        // Jos vastaus on liian suuri tai liian pieni, annetaan virheilmoitus
        else if (3 < huoneen_koko1 || huoneen_koko1 < 1)
        {
            cout << "Huoneiden maara tulee olla valilta (1-3): " << endl;
            huoneen_koko1 = 0; // Palautetaan arvo huoneen koko muuttujaan

            // Tyhjennetään vastaus
            cin.clear();
            cin.ignore(256, '\n');

            goto huoneenKoko; // Mennään takaisin huoneen koko tagille
        }

    öidenMäärä: // Tag joka palauttaa öiden määrä kysymykseen

        // Kysytään haluttujen öiden määrä
        cout << "Montako yota haluat varata: ";
        cin >> oiden_maara1;

        // Jos vastaus ei ole numero, annetaan virheilmoitus
        if (cin.fail())
        {
            cout << "Virheellinen vastaus! Vastaa oiden maara numerolla." << endl;

            oiden_maara1 = 0; // Palautetaan arvo öiden määrä muuttujaan

            // Tyhjennetään vastaus
            cin.clear();
            cin.ignore(256, '\n');

            goto öidenMäärä; // Mennään takaisin öiden määrä tagille
        }

        // Annetaan varattavien öiden määrälle maksimi arvo 50 ja tarkistetaan öiden määrä, jos yli 50 tai alle 1 annetaan virheilmoitus
        else if (50 < oiden_maara1 || oiden_maara1 < 1)
        {
            cout << "Oiden maksimi maara on 50 (minimi 1): " << endl;

            oiden_maara1 = 0; // Palautetaan arvo öiden määrä muuttujaan

            // Tyhjennetään vastaus
            cin.clear();
            cin.ignore(256, '\n');

            goto öidenMäärä; // Mennään takaisin huoneen koko tagille
        }

        // Määritetään varauksen hinta huoneen koon, varattujen öiden ja mahdollisen alennuksen mukaan
        if (huoneen_koko1 == 1) // Jos huonekoko on 1 henkeä, käytetään tätä hintaa
        {
            alennus = rand() % 30 + 0; // Arvotaan alennus välillä 0-30%
            alennus = alennus / 100;   // Jaetaan alennus 100, jotta saadaan prosenttiluku

            hinta1 = 100;                         // annetaan hinnalle arvo huonekoon mukaan
            hinta1 = hinta1 - (hinta1 * alennus); // Lasketaan alennus hintaan
            hinta1 = hinta1 * oiden_maara1;       // Kerrotaan hinta öiden määrällä
        }
        else if (huoneen_koko1 == 2) // Jos huonekoko on 2 henkeä, käytetään tätä hintaa
        {
            alennus = rand() % 30 + 0; // Arvotaan alennus välillä 0-30%
            alennus = alennus / 100;   // Jaetaan alennus 100, jotta saadaan prosenttiluku

            hinta1 = 150;                         // annetaan hinnalle arvo huonekoon mukaan
            hinta1 = hinta1 - (hinta1 * alennus); // Lasketaan alennus hintaan
            hinta1 = hinta1 * oiden_maara1;       // Kerrotaan hinta öiden määrällä
        }
        else if (huoneen_koko1 == 3)
        {
            alennus = rand() % 30 + 0; // Arvotaan alennus välillä 0-30%
            alennus = alennus / 100;   // Jaetaan alennus 100, jotta saadaan prosenttiluku

            hinta1 = 200;                         // annetaan hinnalle arvo huonekoon mukaan
            hinta1 = hinta1 - (hinta1 * alennus); // Lasketaan alennus hintaan
            hinta1 = hinta1 * oiden_maara1;       // Kerrotaan hinta öiden määrällä
        }

        // Kerrotaan käyttäjälle varauksen hinta ja kysytään, että tehdäänkö varaus
        cout << endl
             << "Varauksen hinta on: " << hinta1 << endl;

    vääräVarausVastaus: // Tag joka palauttaa varataanko huone kysymykseen

        // Kysytään käyttäjältä varataanko huone y(yes) / n(no)
        cout << "Haluatko varata huoneen (Y/N): ";
        cin >> varausVastaus;

        // Jos vastaus on Y tai y tehdään varaus
        if (varausVastaus == 'Y' || varausVastaus == 'y')
        {
            // Tehdään struct käyttäjän antamilla arvoilla
            struct Varaus a1 = {nimi, huoneennumero, huoneen_koko1, oiden_maara1, hinta1, varausid, varaus};

            // Lisätään struct vectorin loppuun
            v.push_back(a1);

            // Lisätään huoneen numero varattujen huoneiden vectoriin
            varatuthuoneet.push_back(huoneennumero);

            hinta1 = 0;  // Palautetaan hinnan arvo
            alennus = 0; // Palautetaan alennuksen arvo

            // Kerrotaan käyttäjälle onnistuneesta varauksesta
            cout << "\nVarasit onnistuneesti huoneen" << endl;

            cout << "\n\n--------------------------------------------------------------------------------------------------------------------\n\n";

            goto menu; // Palataan menuun
            break;     // Suljetaan loop
        }

        // Jos vastaus on N tai n lopetetaan varaus
        else if (varausVastaus == 'N' || varausVastaus == 'n')
        {

            // Kerrotaan käyttäjälle lopetetusta varauksesta
            cout << "\nLopetit huoneen varauksen: " << endl;

            cout << "\n\n--------------------------------------------------------------------------------------------------------------------\n\n";

            goto menu; // Palataan menuun
            break;     // Suljetaan loop
        }

        // Jos vastaus ei ole Y, y, N tai n. Kerrotaan virheellisestä vastauksesta ja palautetaan Varausvastauksen kysymykseen
        else
        {
            cout << endl
                 << "Virheellinen vastaus!";

            goto vääräVarausVastaus; // Palataan varausvastaus kysymykseen
        }
    }

    // -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

varausLista:

    while (true) // Loop varauksille
    {
        // Luodaan rakenne varausten näyttämiselle
        cout << "\nTekemasi varaukset" << endl;

        cout << endl
             << setw(13) << left << "Varauksesi"
             << setw(30) << left << "Varaajan nimi"
             << setw(18) << left << "Huoneiden maara"
             << setw(8) << left << "Hinta"
             << setw(17) << left << "Huoneen numero"
             << setw(12) << left << "Varaus id"
             << setw(20) << left << "Varatut yot" << endl;

        // Tulostetaan järjestyksessä kaikki käyttäjän varaukset
        for (auto &a : v)
        {

            cout << setw(13) << left << a.varaus
                 << setw(30) << left << a.varaajan_nimi
                 << setw(18) << left << a.huoneen_koko
                 << setw(8) << left << a.hinta
                 << setw(17) << left << a.varausid
                 << setw(12) << left << a.huoneennumero
                 << setw(20) << left << a.oiden_maara << endl
                 << endl;
        }

        // Lasketaan varausten yhteishinta lisäämällä järjestyksessä kaikkien varausten hinnat yhteen
        for (auto &a : v)
        {

            yhteinenHinta = yhteinenHinta + a.hinta;
        }

        // Kerrotaan varausten hinta
        cout << endl
             << "varausten hinta yhteensa: " << yhteinenHinta << endl;

        cout << "\n\n--------------------------------------------------------------------------------------------------------------------\n\n";

        goto menu; // Palataan menuun
        break;     // Suljetaan loop
    }

    // -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

varauksenPoisto:

    while (true) // loop varauksen poistolle
    {
        // Luodaan rakenne varausten näyttämiselle
        cout << "\nTekemasi varaukset, valitse poistettava varaus" << endl;

        cout << endl
             << setw(13) << left << "Varauksesi"
             << setw(30) << left << "Varaajan nimi"
             << setw(18) << left << "Huoneiden maara"
             << setw(8) << left << "Hinta"
             << setw(17) << left << "Huoneen numero"
             << setw(12) << left << "Varaus id"
             << setw(20) << left << "Varatut yot" << endl;

        // Tulostetaan järjestyksessä kaikki käyttäjän varaukset
        for (auto &a : v)
        {
            cout << setw(13) << left << a.varaus
                 << setw(30) << left << a.varaajan_nimi
                 << setw(18) << left << a.huoneen_koko
                 << setw(8) << left << a.hinta
                 << setw(17) << left << a.varausid
                 << setw(12) << left << a.huoneennumero
                 << setw(20) << left << a.oiden_maara << endl
                 << endl;
        }

    poistettava: // tag poistettavan varauksen kysymykselle

        // Kysytään käyttäjältä mikä huone poistetaan. Käyttäjä vastaa poistettavan huoneen varauksen järjestysnumerolla
        cout << "\nValitse listasta poistettava huone (Varauksesi) valilta 1 - " << v.size() << " : ";
        cin >> poistetaan;

        // Poistetaan vastauksesta -1, jotta saadaan vectorin indeksi luku oikein
        poistetaan = poistetaan - 1;

        // Jos vastaus on enemmän kuin vectorin koko, annetaan virheilmoitus
        if (v.size() < poistetaan)
        {
            cout << "Virheellinen vastaus. Valitse poistettava huone valilta 1 - " << v.size() << " : " << endl;

            poistetaan = 0; // Palautetaan poistettavan huoneen arvo

            goto poistettava; // Palautetaan käyttäjä poistettavan huoneen kysymykseen
        }

        // Vastaus on sopiva ja siirrytään ohjelmassa eteenpäin
        else
        {
            yhteinenHinta = yhteinenHinta - v[poistetaan].hinta; // Poistetaan varauksen hinta yhteishinnasta

            v.erase(v.begin() + poistetaan); // Poistetaan varaus käyttäjien varauksista

            cout << "\n\n--------------------------------------------------------------------------------------------------------------------\n\n";

            goto menu; // Palautetaan käyttäjä menuun
            break;     // Suljetaan loop
        }
    }

    return 0; // Ohjelman lopuksi palautetaan 0
}

bool Huonevarattu(int haluttuhuone, vector<int> varatuthuoneet1)
{

    // Tarkistetaan onko huone varattu
    bool exists = std::find(varatuthuoneet1.begin(), varatuthuoneet1.end(), haluttuhuone) != varatuthuoneet1.end();

    // Jos haluttu huone on listassa, palautetaan true
    if (exists)
    {
        return true;
    }

    // Jos haluttu huone ei ole listassa
    else
    {
        // palautetaan false
        return false;
    }
}

// End of file
