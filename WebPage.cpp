#include "WebPage.h"

WebPage::WebPage(QString url, QWidget *parent) : QWebView(parent)
{
    this->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    this->page()->setForwardUnsupportedContent(true);

    if (url.isEmpty())
    {
        load(QUrl(QCoreApplication::applicationDirPath() + "/data/html/newTab.html"));
    }
    else
    {
        load(QUrl(url));
    }

    // Init
    wheelClic = false;
    cPress = false;
}

bool WebPage::isWheelClicked()
{
    return wheelClic;
}

bool WebPage::isCtrlPressed()
{
    // Getter
    return cPress;
}

// Events

void WebPage::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MidButton)
    {
        wheelClic = true;
        event->accept();
    }
    else
    {
        wheelClic = false;
        event->ignore();
    }
    QWebView::mousePressEvent(event);
}

void WebPage::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier)
    {
        cPress = true;
        event->accept();
    }
    else
    {
        cPress = false;
    }
    QWebView::keyPressEvent(event);
}

void WebPage::keyReleaseEvent(QKeyEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier)
    {
        cPress = false;
        event->accept();
    }
    QWebView::keyReleaseEvent(event); ;
}

void WebPage::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier)
    {
        if (event->delta() > 0)
        {
            emit zoomRequired();
        }
        else
        {
            emit unZoomRequired();
        }
        event->accept();
    }
    QWebView::wheelEvent(event);
}
