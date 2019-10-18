#ifndef TOBIIDGET_H
#define TOBIIDGET_H

#include <assert.h>
#include <QWidget>
#include <QThread>
#include <tobii/tobii.h>
#include <tobii/tobii_streams.h>


class TobiiThread : public QThread
{
    Q_OBJECT

    public:
        TobiiThread(QObject *parent = nullptr);
        ~TobiiThread() override;
        static void GazePointCallback(tobii_gaze_point_t const* gaze_point, void* user_data);

    protected:
        void run() override;

    signals:
        void privateMoved(int x, int y);

    private:
        bool tobiiReconnect();
        bool tobiiCreateApi();
        bool tobiiFindUrl(char* url);
        bool tobiiCreateDevice(char* url);
        bool tobiiSubscribe();
        static int m_ScreenWidth;
        static int m_ScreenHeight;
        static int m_LastX;
        static int m_LastY;
        static bool m_Blinking;
        static int m_BlinkTimer;
        tobii_api_t* m_Api;
        tobii_device_t* m_Device;
};

class Tobiidget : public QWidget
{
    Q_OBJECT

    public:
        explicit Tobiidget(QWidget *parent = nullptr);
        ~Tobiidget();

    private slots:
        void privateMoved(int x, int y);

    signals:
        void eyesMoved(int x, int y);

    private:
        TobiiThread m_Thread;
};

#endif // TOBIIDGET_H
