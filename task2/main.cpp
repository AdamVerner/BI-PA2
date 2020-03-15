#ifndef __PROGTEST__

#include <cassert>

#endif /* __PROGTEST__ */

#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
 *  CPerson BEGIN
 * */

class CPerson {
public:

    string addr;
    string name;
    string account;

    int incomeSum = 0;
    int expenseSum = 0;

    static bool comparePersonByAccount(const CPerson * person1, const CPerson * person2);
    static bool comparePersonByName(const CPerson * person1, const CPerson * person2);

private:

};


bool CPerson::comparePersonByName(const CPerson * person1, const CPerson * person2){

    if (person1==nullptr || person2==nullptr)
        return false;

    if (person1->name != person2->name)
        return person1->name < person2->name;

    return person1->addr < person2->addr;
}


bool CPerson::comparePersonByAccount(const CPerson * person1, const CPerson * person2) {

    if (person1==nullptr || person2==nullptr)
        return false;

    return person1->account < person2->account;
}


/*
 *  CIterator BEGIN
 * */
class CIterator {
public:
    CIterator( const vector<CPerson *> * vec);

    bool AtEnd() const;

    void Next();

    string Name() const;

    string Addr() const;

    string Account() const;

private:
    size_t ptr;
    size_t max;
    const vector<CPerson *> * vec;
};

bool CIterator::AtEnd() const {
    return ptr == max;
}

void CIterator::Next() {
    ptr++;
}

string CIterator::Name() const {
    return (*vec)[ptr]->name;
}

string CIterator::Addr() const {
    return (*vec)[ptr]->addr;
}

string CIterator::Account() const {
    return (*vec)[ptr]->account;
}

CIterator::CIterator(const vector<CPerson *> * vec) {
    this->vec= vec;
    max = vec->size();
    ptr = 0;
}


/*
 *  CTaxRegister BEGIN
 * */
class CTaxRegister {
public:
    bool Birth(const string &name, const string &addr, const string &account);

    bool Death(const string &name, const string &addr);

    bool Income(const string &account, int amount);

    bool Income(const string &name, const string &addr, int amount);

    bool Expense(const string &account, int amount);

    bool Expense(const string &name, const string &addr, int amount);

    bool Audit(const string &name,
               const string &addr,
               string &account,
               int &sumIncome,
               int &sumExpense) const;

    CIterator ListByName() const;

    ~CTaxRegister();

    CPerson * find(const string &name, const string &addr);
    CPerson * find(const string &account);

private:

    std::vector <CPerson *> personListByName;
    std::vector <CPerson *> personListByAccount;

};


CTaxRegister :: ~CTaxRegister(){

    for(const auto& person: personListByName)
        delete person;

}


bool CTaxRegister :: Birth(const string &name,
           const string &addr,
           const string &account){

    // Person is already in database

    auto * person = new CPerson;
    person->name = name;
    person->addr = addr;
    person->account = account;



    if ( std::binary_search(personListByName.begin(), personListByName.end(), person, CPerson::comparePersonByName) ||
         std::binary_search(personListByAccount.begin(), personListByAccount.end(), person, CPerson::comparePersonByAccount) )
    {
        delete person;
        return false;
    }

    // add person to database
    personListByName.insert(std::lower_bound(personListByName.begin(), personListByName.end(), person, CPerson::comparePersonByName), person);
    personListByAccount.insert(std::lower_bound(personListByAccount.begin(), personListByAccount.end(), person, CPerson::comparePersonByAccount), person);
    return true;
}

bool CTaxRegister::Death(const string &name, const string &addr) {

    CPerson * person = find(name, addr);

    if ( !person ) return false;

    personListByName.erase(std::lower_bound(personListByName.begin(), personListByName.end(), person, CPerson::comparePersonByName));
    personListByAccount.erase(std::lower_bound(personListByAccount.begin(), personListByAccount.end(), person, CPerson::comparePersonByAccount));

    delete person;

    return true;
}

bool CTaxRegister::Income(const string &account, int amount) {

    CPerson * person;
    person = CTaxRegister::find(account);

    if (!person ) return false;

    person->incomeSum += amount;
    return true;
}

bool CTaxRegister::Income(const string &name, const string &addr, int amount) {

    CPerson * person;
    person = CTaxRegister::find(name, addr);

    if (!person ) return false;

    person->incomeSum += amount;
    return true;
}

bool CTaxRegister::Expense(const string &account, int amount) {
    CPerson * person;
    person = CTaxRegister::find(account);

    if ( !person ) return false;

    person->expenseSum += amount;
    return true;
}

bool CTaxRegister::Expense(const string &name, const string &addr, int amount) {
    CPerson * person;
    person = CTaxRegister::find(name, addr);

    if ( !person ) return false;

    person->expenseSum += amount;
    return true;
}

bool CTaxRegister::Audit(const string &name, const string &addr, string &account, int &sumIncome, int &sumExpense) const {

    auto * person = new CPerson;
    person->name = name;
    person->addr = addr;

    auto it = std::lower_bound(personListByName.begin(), personListByName.end(), person, CPerson::comparePersonByName);

    // if company is found then remove company from both lists

    delete person;


    if (it == personListByName.end() || (*it)->name != name || (*it)->addr != addr )
        return false;

    sumIncome = (*it)->incomeSum;
    sumExpense = (*it)->expenseSum;
    account  = (*it)->account;

    return true;
}

CIterator CTaxRegister::ListByName(void) const {
    return { & personListByName};
}

