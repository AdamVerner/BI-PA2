// #define __PROGTEST__
#ifndef __PROGTEST__

#include <cassert>

#include <iostream>
#include <sstream>
#include <cstring>

// using namespace std;

#endif /* __PROGTEST__ */

class CTransaction;

class CAccount;

class CBank;

const int DEFAULT_ALLOC_SIZE = 20;

class CTransaction {
public:
    CTransaction() {
     std::cout << "this shouldne be used wtf" << std::endl;
    };

    enum TransactionType {
        to = 1, from = 3
    };

    CTransaction (const CTransaction & other){
        amount = other.amount;
        type = other.type;

        sign = new char[std::strlen(other.sign) + 1];
        strcpy(sign, other.sign);

        accountID = new char[std::strlen(other.accountID) + 1];
        std::strcpy(accountID, other.accountID);
    }

    CTransaction(unsigned int amount, const char *sign, TransactionType type, const char * accountID) {
        this->amount = amount;
        this->type = type;

        this->sign = new char[std::strlen(sign) + 1];
        strcpy(this->sign, sign);

        this->accountID = new char[std::strlen(accountID) + 1];
        std::strcpy(this->accountID, accountID);

    }

    ~CTransaction(){
        delete [] sign;
        delete [] accountID;
    }

    friend std::ostream &operator<<(std::ostream &os, const CTransaction &obj) {
        if (obj.type == to) os << " - " << obj.amount << ", to: ";
        else os << " + " << obj.amount << ", from: ";
        os << obj.accountID << ", sign: " << obj.sign;
        return os;
    }

private:
    unsigned int amount = -1;
    char * sign;
    TransactionType type = to;
    char * accountID;
};


class CAccount {
public:

    /* Default constructor */
    // TODO should never be used IMHO
    CAccount(){
        transactions_used = 0;
        transactions = new CTransaction * [transactions_alloc = 10]; // array of pointers
    }

    /* Copy constructor*/
    CAccount(const CAccount & other) {
        currentBalance = other.currentBalance;
        initialBalance = other.initialBalance;
        transactions_used = other.transactions_used;

        ID = new char[std::strlen(other.ID) + 1];
        std::strcpy(ID, other.ID);

        transactions = new CTransaction * [transactions_alloc = other.transactions_alloc];

        for (size_t i = 0; i < transactions_used; i++)
            transactions[i] = new CTransaction(*other.transactions[i]);

    }

    /* Initialization Constructor*/
    CAccount(const char *ID, int balance) {
        transactions = new CTransaction * [transactions_alloc = DEFAULT_ALLOC_SIZE];
        transactions_used = 0;

        this->ID = new char[std::strlen(ID) + 1];
        std::strcpy(this->ID, ID);

        initialBalance = balance;
        currentBalance = balance;
    }

    ~CAccount(){
        for (size_t i = 0; i < transactions_used; i++)
            delete transactions[i];  // delete structures pointed to by array
        delete [] transactions; // delete array of pointers

        delete [] ID;
    }

    int Balance() { return currentBalance; }

    void Trim(){
        for (size_t i = 0; i < transactions_used; i++)
            delete transactions[i];  // delete structures pointed to by array
        delete [] transactions; // delete array of pointers

        transactions_used = 0;
        transactions = new CTransaction * [transactions_alloc = DEFAULT_ALLOC_SIZE];

        this->initialBalance = this->currentBalance;
    }

    void AddTransaction(unsigned int amount, const char *sign, CTransaction::TransactionType type, const char * otherID) {

        if (transactions_used >= transactions_alloc) {

            CTransaction ** old = transactions;
            transactions = new CTransaction * [transactions_alloc *= 2];

            for (std::size_t i = 0; i < transactions_used; i++)
                transactions[i] = old[i];

            delete[] old;
        }

        transactions[transactions_used++] = new CTransaction(amount, sign, type, otherID);
    }

    friend std::ostream &operator<<(std::ostream &os, const CAccount &obj) {
        os << obj.ID << ":" << std::endl;
        os << "   " << obj.initialBalance << std::endl;

        for (size_t i = 0; i < obj.transactions_used; i++) {
            os << *obj.transactions[i] << std::endl;
        }
        os << " = " << obj.currentBalance << std::endl;
        return os;
    }

    char * ID;
    int currentBalance = 0;
    int initialBalance = 0;

    CTransaction ** transactions;
    std::size_t transactions_used;
    std::size_t transactions_alloc;

};


class CBank {
public:

