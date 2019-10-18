#ifndef DEF_MAFENETRE
#define DEF_MAFENETRE

#include <QApplication>
#include <QResizeEvent>
#include <QMoveEvent>
#include <QCloseEvent>
#include "WWidgets/WWidget.h"
#include "WWidgets/WPushButton.h"
#include "WWidgets/WLabel.h"
#include "Board/BoardGenerator.h"
#include "Tobiidget.h"

class MaFenetre : public WWidget
{
    Q_OBJECT

    public:
        MaFenetre(Tobiidget* tobiidget);
        static bool isRunning;

    public slots:
        void cursorMove(int x, int y);
        void openBoard();
        void openGenerator();

    protected:
        void resizeEvent(QResizeEvent* event) override;
        void moveEvent(QMoveEvent* event) override;
        void closeEvent(QCloseEvent *event) override;

    private:
        WLabel* m_LabelScreen;
        WLabel* m_LabelWindow;
        WLabel* m_LabelTobii;
        WPushButton* m_boutonTR;
        WPushButton* m_boutonTL;
        WPushButton* m_boutonBIG;
        WPushButton* m_boutonBR;
        WPushButton* m_boutonBL;
        WPushButton* m_boutonB1;
        WPushButton* m_boutonB2;
        WPushButton* m_boutonB3;
        Tobiidget* m_tobiidget;
        BoardGenerator m_Generator;
};

#endif