CPerson * CTaxRegister::find(const string &name, const string &addr) {
    auto  * person = new CPerson;
    person->name = name;
    person->addr = addr;

    std::vector<CPerson *>::iterator it;

    it = std::lower_bound(personListByName.begin(), personListByName.end(), person, CPerson::comparePersonByName);

    delete person;

    if (it == personListByName.end() || (*it)->name != name || (*it)->addr != addr )
        return nullptr;

    return *it;
}

CPerson * CTaxRegister::find(const string &account) {
    CPerson person;
    person.account = account;

    std::vector<CPerson *>::iterator it;

    it = std::lower_bound(personListByAccount.begin(), personListByAccount.end(), &person, CPerson::comparePersonByAccount);

    if (it == personListByAccount.end() || (*it)->account != account)
        return nullptr;

    return *it;
}


#ifndef __PROGTEST__

int main( ) {
    string acct;
    int sumIncome, sumExpense;
    CTaxRegister b1;

    assert (b1.Birth("John Smith", "Oak Road 23", "123/456/789"));
    assert (b1.Death("John Smith", "Oak Road 23"));
    assert (b1.Birth("John Smith", "Oak Road 23", "123/456/789"));
    assert (b1.Death("John Smith", "Oak Road 23"));
    assert (!b1.Death("John Smith", "Oak Road 23"));

    assert (b1.Birth("John Smith", "Oak Road 23", "123/456/789"));
    assert (!b1.Birth("John Smith", "Oak Road 23", "123/456/789"));
    assert (!b1.Birth("John Smithaa", "Oak Road 23", "123/456/789"));
    assert (!b1.Birth("John Smith", "Oak Road 23", "123/456/7"));

    assert (b1.Birth("Jane Hacker", "Main Street 17", "Xuj5#94"));
    assert (b1.Birth("Peter Hacker", "Main Street 17", "634oddT"));
    assert (b1.Birth("John Smith", "Main Street 17", "Z343rwZ"));
    assert (b1.Income("Xuj5#94", 1000));
    assert (b1.Income("634oddT", 2000));
    assert (b1.Income("123/456/789", 3000));
    assert (b1.Income("634oddT", 4000));
    assert (b1.Income("Peter Hacker", "Main Street 17", 2000));
    assert (b1.Expense("Jane Hacker", "Main Street 17", 2000));
    assert (b1.Expense("John Smith", "Main Street 17", 500));
    assert (b1.Expense("Jane Hacker", "Main Street 17", 1000));

    assert (!b1.Expense("Invalid", "Main Street 17", 1000));

    assert (b1.Expense("Xuj5#94", 1300));
    assert (b1.Audit("John Smith", "Oak Road 23", acct, sumIncome, sumExpense));
    assert (acct == "123/456/789");
    assert (sumIncome == 3000);
    assert (sumExpense == 0);
    assert (b1.Audit("Jane Hacker", "Main Street 17", acct, sumIncome, sumExpense));
    assert (acct == "Xuj5#94");
    assert (sumIncome == 1000);
    assert (sumExpense == 4300);
    assert (b1.Audit("Peter Hacker", "Main Street 17", acct, sumIncome, sumExpense));
    assert (acct == "634oddT");
    assert (sumIncome == 8000);
    assert (sumExpense == 0);
    assert (b1.Audit("John Smith", "Main Street 17", acct, sumIncome, sumExpense));
    assert (acct == "Z343rwZ");
    assert (sumIncome == 0);
    assert (sumExpense == 500);
    CIterator it = b1.ListByName();
    assert (!it.AtEnd());
    assert ( it.Name() == "Jane Hacker");
    assert ( it.Addr() == "Main Street 17");
    assert ( it.Account() == "Xuj5#94");
    it.Next();
    assert (!it.AtEnd()
            && it.Name() == "John Smith"
            && it.Addr() == "Main Street 17"
            && it.Account() == "Z343rwZ");
    it.Next();
    assert (!it.AtEnd()
            && it.Name() == "John Smith"
            && it.Addr() == "Oak Road 23"
            && it.Account() == "123/456/789");
    it.Next();
    assert (!it.AtEnd()
            && it.Name() == "Peter Hacker"
            && it.Addr() == "Main Street 17"
            && it.Account() == "634oddT");
    it.Next();
    assert (it.AtEnd());

    assert (b1.Death("John Smith", "Main Street 17"));

    CTaxRegister b2;
    assert (b2.Birth("John Smith", "Oak Road 23", "123/456/789"));
    assert (b2.Birth("Jane Hacker", "Main Street 17", "Xuj5#94"));
    assert (!b2.Income("634oddT", 4000));
    assert (!b2.Expense("John Smith", "Main Street 18", 500));
    assert (!b2.Audit("John Nowak", "Second Street 23", acct, sumIncome, sumExpense));
    assert (!b2.Death("Peter Nowak", "5-th Avenue"));
    assert (!b2.Birth("Jane Hacker", "Main Street 17", "4et689A"));
    assert (!b2.Birth("Joe Hacker", "Elm Street 23", "Xuj5#94"));
    assert (b2.Death("Jane Hacker", "Main Street 17"));
    assert (b2.Birth("Joe Hacker", "Elm Street 23", "Xuj5#94"));
    assert (b2.Audit("Joe Hacker", "Elm Street 23", acct, sumIncome, sumExpense));
    assert (acct == "Xuj5#94");
    assert (sumIncome == 0);
    assert (sumExpense == 0);
    assert (!b2.Birth("Joe Hacker", "Elm Street 23", "AAj5#94"));

    return 0;
}

#endif /* __PROGTEST__ */