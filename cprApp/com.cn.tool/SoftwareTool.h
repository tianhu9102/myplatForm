#ifndef SOFTWARETOOL_H
#define SOFTWARETOOL_H

#include "Importinclude.h"

#include <QSql>
#include <qsqlquery.h>
#include <QSqlError>
#include <QSqlTableModel>

class SoftwareTool
{
public:
    SoftwareTool();
    void initVariable();
    void displaySplashScreen();
    QSplashScreen *get_splashscreen();

    void connectDataBase();

private:
    QSplashScreen *splashscreen;
    QFont splashFont;
    QStringList drivers;
    QSqlDatabase db;

    Qt::Alignment topRight;
    QDateTime dateTime;
};

#endif // SOFTWARETOOL_H
