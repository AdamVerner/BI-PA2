#include "progtest.cpp"
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <memory>
#include <functional>
#include <stdexcept>
using namespace std;

class my_bad_cast: public std::bad_cast {
public:
    my_bad_cast(char const* s, char const* d): _source(s), _destination(d) {
        try {
            std::ostringstream oss;
            oss << "Could not cast '" << _source
                << "' into '" << _destination << "'";
            _what = oss.str();
        } catch (...) {
            _what.clear();
        }
    }

    char const* source() const { return _source; }
    char const* destination() const { return _destination; }

    virtual char const* what() const noexcept {
        return not _what.empty() ? _what.c_str() : std::bad_cast::what();
    }

private:
    char const* _source;
    char const* _destination;
    std::string _what;
    // you can even add a stack trace
};

template <typename D, typename S>
D my_dynamic_cast(S&& s) {
    try {
        return dynamic_cast<D>(std::forward<S>(s));
    } catch(std::bad_cast const&) {
        throw my_bad_cast(typeid(S).name(), typeid(D).name());
    }
}

int Vmain (  );
int Stolen ( );

int main(){

    CTable table (2, 2);

    table.SetCell(0, 0, CText("211113", CText::ALIGN_LEFT));
    table.SetCell(1, 1, CText("1\n", CText::ALIGN_LEFT));
    table.SetCell(1, 0, CImage().AddRow("111").AddRow("111"));
    table.SetCell(1, 0, CEmpty());

    cout << table;


    assert(sizeof(CEmpty) < sizeof(CImage));

    cout << "A: " << sizeof(CEmpty) << "; B: " << sizeof(CImage);

    Vmain();
    Stolen();
}

bool compareChars (const string a, const string b)
{
    int c = 0;
    while (a[c] != '\0' || b[c] != '\0')
    {
        if (a[c] == b[c])
            c++;
        else
        {
            cout << '(' << a[c] << ')' << " =/= " << '(' << b[c] << ')' << endl;
            return false;
        }
    }
    return true;
}

