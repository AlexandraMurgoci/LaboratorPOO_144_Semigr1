#include <iostream>

using namespace std;

class Nod
{
    int info;
    Nod *next;
public:
    Nod ()
    {
        next = NULL;
    }
    Nod (int intreg)
    {
        info = intreg;
        next = NULL;
    }

    friend class Vector;

    int Getinfo(){return info;}
    Nod *Getnext(){return next;}
    void Setinfo(int aux){this -> info = aux;}
    void Setnext (Nod *aux){next = aux;}

    void actualizare (int intreg)
    {
        info = intreg;
    }
    void adauga (int intreg)
    {
        next = new Nod(intreg);
    }
};


class Vector
{
    Nod *p,*u;
    int n;
public:
    //constructori
    Vector (int valuare, int nr)
    {
        n = nr;
        p = new Nod;
        p -> info = valuare;
        u = p;
        int i;
        for(i=1;i<n;++i)
        {
            u -> next = new Nod;
            u = u -> next;
            u->info = valuare;
        }
    }
    Vector (): n(0){}
    Vector (int numar)
    {
        n = numar;
        int i;
        p = new Nod;
        p -> info = 0;
        u = p;
        for(i=1;i<n;++i)
        {
            u -> next = new Nod;
            u = u -> next;
            u->info = 0;
        }
    }
    Vector (int tablou[101], int numar)
    {
        n = numar;
        int i;
        p = new Nod;
        p -> info = tablou[0];
        u = p;
        for(i=1;i<n;++i)
        {
            u -> next = new Nod;
            u = u -> next;
            u->info = tablou[i];
        }
    }
    //constructor de copiere
    Vector (const Vector  &ve)
    {
        Nod *i;
        p = new Nod(ve.p -> Getinfo());
        u = p;
        i = ve.p -> next;
        while(i != NULL)
        {
            this -> adaugare(i -> Getinfo());
            i = i -> next;
        }
        n = ve.n;
    }
    //destructor
    ~Vector ()
    {
        n = 0;
        Nod *i,*j;
        i = p;
        j = i -> next;
        delete i;
        while(j!=NULL)
        {
            i = j;
            j = i -> next;
            delete i;
        }
    }
    //geteri, seteri
    int Getn(){return n;}
    Nod *Getp(){return p;}
    Nod *Getu(){return u;}
    void Setn(int numar){n = numar;}
    void Setp(Nod *aux){p = aux;}
    void Setu(Nod *aux){u = aux;}
    //operatori
    friend istream& operator>>(istream& in, Vector& ve)
    {
        in>>ve.n;
        int i,intreg;
        in>>intreg;
        ve.p = new Nod(intreg); //trebuie sa fac metode in clasa nod
        ve.u = ve.p;
        for(i=1;i<ve.n;++i)
        {
            in>>intreg;
            ve.adaugare(intreg);
        }
        return in;
    }
    friend ostream& operator<<(ostream& out, const Vector& ve)
    {
        Nod *i;
        i = ve.p;
        while(i!=NULL)
        {
            out<<i -> Getinfo()<<" ";
            i = i -> Getnext();
        }
        return out;
    }
Vector operator= (Vector ve);
    //metode
    void reactualizare(int numar, int nr);
    int suma ();
    void maxim(int &ma, int &poz);
    void sortare();
    void adaugare(int intreg);
    //operatori cerinte bonus
bool operator== (Vector ve)
{
    if(ve.n != n)
        return 0;
    else
    {
        Nod *i,*j;
        i = ve.p;
        j = p;
        while(i!=NULL)
        {
            if(i -> Getinfo() != j -> Getinfo())
                return 0;
            i = i -> next;
            j = j -> next;
        }
    }
    return 1;
}
bool operator!= (Vector ve)
{
    if(*this == ve)
        return 0;
    return 1;
}
void operator+()
{
    Nod *i;
    i = p;
    while(i != NULL)
    {
        i -> actualizare(i -> info + 1);
        i = i -> next;
    }
}
Vector operator+ (Vector ve)
{
    if(n == 0)
        return ve;
    if(ve.n == 0)
        return *this;
    Nod *j1,*j2,*j3;
    Vector rezultat;
    int nr,i;
    j1 = p;
    j2 = ve.p;
    rezultat.p = new Nod(j1 -> Getinfo() + j2 -> Getinfo());
    j1 = j1 -> next;
    j2 = j2 -> next;
    rezultat.u = rezultat.p;
    nr = min(n,ve.n);
    for(i = 1; i < nr; ++i)
    {
        rezultat.adaugare(j1 -> Getinfo() + j2 -> Getinfo());
        j1 = j1 -> next;
        j2 = j2 -> next;
    }
    if(j1 == NULL)
        j3 = j2;
    else
        j3 = j1;
    while(j3 != NULL)
    {
        rezultat.adaugare(j3 -> Getinfo());
        j3 = j3 -> next;
    }
    return rezultat;
}
void inmultirecuscalar (int x) //metoda auxiliara pentru operator-
{
    Nod *i;
    i = p;
    while(i != NULL)
    {
        i -> Setinfo((-1)*i -> Getinfo());
        i = i -> next;
    }
}
void operator-()
{
    Nod *i;
    i = p;
    while(i != NULL)
    {
        i -> actualizare(i -> info - 1);
        i = i -> next;
    }
}
Vector operator- (Vector ve)
{
    if(n == 0){
        ve.inmultirecuscalar(-1);
        return ve;
    }
    if(ve.n == 0)
        return *this;
    Vector rezultat;
    Nod *j1,*j2,*j3;
    int nr,i;
    j1 = p;
    j2 = ve.p;
    rezultat.p = new Nod(j1 -> Getinfo() - j2 -> Getinfo());
    j1 = j1 -> next;
    j2 = j2 -> next;
    rezultat.u = rezultat.p;
    nr = min(n,ve.n);
    for(i = 1; i < nr; ++i)
    {
        rezultat.adaugare(j1 -> Getinfo() - j2 -> Getinfo());
        j1 = j1 -> next;
        j2 = j2 -> next;
    }
    if(j1 == NULL)
        {j3 = j2;
        while(j3 != NULL)
    {
        rezultat.adaugare(-1*(j3 -> Getinfo()));
        j3 = j3 -> next;
    }
        }
    else{
        j3 = j1;
    while(j3 != NULL)
    {
        rezultat.adaugare(j3 -> Getinfo());
        j3 = j3 -> next;
    }
    }
    return rezultat;
}
bool operator! ()
{
    Nod *i;
    i = p;
    while(i != NULL)
    {
        if(i -> info != 0)
            return 0;
        i = i -> next;
    }
    return 1;
}
int operator[] (int index)
{
    Nod *i;
    int nr = 0;
    i = p;
    while(nr < index)
    {
        i = i -> next;
        ++nr;
    }
    return i -> info;
}
bool operator> (Vector ve)
{
    Vector aux;
    aux = *this - ve;
    int nr = 0;
    Nod *i;
    i = aux.p;
    while(i != NULL)
    {
        if(i -> info > 0)
            ++nr;
        i = i -> next;
    }
    if(nr > aux.n/2)
        return 1;
    else
        return 0;
}
// alnalog operatori <, <=, >=
};
Vector Vector::operator= (Vector ve)
{
    delete p;
    delete u;
    Nod *i;
        p = new Nod(ve.p -> Getinfo());
        u = p;
        i = ve.p -> next;
        while(i != NULL)
        {
            this -> adaugare(i -> Getinfo());
            i = i -> next;
        }
        n = ve.Getn();
        return *this;
};
inline void Vector::reactualizare (int numar, int nr)
{
    n = nr;
    int i;
    delete[] p;
    delete[] u;
    p = new Nod(numar);
    u = p;
    for(i=1;i<n;++i)
        this->adaugare(numar);
}
inline int Vector::suma ()
{
    int s=0;
    Nod *i;
    i = p;
    while(i!=NULL)
    {
        s += i -> Getinfo();
        i = i -> Getnext();
    }
    return s;
}
inline void Vector::maxim(int &ma, int &poz)
{
    Nod *i;
    int nr = 0;
    i = p;
    ma = -999999999;
    while(i != NULL)
        {
            if(i -> Getinfo() > ma)
            {
                ma = i -> Getinfo();
                poz = nr;
            }
            i = i -> Getnext();
            ++nr;
        }
}
inline void Vector::sortare()
{
    //o sortare de complexitate n^2
    Nod *i,*j;
    int intermediar;
    i = p;
    while(i!=NULL)
    {
        j = i -> Getnext();
        while(j!=NULL){
            if (i -> Getinfo() > j -> Getinfo())
            {
                intermediar = i -> Getinfo();
                i -> actualizare(j -> Getinfo());
                j -> actualizare(intermediar);
            }
            j = j -> Getnext();
        }
        i = i -> Getnext();
    }
}
inline void Vector::adaugare(int intreg)
{
    u -> adauga(intreg);
    u = u->next;
}

