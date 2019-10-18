#ifndef BOARDSIGNALS_H
#define BOARDSIGNALS_H

#include <QWidget>

class BoardSignals : public QWidget
{
    Q_OBJECT

    public:
        static BoardSignals* instance()
        {
            static BoardSignals INSTANCE;
            return &INSTANCE;
        }
        ~BoardSignals();

    signals:
        void boardNavigation(QString action, QString name);

    private:
        BoardSignals();
};

#endif // BOARDSIGNALS_H
