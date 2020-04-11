#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
#include <list>
#include <map>
#include <utility>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <memory>
#include <functional>
#include <stdexcept>

#endif /* __PROGTEST */
using namespace std;

#ifndef __PROGTEST__

class CTimeStamp {
public:
    CTimeStamp(int year, int month, int day, int hour, int minute, int sec)
    : year( year), month( month), day( day), hour( hour), minute( minute), sec( sec)
    { stamp = sec + 60 * (minute + 60 * (hour + 24 * (day + 30 * (month + 365 * (long long) year)))); }

    int Compare(const CTimeStamp & other) const{
        if(stamp < other.stamp) return -1;
        if(stamp > other.stamp) return 1;
        return 0;
    };

    friend ostream &operator<<(ostream &os, const CTimeStamp &x) {

        os.fill('0');
        os << setw(4) << x.year << "-" << setw(2) << x.month << "-";
        os << setw(2) << x.day << " " << setw(2) << x.hour << ":" << setw(2) << x.minute << ":" << setw(2) << x.sec;

        return os;
    }

   int64_t stamp;

private:

    int year, month, day, hour, minute, sec;

};

//=================================================================================================
class CMailBody {
public:
    CMailBody(int size, const char *data) : m_Size(size) {
        m_Data = new char[size];
        memcpy(m_Data, data, size);
    }

    CMailBody(const CMailBody & other) : m_Size(other.m_Size) {
        m_Data = new char[m_Size + 1];
        memcpy(m_Data, other.m_Data, m_Size);
    }

    ~CMailBody(){
        delete [] m_Data;
    }

    // copy cons/op=/destructor is correctly implemented in the testing environment
    friend ostream &operator<<(ostream &os,
                               const CMailBody &x) {
        return os << "mail body: " << x.m_Size << " B";
    }

private:
    int m_Size;
    char *m_Data;
};

//=================================================================================================
class CAttach {
public:
    explicit CAttach(int x)
            : m_X(x)
            ,  m_RefCnt(1) {
    }

    void AddRef() const {
        m_RefCnt++;
    }

    void Release() const {
        if (!--m_RefCnt)
            delete this;
    }

    CAttach(const CAttach &x) = delete;

    CAttach &operator=(const CAttach &x) = delete;

private:

    int m_X;

    mutable int m_RefCnt;

    ~CAttach() = default;

    friend ostream &operator<<(ostream &os, const CAttach &x) {
        return os << "attachment: " << x.m_X << " B";
    }
};
//=================================================================================================
#endif /* __PROGTEST__, DO NOT remove */


class CMail {
public:
    CMail(const CTimeStamp &timeStamp, string from, const CMailBody &body, const CAttach *attach)
        : m_timeStamp(timeStamp), m_from(std::move(from)), m_body(body), m_attach(attach)
        { if (m_attach != nullptr) m_attach->AddRef(); }

    CMail(const CMail & ref)
        : m_timeStamp(ref.m_timeStamp), m_from(ref.m_from), m_body(ref.m_body), m_attach(ref.m_attach)
        { if (m_attach != nullptr) m_attach->AddRef(); }

    CMail(const CMail && ref) noexcept
        : m_timeStamp(ref.m_timeStamp), m_from(ref.m_from), m_body(ref.m_body), m_attach(ref.m_attach)
        { if (m_attach != nullptr) m_attach->AddRef(); }

    ~CMail(){ if (m_attach != nullptr) m_attach->Release(); }

    const string     &From()       const { return m_from; }

    const CMailBody  &Body()       const { return m_body; }

    const CTimeStamp &TimeStamp()  const { return m_timeStamp; }

    const CAttach    *Attachment() const { return m_attach; }

    bool operator<(const CMail & other){ return m_timeStamp.Compare(other.m_timeStamp); };


    friend ostream &operator<<(ostream &os, const CMail &x){
        os << x.m_timeStamp << " " << x.m_from << " " << x.m_body;
        if (x.m_attach) os << " + " << *x.m_attach;
        return os;
    }

private:

