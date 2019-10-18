#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <cmath>
#include <iostream>
#include "Tobiidget.h"

int TobiiThread::m_ScreenWidth;
int TobiiThread::m_ScreenHeight;
int TobiiThread::m_LastX;
int TobiiThread::m_LastY;
bool TobiiThread::m_Blinking;
int TobiiThread::m_BlinkTimer;


void TobiiThread::GazePointCallback(tobii_gaze_point_t const* gaze_point, void* user_data)
{
    if(m_Blinking)
    {
        m_BlinkTimer++;
        if(m_BlinkTimer>10) m_Blinking = false;
    }

    if(gaze_point->validity != TOBII_VALIDITY_VALID)
    {
        if(!m_Blinking)
        {
            m_Blinking = true;
            m_BlinkTimer = 0;
        }
        return;
    }

    TobiiThread* instance = static_cast<TobiiThread*>(user_data);

    int x = static_cast<int>(gaze_point->position_xy[0]*m_ScreenWidth);
    int y = static_cast<int>(gaze_point->position_xy[1]*m_ScreenHeight);

    if((abs(m_LastX - x)<4)&&(abs(m_LastY - y)<4)) return;


    if((!m_Blinking)&&(abs(m_LastY - y)>50))
    {
        m_Blinking = true;
        m_BlinkTimer = 0;
    }

    if(!m_Blinking) emit instance->privateMoved((m_LastX+x*3)/4, (m_LastY+y*3)/4);

    m_LastX = x;
    m_LastY = y;
}

bool TobiiThread::tobiiCreateApi()
{
    tobii_error_t error = tobii_api_create(&m_Api, nullptr, nullptr);
    if(error == TOBII_ERROR_NO_ERROR) return true;

    std::cerr << "tobii_device_create returns : " << tobii_error_message(error) << std::endl;
    return false;
}

bool TobiiThread::tobiiFindUrl(char* url)
{
    tobii_error_t error = tobii_enumerate_local_device_urls(m_Api, [](char const* url, void* user_data)
    {
        char* buffer = static_cast<char*>(user_data);
        if(*buffer != '\0') return; // only keep first value
        if(strlen(url) < 256)
        {
            strcpy(buffer, url);
        }
        else
        {
            std::cerr << "tobii local device url too long : " << url << std::endl;
        }
    }, url);


    if(error != TOBII_ERROR_NO_ERROR)
    {
        std::cerr << "tobii_enumerate_local_device_urls returns : " << tobii_error_message(error) << std::endl;
        return false;
    }

    if(*url == '\0')
    {
        std::cerr << "tobii local device url not found" << std::endl;
        return false;
    }

    std::clog << "tobii local device url found : " << url << std::endl;
    return true;
}

bool TobiiThread::tobiiCreateDevice(char* url)
{
    #ifdef _WIN32
        tobii_error_t error = tobii_device_create(m_Api, url, TOBII_FIELD_OF_USE_INTERACTIVE, &m_Device);
    #else
        tobii_error_t error = tobii_device_create(m_Api, url, &m_Device);
    #endif
    if(error == TOBII_ERROR_NO_ERROR) return true;

    std::cerr << "tobii_device_create returns : " << tobii_error_message(error) << std::endl;
    return false;
}

bool TobiiThread::tobiiSubscribe()
{
    tobii_error_t error = tobii_gaze_point_subscribe(m_Device, GazePointCallback, this);
    if(error == TOBII_ERROR_NO_ERROR) return true;

    std::cerr << "tobii_device_create returns : " << tobii_error_message(error) << std::endl;
    return false;
}

TobiiThread::TobiiThread(QObject *parent) : QThread(parent)
{
    m_ScreenWidth = QApplication::desktop()->width();
    m_ScreenHeight = QApplication::desktop()->height();
    m_LastX = m_ScreenWidth/2;
    m_LastY = m_ScreenHeight/2;
    m_Blinking = false;
    m_BlinkTimer = 0;

    m_Device = nullptr;

    char url[256] = {0};

    if(!tobiiCreateApi()) return;
    if(!tobiiFindUrl(url)) return;
    if(!tobiiCreateDevice(url)) return;
    if(!tobiiSubscribe()) return;
}

TobiiThread::~TobiiThread()
{
    tobii_gaze_point_unsubscribe(m_Device);
    tobii_device_destroy(m_Device);
    tobii_api_destroy(m_Api);
}

bool TobiiThread::tobiiReconnect()
{
    for(int i = 0; i<20; i++)
    {
        tobii_error_t error = tobii_device_reconnect(m_Device);
        if(error == TOBII_ERROR_NO_ERROR) return true;
        if(error != TOBII_ERROR_CONNECTION_FAILED)
        {
            std::cerr << "Connection was lost and reconnection returns : " << tobii_error_message(error) << std::endl;
            return false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    std::cerr << "Connection was lost and reconnection failed" << std::endl;
    return false;
}

void TobiiThread::run()
{
    if(m_Device == nullptr) return;

    tobii_error_t error;

    while (!isInterruptionRequested())
    {
        msleep(20);

        error = tobii_wait_for_callbacks(1, &m_Device);
        if(error == TOBII_ERROR_TIMED_OUT) continue;
        if(error == TOBII_ERROR_CONNECTION_FAILED)
        {
            if(!tobiiReconnect()) return;
            error = TOBII_ERROR_NO_ERROR;
        }
        if(error != TOBII_ERROR_NO_ERROR)
        {
            std::cerr << "tobii_wait_for_callbacks returns : " << tobii_error_message(error) << std::endl;
            return;
        }

        error = tobii_device_process_callbacks(m_Device);
        if(error == TOBII_ERROR_CONNECTION_FAILED)
        {
            if(!tobiiReconnect()) return;
            error = TOBII_ERROR_NO_ERROR;
        }
        if(error != TOBII_ERROR_NO_ERROR)
        {
            std::cerr << "tobii_device_process_callbacks returns : " << tobii_error_message(error) << std::endl;
            return;
        }
    }
}

Tobiidget::Tobiidget(QWidget *parent) : QWidget(parent), m_Thread(this)
{
    connect(&m_Thread, &TobiiThread::privateMoved, this, &Tobiidget::privateMoved);
    connect(&m_Thread, &TobiiThread::finished, &m_Thread, &QObject::deleteLater);
    m_Thread.start();
}

Tobiidget::~Tobiidget()
{
    m_Thread.requestInterruption();
    m_Thread.wait();
}

void Tobiidget::privateMoved(int x, int y)
{
    emit eyesMoved(x, y);
}
