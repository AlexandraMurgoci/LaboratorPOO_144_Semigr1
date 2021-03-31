#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Forma {
protected:
  double m_inaltime;

public:
  Forma() : m_inaltime(0) {
    //        std::cout << "CI Forma fara param" << std::endl;
  }
  Forma(double inaltime) : m_inaltime(inaltime) {
    //        std::cout << "CI Forma cu inaltimea" << inaltime << " " <<
    //        std::endl;
  }
  virtual ~Forma() {}

  double GetInaltime() { return m_inaltime; }

  // facem virtual ca la runtime referinta/pointerul catre baza care contine
  // derivata sa apeleze metoda suprascrisa din derivata
  virtual void Afisare() { std::cout << "inaltimea " << m_inaltime; }

  virtual void Citire() { cin >> m_inaltime; }

  // metoda pura => clasa devine abstracta
  // un obiect Forma nu mai poate fi instantiat
  virtual double AriaBaza() = 0;

  double Volum() { return m_inaltime * AriaBaza(); }

  virtual double Suprafata() = 0;

  double CantitateGem() { return 2 * Volum(); }

  double CantitateFrisca() { return Suprafata(); }
};

class Cerc : public Forma {
  double m_raza;

public:
  Cerc() : m_raza(0) {}
  Cerc(double inaltime, double raza) : Forma(inaltime), m_raza(raza) {}
  double GetRaza() { return m_raza; }

  void Afisare() {
    cout << "Cerc: ";
    Forma::Afisare();
    std::cout << " raza: " << m_raza << std::endl;
  }

  void Citire() {
    Forma::Citire();
    cin >> m_raza;
  }

  double AriaBaza() { return M_PI * m_raza * m_raza; }

  double Suprafata() { return 2 * M_PI * m_raza * (m_raza + m_inaltime); };
};

class Dreptunghi : public Forma {
  double m_latura_mica;
  double m_latura_mare;

public:
  Dreptunghi() : Forma(0), m_latura_mica(0), m_latura_mare(0) {}
  Dreptunghi(double inaltime, double latura_mica, double latura_mare)
      : Forma(inaltime), m_latura_mare(latura_mare),
        m_latura_mica(latura_mica) {}
  void Citire() {
    Forma::Citire();
    cin >> m_latura_mica >> m_latura_mare;
  }
  void Afisare() {
    cout << "Dreptunghi: ";
    Forma::Afisare();
    cout << " latura mica: " << m_latura_mica
         << " latura mare: " << m_latura_mare << endl;
  }
  double AriaBaza() { return m_latura_mica * m_latura_mare; }

  double Suprafata() {
    return 2 * (AriaBaza() + m_inaltime * (m_latura_mare + m_latura_mica));
  };
};

class Patrat : public Forma {
  double m_latura;

public:
  Patrat() { m_latura = 0; }
  Patrat(int inaltime, int latura) : Forma(inaltime), m_latura(latura) {}
  double GetLatura() { return m_latura; }
  void Afisare() {
    cout << "Patrat: ";
    Forma::Afisare();
    std::cout << " latura: " << m_latura << std::endl;
  }
  void Citire() {
    Forma::Citire();
    cin >> m_latura;
  }
  double AriaBaza() { return m_latura * m_latura; }

  double Suprafata() { return 2 * AriaBaza() + 4 * m_latura * m_inaltime; };
};

class Triunghi : public Forma {
  double m_cateta_mica, m_cateta_mare;

public:
  Triunghi() : Forma(), m_cateta_mica(0), m_cateta_mare(0) {}
  Triunghi(double inaltime, double cateta_mica, double cateta_mare)
      : Forma(inaltime), m_cateta_mica(cateta_mica),
        m_cateta_mare(cateta_mare) {}
  void Citire() {
    Forma::Citire();
    cin >> m_cateta_mica >> m_cateta_mare;
  }
  void Afisare() {
    cout << "Triunghi: ";
    Forma::Afisare();
    cout << " cateta mica: " << m_cateta_mica
         << " cateta mare: " << m_cateta_mare << endl;
  }
  double AriaBaza() { return m_cateta_mica * m_cateta_mare / 2; }

  double Suprafata() {
    double ipotenuza =
        sqrt(m_cateta_mare * m_cateta_mare + m_cateta_mica * m_cateta_mica);
    return 2 * AriaBaza() +
           m_inaltime * (m_cateta_mare + m_cateta_mica + ipotenuza);
  }
};

Forma *citireForma() {
  Forma *forma;

  int tipForma;
  cin >> tipForma;

  if (tipForma == 1) {
    // putem instantia un cerc nou direct in pointerul catre forma
    forma = new Cerc();
    // pentru ca citire este metoda virtuala in Forma, la runtime se va face
    // citirea corecta (pentru Cerc)
    forma->Citire();
  } else if (tipForma == 2) {
    forma = new Dreptunghi();
    forma->Citire();
  } else if (tipForma == 3) {
    Patrat *patrat = new Patrat();
    patrat->Citire();
    forma = patrat;
  } else if (tipForma == 4) {
    Triunghi *triunghi = new Triunghi();
    triunghi->Citire();
    forma = triunghi;
  }

  return forma;
}

vector<Forma *> citesteCeleNFormeInitiale() {
  int n;
  cin >> n;

  vector<Forma *> forme;

  for (int i = 0; i < n; i++) {
    forme.push_back(citireForma());
  }

  return forme;
}

void meniuInteractiv() {
  vector<Forma *> formeleBunicutei = citesteCeleNFormeInitiale();

  int comanda = 0;
  int comanda_stop = 5;

  while (comanda != comanda_stop) {
    cin >> comanda;

    if (comanda == 1) {
      Forma *forma = citireForma();
      formeleBunicutei.push_back(forma);
    } else if (comanda == 2) {
      int pozitia;
      cin >> pozitia;
      if (0 <= pozitia < formeleBunicutei.size()) {
        delete formeleBunicutei[pozitia];
        formeleBunicutei.erase(formeleBunicutei.begin() + pozitia);
      }
    } else if (comanda == 3) {
      double sumaGem = 0, sumaFrisca = 0;
      for (int i = 0; i < formeleBunicutei.size(); i++) {
        sumaGem += formeleBunicutei[i]->CantitateGem();
        sumaFrisca += formeleBunicutei[i]->CantitateFrisca();
      }
      cout << "Total gem: " << sumaGem << " Total frisca: " << sumaFrisca
           << endl;
    } else if (comanda == 4) {
      for (int i = 0; i < formeleBunicutei.size(); i++)
        formeleBunicutei[i]->Afisare();
      cout << endl;
    }
  }

  for (int i = 0; i < formeleBunicutei.size(); i++)
    delete formeleBunicutei[i];
}

void demo() {
  Forma *forma = new Cerc(1, 2);
  // sa verific daca forma este cerc
  // daca da, sa ii afisez raza
  // vreau forma->GetRaza()
  if (Cerc *cerc = dynamic_cast<Cerc *>(forma)) {
    cout << cerc->GetRaza() << endl;
  }

  if (Patrat *patrat = dynamic_cast<Patrat *>(forma)) {
    // forma nu este patrat, deci codul acesta nu se executa
    cout << patrat->GetLatura();
  }
}

int main() {
  //    meniuInteractiv();
  demo();

  return 0;
}