void citireNvectori(int numar, Vector ve[])
{
    int i;
    for(i=0;i<numar;++i)
    {
        cin>>ve[i];
    }
}
int citireindex(int N)
{
    int i;
    cin>>i;
    while(i<0||i>=N)
    {
        cout<<"Index invalid \n Alege index: ";
        cin>>i;
    }
    return i;
}
int main()
{
    int nr,i,choice,ok,numar,N,ma,poz,j;
    Vector aux,copie,ve[101];
    cin>>N;
    citireNvectori(N,ve);
    for(i=0;i<N;++i)
        cout<<ve[i]<<'\n';
    cout<<"MENU"<<'\n';
    cout<<" apasa 0: EXIT \n apasa 1: reactualizare \n apasa 2: suma \n apasa 3: maxim \n apasa 4: sortare \n ";
    cout<<"apasa 5: utilizeaza constructor de copiere \n apasa 6: pentru a aduna 2 vectori \n apasa 7: pentru a scadea 2 vectori \n apasa 8: afiseaza un elemen la alegere \n ";
    cout<<"apasa 9: compara doi vectori la alegere \n";
    ok = 1;
    while(ok){
    cout<<"Alege orice optiune: ";
    cin>>choice;
    if(choice > 9)
        cout<<"optiune invalida \n";
    switch(choice)
    {
    case 0:
        ok = 0;
        break;
    case 1:
        cout<<"index element = ";
        i = citireindex(N);
        cout<<"Valuare = ";
        cin>>numar;
        cout<<"Numarul elementelor = ";
        cin>>nr;
        ve[i].reactualizare(numar,nr);
        cout<<"acum ve["<<i<<"] = "<<ve[i]<<'\n';
        break;
    case 2:
        cout<<"Alege indexul vectorului al carui suma o vrei:";
        i = citireindex(N);
        cout<<"suma ceruta este: "<<ve[i].suma()<<'\n';
        break;
    case 3:
        cout<<"alegeti indexul vectorului: ";
        i = citireindex(N);
        ve[i].maxim(ma,poz);
        cout<<"maximul este: "<<ma<<'\n'<<"acesta se afla pe pozitia:"<<poz<<'\n';
        break;
    case 4:
        cout<<"Alege indexul vectorului de sortat: ";
        i = citireindex(N);
        ve[i].sortare();
        cout<<"Acum ve["<<i<<"] = "<<ve[i]<<'\n';
        break;
    case 5:
        cout<<"Alege indexul vectorului de copiat: ";
        i = citireindex(N);
        copie = ve[i];
        cout<< "copia vectorului ve["<<i<<"] se numeste copie iar aceste memoreaza valorile:"<<copie<<'\n';
        break;
    case 6:
        cout<<"Alege indexul primului vector: ";
        i = citireindex(N);
        cout<<"Alege indexul celui de al doilea vector: ";
        j = citireindex(N);
        cout << ve[i] + ve[j] << '\n';
        break;
    case 7:
        cout<<"Alege indexul primului vector: ";
        i = citireindex(N);
        cout<<"Alege indexul celui de al doilea vector: ";
        j = citireindex(N);
        cout << ve[i] - ve[j] << '\n';
        break;
    case 8:
        cout<<"Alege indexul vectorului: ";
        i = citireindex(N);
        cout<<"Alege indexul elementului din vectorul ales: ";
        j = citireindex(ve[i].Getn());
        cout<<"Elementul ales este ve["<<i<<"]["<<j<<"] = "<<ve[i][j]<<'\n';
        break;
    case 9:
        cout<<"Alege indexul primului vector: ";
        i = citireindex(N);
        cout<<"Alege indexul vectorului cu care vrei sa il compari: ";
        j = citireindex(N);
        if(ve[i] > ve[j])
            cout<< "ve[" <<i<<"] este mai mare decat ve["<<j<<"]"<<'\n';
        else
            cout<< "ve[" <<i<<"] este mai mic sau egal cu ve["<<j<<"]"<<'\n';
        break;
    }
    }
    return 0;
}