    CTimeStamp m_timeStamp;
    string m_from;
    CMailBody m_body;
    const CAttach * m_attach;
};

//=================================================================================================
class CMailBox {
public:
    CMailBox(){
        m_folders["inbox"]; // inserts default folder "inbox"
    }

    bool Delivery(const CMail &mail) {
        m_folders["inbox"].push_back(mail);
        return true;
    }

    bool NewFolder(const string &folderName){
        auto search = m_folders.find(folderName);
        if (search != m_folders.end())
            return false;

        m_folders[folderName];

        return true;
    }


    bool MoveMail(const string &fromFolder,
                  const string &toFolder){

        auto from_folder_ref = m_folders.find(fromFolder);
        auto to_folder_ref = m_folders.find(toFolder);

        if (from_folder_ref == m_folders.end() || to_folder_ref == m_folders.end())
            return false;

        to_folder_ref->second.insert(
            to_folder_ref->second.end(),
            from_folder_ref->second.begin(),
            from_folder_ref->second.end()
            );

        from_folder_ref->second.clear();

        return true;
    }

    list <CMail> ListMail(const string &folderName, const CTimeStamp &from, const CTimeStamp &to) const{
        auto search = m_folders.find(folderName);
        if (search == m_folders.end())
            return list <CMail> ();

        list <CMail> mails;

        for (const CMail & mail: search->second)
            if(from.Compare(mail.TimeStamp()) <= 0 && mail.TimeStamp().Compare(to) <= 0 )
                mails.push_back(mail);

        mails.sort( [](const CMail & a, const CMail & b) { return a.TimeStamp().Compare(b.TimeStamp()) <= 0; } );

        return mails;
    }

    set <string> ListAddr(const CTimeStamp &from, const CTimeStamp &to) const{

        set < string > users;

        for (const pair < string, list<CMail> > folder: m_folders)
            for (const CMail & mail: folder.second)
                if(from.Compare(mail.TimeStamp()) <= 0 && mail.TimeStamp().Compare(to) <= 0 )
                    users.insert(mail.From());

        return users;
    }

    map < string, list<CMail> > m_folders;


private:
    // todo
};
//=================================================================================================
#ifndef __PROGTEST__

static string showMail(const list <CMail> &mail_list) {
    ostringstream oss;
    for (const auto &mail : mail_list)
        oss << mail << endl;
    return oss.str();
}

static string showUsers(const set <string> &users) {
    ostringstream oss;
    for (const auto &user : users)
        oss << user << endl;
    return oss.str();
}