int Stolen ( void ){
/*
 * K zapnuti testovani automaticky vyrazenych assertu,
 * nastav nasledujici definici na 1.
 */
#define INVALID_0300 0


/*
 * K vypnuti testovani assertu oznacenych jako bonus,
 * nastav nasledujici definici na 0.
 */
#define BONUS_0300 1

/**
* Assert #251
* @author  vagner
* @link  https://progtester.eu/assert/251
*
* Potvrzena spravnost: 18x
* Nahlasena nefukcnost: 1x
* Bonus: NE
*
*/
    {
    assert(sizeof(CEmpty) < sizeof(CImage));
    }
/**
* Assert #261
* @author  Lynxwe
* @link  https://progtester.eu/assert/261
*
* Potvrzena spravnost: 16x
* Nahlasena nefukcnost: 2x
* Bonus: NE
*
*/
/**
* Assert #271
* @author  binamar3
* @link  https://progtester.eu/assert/271
*
* Potvrzena spravnost: 20x
* Nahlasena nefukcnost: 0x
* Bonus: NE
*
*/
    {
        ostringstream oss;
        CTable tt(3,3);
        tt.SetCell(1, 1, CImage()
                .AddRow("CsvNE.'/1NV%6(FM=")
                .AddRow("CsvNE.'/1NV%6(FM="));
        tt.SetCell(2, 1, CText("jhgq xtpscya ifbvlvvkejhgq xtpscya ifbvlvvkejhgq xtpscya ifbvlvvkejhgq xtpscya ifbvlvvke", CText::ALIGN_LEFT));

        tt.SetCell(1,0, tt.GetCell(1,1));
        oss.str("");
        oss.clear();
        oss << tt;
        assert (oss.str() ==
                "+-----------------+----------------------------------------------------------------------------------------++\n"
                "+-----------------+----------------------------------------------------------------------------------------++\n"
                "|CsvNE.'/1NV%6(FM=|                                   CsvNE.'/1NV%6(FM=                                    ||\n"
                "|CsvNE.'/1NV%6(FM=|                                   CsvNE.'/1NV%6(FM=                                    ||\n"
                "+-----------------+----------------------------------------------------------------------------------------++\n"
                "|                 |jhgq xtpscya ifbvlvvkejhgq xtpscya ifbvlvvkejhgq xtpscya ifbvlvvkejhgq xtpscya ifbvlvvke||\n"
                "+-----------------+----------------------------------------------------------------------------------------++\n");

        tt.SetCell(2, 0, CText("width + 1         ", CText::ALIGN_LEFT));
        oss.str("");
        oss.clear();
        oss << tt;
        assert (oss.str() ==
                "+------------------+----------------------------------------------------------------------------------------++\n"
                "+------------------+----------------------------------------------------------------------------------------++\n"
                "|CsvNE.'/1NV%6(FM= |                                   CsvNE.'/1NV%6(FM=                                    ||\n"
                "|CsvNE.'/1NV%6(FM= |                                   CsvNE.'/1NV%6(FM=                                    ||\n"
                "+------------------+----------------------------------------------------------------------------------------++\n"
                "|width + 1         |jhgq xtpscya ifbvlvvkejhgq xtpscya ifbvlvvkejhgq xtpscya ifbvlvvkejhgq xtpscya ifbvlvvke||\n"
                "+------------------+----------------------------------------------------------------------------------------++\n");

        tt.SetCell(2, 0, CText("width + 2          ", CText::ALIGN_LEFT));
        oss.str("");
        oss.clear();
        oss << tt;
        assert (oss.str() ==
                "+-------------------+----------------------------------------------------------------------------------------++\n"
                "+-------------------+----------------------------------------------------------------------------------------++\n"
                "| CsvNE.'/1NV%6(FM= |                                   CsvNE.'/1NV%6(FM=                                    ||\n"
                "| CsvNE.'/1NV%6(FM= |                                   CsvNE.'/1NV%6(FM=                                    ||\n"
                "+-------------------+----------------------------------------------------------------------------------------++\n"
                "|width + 2          |jhgq xtpscya ifbvlvvkejhgq xtpscya ifbvlvvkejhgq xtpscya ifbvlvvkejhgq xtpscya ifbvlvvke||\n"
                "+-------------------+----------------------------------------------------------------------------------------++\n");
        tt.SetCell(2, 0, CText("width + 3           ", CText::ALIGN_LEFT));
        oss.str("");
        oss.clear();
        oss << tt;
        assert (oss.str() ==
                "+--------------------+----------------------------------------------------------------------------------------++\n"
                "+--------------------+----------------------------------------------------------------------------------------++\n"
                "| CsvNE.'/1NV%6(FM=  |                                   CsvNE.'/1NV%6(FM=                                    ||\n"
                "| CsvNE.'/1NV%6(FM=  |                                   CsvNE.'/1NV%6(FM=                                    ||\n"
                "+--------------------+----------------------------------------------------------------------------------------++\n"
                "|width + 3           |jhgq xtpscya ifbvlvvkejhgq xtpscya ifbvlvvkejhgq xtpscya ifbvlvvkejhgq xtpscya ifbvlvvke||\n"
                "+--------------------+----------------------------------------------------------------------------------------++\n");
    }
/**
* Assert #281
* @author  babakjan
* @link  https://progtester.eu/assert/281
*
* Potvrzena spravnost: 20x
* Nahlasena nefukcnost: 0x
* Bonus: NE
*
*/
    {
        //na tomto podlem testu vam muze program padat na nahodných datech
        CTable PodtrhnuSiPodSebouZidli ( 3, 5 );
        PodtrhnuSiPodSebouZidli . SetCell( 0, 0, PodtrhnuSiPodSebouZidli . GetCell( 0 , 0 ) );
    }
/**
* Assert #291
* @author  prevrjan
* @link  https://progtester.eu/assert/291
*
* Potvrzena spravnost: 12x
* Nahlasena nefukcnost: 0x
* Bonus: NE
*
*/
    {
        // test na obří stringy a copy konstruktor
// přidej tuto funkci nad main


// tento test přidej do mainu
        ostringstream oss; // pozor, možná už máš oss deklarovaný
        CTable t1010 (5, 5);
        t1010. SetCell (0, 0, CText ("btmsykgko egnemknxf uxdkahnej clgpeg\nuqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg\nuqqfxfn srukg jjwr pluylxivr\nehcevn rhiwyt grc bbehrc\njvvhup chnqj urgxxw jmo yicq apmcyar icmo \npiclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg\nauavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs\nwdh mqfutdypo mhebblrxn cybkr\nniv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj\nknhrcx rrirp cxwvmxugi kxgwpqd\ncldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap\nanbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj\nksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp\nehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo\nyicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso\njeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc\ngcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr\nniv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj\nknhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h\nbme iqrjh xmv emqap anbwxg ogaki ciky uwsfw\nngg xnyrswqhj wgnsgl fs csj\nksdrcb joipbiv kxmuuwjr eusympkx\neaympe dsllncm gelj fdrp\n", CText::ALIGN_RIGHT));
        t1010. SetCell (1, 1, CText ("btmsykgko egnemknxf uxdkahnej clgpeg\nuqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg\nuqqfxfn srukg jjwr pluylxivr\nehcevn rhiwyt grc bbehrc\njvvhup chnqj urgxxw jmo yicq apmcyar icmo \npiclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg\nauavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs\nwdh mqfutdypo mhebblrxn cybkr\nniv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj\nknhrcx rrirp cxwvmxugi kxgwpqd\ncldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap\nanbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj\nksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp\nehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo\nyicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso\njeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc\ngcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr\nniv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj\nknhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h\nbme iqrjh xmv emqap anbwxg ogaki ciky uwsfw\nngg xnyrswqhj wgnsgl fs csj\nksdrcb joipbiv kxmuuwjr eusympkx\neaympe dsllncm gelj fdrp\n", CText::ALIGN_RIGHT));
        t1010. SetCell (2, 2, CText ("btmsykgko egnemknxf uxdkahnej clgpeg\nuqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg\nuqqfxfn srukg jjwr pluylxivr\nehcevn rhiwyt grc bbehrc\njvvhup chnqj urgxxw jmo yicq apmcyar icmo \npiclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg\nauavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs\nwdh mqfutdypo mhebblrxn cybkr\nniv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj\nknhrcx rrirp cxwvmxugi kxgwpqd\ncldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap\nanbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj\nksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp\nehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo\nyicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso\njeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc\ngcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr\nniv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj\nknhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h\nbme iqrjh xmv emqap anbwxg ogaki ciky uwsfw\nngg xnyrswqhj wgnsgl fs csj\nksdrcb joipbiv kxmuuwjr eusympkx\neaympe dsllncm gelj fdrp\n", CText::ALIGN_LEFT));
        t1010. SetCell (1, 2, CText ("btmsykgko egnemknxf uxdkahnej clgpeg\nuqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg\nuqqfxfn srukg jjwr pluylxivr\nehcevn rhiwyt grc bbehrc\njvvhup chnqj urgxxw jmo yicq apmcyar icmo \npiclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg\nauavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs\nwdh mqfutdypo mhebblrxn cybkr\nniv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj\nknhrcx rrirp cxwvmxugi kxgwpqd\ncldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap\nanbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj\nksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp\nehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo\nyicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso\njeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc\ngcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr\nniv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj\nknhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h\nbme iqrjh xmv emqap anbwxg ogaki ciky uwsfw\nngg xnyrswqhj wgnsgl fs csj\nksdrcb joipbiv kxmuuwjr eusympkx\neaympe dsllncm gelj fdrp\n", CText::ALIGN_RIGHT));
        t1010. SetCell (3, 3, CText ("btmsykgko egnemknxf uxdkahnej clgpeg\nuqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg\nuqqfxfn srukg jjwr pluylxivr\nehcevn rhiwyt grc bbehrc\njvvhup chnqj urgxxw jmo yicq apmcyar icmo \npiclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg\nauavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs\nwdh mqfutdypo mhebblrxn cybkr\nniv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj\nknhrcx rrirp cxwvmxugi kxgwpqd\ncldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap\nanbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj\nksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp\nehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo\nyicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso\njeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc\ngcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr\nniv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj\nknhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h\nbme iqrjh xmv emqap anbwxg ogaki ciky uwsfw\nngg xnyrswqhj wgnsgl fs csj\nksdrcb joipbiv kxmuuwjr eusympkx\neaympe dsllncm gelj fdrp\n", CText::ALIGN_LEFT));
        t1010. SetCell (3, 1, CText ("btmsykgko egnemknxf uxdkahnej clgpeg\nuqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg\nuqqfxfn srukg jjwr pluylxivr\nehcevn rhiwyt grc bbehrc\njvvhup chnqj urgxxw jmo yicq apmcyar icmo \npiclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg\nauavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs\nwdh mqfutdypo mhebblrxn cybkr\nniv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj\nknhrcx rrirp cxwvmxugi kxgwpqd\ncldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap\nanbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj\nksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp\nehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo\nyicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso\njeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc\ngcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr\nniv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj\nknhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h\nbme iqrjh xmv emqap anbwxg ogaki ciky uwsfw\nngg xnyrswqhj wgnsgl fs csj\nksdrcb joipbiv kxmuuwjr eusympkx\neaympe dsllncm gelj fdrp\n", CText::ALIGN_RIGHT));
        t1010. SetCell (4, 4, CText ("btmsykgko egnemknxf uxdkahnej clgpeg\nuqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg\nuqqfxfn srukg jjwr pluylxivr\nehcevn rhiwyt grc bbehrc\njvvhup chnqj urgxxw jmo yicq apmcyar icmo \npiclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg\nauavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs\nwdh mqfutdypo mhebblrxn cybkr\nniv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj\nknhrcx rrirp cxwvmxugi kxgwpqd\ncldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap\nanbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj\nksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp\nehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo\nyicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso\njeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc\ngcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr\nniv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj\nknhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h\nbme iqrjh xmv emqap anbwxg ogaki ciky uwsfw\nngg xnyrswqhj wgnsgl fs csj\nksdrcb joipbiv kxmuuwjr eusympkx\neaympe dsllncm gelj fdrp\n", CText::ALIGN_RIGHT));
        t1010. SetCell (0, 4, CText ("btmsykgko egnemknxf uxdkahnej clgpeg\nuqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg\nuqqfxfn srukg jjwr pluylxivr\nehcevn rhiwyt grc bbehrc\njvvhup chnqj urgxxw jmo yicq apmcyar icmo \npiclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg\nauavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs\nwdh mqfutdypo mhebblrxn cybkr\nniv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj\nknhrcx rrirp cxwvmxugi kxgwpqd\ncldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap\nanbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj\nksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp\nehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo\nyicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso\njeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc\ngcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr\nniv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj\nknhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h\nbme iqrjh xmv emqap anbwxg ogaki ciky uwsfw\nngg xnyrswqhj wgnsgl fs csj\nksdrcb joipbiv kxmuuwjr eusympkx\neaympe dsllncm gelj fdrp\n", CText::ALIGN_LEFT));
        t1010. SetCell (1, 4, CText ("btmsykgko egnemknxf uxdkahnej clgpeg\nuqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg\nuqqfxfn srukg jjwr pluylxivr\nehcevn rhiwyt grc bbehrc\njvvhup chnqj urgxxw jmo yicq apmcyar icmo \npiclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg\nauavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs\nwdh mqfutdypo mhebblrxn cybkr\nniv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj\nknhrcx rrirp cxwvmxugi kxgwpqd\ncldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap\nanbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj\nksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp\nehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo\nyicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso\njeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc\ngcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr\nniv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj\nknhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h\nbme iqrjh xmv emqap anbwxg ogaki ciky uwsfw\nngg xnyrswqhj wgnsgl fs csj\nksdrcb joipbiv kxmuuwjr eusympkx\neaympe dsllncm gelj fdrp\n", CText::ALIGN_RIGHT));
        t1010. SetCell (3, 2, CText ("btmsykgko egnemknxf uxdkahnej clgpeg\nuqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg\nuqqfxfn srukg jjwr pluylxivr\nehcevn rhiwyt grc bbehrc\njvvhup chnqj urgxxw jmo yicq apmcyar icmo \npiclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg\nauavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs\nwdh mqfutdypo mhebblrxn cybkr\nniv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj\nknhrcx rrirp cxwvmxugi kxgwpqd\ncldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap\nanbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj\nksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp\nehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo\nyicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso\njeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc\ngcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr\nniv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj\nknhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h\nbme iqrjh xmv emqap anbwxg ogaki ciky uwsfw\nngg xnyrswqhj wgnsgl fs csj\nksdrcb joipbiv kxmuuwjr eusympkx\neaympe dsllncm gelj fdrp\n", CText::ALIGN_LEFT));


        CTable t1010_2 ( t1010 );
        oss . str ("");
        oss . clear ();
        oss << t1010_2;
        cout << t1010 << flush;
        cout <<                                 "+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+\n"
                                                "|                            btmsykgko egnemknxf uxdkahnej clgpeg|                                                                |                                                                |                                                                |btmsykgko egnemknxf uxdkahnej clgpeg                            |\n"
                                                "|uqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg|                                                                |                                                                |                                                                |uqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg|\n"
                                                "|                                    uqqfxfn srukg jjwr pluylxivr|                                                                |                                                                |                                                                |uqqfxfn srukg jjwr pluylxivr                                    |\n"
                                                "|                                        ehcevn rhiwyt grc bbehrc|                                                                |                                                                |                                                                |ehcevn rhiwyt grc bbehrc                                        |\n"
                                                "|                      jvvhup chnqj urgxxw jmo yicq apmcyar icmo |                                                                |                                                                |                                                                |jvvhup chnqj urgxxw jmo yicq apmcyar icmo                       |\n"
                                                "|            piclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg|                                                                |                                                                |                                                                |piclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg            |\n"
                                                "|         auavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs|                                                                |                                                                |                                                                |auavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs         |\n"
                                                "|                                   wdh mqfutdypo mhebblrxn cybkr|                                                                |                                                                |                                                                |wdh mqfutdypo mhebblrxn cybkr                                   |\n"
                                                "|             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|                                                                |                                                                |                                                                |niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj             |\n"
                                                "|                                  knhrcx rrirp cxwvmxugi kxgwpqd|                                                                |                                                                |                                                                |knhrcx rrirp cxwvmxugi kxgwpqd                                  |\n"
                                                "|                    cldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap|                                                                |                                                                |                                                                |cldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap                    |\n"
                                                "|             anbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj|                                                                |                                                                |                                                                |anbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj             |\n"
                                                "|               ksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp|                                                                |                                                                |                                                                |ksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp               |\n"
                                                "|                ehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo|                                                                |                                                                |                                                                |ehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo                |\n"
                                                "|                  yicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso|                                                                |                                                                |                                                                |yicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso                  |\n"
                                                "|   jeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc|                                                                |                                                                |                                                                |jeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc   |\n"
                                                "|          gcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr|                                                                |                                                                |                                                                |gcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr          |\n"
                                                "|             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|                                                                |                                                                |                                                                |niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj             |\n"
                                                "|             knhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h|                                                                |                                                                |                                                                |knhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h             |\n"
                                                "|                     bme iqrjh xmv emqap anbwxg ogaki ciky uwsfw|                                                                |                                                                |                                                                |bme iqrjh xmv emqap anbwxg ogaki ciky uwsfw                     |\n"
                                                "|                                     ngg xnyrswqhj wgnsgl fs csj|                                                                |                                                                |                                                                |ngg xnyrswqhj wgnsgl fs csj                                     |\n"
                                                "|                                ksdrcb joipbiv kxmuuwjr eusympkx|                                                                |                                                                |                                                                |ksdrcb joipbiv kxmuuwjr eusympkx                                |\n"
                                                "|                                        eaympe dsllncm gelj fdrp|                                                                |                                                                |                                                                |eaympe dsllncm gelj fdrp                                        |\n"
                                                "|                                                                |                                                                |                                                                |                                                                |                                                                |\n"
                                                "+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+\n"
                                                "|                                                                |                            btmsykgko egnemknxf uxdkahnej clgpeg|                            btmsykgko egnemknxf uxdkahnej clgpeg|                                                                |                            btmsykgko egnemknxf uxdkahnej clgpeg|\n"
                                                "|                                                                |uqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg|uqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg|                                                                |uqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg|\n"
                                                "|                                                                |                                    uqqfxfn srukg jjwr pluylxivr|                                    uqqfxfn srukg jjwr pluylxivr|                                                                |                                    uqqfxfn srukg jjwr pluylxivr|\n"
                                                "|                                                                |                                        ehcevn rhiwyt grc bbehrc|                                        ehcevn rhiwyt grc bbehrc|                                                                |                                        ehcevn rhiwyt grc bbehrc|\n"
                                                "|                                                                |                      jvvhup chnqj urgxxw jmo yicq apmcyar icmo |                      jvvhup chnqj urgxxw jmo yicq apmcyar icmo |                                                                |                      jvvhup chnqj urgxxw jmo yicq apmcyar icmo |\n"
                                                "|                                                                |            piclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg|            piclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg|                                                                |            piclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg|\n"
                                                "|                                                                |         auavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs|         auavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs|                                                                |         auavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs|\n"
                                                "|                                                                |                                   wdh mqfutdypo mhebblrxn cybkr|                                   wdh mqfutdypo mhebblrxn cybkr|                                                                |                                   wdh mqfutdypo mhebblrxn cybkr|\n"
                                                "|                                                                |             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|                                                                |             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|\n"
                                                "|                                                                |                                  knhrcx rrirp cxwvmxugi kxgwpqd|                                  knhrcx rrirp cxwvmxugi kxgwpqd|                                                                |                                  knhrcx rrirp cxwvmxugi kxgwpqd|\n"
                                                "|                                                                |                    cldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap|                    cldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap|                                                                |                    cldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap|\n"
                                                "|                                                                |             anbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj|             anbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj|                                                                |             anbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj|\n"
                                                "|                                                                |               ksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp|               ksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp|                                                                |               ksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp|\n"
                                                "|                                                                |                ehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo|                ehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo|                                                                |                ehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo|\n"
                                                "|                                                                |                  yicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso|                  yicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso|                                                                |                  yicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso|\n"
                                                "|                                                                |   jeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc|   jeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc|                                                                |   jeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc|\n"
                                                "|                                                                |          gcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr|          gcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr|                                                                |          gcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr|\n"
                                                "|                                                                |             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|                                                                |             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|\n"
                                                "|                                                                |             knhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h|             knhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h|                                                                |             knhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h|\n"
                                                "|                                                                |                     bme iqrjh xmv emqap anbwxg ogaki ciky uwsfw|                     bme iqrjh xmv emqap anbwxg ogaki ciky uwsfw|                                                                |                     bme iqrjh xmv emqap anbwxg ogaki ciky uwsfw|\n"
                                                "|                                                                |                                     ngg xnyrswqhj wgnsgl fs csj|                                     ngg xnyrswqhj wgnsgl fs csj|                                                                |                                     ngg xnyrswqhj wgnsgl fs csj|\n"
                                                "|                                                                |                                ksdrcb joipbiv kxmuuwjr eusympkx|                                ksdrcb joipbiv kxmuuwjr eusympkx|                                                                |                                ksdrcb joipbiv kxmuuwjr eusympkx|\n"
                                                "|                                                                |                                        eaympe dsllncm gelj fdrp|                                        eaympe dsllncm gelj fdrp|                                                                |                                        eaympe dsllncm gelj fdrp|\n"
                                                "|                                                                |                                                                |                                                                |                                                                |                                                                |\n"
                                                "+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+\n"
                                                "|                                                                |                                                                |btmsykgko egnemknxf uxdkahnej clgpeg                            |                                                                |                                                                |\n"
                                                "|                                                                |                                                                |uqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg|                                                                |                                                                |\n"
                                                "|                                                                |                                                                |uqqfxfn srukg jjwr pluylxivr                                    |                                                                |                                                                |\n"
                                                "|                                                                |                                                                |ehcevn rhiwyt grc bbehrc                                        |                                                                |                                                                |\n"
                                                "|                                                                |                                                                |jvvhup chnqj urgxxw jmo yicq apmcyar icmo                       |                                                                |                                                                |\n"
                                                "|                                                                |                                                                |piclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg            |                                                                |                                                                |\n"
                                                "|                                                                |                                                                |auavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs         |                                                                |                                                                |\n"
                                                "|                                                                |                                                                |wdh mqfutdypo mhebblrxn cybkr                                   |                                                                |                                                                |\n"
                                                "|                                                                |                                                                |niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj             |                                                                |                                                                |\n"
                                                "|                                                                |                                                                |knhrcx rrirp cxwvmxugi kxgwpqd                                  |                                                                |                                                                |\n"
                                                "|                                                                |                                                                |cldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap                    |                                                                |                                                                |\n"
                                                "|                                                                |                                                                |anbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj             |                                                                |                                                                |\n"
                                                "|                                                                |                                                                |ksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp               |                                                                |                                                                |\n"
                                                "|                                                                |                                                                |ehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo                |                                                                |                                                                |\n"
                                                "|                                                                |                                                                |yicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso                  |                                                                |                                                                |\n"
                                                "|                                                                |                                                                |jeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc   |                                                                |                                                                |\n"
                                                "|                                                                |                                                                |gcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr          |                                                                |                                                                |\n"
                                                "|                                                                |                                                                |niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj             |                                                                |                                                                |\n"
                                                "|                                                                |                                                                |knhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h             |                                                                |                                                                |\n"
                                                "|                                                                |                                                                |bme iqrjh xmv emqap anbwxg ogaki ciky uwsfw                     |                                                                |                                                                |\n"
                                                "|                                                                |                                                                |ngg xnyrswqhj wgnsgl fs csj                                     |                                                                |                                                                |\n"
                                                "|                                                                |                                                                |ksdrcb joipbiv kxmuuwjr eusympkx                                |                                                                |                                                                |\n"
                                                "|                                                                |                                                                |eaympe dsllncm gelj fdrp                                        |                                                                |                                                                |\n"
                                                "|                                                                |                                                                |                                                                |                                                                |                                                                |\n"
                                                "+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+\n"
                                                "|                                                                |                            btmsykgko egnemknxf uxdkahnej clgpeg|btmsykgko egnemknxf uxdkahnej clgpeg                            |btmsykgko egnemknxf uxdkahnej clgpeg                            |                                                                |\n"
                                                "|                                                                |uqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg|uqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg|uqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg|                                                                |\n"
                                                "|                                                                |                                    uqqfxfn srukg jjwr pluylxivr|uqqfxfn srukg jjwr pluylxivr                                    |uqqfxfn srukg jjwr pluylxivr                                    |                                                                |\n"
                                                "|                                                                |                                        ehcevn rhiwyt grc bbehrc|ehcevn rhiwyt grc bbehrc                                        |ehcevn rhiwyt grc bbehrc                                        |                                                                |\n"
                                                "|                                                                |                      jvvhup chnqj urgxxw jmo yicq apmcyar icmo |jvvhup chnqj urgxxw jmo yicq apmcyar icmo                       |jvvhup chnqj urgxxw jmo yicq apmcyar icmo                       |                                                                |\n"
                                                "|                                                                |            piclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg|piclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg            |piclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg            |                                                                |\n"
                                                "|                                                                |         auavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs|auavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs         |auavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs         |                                                                |\n"
                                                "|                                                                |                                   wdh mqfutdypo mhebblrxn cybkr|wdh mqfutdypo mhebblrxn cybkr                                   |wdh mqfutdypo mhebblrxn cybkr                                   |                                                                |\n"
                                                "|                                                                |             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj             |niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj             |                                                                |\n"
                                                "|                                                                |                                  knhrcx rrirp cxwvmxugi kxgwpqd|knhrcx rrirp cxwvmxugi kxgwpqd                                  |knhrcx rrirp cxwvmxugi kxgwpqd                                  |                                                                |\n"
                                                "|                                                                |                    cldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap|cldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap                    |cldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap                    |                                                                |\n"
                                                "|                                                                |             anbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj|anbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj             |anbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj             |                                                                |\n"
                                                "|                                                                |               ksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp|ksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp               |ksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp               |                                                                |\n"
                                                "|                                                                |                ehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo|ehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo                |ehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo                |                                                                |\n"
                                                "|                                                                |                  yicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso|yicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso                  |yicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso                  |                                                                |\n"
                                                "|                                                                |   jeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc|jeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc   |jeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc   |                                                                |\n"
                                                "|                                                                |          gcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr|gcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr          |gcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr          |                                                                |\n"
                                                "|                                                                |             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj             |niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj             |                                                                |\n"
                                                "|                                                                |             knhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h|knhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h             |knhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h             |                                                                |\n"
                                                "|                                                                |                     bme iqrjh xmv emqap anbwxg ogaki ciky uwsfw|bme iqrjh xmv emqap anbwxg ogaki ciky uwsfw                     |bme iqrjh xmv emqap anbwxg ogaki ciky uwsfw                     |                                                                |\n"
                                                "|                                                                |                                     ngg xnyrswqhj wgnsgl fs csj|ngg xnyrswqhj wgnsgl fs csj                                     |ngg xnyrswqhj wgnsgl fs csj                                     |                                                                |\n"
                                                "|                                                                |                                ksdrcb joipbiv kxmuuwjr eusympkx|ksdrcb joipbiv kxmuuwjr eusympkx                                |ksdrcb joipbiv kxmuuwjr eusympkx                                |                                                                |\n"
                                                "|                                                                |                                        eaympe dsllncm gelj fdrp|eaympe dsllncm gelj fdrp                                        |eaympe dsllncm gelj fdrp                                        |                                                                |\n"
                                                "|                                                                |                                                                |                                                                |                                                                |                                                                |\n"
                                                "+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+\n"
                                                "|                                                                |                                                                |                                                                |                                                                |                            btmsykgko egnemknxf uxdkahnej clgpeg|\n"
                                                "|                                                                |                                                                |                                                                |                                                                |uqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg|\n"
                                                "|                                                                |                                                                |                                                                |                                                                |                                    uqqfxfn srukg jjwr pluylxivr|\n"
                                                "|                                                                |                                                                |                                                                |                                                                |                                        ehcevn rhiwyt grc bbehrc|\n"
                                                "|                                                                |                                                                |                                                                |                                                                |                      jvvhup chnqj urgxxw jmo yicq apmcyar icmo |\n"
                                                "|                                                                |                                                                |                                                                |                                                                |            piclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg|\n"
                                                "|                                                                |                                                                |                                                                |                                                                |         auavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs|\n"
                                                "|                                                                |                                                                |                                                                |                                                                |                                   wdh mqfutdypo mhebblrxn cybkr|\n"
                                                "|                                                                |                                                                |                                                                |                                                                |             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|\n"
                                                "|                                                                |                                                                |                                                                |                                                                |                                  knhrcx rrirp cxwvmxugi kxgwpqd|\n"
                                                "|                                                                |                                                                |                                                                |                                                                |                    cldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap|\n"
                                                "|                                                                |                                                                |                                                                |                                                                |             anbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj|\n"
                                                "|                                                                |                                                                |                                                                |                                                                |               ksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp|\n"
                                                "|                                                                |                                                                |                                                                |                                                                |                ehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo|\n"
                                                "|                                                                |                                                                |                                                                |                                                                |                  yicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso|\n"
                                                "|                                                                |                                                                |                                                                |                                                                |   jeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc|\n"
                                                "|                                                                |                                                                |                                                                |                                                                |          gcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr|\n"
                                                "|                                                                |                                                                |                                                                |                                                                |             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|\n"
                                                "|                                                                |                                                                |                                                                |                                                                |             knhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h|\n"
                                                "|                                                                |                                                                |                                                                |                                                                |                     bme iqrjh xmv emqap anbwxg ogaki ciky uwsfw|\n"
                                                "|                                                                |                                                                |                                                                |                                                                |                                     ngg xnyrswqhj wgnsgl fs csj|\n"
                                                "|                                                                |                                                                |                                                                |                                                                |                                ksdrcb joipbiv kxmuuwjr eusympkx|\n"
                                                "|                                                                |                                                                |                                                                |                                                                |                                        eaympe dsllncm gelj fdrp|\n"
                                                "|                                                                |                                                                |                                                                |                                                                |                                                                |\n"
                                                "+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+\n"<< flush;

        assert ( compareChars ( oss . str (),
                                "+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+\n"
                                "|                            btmsykgko egnemknxf uxdkahnej clgpeg|                                                                |                                                                |                                                                |btmsykgko egnemknxf uxdkahnej clgpeg                            |\n"
                                "|uqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg|                                                                |                                                                |                                                                |uqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg|\n"
                                "|                                    uqqfxfn srukg jjwr pluylxivr|                                                                |                                                                |                                                                |uqqfxfn srukg jjwr pluylxivr                                    |\n"
                                "|                                        ehcevn rhiwyt grc bbehrc|                                                                |                                                                |                                                                |ehcevn rhiwyt grc bbehrc                                        |\n"
                                "|                      jvvhup chnqj urgxxw jmo yicq apmcyar icmo |                                                                |                                                                |                                                                |jvvhup chnqj urgxxw jmo yicq apmcyar icmo                       |\n"
                                "|            piclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg|                                                                |                                                                |                                                                |piclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg            |\n"
                                "|         auavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs|                                                                |                                                                |                                                                |auavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs         |\n"
                                "|                                   wdh mqfutdypo mhebblrxn cybkr|                                                                |                                                                |                                                                |wdh mqfutdypo mhebblrxn cybkr                                   |\n"
                                "|             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|                                                                |                                                                |                                                                |niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj             |\n"
                                "|                                  knhrcx rrirp cxwvmxugi kxgwpqd|                                                                |                                                                |                                                                |knhrcx rrirp cxwvmxugi kxgwpqd                                  |\n"
                                "|                    cldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap|                                                                |                                                                |                                                                |cldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap                    |\n"
                                "|             anbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj|                                                                |                                                                |                                                                |anbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj             |\n"
                                "|               ksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp|                                                                |                                                                |                                                                |ksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp               |\n"
                                "|                ehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo|                                                                |                                                                |                                                                |ehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo                |\n"
                                "|                  yicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso|                                                                |                                                                |                                                                |yicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso                  |\n"
                                "|   jeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc|                                                                |                                                                |                                                                |jeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc   |\n"
                                "|          gcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr|                                                                |                                                                |                                                                |gcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr          |\n"
                                "|             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|                                                                |                                                                |                                                                |niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj             |\n"
                                "|             knhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h|                                                                |                                                                |                                                                |knhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h             |\n"
                                "|                     bme iqrjh xmv emqap anbwxg ogaki ciky uwsfw|                                                                |                                                                |                                                                |bme iqrjh xmv emqap anbwxg ogaki ciky uwsfw                     |\n"
                                "|                                     ngg xnyrswqhj wgnsgl fs csj|                                                                |                                                                |                                                                |ngg xnyrswqhj wgnsgl fs csj                                     |\n"
                                "|                                ksdrcb joipbiv kxmuuwjr eusympkx|                                                                |                                                                |                                                                |ksdrcb joipbiv kxmuuwjr eusympkx                                |\n"
                                "|                                        eaympe dsllncm gelj fdrp|                                                                |                                                                |                                                                |eaympe dsllncm gelj fdrp                                        |\n"
                                "|                                                                |                                                                |                                                                |                                                                |                                                                |\n"
                                "+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+\n"
                                "|                                                                |                            btmsykgko egnemknxf uxdkahnej clgpeg|                            btmsykgko egnemknxf uxdkahnej clgpeg|                                                                |                            btmsykgko egnemknxf uxdkahnej clgpeg|\n"
                                "|                                                                |uqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg|uqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg|                                                                |uqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg|\n"
                                "|                                                                |                                    uqqfxfn srukg jjwr pluylxivr|                                    uqqfxfn srukg jjwr pluylxivr|                                                                |                                    uqqfxfn srukg jjwr pluylxivr|\n"
                                "|                                                                |                                        ehcevn rhiwyt grc bbehrc|                                        ehcevn rhiwyt grc bbehrc|                                                                |                                        ehcevn rhiwyt grc bbehrc|\n"
                                "|                                                                |                      jvvhup chnqj urgxxw jmo yicq apmcyar icmo |                      jvvhup chnqj urgxxw jmo yicq apmcyar icmo |                                                                |                      jvvhup chnqj urgxxw jmo yicq apmcyar icmo |\n"
                                "|                                                                |            piclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg|            piclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg|                                                                |            piclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg|\n"
                                "|                                                                |         auavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs|         auavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs|                                                                |         auavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs|\n"
                                "|                                                                |                                   wdh mqfutdypo mhebblrxn cybkr|                                   wdh mqfutdypo mhebblrxn cybkr|                                                                |                                   wdh mqfutdypo mhebblrxn cybkr|\n"
                                "|                                                                |             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|                                                                |             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|\n"
                                "|                                                                |                                  knhrcx rrirp cxwvmxugi kxgwpqd|                                  knhrcx rrirp cxwvmxugi kxgwpqd|                                                                |                                  knhrcx rrirp cxwvmxugi kxgwpqd|\n"
                                "|                                                                |                    cldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap|                    cldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap|                                                                |                    cldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap|\n"
                                "|                                                                |             anbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj|             anbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj|                                                                |             anbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj|\n"
                                "|                                                                |               ksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp|               ksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp|                                                                |               ksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp|\n"
                                "|                                                                |                ehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo|                ehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo|                                                                |                ehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo|\n"
                                "|                                                                |                  yicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso|                  yicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso|                                                                |                  yicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso|\n"
                                "|                                                                |   jeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc|   jeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc|                                                                |   jeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc|\n"
                                "|                                                                |          gcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr|          gcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr|                                                                |          gcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr|\n"
                                "|                                                                |             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|                                                                |             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|\n"
                                "|                                                                |             knhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h|             knhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h|                                                                |             knhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h|\n"
                                "|                                                                |                     bme iqrjh xmv emqap anbwxg ogaki ciky uwsfw|                     bme iqrjh xmv emqap anbwxg ogaki ciky uwsfw|                                                                |                     bme iqrjh xmv emqap anbwxg ogaki ciky uwsfw|\n"
                                "|                                                                |                                     ngg xnyrswqhj wgnsgl fs csj|                                     ngg xnyrswqhj wgnsgl fs csj|                                                                |                                     ngg xnyrswqhj wgnsgl fs csj|\n"
                                "|                                                                |                                ksdrcb joipbiv kxmuuwjr eusympkx|                                ksdrcb joipbiv kxmuuwjr eusympkx|                                                                |                                ksdrcb joipbiv kxmuuwjr eusympkx|\n"
                                "|                                                                |                                        eaympe dsllncm gelj fdrp|                                        eaympe dsllncm gelj fdrp|                                                                |                                        eaympe dsllncm gelj fdrp|\n"
                                "|                                                                |                                                                |                                                                |                                                                |                                                                |\n"
                                "+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+\n"
                                "|                                                                |                                                                |btmsykgko egnemknxf uxdkahnej clgpeg                            |                                                                |                                                                |\n"
                                "|                                                                |                                                                |uqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg|                                                                |                                                                |\n"
                                "|                                                                |                                                                |uqqfxfn srukg jjwr pluylxivr                                    |                                                                |                                                                |\n"
                                "|                                                                |                                                                |ehcevn rhiwyt grc bbehrc                                        |                                                                |                                                                |\n"
                                "|                                                                |                                                                |jvvhup chnqj urgxxw jmo yicq apmcyar icmo                       |                                                                |                                                                |\n"
                                "|                                                                |                                                                |piclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg            |                                                                |                                                                |\n"
                                "|                                                                |                                                                |auavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs         |                                                                |                                                                |\n"
                                "|                                                                |                                                                |wdh mqfutdypo mhebblrxn cybkr                                   |                                                                |                                                                |\n"
                                "|                                                                |                                                                |niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj             |                                                                |                                                                |\n"
                                "|                                                                |                                                                |knhrcx rrirp cxwvmxugi kxgwpqd                                  |                                                                |                                                                |\n"
                                "|                                                                |                                                                |cldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap                    |                                                                |                                                                |\n"
                                "|                                                                |                                                                |anbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj             |                                                                |                                                                |\n"
                                "|                                                                |                                                                |ksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp               |                                                                |                                                                |\n"
                                "|                                                                |                                                                |ehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo                |                                                                |                                                                |\n"
                                "|                                                                |                                                                |yicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso                  |                                                                |                                                                |\n"
                                "|                                                                |                                                                |jeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc   |                                                                |                                                                |\n"
                                "|                                                                |                                                                |gcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr          |                                                                |                                                                |\n"
                                "|                                                                |                                                                |niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj             |                                                                |                                                                |\n"
                                "|                                                                |                                                                |knhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h             |                                                                |                                                                |\n"
                                "|                                                                |                                                                |bme iqrjh xmv emqap anbwxg ogaki ciky uwsfw                     |                                                                |                                                                |\n"
                                "|                                                                |                                                                |ngg xnyrswqhj wgnsgl fs csj                                     |                                                                |                                                                |\n"
                                "|                                                                |                                                                |ksdrcb joipbiv kxmuuwjr eusympkx                                |                                                                |                                                                |\n"
                                "|                                                                |                                                                |eaympe dsllncm gelj fdrp                                        |                                                                |                                                                |\n"
                                "|                                                                |                                                                |                                                                |                                                                |                                                                |\n"
                                "+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+\n"
                                "|                                                                |                            btmsykgko egnemknxf uxdkahnej clgpeg|btmsykgko egnemknxf uxdkahnej clgpeg                            |btmsykgko egnemknxf uxdkahnej clgpeg                            |                                                                |\n"
                                "|                                                                |uqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg|uqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg|uqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg|                                                                |\n"
                                "|                                                                |                                    uqqfxfn srukg jjwr pluylxivr|uqqfxfn srukg jjwr pluylxivr                                    |uqqfxfn srukg jjwr pluylxivr                                    |                                                                |\n"
                                "|                                                                |                                        ehcevn rhiwyt grc bbehrc|ehcevn rhiwyt grc bbehrc                                        |ehcevn rhiwyt grc bbehrc                                        |                                                                |\n"
                                "|                                                                |                      jvvhup chnqj urgxxw jmo yicq apmcyar icmo |jvvhup chnqj urgxxw jmo yicq apmcyar icmo                       |jvvhup chnqj urgxxw jmo yicq apmcyar icmo                       |                                                                |\n"
                                "|                                                                |            piclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg|piclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg            |piclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg            |                                                                |\n"
                                "|                                                                |         auavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs|auavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs         |auavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs         |                                                                |\n"
                                "|                                                                |                                   wdh mqfutdypo mhebblrxn cybkr|wdh mqfutdypo mhebblrxn cybkr                                   |wdh mqfutdypo mhebblrxn cybkr                                   |                                                                |\n"
                                "|                                                                |             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj             |niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj             |                                                                |\n"
                                "|                                                                |                                  knhrcx rrirp cxwvmxugi kxgwpqd|knhrcx rrirp cxwvmxugi kxgwpqd                                  |knhrcx rrirp cxwvmxugi kxgwpqd                                  |                                                                |\n"
                                "|                                                                |                    cldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap|cldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap                    |cldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap                    |                                                                |\n"
                                "|                                                                |             anbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj|anbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj             |anbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj             |                                                                |\n"
                                "|                                                                |               ksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp|ksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp               |ksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp               |                                                                |\n"
                                "|                                                                |                ehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo|ehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo                |ehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo                |                                                                |\n"
                                "|                                                                |                  yicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso|yicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso                  |yicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso                  |                                                                |\n"
                                "|                                                                |   jeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc|jeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc   |jeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc   |                                                                |\n"
                                "|                                                                |          gcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr|gcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr          |gcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr          |                                                                |\n"
                                "|                                                                |             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj             |niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj             |                                                                |\n"
                                "|                                                                |             knhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h|knhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h             |knhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h             |                                                                |\n"
                                "|                                                                |                     bme iqrjh xmv emqap anbwxg ogaki ciky uwsfw|bme iqrjh xmv emqap anbwxg ogaki ciky uwsfw                     |bme iqrjh xmv emqap anbwxg ogaki ciky uwsfw                     |                                                                |\n"
                                "|                                                                |                                     ngg xnyrswqhj wgnsgl fs csj|ngg xnyrswqhj wgnsgl fs csj                                     |ngg xnyrswqhj wgnsgl fs csj                                     |                                                                |\n"
                                "|                                                                |                                ksdrcb joipbiv kxmuuwjr eusympkx|ksdrcb joipbiv kxmuuwjr eusympkx                                |ksdrcb joipbiv kxmuuwjr eusympkx                                |                                                                |\n"
                                "|                                                                |                                        eaympe dsllncm gelj fdrp|eaympe dsllncm gelj fdrp                                        |eaympe dsllncm gelj fdrp                                        |                                                                |\n"
                                "|                                                                |                                                                |                                                                |                                                                |                                                                |\n"
                                "+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+\n"
                                "|                                                                |                                                                |                                                                |                                                                |                            btmsykgko egnemknxf uxdkahnej clgpeg|\n"
                                "|                                                                |                                                                |                                                                |                                                                |uqqfxfn srukg jjwr pluylxivrbtmsykgko egnemknxf uxdkahnej clgpeg|\n"
                                "|                                                                |                                                                |                                                                |                                                                |                                    uqqfxfn srukg jjwr pluylxivr|\n"
                                "|                                                                |                                                                |                                                                |                                                                |                                        ehcevn rhiwyt grc bbehrc|\n"
                                "|                                                                |                                                                |                                                                |                                                                |                      jvvhup chnqj urgxxw jmo yicq apmcyar icmo |\n"
                                "|                                                                |                                                                |                                                                |                                                                |            piclhnau dvp wwqg nfwso jeeiaq yyvgf esdpl tuvwdbpeg|\n"
                                "|                                                                |                                                                |                                                                |                                                                |         auavpu nxtddas tsmtbgjq ydc gcijfic dukwwrhnt qvbq kqhs|\n"
                                "|                                                                |                                                                |                                                                |                                                                |                                   wdh mqfutdypo mhebblrxn cybkr|\n"
                                "|                                                                |                                                                |                                                                |                                                                |             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|\n"
                                "|                                                                |                                                                |                                                                |                                                                |                                  knhrcx rrirp cxwvmxugi kxgwpqd|\n"
                                "|                                                                |                                                                |                                                                |                                                                |                    cldkd jgsgcffx nnwmut lx bme iqrjh xmv emqap|\n"
                                "|                                                                |                                                                |                                                                |                                                                |             anbwxg ogaki ciky uwsfw ngg xnyrswqhj wgnsglafs csj|\n"
                                "|                                                                |                                                                |                                                                |                                                                |               ksdrcb joipbiv kxmuuwjr  eaympe dsllncm gelj fdrp|\n"
                                "|                                                                |                                                                |                                                                |                                                                |                ehcevn rhiwyt grc bbehrc jvvhup chnqj urgxxw jmo|\n"
                                "|                                                                |                                                                |                                                                |                                                                |                  yicq apmcyar icmo hjsy piclhnau dvp wwqg nfwso|\n"
                                "|                                                                |                                                                |                                                                |                                                                |   jeeiaq yyvgf esdpl tu vw auavpuawd dagew nxtddas tsmtbgjq ydc|\n"
                                "|                                                                |                                                                |                                                                |                                                                |          gcijfic dukwwrhnt qvbq k wdh mqfutdypo mhebblrxn cybkr|\n"
                                "|                                                                |                                                                |                                                                |                                                                |             niv tlv bbxucd dxgchcfr shoq psyyxpk xtnbx ktdoqmrj|\n"
                                "|                                                                |                                                                |                                                                |                                                                |             knhrcx rrirp cxwvmxugi k cldkd jgsgcffx nnwmut lx h|\n"
                                "|                                                                |                                                                |                                                                |                                                                |                     bme iqrjh xmv emqap anbwxg ogaki ciky uwsfw|\n"
                                "|                                                                |                                                                |                                                                |                                                                |                                     ngg xnyrswqhj wgnsgl fs csj|\n"
                                "|                                                                |                                                                |                                                                |                                                                |                                ksdrcb joipbiv kxmuuwjr eusympkx|\n"
                                "|                                                                |                                                                |                                                                |                                                                |                                        eaympe dsllncm gelj fdrp|\n"
                                "|                                                                |                                                                |                                                                |                                                                |                                                                |\n"
                                "+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+----------------------------------------------------------------+\n"));
    }
/**
* Assert #321
* @author  test
* @link  https://progtester.eu/assert/321
*
* Potvrzena spravnost: 6x
* Nahlasena nefukcnost: 4x
* Bonus: NE
*
*/

/**
* Assert #351
* @author  mikulda3
* @link  https://progtester.eu/assert/351
*
* Potvrzena spravnost: 0x
* Nahlasena nefukcnost: 0x
* Bonus: NE
*
*/
    {
        // pomohlo mi to na nahodna data, bez kontroly vystupu, ale poznate, jestli jsou hlavne CImage spravne zarovnane
        CTable tt ( 5, 5 );
        tt.SetCell ( 0, 0, CText ( "Hello,\n\n\n", CText::ALIGN_LEFT ) );
        tt . SetCell ( 1, 1, CImage ()
                . AddRow ( "1abc" )
                . AddRow ( "2abc" )
                . AddRow ( "3abc" )
                . AddRow ( "4abc" )
                . AddRow ( "5abc" ) );
        tt . SetCell ( 1, 0, CImage ()
                . AddRow ( "111111" )
                . AddRow ( "222222" )
                . AddRow ( "333333" )
                . AddRow ( "444444" )
                . AddRow ( "555555" ) );
        tt . SetCell ( 1, 3, CImage ()
                . AddRow ( "1" )
                . AddRow ( "2" )
                . AddRow ( "3" ) );
        tt . SetCell ( 0, 3, CImage ()
                . AddRow ( "22222222222222" ) );
        tt . SetCell ( 0, 1, CText ( "progtes         t\n", CText::ALIGN_LEFT ) );
        tt . SetCell ( 1, 2, CText ( "Hello Kitty\nHello Kitty\nHello Kitty\nHello Kitty\nHello Kitty\nHello Kitty\nHello Kitty\nHello Kitty\nHello Kitty\nHello Kitty\nHello Kitty\n", CText::ALIGN_LEFT ) );
        tt . SetCell ( 0, 0, CText ( "Hello Kitty\nHello Kitty\nHello Kitty\nHello Kitty\nHello Kitty\nHello Kitty\nHello Kitty\nHello Kitty\nHello Kitty\nHello Kitty\nHello Kitty\n", CText::ALIGN_LEFT ) );
        cout << tt;
// vypis bunky s textem Hello Kitty musi vypsat i posledni prazdnou radku kvuli posledni \n
    }
    return 0;

}


