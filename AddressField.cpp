#include "AddressField.h"

AddressField::AddressField() : QLineEdit()
{
    // Url field properties
    setFont(QFont("Verdana", 11));
    setTextMargins(10, 2, 0, 2);

    // Clear Button
    clearButton = new QPushButton(this);
    QPixmap pixmap(QCoreApplication::applicationDirPath() + "/data/resetUrl.png");
    clearButton->setIcon(QIcon(pixmap));
    clearButton->setCursor(Qt::ArrowCursor);
    clearButton->setStyleSheet("QPushButton { border: none; padding: 0px; }");
    clearButton->hide();
    frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);

    // Style
    cssStyle = QString("QLineEdit { padding: 1 20px; color: #232323; border: 1px solid gray; border-radius: 5px; padding-right: %1px; } ").arg(clearButton->sizeHint().width() + frameWidth + 1);
    this->setStyleSheet(cssStyle);
    QSize msz = minimumSizeHint();
    setMinimumSize(qMax(msz.width(), clearButton->sizeHint().height() + frameWidth * 2 + 2), qMax(msz.height(), clearButton->sizeHint().height() + frameWidth * 2 + 2));

    connect(this, SIGNAL(textChanged(QString)), this, SLOT(initUrlField()));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(isCleared()));
    connect(this, SIGNAL(cleared()), this, SLOT(resetUrlField()));
}

void AddressField::isCleared()
{
    this->clear();
    emit cleared();
}

void AddressField::initUrlField()
{
    clearButton->show();
    this->setStyleSheet(cssStyle);
    if (this->text().isEmpty())
    {
        emit cleared();
    }
}

void AddressField::resetUrlField()
{
    clearButton->hide();
    setTextMargins(10, 2, 0, 2);
    this->setStyleSheet(QString("QLineEdit { }"));
    setFocus();
}

void AddressField::resizeEvent(QResizeEvent *)
{
    QSize sz = clearButton->sizeHint();
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    clearButton->move(rect().right() - frameWidth - sz.width(), (rect().bottom() + 1 - sz.height())/2);
}
