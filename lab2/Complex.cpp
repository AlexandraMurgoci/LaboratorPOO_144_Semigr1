#include <iostream>
#include <cmath>
using namespace std;
class Complex
{
    double m_real;
    double m_imaginary;
public:
    Complex(): m_real(0), m_imaginary(0){}
    Complex(double real): m_real(real), m_imaginary(0) {}
    Complex(double real, double imaginary): m_real(real), m_imaginary(imaginary)
    {
        //Nu mai este nevoie de atribuire pentru ca am folosit constructorii membrilor mai sus
//        m_real = real; m_imaginary = imaginary;
    }
    Complex(Complex &complex): m_real(complex.m_real), m_imaginary(complex.m_imaginary) {}
    ~Complex(){}

    //Getteri
    double GetReal() {return m_real;}
    double GetImaginary() {return m_imaginary;}
    //Setteri
    void SetReal(double real) {m_real = real;}
    void SetImaginary(double imaginary) {m_imaginary = imaginary;}

    //modulul unui numar complex
    double Abs()
    {
        return sqrt(m_real * m_real + m_imaginary * m_imaginary);
    }

    Complex operator+ (Complex complex)
    {
        Complex result(m_real + complex.m_real, m_imaginary + complex.m_imaginary);
        return result;
    }
    Complex operator /(Complex c){
        double real = c.GetReal();
        double imaginar = c.GetImaginary();
        double numitor_rationalizat = real*real+imaginar*imaginar;

        c.SetImaginary(-c.GetImaginary());
        double numarator_rationalizat_real=c.GetReal() * m_real - c.GetImaginary() * m_imaginary;
        double numaratot_rationalizat_imaginar = c.GetReal() * m_imaginary + c.GetImaginary() * m_real;

        Complex result(numarator_rationalizat_real/numitor_rationalizat,numaratot_rationalizat_imaginar/numitor_rationalizat);
        return result;
    }
    friend Complex operator* (Complex c1, Complex c2);



    friend std::istream& operator>>(std::istream& in, Complex& complex)
    {
        in >> complex.m_real >> complex.m_imaginary;
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out, Complex& complex)
    {
        if(complex.m_real==0 && complex.m_imaginary==0){
            out<<0<<" ";
        }
        else if(complex.m_real==0 && complex.m_imaginary!=0){
            out<<complex.m_imaginary<<"i ";
        }
        else if(complex.m_real!=0 && complex.m_imaginary==0){
            out<<complex.m_real<<" ";
        }
        else{
            out << complex.m_real << " " << complex.m_imaginary<<"i ";
        }
        return out;
    }
};

Complex operator* (Complex c1, Complex c2)
{
    // (a + bi)(c + di) = ac - bd + i(ad + bc)
    Complex result;
    result.m_real = c1.m_real * c2.m_real - c1.m_imaginary * c2.m_imaginary;
    result.m_imaginary = c1.m_real * c2.m_imaginary + c1.m_imaginary * c2.m_real;
    return result;
}

//TODO: citim n obiecte, memoram si afisam

//TODO: meniul interactiv

int main() {
//    double real, imaginary;
//    std::cin >> real >> imaginary;
//    Complex complex(real, imaginary);
    Complex c(2,1);
    Complex c2(2,0);
    Complex c3;
    cout<<c;
    c3=c/c2;
    cout<<c3;

    return 0;
}

