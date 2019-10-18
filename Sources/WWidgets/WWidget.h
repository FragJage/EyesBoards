#ifndef WWIDGET_H
#define WWIDGET_H

#include <QWidget>
#include <QResizeEvent>

class WWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit WWidget(QWidget *parent = nullptr);

    signals:
        void initAnchor();
        void refreshAnchor(QSize relativeSize);

    protected:
        void showEvent(QShowEvent* event) override;
        void resizeEvent(QResizeEvent *event) override;

    private:
        QSize m_InitialSize;
};

#endif // WWIDGET_H
