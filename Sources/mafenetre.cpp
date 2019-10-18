#include <QDesktopWidget>
#include <QtDebug>
#include "mafenetre.h"
#include "Board/BoardGenerator.h"

bool MaFenetre::isRunning = true;
extern Board* mainboard;

MaFenetre::MaFenetre(Tobiidget* tobiidget) : WWidget()
{
    m_LabelScreen = new WLabel(this);
    m_LabelScreen->setGeometry(10, 10, 140, 18);
    m_LabelScreen->setText(QString("Ecran %1x%2").arg(QApplication::desktop()->width()).arg(QApplication::desktop()->height()));
    m_LabelScreen->setStyleSheet("QLabel { background-color : #AAAAAA;}");
    m_LabelScreen->setAnchor(WAnchorFlags::Width);

    m_LabelWindow = new WLabel(this);
    m_LabelWindow->setGeometry(10, 30, 140, 18);
    m_LabelWindow->setStyleSheet("QLabel { background-color : #AAAAAA;}");
    m_LabelWindow->setAnchor(WAnchorFlags::Width);

    m_LabelTobii = new WLabel(this);
    m_LabelTobii->setGeometry(10, 50, 140, 18);
    m_LabelTobii->setStyleSheet("QLabel { background-color : #AAAAAA;}");
    m_LabelTobii->setAnchor(WAnchorFlags::Width);

    m_boutonTL = new WPushButton("TL", this);
    m_boutonTL->setGeometry(10, 70, 50, 20);
    m_boutonTL->setAnchor(WAnchorFlags::TopLeft);

    m_boutonTR = new WPushButton("TR", this);
    m_boutonTR->setGeometry(100, 70, 50, 20);
    m_boutonTR->setAnchor(WAnchorFlags::Right);

    m_boutonBIG = new WPushButton("Open the board !", this);
    m_boutonBIG->setGeometry(10, 91, 140, 20);
    m_boutonBIG->setAnchor(WAnchorFlags::Width|WAnchorFlags::Height);

    m_boutonBL = new WPushButton("BL", this);
    m_boutonBL->setGeometry(10, 112, 70, 20);
    m_boutonBL->setAnchor(0,100,50,0);

    m_boutonBR = new WPushButton("BR", this);
    m_boutonBR->setGeometry(80, 112, 70, 20);
    m_boutonBR->setAnchor(50,100,50,0);

    m_boutonB1 = new WPushButton("B1", this);
    m_boutonB1->setGeometry(10, 133, 40, 20);
    m_boutonB1->setAnchor(0, 100,33.33,0);

    m_boutonB2 = new WPushButton("B2", this);
    m_boutonB2->setGeometry(60, 133, 40, 20);
    m_boutonB2->setAnchor(33.33,100,33.33,0);

    m_boutonB3 = new WPushButton("B3", this);
    m_boutonB3->setGeometry(110, 133, 40, 20);
    m_boutonB3->setAnchor(66.66,100,33.33,0);

    m_tobiidget = tobiidget;

    QObject::connect(m_tobiidget, SIGNAL(eyesMoved(int, int)), this, SLOT(cursorMove(int, int)));
    QObject::connect(m_boutonBIG, SIGNAL(clicked()), this, SLOT(openBoard()));
    QObject::connect(m_boutonTL, SIGNAL(clicked()), this, SLOT(openGenerator()));
}

void MaFenetre::cursorMove(int x, int y)
{
    m_LabelTobii->setText(QString("Tobii %1x%2").arg(x).arg(y));
}

void MaFenetre::openBoard()
{
    mainboard->defaultFrames(4, 3);
    mainboard->show();
}

void MaFenetre::openGenerator()
{
#ifdef _WIN32
    BoardError err = m_Generator.loadBoards("C:\\Users\\Utilisateur\\Documents\\EyesBoards\\Couleurs\\couleurs.json");
#else
    BoardError err = m_Generator.loadBoards("/home/francois/EyesBoards/Couleurs/couleurs.json");
#endif
    if(err.code()!="")
    {
        qWarning() << err.message();
        return;
    }

    Board* brd;
    int i=0;
    while((brd=m_Generator.getBoard(i))!=nullptr)
    {
        QObject::connect(m_tobiidget, SIGNAL(eyesMoved(int, int)), brd, SLOT(cursorMove(int, int)));
        i++;
    }

    m_Generator.show();
}

void MaFenetre::closeEvent(QCloseEvent* event)
{
    event->accept();
    MaFenetre::isRunning = false;
}

void MaFenetre::resizeEvent(QResizeEvent* event)
{
    QRect geom = geometry();
    QString s = QString("Fenêtre %1,%2 -> %3x%4").arg(geom.x()).arg(geom.y()).arg(geom.width()).arg(geom.height());
    m_LabelWindow->setText(s);
    WWidget::resizeEvent(event);
}

void MaFenetre::moveEvent(QMoveEvent* event)
{
    QRect geom = geometry();
    QString s = QString("Fenêtre %1,%2 -> %3x%4").arg(geom.x()).arg(geom.y()).arg(geom.width()).arg(geom.height());
    m_LabelWindow->setText(s);
    WWidget::moveEvent(event);
}
