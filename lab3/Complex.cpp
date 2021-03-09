#include <cmath>
#include <iostream>

class Complex {
    double m_real;
    double m_imaginary;

public:
    Complex() : m_real(0), m_imaginary(0) {}
    Complex(double real) : m_real(real), m_imaginary(0) {}
    Complex(double real, double imaginary)
            : m_real(real), m_imaginary(imaginary) {
        // Nu mai este nevoie de atribuire pentru ca am folosit constructorii
        // membrilor mai sus
        //        m_real = real; m_imaginary = imaginary;
    }
    Complex(Complex &complex)
            : m_real(complex.m_real), m_imaginary(complex.m_imaginary) {}
    ~Complex() {}
    
    Complex& operator=(const Complex& complex)
    {
        m_real = complex.m_real;
        m_imaginary = complex.m_imaginary;
        return *this;
    }

    // Getteri
    double GetReal() { return m_real; }
    double GetImaginary() { return m_imaginary; }
    // Setteri
    void SetReal(double real) { m_real = real; }
    void SetImaginary(double imaginary) { m_imaginary = imaginary; }

    // modulul unui numar complex
    double Abs() { return sqrt(m_real * m_real + m_imaginary * m_imaginary); }

    Complex operator+(Complex complex) {
        Complex result(m_real + complex.m_real, m_imaginary + complex.m_imaginary);
        return result;
    }

    friend Complex operator*(Complex c1, Complex c2);

    friend Complex operator/(Complex c1, Complex c2);

    friend std::istream &operator>>(std::istream &in, Complex &complex) {
        in >> complex.m_real >> complex.m_imaginary;
        return in;
    }
    friend std::ostream &operator<<(std::ostream &out, Complex &complex) {
        if (complex.m_real != 0 && complex.m_imaginary != 0)
        {
            //afisare a+i*b sau a-i*b
            if (complex.m_imaginary < 0)
            {
                //afisare a-i*b
                out << complex.m_real << "-i*" << -complex.m_imaginary;
            }
            else
            {
                //afisare a+i*b
                out << complex.m_real << "+i*" << complex.m_imaginary;
            }
        }
        else if (complex.m_imaginary == 0)
        {
            out << complex.m_real;
        }
        else
        { // complex.m_real == 0
            if (complex.m_imaginary < 0) {
                out << "-i*" << -complex.m_imaginary;
            }
            else
                out << "i*" << complex.m_imaginary;
        }
        return out;
    }
};

Complex operator*(Complex c1, Complex c2) {
    // (a + bi)(c + di) = ac - bd + i(ad + bc)
    Complex result;
    result.m_real = c1.m_real * c2.m_real - c1.m_imaginary * c2.m_imaginary;
    result.m_imaginary = c1.m_real * c2.m_imaginary + c1.m_imaginary * c2.m_real;
    return result;
}

Complex operator/(Complex c1, Complex c2) {
    Complex result;
    // declaram un complex tmp ca fiind conjugatul
    Complex tmp(c2.m_real, -c2.m_imaginary);
    result = c1 * tmp;
    // nu este modulul la patrat
    double nu = (c2.m_real * c2.m_real + c2.m_imaginary * c2.m_imaginary);
    result.m_real /= nu;
    result.m_imaginary /= nu;

    return result;
}

Complex *readNComplexNumbers(int& n) {
    std::cout << "Number of complex numbers to read:" << std::endl;
    std::cin >> n;
    std::cout << "Write n complex numbers." << std::endl;
    Complex *numbers = new Complex[n];
    for (int i = 0; i < n; i++) {
        std::cin >> numbers[i];
    }

    std::cout << "You read the following " << n << " numbers:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << numbers[i] << std::endl;
    }
    return numbers;
}

// TODO: meniul interactiv
//TEMA: de completat cu optiuni

void demoPentruAfisareSiImpartire() {
    std::cout << "teste\n";
    //1+i*1
    Complex c1(1, 1);
    //1
    Complex c2(1, 0);
    //i*1
    Complex c3(0, 1);
    //-i*11
    Complex c7(0, -11);
    //-1+i*1
    Complex c4(-1, 1);
    //1-i*1
    Complex c5(1, -1);
    //-1-i*1;
    Complex c6(-1, -1);

    std::cout << c1 << "\n"
              << c2 << "\n"
              << c3 << "\n"
              << c7 << "\n"
              << c4 << "\n"
              << c5 << "\n"
              << c6 << "\n";
    Complex res;
    res = c1 / c4;
    std::cout << "c1 / c4 = " << res;
}

void DemoOperatorAtribuire() {
    Complex c1(1);
    Complex c2(5,7);
    c1 = c2;
    std::cout << c1;
}

void printMenuOptions() {
    std::cout << "1. Cititi, memorati si afisati n numere complexe." << std::endl;
    std::cout << "2. Rulati demo pentru afisare si impartire." << std::endl;
    std::cout << "3. Totatul numerelor memorate." << std::endl;
    std::cout << "4. Oprire." << std::endl;
    std::cout << std::endl;
}

void interactiveMenu() {
    std::cout << "Alegeti dintre urmatoarele optiuni: " << std::endl;
    printMenuOptions();
    int option = 0;
    int exit_option = 4;
    int nr = 0;
    Complex *numbers = nullptr;

    std:: cin >> option;
    while(option != exit_option) {
        if(option == 1) {
            //am modificat functia, ca nr sa fie parametru trimis prin referinta, deci actualizat si in exterior in urma citirii
            numbers = readNComplexNumbers(nr);
        }
        else if(option == 2) {
            demoPentruAfisareSiImpartire();
            std::cout << std::endl;
        }
        else if(option == 3) {
            Complex sum;
            for(int i=0; i<nr; i++) {
                sum = sum + numbers[i];
            }
            std::cout << sum;
        }
        //reafisam meniul
        std::cout << std::endl;
        printMenuOptions();
        //citim noua optiune
        std::cin >> option;
    }

    //eliberam memoria
    delete[] numbers;
}

int main() {
    //    double real, imaginary;
    //    std::cin >> real >> imaginary;
    //    Complex complex(real, imaginary);
    //    Complex complex;
    //    std::cin >> complex;
    //    std::cout << complex.GetReal() << " " << complex.GetImaginary() <<
    //    std::endl;
    //
    //    Complex complex2(complex);
    ////    std:: cout << complex2.Abs();
    //    Complex c3;
    //    c3 = complex + complex2;
    //    std::cout << c3.GetReal() << " " << c3.GetImaginary() << std::endl;
    //    Complex c4;
    //    c4 = complex * c3;
    //    std::cout << c4 <<std::endl;


    interactiveMenu();
    // DemoOperatorAtribuire();

    return 0;
}
