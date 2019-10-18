#ifndef WANCHOR_H
#define WANCHOR_H

#include "WWidget.h"

enum WAnchorFlags
{
    TopLeft = 0,
    Bottom = 1,
    Right = 2,
    Height = 4,
    Width = 8
};

inline WAnchorFlags operator|(WAnchorFlags a, WAnchorFlags b)
{return static_cast<WAnchorFlags>(static_cast<int>(a) | static_cast<int>(b));}

class WAnchor
{
    public:
        WAnchor(QWidget *anchorWidget);
        double anchorRateBottom() const;
        double anchorRateRight() const;
        double anchorRateHeight() const;
        double anchorRateWidth() const;
        void setAnchor(WAnchorFlags anchor);
        void setAnchor(int anchor);
        void setAnchor(double rateRight, double rateBottom=-1.0, double rateWidth=-1.0, double rateHeight=-1.0);
        void setAnchorRateBottom(double rate);
        void setAnchorRateRight(double rate);
        void setAnchorRateHeight(double rate);
        void setAnchorRateWidth(double rate);

    public slots:
        void initialise();
        void refresh(QSize relativeSize);

    private:
        bool m_Initialized;
        double m_RateBottom;
        double m_RateRight;
        double m_RateHeight;
        double m_RateWidth;
        QRect m_InitialGeom;
        QWidget *m_AnchorWidget;
};

#endif // WANCHOR_H