    CBank(){
        accounts_used = 0;
        accounts = new CAccount * [accounts_allocated = DEFAULT_ALLOC_SIZE] ;
    }

    CBank( const CBank & other){
        // deep copy
        accounts_used = other.accounts_used;
        accounts = new CAccount * [accounts_allocated = other.accounts_allocated];

        for (size_t i = 0; i < accounts_used; i++)
            accounts[i] = new CAccount(*other.accounts[i]);
    }

    ~CBank (){
        for (size_t i = 0; i < accounts_used; i++)
            delete accounts[i];  // delete structures pointed to by array
        delete [] accounts; // delete array of pointers

        accounts_allocated = 0;
        accounts_used = 0;
    }

    CBank & operator= (const CBank & other){

        for (size_t i = 0; i < accounts_used; i++)
            delete accounts[i];  // delete structures pointed to by array
        delete [] accounts; // delete array of pointers

        accounts_allocated = 0;
        accounts_used = 0;

        if (this != &other){
            accounts_used = other.accounts_used;
            accounts = new CAccount * [accounts_allocated = other.accounts_allocated];

            for (size_t i = 0; i < accounts_used; i++)
                accounts[i] = new CAccount(*other.accounts[i]);
        }
        return *this;
    }

    bool NewAccount(const char *accID, int initialBalance) {

        // Verify uniqueness of new account
        for( size_t i = 0; i < accounts_used; i++){
            if ( !strcmp(accounts[i]->ID, accID) ) return false;
        }

        if (accounts_used >= accounts_allocated) {

            CAccount ** old = accounts;
            accounts = new CAccount * [accounts_allocated *= 2];

            for (std::size_t i = 0; i < accounts_used; i++)
                accounts[i] = old[i];

            delete[] old;
        }

        accounts[accounts_used++] = new CAccount(accID, initialBalance);
        return true;
    }

    bool Transaction(const char *debAccID, const char *credAccID, unsigned int amount, const char *signature) {

        CAccount * debit = nullptr;
        CAccount * credit = nullptr;

        for( size_t i = 0; i < accounts_used; i++){
            if ( ! strcmp( accounts[i]->ID, debAccID ) ) debit = accounts[i];
            if ( ! strcmp( accounts[i]->ID, credAccID ) ) credit = accounts[i];
        }

        if (!debit || !credit || debit == credit)  // Neither null nor same
            return false;

        debit->AddTransaction(amount, signature, CTransaction:: to, credit->ID);
        credit->AddTransaction(amount, signature, CTransaction:: from, debit->ID);

        debit->currentBalance -= amount;
        credit->currentBalance += amount;

        return true;
    }

    bool TrimAccount(const char *accID) {
        for (size_t i = 0; i < accounts_used; i++) {
            if (!strcmp( accounts[i]->ID, accID )) {
                accounts[i]->Trim();
                return true;
            }
        }
        return false;
    }

    CAccount Account(const char * ID){
        for( size_t i = 0; i < accounts_used; i++) {
            if ( !strcmp( accounts[i]->ID, ID ) ) return *accounts[i];
        }
        throw std::exception();
    }

    CAccount ** accounts = nullptr;
    std::size_t accounts_used;
    std::size_t accounts_allocated;

};