int main() {
    CAttach *ca;

    CMailBox mtest;

    list <CTimeStamp> tst;
    tst.push_back(CTimeStamp(1998, 3, 31, 15, 24, 13));
    tst.push_back(CTimeStamp(1998, 2, 31, 15, 24, 13));
    tst.push_back(CTimeStamp(1998, 1, 31, 15, 24, 13));
    tst.push_back(CTimeStamp(1998, 3, 1, 15, 24, 13));
    tst.push_back(CTimeStamp(1998, 3, 21, 15, 24, 13));

    tst.sort( [](const CTimeStamp & a, const CTimeStamp & b) { return a.Compare(b) == -1; } );

    //for ( const auto & l: tst)
    //    cout <<  l << endl;


    assert(mtest.Delivery(CMail(CTimeStamp(1998, 3, 31, 15, 24, 13), "user1@fit.cvut.cz", CMailBody(14, "mail content 1"), nullptr)));
    assert(mtest.Delivery(CMail(CTimeStamp(2014, 3, 31, 15, 24, 13), "user1@fit.cvut.cz", CMailBody(14, "mail content 1"), nullptr)));
    assert(mtest.Delivery(CMail(CTimeStamp(2014, 3, 31, 15, 24, 13), "user1@fit.cvut.cz", CMailBody(14, "mail content 1"), nullptr)));
    ca = new CAttach(200);
    assert(mtest.Delivery(CMail(CTimeStamp(2014, 3, 31, 15, 24, 13), "user1@fit.cvut.cz", CMailBody(14, "mail content 1"), ca)));
    assert(mtest.Delivery(CMail(CTimeStamp(2014, 3, 31, 15, 24, 13), "user1@fit.cvut.cz", CMailBody(14, "mail content 2"), ca)));
    ca->Release();
    assert(mtest.Delivery(CMail(CTimeStamp(2014, 3, 31, 15, 24, 13), "user1@fit.cvut.cz", CMailBody(14, "mail content 1"), nullptr)));

    // cout << showMail(mtest.ListMail("inbox", CTimeStamp(2000, 1, 1, 0, 0, 0), CTimeStamp(2050, 12, 31, 23, 59, 59)));

    assert(!mtest.MoveMail("inbox", "work"));
    assert(mtest.NewFolder("work"));
    assert(mtest.MoveMail("inbox", "work"));
    // cout << showMail(mtest.ListMail("inbox", CTimeStamp(2000, 1, 1, 0, 0, 0),CTimeStamp(2050, 12, 31, 23, 59, 59)));
    // cout << showMail(mtest.ListMail("work", CTimeStamp(2000, 1, 1, 0, 0, 0), CTimeStamp(2050, 12, 31, 23, 59, 59)));
    //exit(0);

    list <CMail> mailList;
    set <string> users;
    CAttach *att;


    CMailBox m0;
    assert(m0.Delivery(CMail(CTimeStamp(2014, 3, 31, 15, 24, 13), "user1@fit.cvut.cz", CMailBody(14, "mail content 1"), nullptr)));
    assert(m0.Delivery(CMail(CTimeStamp(2014, 3, 31, 15, 26, 23), "user2@fit.cvut.cz", CMailBody(22, "some different content"), nullptr)));
    att = new CAttach(200);
    assert(m0.Delivery(CMail(CTimeStamp(2014, 3, 31, 11, 23, 43), "boss1@fit.cvut.cz", CMailBody(14, "urgent message"), att)));
    assert(m0.Delivery(CMail(CTimeStamp(2014, 3, 31, 18, 52, 27), "user1@fit.cvut.cz", CMailBody(14, "mail content 2"), att)));
    att->Release();
    att = new CAttach(97);
    assert(m0.Delivery(CMail(CTimeStamp(2014, 3, 31, 16, 12, 48), "boss1@fit.cvut.cz", CMailBody(24, "even more urgent message"), att)));
    att->Release();

    cout << showMail(m0.ListMail("inbox",
                                 CTimeStamp(2000, 1, 1, 0, 0, 0),
                                 CTimeStamp(2050, 12, 31, 23, 59, 59)));

    assert(showMail(m0.ListMail("inbox",
                                CTimeStamp(2000, 1, 1, 0, 0, 0),
                                CTimeStamp(2050, 12, 31, 23, 59, 59))) ==
           "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B + attachment: 200 B\n"
           "2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
           "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B\n"
           "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B + attachment: 97 B\n"
           "2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 200 B\n");

    assert(showMail(m0.ListMail("inbox",
                                CTimeStamp(2014, 3, 31, 15, 26, 23),
                                CTimeStamp(2014, 3, 31, 16, 12, 48))) ==
           "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B\n"
           "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B + attachment: 97 B\n");

    assert(showUsers(m0.ListAddr(CTimeStamp(2000, 1, 1, 0, 0, 0),
                                 CTimeStamp(2050, 12, 31, 23, 59, 59))) == "boss1@fit.cvut.cz\n"
                                                                           "user1@fit.cvut.cz\n"
                                                                           "user2@fit.cvut.cz\n");
    assert(showUsers(m0.ListAddr(CTimeStamp(2014, 3, 31, 15, 26, 23),
                                 CTimeStamp(2014, 3, 31, 16, 12, 48))) == "boss1@fit.cvut.cz\n"
                                                                          "user2@fit.cvut.cz\n");

    CMailBox m1;
    assert(m1.NewFolder("work"));
    assert(m1.NewFolder("spam"));
    assert(!m1.NewFolder("spam"));
    assert(m1.Delivery(
            CMail(CTimeStamp(2014, 3, 31, 15, 24, 13), "user1@fit.cvut.cz", CMailBody(14, "mail content 1"), nullptr)));
    att = new CAttach(500);
    assert(m1.Delivery(
            CMail(CTimeStamp(2014, 3, 31, 15, 26, 23), "user2@fit.cvut.cz", CMailBody(22, "some different content"),
                  att)));
    att->Release();
    assert(m1.Delivery(
            CMail(CTimeStamp(2014, 3, 31, 11, 23, 43), "boss1@fit.cvut.cz", CMailBody(14, "urgent message"), nullptr)));
    att = new CAttach(468);
    assert(m1.Delivery(
            CMail(CTimeStamp(2014, 3, 31, 18, 52, 27), "user1@fit.cvut.cz", CMailBody(14, "mail content 2"), att)));
    att->Release();
    assert(m1.Delivery(
            CMail(CTimeStamp(2014, 3, 31, 16, 12, 48), "boss1@fit.cvut.cz", CMailBody(24, "even more urgent message"),
                  nullptr)));
    assert(showMail(m1.ListMail("inbox",
                                CTimeStamp(2000, 1, 1, 0, 0, 0),
                                CTimeStamp(2050, 12, 31, 23, 59, 59))) ==
           "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B\n"
           "2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
           "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B\n"
           "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B\n"
           "2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B\n");
    assert(showMail(m1.ListMail("work",
                                CTimeStamp(2000, 1, 1, 0, 0, 0),
                                CTimeStamp(2050, 12, 31, 23, 59, 59))) == "");
    assert(m1.MoveMail("inbox", "work"));
    assert(showMail(m1.ListMail("inbox",
                                CTimeStamp(2000, 1, 1, 0, 0, 0),
                                CTimeStamp(2050, 12, 31, 23, 59, 59))) == "");
    assert(showMail(m1.ListMail("work",
                                CTimeStamp(2000, 1, 1, 0, 0, 0),
                                CTimeStamp(2050, 12, 31, 23, 59, 59))) ==
           "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B\n"
           "2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
           "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B\n"
           "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B\n"
           "2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B\n");
    assert(m1.Delivery(
            CMail(CTimeStamp(2014, 3, 31, 19, 24, 13), "user2@fit.cvut.cz", CMailBody(14, "mail content 4"), nullptr)));
    att = new CAttach(234);
    assert(m1.Delivery(
            CMail(CTimeStamp(2014, 3, 31, 13, 26, 23), "user3@fit.cvut.cz", CMailBody(9, "complains"), att)));
    att->Release();
    assert(showMail(m1.ListMail("inbox",
                                CTimeStamp(2000, 1, 1, 0, 0, 0),
                                CTimeStamp(2050, 12, 31, 23, 59, 59))) ==
           "2014-03-31 13:26:23 user3@fit.cvut.cz mail body: 9 B + attachment: 234 B\n"
           "2014-03-31 19:24:13 user2@fit.cvut.cz mail body: 14 B\n");
    assert(showMail(m1.ListMail("work",
                                CTimeStamp(2000, 1, 1, 0, 0, 0),
                                CTimeStamp(2050, 12, 31, 23, 59, 59))) ==
           "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B\n"
           "2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
           "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B\n"
           "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B\n"
           "2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B\n");
    assert(m1.MoveMail("inbox", "work"));
    assert(showMail(m1.ListMail("inbox",
                                CTimeStamp(2000, 1, 1, 0, 0, 0),
                                CTimeStamp(2050, 12, 31, 23, 59, 59))) == "");
    assert(showMail(m1.ListMail("work",
                                CTimeStamp(2000, 1, 1, 0, 0, 0),
                                CTimeStamp(2050, 12, 31, 23, 59, 59))) ==
           "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B\n"
           "2014-03-31 13:26:23 user3@fit.cvut.cz mail body: 9 B + attachment: 234 B\n"
           "2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
           "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B\n"
           "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B\n"
           "2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B\n"
           "2014-03-31 19:24:13 user2@fit.cvut.cz mail body: 14 B\n");

    return 0;
}

#endif /* __PROGTEST__ */
