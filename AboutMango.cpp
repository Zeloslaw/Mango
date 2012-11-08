#include "AboutMango.h"

AboutMango::AboutMango(QWidget *parent) : QDialog(parent)
{
    // Window content

    // Close button
    close = new QPushButton(tr("Close"));
    close->setFocus(Qt::OtherFocusReason);
    close->setFixedSize(55, 35);

    // Labels
    aboutMango = new QLabel(tr("<p><b>Mango</b> is a web browser written in C++ and based on WebKit. It is built using Qt Framework. <br/></p> <p>The used pictures have been created by <a href=\"http://www.everaldo.com\">Everaldo Coelho</a>. <br/></p> <p>To know more about the project, please consult our website <a href=\"http://www.thomasutc.fr/\">here</a>.</p><p><br/>Current version : <strong>1.2</strong></p>"));
    aboutMango->setAlignment(Qt::AlignJustify);
    aboutMango->setWordWrap(true);
    aboutMango->setStyleSheet("QLabel { font-size: 13px; margin-left: 20px; margin-top: 70px; padding-right: 15px; } ");
    QLabel *logoMango = new QLabel();
    logoMango->setPixmap(QPixmap::fromImage(QImage(QCoreApplication::applicationDirPath() + "/data/logo/logo.png")));

    // Layouts
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->setAlignment(Qt::AlignRight);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(logoMango);
    layout->addWidget(aboutMango);
    buttonLayout->addWidget(close);
    mainLayout->addLayout(layout);
    mainLayout->addLayout(buttonLayout);

    // Window properties
    setWindowTitle(tr("About - Mango"));
    setWindowIcon(QIcon(QCoreApplication::applicationDirPath() + "/data/logo/logo.png"));
    setFixedSize(600, 400);
    setLayout(mainLayout);

    // Connections
    connect(close, SIGNAL(clicked()), this, SLOT(accept()));
}

QLabel *AboutMango::getLabelAboutMango()
{
    return this->aboutMango;
}
