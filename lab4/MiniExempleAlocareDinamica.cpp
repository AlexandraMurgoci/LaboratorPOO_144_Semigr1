#include <iostream>

class Node {
    int m_info;
    Node *m_next;

public:
    Node(int info)
    {
        m_info = info;
        m_next = nullptr;
    }

    void SetNext(Node *next)
    {
        m_next = next;
    }

    ~Node()
    {
        std::cout << "Destructor m_next cu id: " << m_info <<std::endl;
        //aici nu vrem neaparat sa facem delete[] m_next;
//        delete m_next;
    }
};

class Dynamic {
    int m_size;
    int *m_vector;

public:
    Dynamic(int size, int initial_value)
    {
        m_size = size;
        m_vector = new int[m_size];
        for(int i=0;i<m_size;i++) m_vector[i]=initial_value;
    }

    Dynamic(const Dynamic& aDynamic)
    {
        m_size = aDynamic.m_size;
        //ASA NU
//        m_vector = aDynamic.m_vector;
        m_vector = new int[m_size];
        for(int i=0;i<m_size;i++) m_vector[i]=aDynamic.m_vector[i];
    }

    Dynamic& operator=(const Dynamic& aDynamic)
    {
        m_size = aDynamic.m_size;
        //ASA NU
//        m_vector = aDynamic.m_vector;
        delete[] m_vector;
        m_vector = new int[m_size];
        for(int i=0;i<m_size;i++) m_vector[i]=aDynamic.m_vector[i];
        return *this;
    }

    ~Dynamic()
    {
        delete[] m_vector;
    }

    void Display()
    {
        for(int i=0;i<m_size;i++) std::cout << m_vector[i] << ' ';
    }

    bool ReplaceAt(int index, int value)
    {
        if(index >= m_size || index < 0) return false;
        m_vector[index] = value;
    }

    void SetVector(int *vector)
    {
        delete[] m_vector;
        m_vector = vector;
    }
};

void DemoDynamic()
{
    Dynamic d1(3,0);
    Dynamic d2(d1);

    d1.ReplaceAt(1,5);

    d1.Display();
    std::cout << std::endl;
    d2.Display();
}

class StaticVector {
    int m_size;
    int m_vector[100];

public:
    StaticVector(int size, int initialValue)
    {
        m_size = size;
        for(int i=0;i<m_size;i++) m_vector[i]=initialValue;
    }

    void Display()
    {
        for(int i=0;i<m_size;i++) std::cout << m_vector[i] << ' ';
    }

    bool ReplaceAt(int index, int value)
    {
        if(index >= m_size || index < 0) return false;
        m_vector[index] = value;
        return true;
    }
};

void DemoStaticVector()
{
    StaticVector v1(3, 0);
    StaticVector v2(v1);

    v1.ReplaceAt(1, 5);

    v1.Display();
    std::cout << std::endl;
    v2.Display();
}

void DemoDeleteNodes()
{
    //ce se intampla daca facem delete in destructor la Node ?
    Node *node1 = new Node(1);
    Node node2(2);
    Node node3(3);

    node1->SetNext(&node2);
    node2.SetNext(&node3);

    delete node1;
    std::cout << "Terminare demo.";
}

void DemoRand() {
    srand(time(NULL));
    std::cout << rand() % 10 + 1 << std::endl;
    std::cout << rand() % 10 + 1 << std::endl;
    std::cout << rand() % 10 + 1 << std::endl;
}

//mini exemplu forward declaration
//cum putem accesa metode/instante de la o clasa declarata dupa
class B;

class A {
    B *m;
public:
    void metoda();
};

class B {
    A *m;
public:
    void metoda(){}
};

void A::metoda() {
    m->metoda();
}

int main() {
//    DemoDynamic();
//    DemoStaticVector();
//    DemoDeleteNodes();
//    DemoRand();
    return 0;
}
