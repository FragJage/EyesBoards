#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include "Tobiidget.h"
#include "mafenetre.h"
#include "Board/Board.h"

Board* mainboard;
MaFenetre* fenetre;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);

    Tobiidget tobii;
    fenetre = new MaFenetre(&tobii);
    mainboard = new Board("Test");

    QObject::connect(&tobii, SIGNAL(eyesMoved(int, int)), mainboard, SLOT(cursorMove(int, int)));
    fenetre->show();

    return app.exec();
}
