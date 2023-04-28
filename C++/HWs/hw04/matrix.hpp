/*** PPC - HW03 ***/
/* Tento soubor se odevzdava, muzete ho upravit, pridat funkce. Funkce neumazavejte, nemente jejich rozhrani. */

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

// Definici vyjimek neupravujte, je potreba pro spravne vyhodnoceni

// Vyjimka pri spatnych rozmerech matice pro danou operaci:
struct matrix_bad_sizes: public std::exception 
    {const char * what () const throw (){return "matrix_bad_sizes";}};
// Vyjimka pri zadani negativniho rozmeru
struct matrix_negative_size: public std::exception 
    {const char * what () const throw (){return "matrix_negative_size";}};
// Vyjimka pri chybe nacteni rozmeru matice
struct matrix_in_bad_header: public std::exception 
    {const char * what () const throw (){return "matrix_in_bad_header";}}; 
// Vyjimka pri chybe nacteni prvku matice
struct matrix_in_bad_body: public std::exception 
    {const char * what () const throw (){return "matrix_in_bad_body";}};
// Vyjimka pri otevirani souboru matice
struct cannot_open_file: public std::exception 
    {const char * what () const throw (){return "cannot_open_file";}};

using value = int;

struct Matrix{
    int nrows; // L1 Pocet radku
    int ncols; // L1 Pocet sloupcu
    std::vector<value> data; // L1 vhodne uchovana data matice
    // Konstruktory+ destruktory:
    Matrix(int rows, int cols);     // L1 Vytvori matici naplnenou nulami o prislusnych rozmerech
    Matrix(int rowscols=0);     // L1 Vytvori ctvercovou matici naplnenou nulami o prislusnych rozmerech
    Matrix(const Matrix &m);        // L1 Kopirujici konstruktor

    Matrix(const std::vector<value> &v); // L3 Vytvori diagonalni (ctvercovou) matici. Prvky na diagonale jsou z vectoru, ostatni nulove.

    ~Matrix(); // L1 Destruktor

    // Funkce tridy Matrix::
    void zeros();           // L1 Nastavi vsechny prvky matice na 0
    void uniform(value element); // L1 Nastavi vsechny prvky matice na hodnotu element
    void eye();             // L1 Vytvori matici identity. Pokkud neni ctvercova, doplni se nulami.
    void bias(value b);     // L1 Pricte ke kazdemu prvku matice hodnotu b

    void scale(value s);    // L2 Nasobi kazdy prvek matice hodnotou s
    void transpose();       // L2 Transponuje matici

    void changedim(int rows, int cols); // L3 Zmeni rozmery matice. Korektne ji orizne nebo popripade doplni nulami.
    
    // Operatory tridy Matrix::
    bool operator == (const Matrix & m) ;   // L1 Porovnani dvou matic - musi sedet rozmery i vsechny prvky
    Matrix & operator=(const Matrix &m);    // L1 Operator prirazeni cele matice
    

    value operator () (int row, int col) const; // L1 Vraci prvek na danych indexech
    value & operator () (int row, int col);     // L1 Pristup k prvku na danych indexech
    // pri prekroceni rozmeru matice, nebo zapornem indexu vyvolaji vyse zminene operatoru jednu z techto vyjimek:
    // std::out_of_range("Row index is out of range");
    // std::out_of_range("Column index is out of range");
    // Pokud jsou oba indexy spatne, je vyhozena prvni z vyjimek. 

    std::vector<value> operator () (void) const; //L3 Vrati vektor prvku na diagonale matice
};

// L1 Vypis matice do terminalu.
std::ostream & operator << (std::ostream & os, const Matrix & m);
// Sirka pole pro hodnotu je 6 znaku, zarovnani vpravo, oddeleni mezerami. Na konci matice je newline. 
// Pokud matice neobsahuje zadny prvek, vypise se pouze std::endl;

// L1 nacteni matice ze souboru.
void loadMatrixFile(Matrix &m, std::string fname); 
// Na prvnim radku souboru jsou rozmery matice (pocet radku a pocet sloupcu, oddelene mezerami).
// Pokud je spatne tento radek, je vyvolana vyjimka "matrix_in_bad_header".
// Na dalsich radcich jsou prvky matice oddelene mezerami. 
// Pokud dojde k chybe, nebo nesedi rozmery, je vyvolana vyjimka "matrix_in_bad_body".
// Pokud nepujde otevrit soubor, je vyvolana vyjimka "cannot_open_file"

// L1 Scitani matic.
Matrix operator + (const Matrix & lhs, const Matrix & rhs);
// L1 Pricteni skalaru k cele matici.
Matrix operator + (const value & lhs, const Matrix & rhs);
Matrix operator + (const Matrix & lhs, const value & rhs);

// L1 Odecitani matic.
Matrix operator - (const Matrix & lhs, const Matrix & rhs);
// L1 Odecitani skalaru a matic.
Matrix operator - (const value & lhs, const Matrix & rhs);
Matrix operator - (const Matrix & lhs, const value & rhs);

// L2 Maticovy soucin.
Matrix operator * (const Matrix & lhs, const Matrix & rhs);
Matrix operator * (const value & lhs, const Matrix & rhs);
// L2 nasobeni matice skalarem
Matrix operator * (const Matrix & lhs, const value & rhs);

// L2 Hadamarduv soucin - prvek po prvku (ekvivalent .* z Matlabu).
Matrix hadamard (const Matrix & lhs, const Matrix & rhs);

// L2 Kladna mocnina ctvercove matice: power(A, 3) je ekvivalent A*A*A. Nulta mocnina je jednotkova matice. 
Matrix power (const Matrix & m, unsigned int pow);

// L3 Slouceni matic horizontalne (ekvivalent [lhs, rhs] z Matlabu).
Matrix horzcat (const Matrix & lhs, const Matrix & rhs);

// L3 Slouceni matic vertikalne (ekvivalent [top; bot] z Matlabu). 
Matrix vertcat (const Matrix & top, const Matrix & bot);

// L3 Diagonalni skladani matic. 
// Vstupy musi byt ctvercove matice nebo skalary (chovaji se jako matice 1x1), zbytek doplnen nulami.
Matrix blkdiag (const Matrix & lhs, const Matrix & rhs);
Matrix blkdiag (const value & lhs, const Matrix & rhs);
Matrix blkdiag (const Matrix & lhs, const value & rhs);
Matrix blkdiag (const value & lhs, const value & rhs);

// L3 Kroneckeruv soucin matic dle definice: https://mathworld.wolfram.com/KroneckerProduct.html 
Matrix kronecker (const Matrix & lhs, const Matrix & rhs);