int Vmain ( void )
{
    ostringstream oss;
    CTable t0 ( 3, 2 );
    t0 . SetCell ( 0, 0, CText ( "Hello,\n"
                                 "Hello Kitty", CText::ALIGN_LEFT ) );
    t0 . SetCell ( 1, 0, CText ( "Lorem ipsum dolor sit amet", CText::ALIGN_LEFT ) );
    t0 . SetCell ( 2, 0, CText ( "Bye,\n"
                                 "Hello Kitty", CText::ALIGN_RIGHT ) );
    t0.SetCell ( 1, 1, CImage ()
            .AddRow ( "###                   " )
            .AddRow ( "#  #                  " )
            .AddRow ( "#  # # ##   ###    ###" )
            .AddRow ( "###  ##    #   #  #  #" )
            .AddRow ( "#    #     #   #  #  #" )
            .AddRow ( "#    #     #   #  #  #" )
            .AddRow ( "#    #      ###    ###" )
            .AddRow ( "                     #" )
            .AddRow ( "                   ## " )
            .AddRow ( "                      " )
            .AddRow ( " #    ###   ###   #   " )
            .AddRow ( "###  #   # #     ###  " )
            .AddRow ( " #   #####  ###   #   " )
            .AddRow ( " #   #         #  #   " )
            .AddRow ( "  ##  ###   ###    ## " ) );
    t0 . SetCell ( 2, 1, CEmpty () );
    oss . str ("");
    oss . clear ();
    oss << t0;
    assert ( oss . str () ==
             "+--------------------------+----------------------+\n"
             "|Hello,                    |                      |\n"
             "|Hello Kitty               |                      |\n"
             "+--------------------------+----------------------+\n"
             "|Lorem ipsum dolor sit amet|###                   |\n"
             "|                          |#  #                  |\n"
             "|                          |#  # # ##   ###    ###|\n"
             "|                          |###  ##    #   #  #  #|\n"
             "|                          |#    #     #   #  #  #|\n"
             "|                          |#    #     #   #  #  #|\n"
             "|                          |#    #      ###    ###|\n"
             "|                          |                     #|\n"
             "|                          |                   ## |\n"
             "|                          |                      |\n"
             "|                          | #    ###   ###   #   |\n"
             "|                          |###  #   # #     ###  |\n"
             "|                          | #   #####  ###   #   |\n"
             "|                          | #   #         #  #   |\n"
             "|                          |  ##  ###   ###    ## |\n"
             "+--------------------------+----------------------+\n"
             "|                      Bye,|                      |\n"
             "|               Hello Kitty|                      |\n"
             "+--------------------------+----------------------+\n" );
    t0 . SetCell ( 0, 1, t0 . GetCell ( 1, 1 ) );
    t0 . SetCell ( 2, 1, CImage ()
            . AddRow ( "*****   *      *  *      ******* ******  *" )
            . AddRow ( "*    *  *      *  *      *            *  *" )
            . AddRow ( "*    *  *      *  *      *           *   *" )
            . AddRow ( "*    *  *      *  *      *****      *    *" )
            . AddRow ( "****    *      *  *      *         *     *" )
            . AddRow ( "*  *    *      *  *      *        *       " )
            . AddRow ( "*   *   *      *  *      *       *       *" )
            . AddRow ( "*    *    *****   ****** ******* ******  *" ) );
    dynamic_cast<CText &> ( t0 . GetCell ( 1, 0 ) ) . SetText ( "Lorem ipsum dolor sit amet,\n"
                                                                "consectetur adipiscing\n"
                                                                "elit. Curabitur scelerisque\n"
                                                                "lorem vitae lectus cursus,\n"
                                                                "vitae porta ante placerat. Class aptent taciti\n"
                                                                "sociosqu ad litora\n"
                                                                "torquent per\n"
                                                                "conubia nostra,\n"
                                                                "per inceptos himenaeos.\n"
                                                                "\n"
                                                                "Donec tincidunt augue\n"
                                                                "sit amet metus\n"
                                                                "pretium volutpat.\n"
                                                                "Donec faucibus,\n"
                                                                "ante sit amet\n"
                                                                "luctus posuere,\n"
                                                                "mauris tellus" );
    oss . str ("");
    oss . clear ();
    oss << t0;
    // cout << oss.str() << flush;
    assert ( oss . str () ==
             "+----------------------------------------------+------------------------------------------+\n"
             "|Hello,                                        |          ###                             |\n"
             "|Hello Kitty                                   |          #  #                            |\n"
             "|                                              |          #  # # ##   ###    ###          |\n"
             "|                                              |          ###  ##    #   #  #  #          |\n"
             "|                                              |          #    #     #   #  #  #          |\n"
             "|                                              |          #    #     #   #  #  #          |\n"
             "|                                              |          #    #      ###    ###          |\n"
             "|                                              |                               #          |\n"
             "|                                              |                             ##           |\n"
             "|                                              |                                          |\n"
             "|                                              |           #    ###   ###   #             |\n"
             "|                                              |          ###  #   # #     ###            |\n"
             "|                                              |           #   #####  ###   #             |\n"
             "|                                              |           #   #         #  #             |\n"
             "|                                              |            ##  ###   ###    ##           |\n"
             "+----------------------------------------------+------------------------------------------+\n"
             "|Lorem ipsum dolor sit amet,                   |                                          |\n"
             "|consectetur adipiscing                        |          ###                             |\n"
             "|elit. Curabitur scelerisque                   |          #  #                            |\n"
             "|lorem vitae lectus cursus,                    |          #  # # ##   ###    ###          |\n"
             "|vitae porta ante placerat. Class aptent taciti|          ###  ##    #   #  #  #          |\n"
             "|sociosqu ad litora                            |          #    #     #   #  #  #          |\n"
             "|torquent per                                  |          #    #     #   #  #  #          |\n"
             "|conubia nostra,                               |          #    #      ###    ###          |\n"
             "|per inceptos himenaeos.                       |                               #          |\n"
             "|                                              |                             ##           |\n"
             "|Donec tincidunt augue                         |                                          |\n"
             "|sit amet metus                                |           #    ###   ###   #             |\n"
             "|pretium volutpat.                             |          ###  #   # #     ###            |\n"
             "|Donec faucibus,                               |           #   #####  ###   #             |\n"
             "|ante sit amet                                 |           #   #         #  #             |\n"
             "|luctus posuere,                               |            ##  ###   ###    ##           |\n"
             "|mauris tellus                                 |                                          |\n"
             "+----------------------------------------------+------------------------------------------+\n"
             "|                                          Bye,|*****   *      *  *      ******* ******  *|\n"
             "|                                   Hello Kitty|*    *  *      *  *      *            *  *|\n"
             "|                                              |*    *  *      *  *      *           *   *|\n"
             "|                                              |*    *  *      *  *      *****      *    *|\n"
             "|                                              |****    *      *  *      *         *     *|\n"
             "|                                              |*  *    *      *  *      *        *       |\n"
             "|                                              |*   *   *      *  *      *       *       *|\n"
             "|                                              |*    *    *****   ****** ******* ******  *|\n"
             "+----------------------------------------------+------------------------------------------+\n" );
    CTable t1 ( t0 );
    t1 . SetCell ( 1, 0, CEmpty () );
    t1 . SetCell ( 1, 1, CEmpty () );
    oss . str ("");
    oss . clear ();
    oss << t0;
    assert ( oss . str () ==
             "+----------------------------------------------+------------------------------------------+\n"
             "|Hello,                                        |          ###                             |\n"
             "|Hello Kitty                                   |          #  #                            |\n"
             "|                                              |          #  # # ##   ###    ###          |\n"
             "|                                              |          ###  ##    #   #  #  #          |\n"
             "|                                              |          #    #     #   #  #  #          |\n"
             "|                                              |          #    #     #   #  #  #          |\n"
             "|                                              |          #    #      ###    ###          |\n"
             "|                                              |                               #          |\n"
             "|                                              |                             ##           |\n"
             "|                                              |                                          |\n"
             "|                                              |           #    ###   ###   #             |\n"
             "|                                              |          ###  #   # #     ###            |\n"
             "|                                              |           #   #####  ###   #             |\n"
             "|                                              |           #   #         #  #             |\n"
             "|                                              |            ##  ###   ###    ##           |\n"
             "+----------------------------------------------+------------------------------------------+\n"
             "|Lorem ipsum dolor sit amet,                   |                                          |\n"
             "|consectetur adipiscing                        |          ###                             |\n"
             "|elit. Curabitur scelerisque                   |          #  #                            |\n"
             "|lorem vitae lectus cursus,                    |          #  # # ##   ###    ###          |\n"
             "|vitae porta ante placerat. Class aptent taciti|          ###  ##    #   #  #  #          |\n"
             "|sociosqu ad litora                            |          #    #     #   #  #  #          |\n"
             "|torquent per                                  |          #    #     #   #  #  #          |\n"
             "|conubia nostra,                               |          #    #      ###    ###          |\n"
             "|per inceptos himenaeos.                       |                               #          |\n"
             "|                                              |                             ##           |\n"
             "|Donec tincidunt augue                         |                                          |\n"
             "|sit amet metus                                |           #    ###   ###   #             |\n"
             "|pretium volutpat.                             |          ###  #   # #     ###            |\n"
             "|Donec faucibus,                               |           #   #####  ###   #             |\n"
             "|ante sit amet                                 |           #   #         #  #             |\n"
             "|luctus posuere,                               |            ##  ###   ###    ##           |\n"
             "|mauris tellus                                 |                                          |\n"
             "+----------------------------------------------+------------------------------------------+\n"
             "|                                          Bye,|*****   *      *  *      ******* ******  *|\n"
             "|                                   Hello Kitty|*    *  *      *  *      *            *  *|\n"
             "|                                              |*    *  *      *  *      *           *   *|\n"
             "|                                              |*    *  *      *  *      *****      *    *|\n"
             "|                                              |****    *      *  *      *         *     *|\n"
             "|                                              |*  *    *      *  *      *        *       |\n"
             "|                                              |*   *   *      *  *      *       *       *|\n"
             "|                                              |*    *    *****   ****** ******* ******  *|\n"
             "+----------------------------------------------+------------------------------------------+\n" );
    oss . str ("");
    oss . clear ();
    oss << t1;
    assert ( oss . str () ==
             "+-----------+------------------------------------------+\n"
             "|Hello,     |          ###                             |\n"
             "|Hello Kitty|          #  #                            |\n"
             "|           |          #  # # ##   ###    ###          |\n"
             "|           |          ###  ##    #   #  #  #          |\n"
             "|           |          #    #     #   #  #  #          |\n"
             "|           |          #    #     #   #  #  #          |\n"
             "|           |          #    #      ###    ###          |\n"
             "|           |                               #          |\n"
             "|           |                             ##           |\n"
             "|           |                                          |\n"
             "|           |           #    ###   ###   #             |\n"
             "|           |          ###  #   # #     ###            |\n"
             "|           |           #   #####  ###   #             |\n"
             "|           |           #   #         #  #             |\n"
             "|           |            ##  ###   ###    ##           |\n"
             "+-----------+------------------------------------------+\n"
             "+-----------+------------------------------------------+\n"
             "|       Bye,|*****   *      *  *      ******* ******  *|\n"
             "|Hello Kitty|*    *  *      *  *      *            *  *|\n"
             "|           |*    *  *      *  *      *           *   *|\n"
             "|           |*    *  *      *  *      *****      *    *|\n"
             "|           |****    *      *  *      *         *     *|\n"
             "|           |*  *    *      *  *      *        *       |\n"
             "|           |*   *   *      *  *      *       *       *|\n"
             "|           |*    *    *****   ****** ******* ******  *|\n"
             "+-----------+------------------------------------------+\n" );
    t1 = t0;
    t1 . SetCell ( 0, 0, CEmpty () );
    t1 . SetCell ( 1, 1, CImage ()
            . AddRow ( "  ********                    " )
            . AddRow ( " **********                   " )
            . AddRow ( "**        **                  " )
            . AddRow ( "**             **        **   " )
            . AddRow ( "**             **        **   " )
            . AddRow ( "***         ********  ********" )
            . AddRow ( "****        ********  ********" )
            . AddRow ( "****           **        **   " )
            . AddRow ( "****           **        **   " )
            . AddRow ( "****      **                  " )
            . AddRow ( " **********                   " )
            . AddRow ( "  ********                    " ) );
    oss . str ("");
    oss . clear ();
    oss << t0;
    cout << t0 << flush;
    assert ( oss . str () ==
             "+----------------------------------------------+------------------------------------------+\n"
             "|Hello,                                        |          ###                             |\n"
             "|Hello Kitty                                   |          #  #                            |\n"
             "|                                              |          #  # # ##   ###    ###          |\n"
             "|                                              |          ###  ##    #   #  #  #          |\n"
             "|                                              |          #    #     #   #  #  #          |\n"
             "|                                              |          #    #     #   #  #  #          |\n"
             "|                                              |          #    #      ###    ###          |\n"
             "|                                              |                               #          |\n"
             "|                                              |                             ##           |\n"
             "|                                              |                                          |\n"
             "|                                              |           #    ###   ###   #             |\n"
             "|                                              |          ###  #   # #     ###            |\n"
             "|                                              |           #   #####  ###   #             |\n"
             "|                                              |           #   #         #  #             |\n"
             "|                                              |            ##  ###   ###    ##           |\n"
             "+----------------------------------------------+------------------------------------------+\n"
             "|Lorem ipsum dolor sit amet,                   |                                          |\n"
             "|consectetur adipiscing                        |          ###                             |\n"
             "|elit. Curabitur scelerisque                   |          #  #                            |\n"
             "|lorem vitae lectus cursus,                    |          #  # # ##   ###    ###          |\n"
             "|vitae porta ante placerat. Class aptent taciti|          ###  ##    #   #  #  #          |\n"
             "|sociosqu ad litora                            |          #    #     #   #  #  #          |\n"
             "|torquent per                                  |          #    #     #   #  #  #          |\n"
             "|conubia nostra,                               |          #    #      ###    ###          |\n"
             "|per inceptos himenaeos.                       |                               #          |\n"
             "|                                              |                             ##           |\n"
             "|Donec tincidunt augue                         |                                          |\n"
             "|sit amet metus                                |           #    ###   ###   #             |\n"
             "|pretium volutpat.                             |          ###  #   # #     ###            |\n"
             "|Donec faucibus,                               |           #   #####  ###   #             |\n"
             "|ante sit amet                                 |           #   #         #  #             |\n"
             "|luctus posuere,                               |            ##  ###   ###    ##           |\n"
             "|mauris tellus                                 |                                          |\n"
             "+----------------------------------------------+------------------------------------------+\n"
             "|                                          Bye,|*****   *      *  *      ******* ******  *|\n"
             "|                                   Hello Kitty|*    *  *      *  *      *            *  *|\n"
             "|                                              |*    *  *      *  *      *           *   *|\n"
             "|                                              |*    *  *      *  *      *****      *    *|\n"
             "|                                              |****    *      *  *      *         *     *|\n"
             "|                                              |*  *    *      *  *      *        *       |\n"
             "|                                              |*   *   *      *  *      *       *       *|\n"
             "|                                              |*    *    *****   ****** ******* ******  *|\n"
             "+----------------------------------------------+------------------------------------------+\n" );
    oss . str ("");
    oss . clear ();
    oss << t1;
    assert ( oss . str () ==
             "+----------------------------------------------+------------------------------------------+\n"
             "|                                              |          ###                             |\n"
             "|                                              |          #  #                            |\n"
             "|                                              |          #  # # ##   ###    ###          |\n"
             "|                                              |          ###  ##    #   #  #  #          |\n"
             "|                                              |          #    #     #   #  #  #          |\n"
             "|                                              |          #    #     #   #  #  #          |\n"
             "|                                              |          #    #      ###    ###          |\n"
             "|                                              |                               #          |\n"
             "|                                              |                             ##           |\n"
             "|                                              |                                          |\n"
             "|                                              |           #    ###   ###   #             |\n"
             "|                                              |          ###  #   # #     ###            |\n"
             "|                                              |           #   #####  ###   #             |\n"
             "|                                              |           #   #         #  #             |\n"
             "|                                              |            ##  ###   ###    ##           |\n"
             "+----------------------------------------------+------------------------------------------+\n"
             "|Lorem ipsum dolor sit amet,                   |                                          |\n"
             "|consectetur adipiscing                        |                                          |\n"
             "|elit. Curabitur scelerisque                   |        ********                          |\n"
             "|lorem vitae lectus cursus,                    |       **********                         |\n"
             "|vitae porta ante placerat. Class aptent taciti|      **        **                        |\n"
             "|sociosqu ad litora                            |      **             **        **         |\n"
             "|torquent per                                  |      **             **        **         |\n"
             "|conubia nostra,                               |      ***         ********  ********      |\n"
             "|per inceptos himenaeos.                       |      ****        ********  ********      |\n"
             "|                                              |      ****           **        **         |\n"
             "|Donec tincidunt augue                         |      ****           **        **         |\n"
             "|sit amet metus                                |      ****      **                        |\n"
             "|pretium volutpat.                             |       **********                         |\n"
             "|Donec faucibus,                               |        ********                          |\n"
             "|ante sit amet                                 |                                          |\n"
             "|luctus posuere,                               |                                          |\n"
             "|mauris tellus                                 |                                          |\n"
             "+----------------------------------------------+------------------------------------------+\n"
             "|                                          Bye,|*****   *      *  *      ******* ******  *|\n"
             "|                                   Hello Kitty|*    *  *      *  *      *            *  *|\n"
             "|                                              |*    *  *      *  *      *           *   *|\n"
             "|                                              |*    *  *      *  *      *****      *    *|\n"
             "|                                              |****    *      *  *      *         *     *|\n"
             "|                                              |*  *    *      *  *      *        *       |\n"
             "|                                              |*   *   *      *  *      *       *       *|\n"
             "|                                              |*    *    *****   ****** ******* ******  *|\n"
             "+----------------------------------------------+------------------------------------------+\n" );

    return 0;
}