#ifndef __PROGTEST__
int main ( void )
{

    std::ostringstream os;
    char accCpy[100], debCpy[100], credCpy[100], signCpy[100];
    CBank x0;
    assert ( x0 . NewAccount ( "123456", 1000 ) );
    assert ( x0 . NewAccount ( "987654", -500 ) );
    assert ( x0 . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" ) );
    assert ( x0 . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" ) );
    assert ( x0 . NewAccount ( "111111", 5000 ) );
    assert ( x0 . Transaction ( "111111", "987654", 290, "Okh6e+8rAiuT5=" ) );
    assert ( x0 . Account ( "123456" ). Balance ( ) ==  -2190 );
    assert ( x0 . Account ( "987654" ). Balance ( ) ==  2980 );
    assert ( x0 . Account ( "111111" ). Balance ( ) ==  4710 );
    os . str ( "" );
    os << x0 . Account ( "123456" );
    assert ( ! strcmp ( os . str () . c_str (), "123456:\n   1000\n - 300, to: 987654, sign: XAbG5uKz6E=\n - 2890, to: 987654, sign: AbG5uKz6E=\n = -2190\n" ) );
    os . str ( "" );
    os << x0 . Account ( "987654" );
    assert ( ! strcmp ( os . str () . c_str (), "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 290, from: 111111, sign: Okh6e+8rAiuT5=\n = 2980\n" ) );
    os . str ( "" );
    os << x0 . Account ( "111111" );
    assert ( ! strcmp ( os . str () . c_str (), "111111:\n   5000\n - 290, to: 987654, sign: Okh6e+8rAiuT5=\n = 4710\n" ) );
    assert ( x0 . TrimAccount ( "987654" ) );
    assert ( x0 . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" ) );
    os . str ( "" );
    os << x0 . Account ( "987654" );
    assert ( ! strcmp ( os . str () . c_str (), "987654:\n   2980\n + 123, from: 111111, sign: asdf78wrnASDT3W\n = 3103\n" ) );

    CBank x2;
    strncpy ( accCpy, "123456", sizeof ( accCpy ) );
    assert ( x2 . NewAccount ( accCpy, 1000 ));
    strncpy ( accCpy, "987654", sizeof ( accCpy ) );
    assert ( x2 . NewAccount ( accCpy, -500 ));
    strncpy ( debCpy, "123456", sizeof ( debCpy ) );
    strncpy ( credCpy, "987654", sizeof ( credCpy ) );
    strncpy ( signCpy, "XAbG5uKz6E=", sizeof ( signCpy ) );
    assert ( x2 . Transaction ( debCpy, credCpy, 300, signCpy ) );
    strncpy ( debCpy, "123456", sizeof ( debCpy ) );
    strncpy ( credCpy, "987654", sizeof ( credCpy ) );
    strncpy ( signCpy, "AbG5uKz6E=", sizeof ( signCpy ) );
    assert ( x2 . Transaction ( debCpy, credCpy, 2890, signCpy ) );
    strncpy ( accCpy, "111111", sizeof ( accCpy ) );
    assert ( x2 . NewAccount ( accCpy, 5000 ));
    strncpy ( debCpy, "111111", sizeof ( debCpy ) );
    strncpy ( credCpy, "987654", sizeof ( credCpy ) );
    strncpy ( signCpy, "Okh6e+8rAiuT5=", sizeof ( signCpy ) );
    assert ( x2 . Transaction ( debCpy, credCpy, 2890, signCpy ) );
    assert ( x2 . Account ( "123456" ). Balance ( ) ==  -2190 );
    assert ( x2 . Account ( "987654" ). Balance ( ) ==  5580 );
    assert ( x2 . Account ( "111111" ). Balance ( ) ==  2110 );
    os . str ( "" );
    os << x2 . Account ( "123456" );
    assert ( ! strcmp ( os . str () . c_str (), "123456:\n   1000\n - 300, to: 987654, sign: XAbG5uKz6E=\n - 2890, to: 987654, sign: AbG5uKz6E=\n = -2190\n" ) );
    os . str ( "" );
    os << x2 . Account ( "987654" );
    assert ( ! strcmp ( os . str () . c_str (), "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 2890, from: 111111, sign: Okh6e+8rAiuT5=\n = 5580\n" ) );
    os . str ( "" );
    os << x2 . Account ( "111111" );
    assert ( ! strcmp ( os . str () . c_str (), "111111:\n   5000\n - 2890, to: 987654, sign: Okh6e+8rAiuT5=\n = 2110\n" ) );
    assert ( x2 . TrimAccount ( "987654" ) );
    strncpy ( debCpy, "111111", sizeof ( debCpy ) );
    strncpy ( credCpy, "987654", sizeof ( credCpy ) );
    strncpy ( signCpy, "asdf78wrnASDT3W", sizeof ( signCpy ) );
    assert ( x2 . Transaction ( debCpy, credCpy, 123, signCpy ) );
    os . str ( "" );
    os << x2 . Account ( "987654" );
    assert ( ! strcmp ( os . str () . c_str (), "987654:\n   5580\n + 123, from: 111111, sign: asdf78wrnASDT3W\n = 5703\n" ) );

    CBank x4;
    assert ( x4 . NewAccount ( "123456", 1000 ) );
    assert ( x4 . NewAccount ( "987654", -500 ) );
    assert ( !x4 . NewAccount ( "123456", 3000 ) );
    assert ( !x4 . Transaction ( "123456", "666", 100, "123nr6dfqkwbv5" ) );
    assert ( !x4 . Transaction ( "666", "123456", 100, "34dGD74JsdfKGH" ) );
    assert ( !x4 . Transaction ( "123456", "123456", 100, "Juaw7Jasdkjb5" ) );
    try
    {
        x4 . Account ( "666" ). Balance ( );
        assert ( "Missing exception !!" == NULL );
    }
    catch ( ... )
    {
    }
    try
    {
        os << x4 . Account ( "666" ). Balance ( );
        assert ( "Missing exception !!" == NULL );
    }
    catch ( ... )
    {
    }
    assert ( !x4 . TrimAccount ( "666" ) );

    CBank x6;
    assert ( x6 . NewAccount ( "123456", 1000 ) );
    assert ( x6 . NewAccount ( "987654", -500 ) );
    assert ( x6 . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" ) );
    assert ( x6 . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" ) );
    assert ( x6 . NewAccount ( "111111", 5000 ) );
    assert ( x6 . Transaction ( "111111", "987654", 2890, "Okh6e+8rAiuT5=" ) );
    CBank x7 ( x6 );
    assert ( x6 . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" ) );
    assert ( x7 . Transaction ( "111111", "987654", 789, "SGDFTYE3sdfsd3W" ) );
    assert ( x6 . NewAccount ( "99999999", 7000 ) );
    assert ( x6 . Transaction ( "111111", "99999999", 3789, "aher5asdVsAD" ) );
    assert ( x6 . TrimAccount ( "111111" ) );
    assert ( x6 . Transaction ( "123456", "111111", 221, "Q23wr234ER==" ) );
    os . str ( "" );
    os << x6 . Account ( "111111" );
    assert ( ! strcmp ( os . str () . c_str (), "111111:\n   -1802\n + 221, from: 123456, sign: Q23wr234ER==\n = -1581\n" ) );
    os . str ( "" );
    os << x6 . Account ( "99999999" );
    assert ( ! strcmp ( os . str () . c_str (), "99999999:\n   7000\n + 3789, from: 111111, sign: aher5asdVsAD\n = 10789\n" ) );
    os . str ( "" );
    os << x6 . Account ( "987654" );
    assert ( ! strcmp ( os . str () . c_str (), "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 2890, from: 111111, sign: Okh6e+8rAiuT5=\n + 123, from: 111111, sign: asdf78wrnASDT3W\n = 5703\n" ) );
    os . str ( "" );
    os << x7 . Account ( "111111" );
    assert ( ! strcmp ( os . str () . c_str (), "111111:\n   5000\n - 2890, to: 987654, sign: Okh6e+8rAiuT5=\n - 789, to: 987654, sign: SGDFTYE3sdfsd3W\n = 1321\n" ) );
    try
    {
        os << x7 . Account ( "99999999" ). Balance ( );
        assert ( "Missing exception !!" == NULL );
    }
    catch ( ... )
    {
    }
    os . str ( "" );
    os << x7 . Account ( "987654" );
    assert ( ! strcmp ( os . str () . c_str (), "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 2890, from: 111111, sign: Okh6e+8rAiuT5=\n + 789, from: 111111, sign: SGDFTYE3sdfsd3W\n = 6369\n" ) );

    CBank x8;
    CBank x9;
    assert ( x8 . NewAccount ( "123456", 1000 ) );
    assert ( x8 . NewAccount ( "987654", -500 ) );
    assert ( x8 . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" ) );
    assert ( x8 . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" ) );
    assert ( x8 . NewAccount ( "111111", 5000 ) );
    assert ( x8 . Transaction ( "111111", "987654", 2890, "Okh6e+8rAiuT5=" ) );
    x9 = x8;
    assert ( x8 . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" ) );
    assert ( x9 . Transaction ( "111111", "987654", 789, "SGDFTYE3sdfsd3W" ) );
    assert ( x8 . NewAccount ( "99999999", 7000 ) );
    assert ( x8 . Transaction ( "111111", "99999999", 3789, "aher5asdVsAD" ) );
    assert ( x8 . TrimAccount ( "111111" ) );
    os . str ( "" );
    os << x8 . Account ( "111111" );
    assert ( ! strcmp ( os . str () . c_str (), "111111:\n   -1802\n = -1802\n" ) );
    os . str ( "" );
    os << x9 . Account ( "111111" );
    assert ( ! strcmp ( os . str () . c_str (), "111111:\n   5000\n - 2890, to: 987654, sign: Okh6e+8rAiuT5=\n - 789, to: 987654, sign: SGDFTYE3sdfsd3W\n = 1321\n" ) );

    return 0;
}
#endif /* __PROGTEST__ */
