#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Forma
{
    static const double S_MAX_INALTIME;
protected:
    double m_inaltime;
public:
    Forma(): m_inaltime(0)
    {
//        std::cout << "CI Forma fara param" << std::endl;
    }
    Forma(double inaltime): m_inaltime(inaltime)
    {
//        std::cout << "CI Forma cu inaltimea" << inaltime << " " << std::endl;
    }

    double GetInaltime() {return m_inaltime;}

    //facem virtual ca la runtime referinta/pointerul catre baza care contine derivata sa apeleze metoda suprascrisa din derivata
    virtual void Afisare()
    {
        std::cout << "inaltimea " << m_inaltime;
    }

    virtual void Citire()
    {
        cin >> m_inaltime;
        if(m_inaltime > S_MAX_INALTIME) {cout << "Inaltime invalida!" << endl;}
    }

    //metoda pura => clasa devine abstracta
    //un obiect Forma nu mai poate fi instantiat
    virtual double Aria()=0;

    double Volum()
    {
//        return m_inaltime * Aria();
        return Volum(m_inaltime, Aria());
    }

    static double Volum(double inaltime, double ariaBazei)
    {
        return inaltime * ariaBazei;
    }

    double Suprafata()
    {
        //TODO
        return 0;
    }

    double CantitateGem()
    {
        return 2 * Volum();
    }
    double CantitateFrisca()
    {
        //GRESIT!: defapt cantitatea de frisca depinde de suprafata
        //TODO: implementeaza cu suprafata
        return Volum();
    }
    virtual ~Forma(){}
};

const double S_MAX_INALTIME = 10;

class Cerc: public Forma
{
    double m_raza;
    static int s_nr_cercuri;
public:
    Cerc():m_raza(0) {s_nr_cercuri++;}
    Cerc(double inaltime, double raza): Forma(inaltime), m_raza(raza){s_nr_cercuri++;}
    Cerc(const Cerc &cerc): m_raza(cerc.m_raza), Forma(cerc.m_inaltime) {s_nr_cercuri++;}
    double GetRaza(){return m_raza;}
    static int GetNrCercuri() {return s_nr_cercuri;}

    void Afisare()
    {
        cout << "Cerc: ";
        Forma::Afisare();
        std::cout << " raza: " << m_raza << std::endl;
    }

    void Citire()
    {
        Forma::Citire();
        cin >> m_raza;
    }

    double Aria()
    {
        return M_PI * m_raza * m_raza;
    }
    ~Cerc(){s_nr_cercuri--;}
};
int Cerc::s_nr_cercuri = 0;

class Dreptunghi: public Forma
{
    double m_latura_mica;
    double m_latura_mare;
public:
    Dreptunghi(): Forma(0), m_latura_mica(0), m_latura_mare(0){}
    Dreptunghi(double inaltime, double latura_mica, double latura_mare):Forma(inaltime), m_latura_mare(latura_mare), m_latura_mica(latura_mica) {}
    void Citire()
    {
        Forma::Citire();
        cin >> m_latura_mica >> m_latura_mare;
    }
    void Afisare()
    {
        cout << "Dreptunghi: ";
        Forma::Afisare();
        cout << " latura mica: " << m_latura_mica << " latura mare: " << m_latura_mare << endl;
    }
    double Aria()
    {
        return m_latura_mica * m_latura_mare;
    }
};

class Patrat: public Forma
{
    double m_latura;
public:
    Patrat() {m_latura = 0;}
    Patrat(int inaltime, int latura): Forma(inaltime), m_latura(latura) {}
    double GetLatura() {return m_latura;}
    void Afisare()
    {
        cout << "Patrat: ";
        Forma::Afisare();
        std::cout << " latura: " << m_latura << std::endl;
    }
    void Citire()
    {
        Forma::Citire();
        cin >> m_latura;
    }
    double Aria()
    {
        return m_latura * m_latura;
    }
};

