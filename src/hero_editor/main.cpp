#pragma execution_character_set("utf-8")

#include <QCoreApplication>
#include <QDebug>
#include <QVariant>
#include <QtCore>
#include <QtGlobal>

#include <iostream>

#include "QXlsx/header/xlsxcellrange.h"
#include "QXlsx/header/xlsxchart.h"
#include "QXlsx/header/xlsxchartsheet.h"
#include "QXlsx/header/xlsxdocument.h"
#include "QXlsx/header/xlsxrichstring.h"
#include "QXlsx/header/xlsxworkbook.h"

int main(int argc, char* argv[])
{
    using namespace std;
    using namespace QXlsx;

    QCoreApplication app(argc, argv);

    // 获取表格:表单、大小
    Document* xlsx_r = new Document("我是大侠.xlsx");
    if (!xlsx_r->load()) // load excel file
    {
        return 0;
    }

    auto sheet_names = xlsx_r->sheetNames();
    auto range = xlsx_r->dimension();
    int row = 1;
    int col = 1;
    for (; col <= range.columnCount(); ++col) {
        Cell* cell = xlsx_r->cellAt(row, col);
        if (cell != NULL) {
            QVariant var = cell->readValue();
            qDebug() << row << col << var;
        }
    }

    return 0;
}
