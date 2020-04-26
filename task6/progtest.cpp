#ifndef __PROGTEST__

#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <memory>
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
#endif /* __PROGTEST__ */

class CTable;
class CCell;
class CEmpty;
class CTextContentCell;

class CText;
class CImage;

/* ====================================================== */
/*                     class definitions                   */
/* ====================================================== */


/*
 * Main class containing data store for table cells.
 * Takes care of their rendering.
 * */
class CTable {
public:

    /*
     * @param rows height of the table
     * @param cols width of the table
     * */
    CTable(int rows, int cols) : body(rows, vector<CCell *>(cols, nullptr)), width(cols), height(rows) {}

    CTable(const CTable &);

    CTable &operator=(const CTable &);

    ~CTable();

    /*
     * raises exception when invalid coordinates are specified
     * @param row Y coordinate
     * @param col X coordinate
     * @return CCell (or subclass) reference to the specified cell
     * */
    CCell &GetCell(int row, int col);

    /*
     * raises exception when invalid coordinates are specified
     * @param row Y coordinate
     * @param col X coordinate
     * @param cell reference to new content of the specified cell
     * @return CCell (or subclass) reference to the specified cell
     * */
    void SetCell(int row, int col, const CCell &cell);

    friend ostream &operator<<(ostream &, const CTable &);

private:
    vector<vector<CCell *> > body;
    size_t width;
    size_t height;

    void empty();

};


/*
 * Base class for table cells.
 * When rendering each cell is split into sub rows that get printed into the stream
 * */
class CCell {
public:

    CCell() = default;

    virtual ~CCell() = default;

    virtual CCell *copy() const { return new CCell(*this); }

    /* overwrite this function in baseclasses.
     * @param row number of the cells inner cell row
     * @param w the required width of cell
     * @param h the required height of cell
     * this dummy class always print space depending on the cell width
     * */
    inline virtual void print(ostream &os, size_t row, size_t w, size_t h){ os << string(w, ' '); }

    /* @return width needed to render this cell */
    virtual size_t GetWidth() const { return 0; }

    /* @return height needed to render this cell */
    virtual size_t GetHeight() const { return 0; }


};

/* Empty table cell */
class CEmpty : virtual public CCell {
private:
    CEmpty *copy() const override { return new CEmpty(*this); }
};

/* Cell that holds any type of text information.
 * Can be aligned horizontally or vertically based on Valign and Align
 * */
class CTextContentCell : virtual public CCell {
public:

    enum Align {
        ALIGN_LEFT, CENTER, ALIGN_RIGHT
    };

    enum VAlign {
        TOP, MIDDLE, BOTTOM
    };

    CTextContentCell &operator=(const CTextContentCell &x);

    /* Vertically center the cell body. If the height(width) is odd, move it upwards(to left)
     * @param os stream to print to
     * @param row which cell sub row to print
     * @param w required cell width
     * @param h height of the cell
     * */
    void print(ostream &os, size_t row, size_t w, size_t h) override;

    /* prints one cell sub row based on the alignment such that it fits cell width into os
     * assume content fits into width
     * @param os stream to print to
     * @param row which cell sub row to print
     * @param w required cell width
     * */
    virtual void printRow(ostream &os, size_t row, size_t w);

    /* @return width needed to render this cell */
    size_t GetWidth() const override { return width; }

    /* @return height needed to render this cell */
    size_t GetHeight() const override { return content.size(); }



protected:
    vector<string> content;
    std::size_t width = 0; // height is stored inside content.size()
    Align alignment = CENTER;
    VAlign valignment = MIDDLE;

};

class CText : virtual public CTextContentCell{
public:

    CText(const string &text, Align alignment);

    ~CText() override = default;

    CText *copy() const override { return new CText(*this); }

    /* erase old text and set new
     * @param new text*/
    void SetText(const string &text);
};

class CImage : virtual public CCell, public CTextContentCell {
public:

    /* @return self with appended image Row */
    CImage &AddRow(const string &imageRow);

private:
    CImage *copy() const override { return new CImage(*this); }

};


/* ====================================================== */
/*            class function implementations              */
/* ====================================================== */

/* CTable function definitions */

CTable::CTable(const CTable &other) {
    width = other.width;
    height = other.height;

    body = vector<vector<CCell * >>(height, vector<CCell *>(width, nullptr));

    for (size_t y = 0; y < height; y++)
        for (size_t x = 0; x < width; x++) {
            if (other.body[y][x]) {
                body[y][x] = other.body[y][x]->copy();
            }
        }

}

