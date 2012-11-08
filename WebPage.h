#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <QtGui>
#include <QtWebKit>

class WebPage : public QWebView
{
    Q_OBJECT

    public:
        WebPage(QWidget *parent = 0);
        WebPage(QString url = "", QWidget *parent = 0);
        bool isWheelClicked();
        bool isCtrlPressed();

    private:
        // Events
        void mousePressEvent(QMouseEvent *event);
        void keyPressEvent(QKeyEvent *event);
        void keyReleaseEvent(QKeyEvent *event);
        void wheelEvent(QWheelEvent *event);

    signals:
        void zoomRequired();
        void unZoomRequired();

    private:
        bool wheelClic;
        bool cPress;
};

#endif // WEBPAGE_H
