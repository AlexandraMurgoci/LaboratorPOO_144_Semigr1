#include <iostream>
#include <cstring>
using namespace std;

template <class T>
T GetMax(T a, T b)
{
    return (a > b) ? a : b;
}

class A
{
    int m_x;
public:
    A(int x): m_x(x) {}
    virtual int GetX() const {return m_x;}
    virtual ~A() {}
    A& operator=(const A& a)
    {
        //conditie necesara daca am memorie dinamica la care trebuie sa dau delete inainte sa o realoc
        if(this != &a) {
            m_x = a.m_x;
        }
        return *this;
    }

    friend istream &operator>> (istream& in, A& a);
};

istream &operator>> (istream& in, A& a)
{
    in >> a.m_x;
    return in;
}

class B: public A {
    int m_y;
public:
    B(int x, int y): A(x), m_y(y) {}
    int GetX() const {return A::GetX() + 5;}
    void Afisare() {cout << A::GetX() << " " << m_y;}

    friend istream &operator>> (istream& in, B& b);
};

//cerinta: utilizare in operator>> la derivate operatorul >> din baza
istream &operator>> (istream& in, B& b)
{
    in >> dynamic_cast<A&>(b);
    in >> b.m_y;
    return in;
}

ostream &operator<<(ostream& out, const A& a)
{
    out << a.GetX();
    return out;
}

bool operator>(const A& a1, const A& a2)
{
    return a1.GetX() > a2.GetX();
}

template <class T, class R>
bool operator==(const T& obj1, const R& obj2)
{
    return false;
}

template <class T>
T afiseaza(const T& obj) {
    cout << "Afisare din template: " << obj;
    return obj;
}

string afiseaza(string c) {
    cout << "x" + c;
    return c;
}

A afiseaza(const A& obj) {
    cout << "Afisare din functia pentru A: " << obj;
    return obj;
}

template <class T>
class Vector
{
    T* m_vector;
    int m_size;
};

//-------------------------------------- *********
//de lamurit

template <class T> T maxim(T t1, T t2){
    cout<<"template: ";
    if (t1 > t2)
        return t1;
    else
        return t2;
}

//se poate scrie doar odata si pentru const si pentru fara const ?
template <>const char* maxim(const char* t1, const char* t2)
{ cout<<"const *: ";
    if (strcmp(t1, t2) > 0)
        return t1;
    else
        return t2;
}
char* maxim( char* t1, char* t2)
{ cout<< "char *: ";
    if (strcmp(t1, t2) > 0)
        return t1;
    else
        return t2;
}


int main() {
    // -----------------------
    // demo de la intrebare
//    char v1[10]="Andra", v2[10]="Ana";
//    cout << maxim(3, 5)<<endl;
//    cout << maxim ('a', 'z')<<endl;
//    cout << maxim("Ana", "Andra")<<endl;
//    cout<<maxim (v1,v2)<<endl;
//    cout<<maxim(v1,"Ana");
    // -----------------------

//    int x = 5, y = 10;
//    cout << GetMax(x,y) << endl;
//    double r = 2.5, t = 3.7;
//    cout << GetMax(r,t) << endl;
//    A a1(5), a2(10);
//    cout << GetMax(a1,a2);
//    string s("abc");
//    afiseaza(s);
//    B b(5);
//    afiseaza(b);
//    A a(5);
//    a=a;

    B b(0,0);
    cin >> b;
    b.Afisare();
    return 0;
}