CTable &CTable::operator=(const CTable &other) {
    if (&other == this) return *this;
    empty();
    width = other.width;
    height = other.height;

    body = vector<vector<CCell * >>(height, vector<CCell *>(width, nullptr));

    for (size_t y = 0; y < height; y++)
        for (size_t x = 0; x < width; x++) {
            if (other.body[y][x]) {
                body[y][x] = other.body[y][x]->copy();
            }
        }
    return *this;
}

CTable::~CTable() {
    for (auto &row: body)
        for (auto &cell: row)
            delete cell;
}

CCell & CTable::GetCell(int row, int col)  {
    CCell &tmp = *body.at(row).at(col);
    return tmp;
}

void CTable::SetCell(int row, int col, const CCell &cell) {
    if (&cell == body.at(row).at(col)) return;
    delete body[row][col];
    body[row][col] = cell.copy();
}

ostream &operator<<(ostream &os, const CTable &table) {

    vector<size_t> widths(table.width, 0);
    vector<size_t> heights(table.height, 0);

    for (size_t y = 0; y < table.height; y++)
        for (size_t x = 0; x < table.width; x++) {
            if (table.body[y][x]) {
                heights[y] = max(heights[y], table.body[y][x]->GetHeight());
                widths[x] = max(widths[x], table.body[y][x]->GetWidth());
            }
        }

    // print first row
    for (auto width : widths)
        os << '+' << string(width, '-');
    os << "+" << endl;

    for (size_t y = 0; y < heights.size(); y++) { // for each row

        for (size_t sub_y = 0; sub_y < heights[y]; sub_y++) { // for each sub_row

            // for(auto & cell : table.body[y]){ // for each cell (x)
            for (size_t x = 0; x < table.body[y].size(); x++) { // for each cell (x)
                os << '|' << flush;
                if (table.body[y][x]) table.body[y][x]->print(os, sub_y, widths[x], heights[y]);
                else os << string(widths[x], ' ');
            }
            os << '|' << endl;
        }

        for (auto width : widths)
            os << '+' << string(width, '-');
        os << "+" << endl;

    }

    return os;
}

void CTable::empty() {

    for (auto &row: body)
        for (auto &cell: row)
            delete cell;

    body.clear();
    width = 0;
    height = 0;
}


/* CTextContentCell function definitions */

CTextContentCell &CTextContentCell::operator=(const CTextContentCell &x) {
    if (this != &x) {
        content = x.content;
        width = x.width;
        alignment = x.alignment;
        valignment = x.valignment;
    }
    return *this;
}

void CTextContentCell::print(ostream &os, size_t row, size_t w, size_t h) {

    size_t val = h - content.size();
    if (valignment == TOP && row < content.size()) {
        printRow(os, row, w);
    } else if (valignment == BOTTOM && row >= val) {
        size_t off = row - (h - content.size());
        printRow(os, off, w);
    } else if (valignment == MIDDLE && row >= val / 2 && row < val / 2 + content.size()) {
        printRow(os, row - val / 2, w);
    } else
        os << string(w, ' ');
}

void CTextContentCell::printRow(ostream &os, size_t row, size_t w) {

    if (alignment == ALIGN_LEFT) os << left << setw(w) << setfill(' ') << content[row];
    else if (alignment == ALIGN_RIGHT) os << right << setw(w) << setfill(' ') << content[row];
    else { // CENTER
        size_t space = (w - (int) width) / 2;
        if ((w - width) % 2)
            os << string(space, ' ') << setw(width) << setfill(' ') << content[row] << string(space + 1, ' ');
        else os << string(space, ' ') << setw(width) << setfill(' ') << content[row] << string(space, ' ');
    }
}


/* CText function definitions */

CText::CText(const string &text, CTextContentCell::Align alignment) {
    this->alignment = alignment;
    this->valignment = TOP;
    SetText(text);
}

void CText::SetText(const string &text) {
    content.clear();
    string tmp;
    stringstream ss(text);
    while (getline(ss, tmp, '\n')) {
        content.push_back(tmp);
        width = max(tmp.size(), width);
    }
}


/* CImage function definitions */

CImage &CImage::AddRow(const string &imageRow) {

    width = imageRow.size();
    content.push_back(imageRow);
    return *this;
}

