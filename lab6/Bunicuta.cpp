#include <iostream>

class Baza {
    int m_x;
public:
    Baza(int x): m_x(x)
    {
        std::cout << "CI Baza cu x  " << x << std::endl;
    }
    ~Baza()
    {
        std::cout << "D Baza" << std::endl;
    }
};

class Deriv1: public Baza {
    int m_y;
public:
    Deriv1(int x, int y): Baza(x), m_y(y)
    {
        std::cout << "CI Deriv 1 cu x si y " << x << " " << y << std::endl;
    }
    ~Deriv1()
    {
        std::cout << "D Deriv1" << std::endl;
    }
};

class AltaBaza {
    char m_c;
public:
    AltaBaza(char c): m_c(c){}
};

class Deriv2: public Deriv1, AltaBaza
{
    int m_z;
public:
    Deriv2(int z): Deriv1(0,0), m_z(z), AltaBaza('x')
    {
        std::cout << "CI Deriv 2" << std::endl;
    }

    ~Deriv2()
    {
        std::cout << "D Deriv2" << std::endl;
    }
};


//-------------------------------------------------------------

class Forma
{
protected:
    double m_inaltime;
public:
    Forma(): m_inaltime(0)
    {
        std::cout << "CI Forma fara param" << std::endl;
    }
    Forma(double inaltime): m_inaltime(inaltime)
    {
        std::cout << "CI Forma cu inaltimea" << inaltime << " " << std::endl;
    }

    double GetInaltime() {return m_inaltime;}

    //facem virtual ca la runtime referinta/pointerul catre baza care contine derivata sa apeleze metoda suprascrisa din derivata
    virtual void Afisare()
    {
        std::cout << "Forma: inaltimea " << m_inaltime << std::endl;
    }
};

class Cerc: public Forma
{
    double m_raza;
public:
    Cerc():m_raza(0) {}
    Cerc(double inaltime, double raza): Forma(inaltime), m_raza(raza){}
    double GetRaza(){return m_raza;}

    void Afisare()
    {
        Forma::Afisare();
        std::cout << "Cerc: raza " << m_raza << std::endl;
    }
};

class Dreptunghi: public Forma
{
    double m_latura_mica;
    double m_latura_mare;
public:
    Dreptunghi(double inaltime, double latura_mica, double latura_mare):Forma(inaltime), m_latura_mare(latura_mare), m_latura_mica(latura_mica) {}
};

int main() {
//    Deriv2 d(3);

    Cerc cerc(1,2);
//    std::cout << cerc.GetRaza() << " " << cerc.GetInaltime();
//    cerc.Afisare();

    Forma *forma = new Cerc(5,6);
    forma -> Afisare();

    Forma &forma1 = cerc;
    forma1.Afisare();

    Forma **formeleBunicutei = new Forma*[100];
    formeleBunicutei[0] = new Cerc(1,2);
    formeleBunicutei[1] = new Dreptunghi(2,4,5);
    return 0;
}