class Triunghi : public Forma
{
    double m_cateta_mica, m_cateta_mare;
public:
    Triunghi(): Forma(), m_cateta_mica(0), m_cateta_mare(0) {}
    Triunghi(double inaltime, double cateta_mica, double cateta_mare): Forma(inaltime), m_cateta_mica(cateta_mica), m_cateta_mare(cateta_mare) {}
    void Citire()
    {
        Forma::Citire();
        cin >> m_cateta_mica >> m_cateta_mare;
    }
    void Afisare()
    {
        cout << "Triunghi: ";
        Forma::Afisare();
        cout << " cateta mica: " << m_cateta_mica << " cateta mare: " << m_cateta_mare << endl;
    }
    double Aria()
    {
        return m_cateta_mica * m_cateta_mare / 2;
    }
};

Forma * citireForma()
{
    Forma *forma;

    int tipForma;
    cin >> tipForma;

    if(tipForma == 1)
    {
        //putem instantia un cerc nou direct in pointerul catre forma
        forma = new Cerc();
        //pentru ca citire este metoda virtuala in Forma, la runtime se va face citirea corecta (pentru Cerc)
        forma -> Citire();
    }
    else if(tipForma == 2)
    {
        forma = new Dreptunghi();
        forma -> Citire();
    }
    else if(tipForma == 3)
    {
        Patrat *patrat = new Patrat();
        patrat -> Citire();
        forma = patrat;
    }
    else if(tipForma == 4)
    {
        Triunghi *triunghi = new Triunghi();
        triunghi -> Citire();
        forma = triunghi;
    }

    return forma;
}

vector<Forma*> citesteCeleNFormeInitiale()
{
    int n;
    cin >> n;

    vector<Forma *> forme;

    for(int i=0; i<n; i++)
    {
        forme.push_back(citireForma());
    }

    return forme;
}

void meniuInteractiv()
{
    vector<Forma*> formeleBunicutei = citesteCeleNFormeInitiale();

    int comanda = 0;
    int comanda_stop = 6;

    while (comanda != comanda_stop)
    {
        cin >> comanda;

        if(comanda == 1)
        {
            Forma *forma = citireForma();
            formeleBunicutei.push_back(forma);
        }
        else if(comanda == 2)
        {
            int pozitia;
            cin >> pozitia;
            if(0 <= pozitia < formeleBunicutei.size())
            {
                delete formeleBunicutei[pozitia];
                formeleBunicutei.erase(formeleBunicutei.begin() + pozitia);
            }
        }
        else if(comanda == 3)
        {
            double sumaGem = 0, sumaFrisca = 0;
            for(int i=0; i < formeleBunicutei.size(); i++)
            {
                sumaGem += formeleBunicutei[i] -> CantitateGem();
                sumaFrisca += formeleBunicutei[i] -> CantitateFrisca();
            }
            cout << "Total gem: " << sumaGem << " Total frisca: " << sumaFrisca << endl;
        }
        else if(comanda == 4)
        {
            for(int i=0; i < formeleBunicutei.size(); i++) formeleBunicutei[i] -> Afisare();
            cout << endl;
        }
        else if(comanda == 5)
        {
            cout << "Numar cercuri in program: " << Cerc::GetNrCercuri() << endl;
        }
    }

    for(int i=0; i < formeleBunicutei.size(); i++) delete formeleBunicutei[i];
}

void demo()
{
    Forma *forma = new Cerc(1,2);
    //sa verific daca forma este cerc
    //daca da, sa ii afisez raza
    //vreau forma->GetRaza()
    if(Cerc *cerc = dynamic_cast<Cerc *>(forma))
    {
        cout << cerc -> GetRaza() << endl;
    }

    if(Patrat *patrat = dynamic_cast<Patrat *>(forma))
    {
        //forma nu este patrat, deci codul acesta nu se executa
        cout << patrat -> GetLatura();
    }
}

class DemoStaticVariable
{
public:
    DemoStaticVariable() {cout << "CI" << endl;}
    ~DemoStaticVariable() {cout << "D" << endl;}
};

int main() {
//    meniuInteractiv();
//    demo();

//memoria pentru variabilele statice persista pe toata viata programului
//obiectul nu se distruge la iesirea din if {}
    if(0 == 0)
    {
        static DemoStaticVariable obj;
    }

    cout << "Finalul programului" << endl;

    return 0;
}
