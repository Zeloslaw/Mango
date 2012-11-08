#include "PreferencesWindow.h"

PreferencesWindow::PreferencesWindow(QWidget *parent) : QDialog(parent)
{
    // Variables load from the config.ini file
    QFile configFile(QCoreApplication::applicationDirPath() + "/data/config/config.ini");
    QString fileHomePage;
    QString fileSearchEngine;
    QString fileDownloadPath;
    QString fileZoomTextOnly;
    bool isZoomEnabled;
    QString fileJs;
    bool isJsEnabled;
    QString fileFlash;
    bool isFlashEnabled;
    if (!configFile.exists())
    {
        QMessageBox::critical(NULL, tr("Error"), tr("<p>Configuration file missing ! Please try to reinstall.</p><p>The application will stop.</p>"));
        qApp->quit();
    }
    else
    {
        if (configFile.open(QIODevice::ReadOnly))
        {
            QTextStream flux(&configFile);
            flux >> fileHomePage;
            flux >> fileSearchEngine;
            flux >> fileDownloadPath;
            flux >> fileZoomTextOnly;
            flux >> fileJs;
            flux >> fileFlash;
            if (fileZoomTextOnly == "true")
            {
                isZoomEnabled = true;
            }
            else
            {
                isZoomEnabled = false;
            }
            if (fileJs == "true")
            {
                isJsEnabled = true;
            }
            else
            {
                isJsEnabled = false;
            }
            if (fileFlash == "true")
            {
                isFlashEnabled = true;
            }
            else
            {
                isFlashEnabled = false;
            }
            configFile.close();
        }
    }

    // Tabs Widgets

    // General widget

    // Container widget
    QWidget *generalWidget = new QWidget();

    // Home page url label
    QLabel *homePage = new QLabel;
    homePage->setText(tr("Home page"));
    homePage->setFixedSize(260, 35);
    homePage->setStyleSheet("QLabel { font-family: \"Trebuchet MS\"; font-size: 13px; margin-left: 20px; } ");
    QHBoxLayout *urlLabelLayout = new QHBoxLayout;
    urlLabelLayout->addWidget(homePage);
    urlLabelLayout->setAlignment(Qt::AlignLeft);
    // Home page url field
    urlHomePage = new QLineEdit;
    urlHomePage->setFixedSize(220, 35);
    urlHomePage->setStyleSheet("QLineEdit { margin-top: 10px; margin-left: 0px; } ");
    urlHomePage->setText(fileHomePage);
    // Home icon
    QLabel *iconHome = new QLabel;
    iconHome->setPixmap(QPixmap::fromImage(QImage(QCoreApplication::applicationDirPath() + "/data/homePage.png")));
    QHBoxLayout *urlFieldLayout = new QHBoxLayout;
    urlFieldLayout->addWidget(urlHomePage);
    urlFieldLayout->addWidget(iconHome);
    urlFieldLayout->setAlignment(Qt::AlignCenter);
    // Home page layout
    QHBoxLayout *homePageLayout = new QHBoxLayout;
    homePageLayout->addLayout(urlLabelLayout);
    homePageLayout->addLayout(urlFieldLayout);
    homePageLayout->setMargin(15);

    // Default search engine label
    QLabel *searchEngineLabel = new QLabel;
    searchEngineLabel->setText(tr("Default search engine"));
    searchEngineLabel->setFixedSize(260, 35);
    searchEngineLabel->setStyleSheet("QLabel { font-family: \"Trebuchet MS\"; font-size: 13px; margin-left: 20px; } ");
    QHBoxLayout *searchLabelLayout = new QHBoxLayout;
    searchLabelLayout->addWidget(searchEngineLabel);
    searchLabelLayout->setAlignment(Qt::AlignLeft);
    // Default search engine field
    searchEngineComboBox = new QComboBox;
    searchEngineComboBox->setFixedSize(220, 35);
    searchEngineComboBox->setStyleSheet("QComboBox { margin-top: 10px; margin-left: 0px; } ");
    searchEngineComboBox->addItem(QIcon(QCoreApplication::applicationDirPath() + "/data/iconGoogle.png"), "Google");
    searchEngineComboBox->addItem(QIcon(QCoreApplication::applicationDirPath() + "/data/iconBing.png"), "Bing");
    searchEngineComboBox->addItem(QIcon(QCoreApplication::applicationDirPath() + "/data/iconYahoo.png"), "Yahoo");
    searchEngineComboBox->addItem(QIcon(QCoreApplication::applicationDirPath() + "/data/iconWiki.png"), "Wikipedia");
    for (int i = 0; i < searchEngineComboBox->count(); i++)
    {
        if (fileSearchEngine == searchEngineComboBox->itemText(i))
        {
            searchEngineComboBox->setCurrentIndex(i);
        }
    }
    // Search icon
    QLabel *iconSearch = new QLabel;
    iconSearch->setPixmap(QPixmap::fromImage(QImage(QCoreApplication::applicationDirPath() + "/data/iconSearch.png")));
    QHBoxLayout *searchEngineComboBoxLayout = new QHBoxLayout;
    searchEngineComboBoxLayout->addWidget(searchEngineComboBox);
    searchEngineComboBoxLayout->addWidget(iconSearch);
    searchEngineComboBoxLayout->setAlignment(Qt::AlignCenter);
    // Search engine layout
    QHBoxLayout *searchEngineLayout = new QHBoxLayout;
    searchEngineLayout->addLayout(searchLabelLayout);
    searchEngineLayout->addLayout(searchEngineComboBoxLayout);
    searchEngineLayout->setMargin(15);

    // Download path
    QLabel *downloadPath = new QLabel;
    downloadPath->setText(tr("Download path"));
    downloadPath->setFixedSize(260, 35);
    downloadPath->setStyleSheet("QLabel { font-family: \"Trebuchet MS\"; font-size: 13px; margin-left: 20px; } ");
    QHBoxLayout *pathLabelLayout = new QHBoxLayout;
    pathLabelLayout->addWidget(downloadPath);
    pathLabelLayout->setAlignment(Qt::AlignLeft);
    // Download path field
    urlDownloadPath = new QLineEdit;
    urlDownloadPath->setFixedSize(220, 35);
    urlDownloadPath->setStyleSheet("QLineEdit { margin-top: 10px; margin-left: 0px; } ");
    urlDownloadPath->setText(fileDownloadPath); // Windows
    // Choose directory
    QPushButton *buttonOpenDir = new QPushButton;
    buttonOpenDir->setFixedSize(39, 39);
    buttonOpenDir->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/data/openDir.png"));
    buttonOpenDir->setIconSize(QSize(30, 30));
    QHBoxLayout *urlDownloadPathLayout = new QHBoxLayout;
    urlDownloadPathLayout->addWidget(urlDownloadPath);
    urlDownloadPathLayout->addWidget(buttonOpenDir);
    urlDownloadPathLayout->setAlignment(Qt::AlignCenter);
    // Download path layout
    QHBoxLayout *downloadPathLayout = new QHBoxLayout;
    downloadPathLayout->addLayout(pathLabelLayout);
    downloadPathLayout->addLayout(urlDownloadPathLayout);
    downloadPathLayout->setMargin(15);

    // General layout
    QVBoxLayout *generalLayout = new QVBoxLayout;
    generalLayout->addLayout(homePageLayout);
    generalLayout->addLayout(searchEngineLayout);
    generalLayout->addLayout(downloadPathLayout);
    generalLayout->setAlignment(Qt::AlignTop);
    generalWidget->setLayout(generalLayout);

    // Appearance widget
    QWidget *appearanceWidget = new QWidget();

    // Zoom text only
    QLabel *zoomTextOnly = new QLabel;
    zoomTextOnly->setText(tr("Zoom : "));
    zoomTextOnly->setFixedSize(260, 35);
    zoomTextOnly->setStyleSheet("QLabel { font-family: \"Trebuchet MS\"; font-size: 13px; margin-left: 20px; } ");
    QHBoxLayout *zoomLabelLayout = new QHBoxLayout;
    zoomLabelLayout->addWidget(zoomTextOnly);
    zoomLabelLayout->setAlignment(Qt::AlignLeft);
    // Zoom text only checkbox
    zoomCheckBox = new QCheckBox;
    zoomCheckBox->setFixedSize(220, 35);
    zoomCheckBox->setStyleSheet("QCheckBox { margin-top: 10px; margin-left: 0px; } ");
    zoomCheckBox->setText(tr("Text only"));
    zoomCheckBox->setChecked(isZoomEnabled);
    // Zoom icon
    QLabel *iconZoom = new QLabel;
    iconZoom->setPixmap(QPixmap::fromImage(QImage(QCoreApplication::applicationDirPath() + "/data/magnifyingGlass.png")));
    QHBoxLayout *zoomCheckBoxLayout = new QHBoxLayout;
    zoomCheckBoxLayout->addWidget(zoomCheckBox);
    zoomCheckBoxLayout->addWidget(iconZoom);
    zoomCheckBoxLayout->setAlignment(Qt::AlignCenter);
    // Zoom text only layout
    QHBoxLayout *zoomTextOnlyLayout = new QHBoxLayout;
    zoomTextOnlyLayout->addLayout(zoomLabelLayout);
    zoomTextOnlyLayout->addLayout(zoomCheckBoxLayout);
    zoomTextOnlyLayout->setMargin(15);

    // Appearance layout
    QVBoxLayout *appearanceLayout = new QVBoxLayout;
    appearanceLayout->addLayout(zoomTextOnlyLayout);
    appearanceLayout->setAlignment(Qt::AlignTop);
    appearanceWidget->setLayout(appearanceLayout);

    // Privacy widget
    QWidget *privacyWidget = new QWidget();

    // Disable Javascript
    QLabel *disableJs = new QLabel;
    disableJs->setText(tr("Javascript : "));
    disableJs->setFixedSize(260, 35);
    disableJs->setStyleSheet("QLabel { font-family: \"Trebuchet MS\"; font-size: 13px; margin-left: 20px; } ");
    QHBoxLayout *disableJsLabelLayout = new QHBoxLayout;
    disableJsLabelLayout->addWidget(disableJs);
    disableJsLabelLayout->setAlignment(Qt::AlignLeft);
    // Disable JS Checkbox
    disableJsCheckBox = new QCheckBox;
    disableJsCheckBox->setFixedSize(220, 35);
    disableJsCheckBox->setStyleSheet("QCheckBox { margin-top: 10px; margin-left: 0px; } ");
    disableJsCheckBox->setText(tr("Enable / Disable"));
    disableJsCheckBox->setChecked(isJsEnabled);
    // JS icon
    QLabel *iconJs = new QLabel;
    iconJs->setPixmap(QPixmap::fromImage(QImage(QCoreApplication::applicationDirPath() + "/data/iconJs.png")));
    QHBoxLayout *disableJsCheckBoxLayout = new QHBoxLayout;
    disableJsCheckBoxLayout->addWidget(disableJsCheckBox);
    disableJsCheckBoxLayout->addWidget(iconJs);
    disableJsCheckBoxLayout->setAlignment(Qt::AlignCenter);
    // Disable JS Layout
    QHBoxLayout *disableJsLayout = new QHBoxLayout;
    disableJsLayout->addLayout(disableJsLabelLayout);
    disableJsLayout->addLayout(disableJsCheckBoxLayout);
    disableJsLayout->setMargin(15);

    // Disable Flash
    QLabel *disableFlash = new QLabel;
    disableFlash->setText(tr("Flash : "));
    disableFlash->setFixedSize(260, 35);
    disableFlash->setStyleSheet("QLabel { font-family: \"Trebuchet MS\"; font-size: 13px; margin-left: 20px; } ");
    QHBoxLayout *disableFlashLabelLayout = new QHBoxLayout;
    disableFlashLabelLayout->addWidget(disableFlash);
    disableFlashLabelLayout->setAlignment(Qt::AlignLeft);
    // Disable Flash Checkbox
    disableFlashCheckBox = new QCheckBox;
    disableFlashCheckBox->setFixedSize(220, 35);
    disableFlashCheckBox->setStyleSheet("QCheckBox { margin-top: 10px; margin-left: 0px; } ");
    disableFlashCheckBox->setText(tr("Enable / Disable"));
    disableFlashCheckBox->setChecked(isFlashEnabled);
    // Flash icon
    QLabel *iconFlash = new QLabel;
    iconFlash->setPixmap(QPixmap::fromImage(QImage(QCoreApplication::applicationDirPath() + "/data/iconFlash.png")));
    QHBoxLayout *disableFlashCheckBoxLayout = new QHBoxLayout;
    disableFlashCheckBoxLayout->addWidget(disableFlashCheckBox);
    disableFlashCheckBoxLayout->addWidget(iconFlash);
    disableFlashCheckBoxLayout->setAlignment(Qt::AlignCenter);

    // Disable Flash Layout
    QHBoxLayout *disableFlashLayout = new QHBoxLayout;
    disableFlashLayout->addLayout(disableFlashLabelLayout);
    disableFlashLayout->addLayout(disableFlashCheckBoxLayout);
    disableFlashLayout->setMargin(15);

    // Privacy layout
    QVBoxLayout *privacyLayout = new QVBoxLayout;
    privacyLayout->addLayout(disableJsLayout);
    privacyLayout->addLayout(disableFlashLayout);
    privacyLayout->setAlignment(Qt::AlignTop);
    privacyWidget->setLayout(privacyLayout);

    // Buttons widgets
    QPushButton *submitButton = new QPushButton(tr("OK"));
    QPushButton *cancelButton = new QPushButton(tr("Cancel"));
    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(submitButton);
    buttonsLayout->addWidget(cancelButton);
    buttonsLayout->setAlignment(Qt::AlignRight);

    // Tab
    QTabWidget *tabs = new QTabWidget();
    tabs->setStyle(new QWindowsStyle);
    tabs->setMovable(true);
    tabs->setElideMode(Qt::ElideRight);
    tabs->addTab(generalWidget, tr("General"));
    tabs->addTab(appearanceWidget, tr("Appearance"));
    tabs->addTab(privacyWidget, tr("Privacy"));

    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabs);
    mainLayout->addLayout(buttonsLayout);

    // Tab style
    QString style = "QTabBar::tab:selected { margin-left: -2px; margin-right: -2px; } QTabBar::tab:first:selected { margin-left: 0; } QTabBar::tab:last:selected { margin-right: 0; } ";
    style += "QTabBar::tab:only-one { margin: 0; } QTabWidget::pane { border-top: 2px solid #C2C7CB; } QTabWidget::tab-bar { left: 5px; } ";
    style += "QTabBar::tab { font-family: Calibri, Arial; font-size: 15px; background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E1E1E1, stop: 0.4 #DDDDDD, stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3); border: 1px solid #C4C4C3; border-bottom-color: #C2C7CB; border-top-left-radius: 4px; border-top-right-radius: 4px; min-width: 80px; padding: 8px; }";
    style += "QTabBar::tab:selected, QTabBar::tab:hover { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #fafafa, stop: 0.4 #f4f4f4, stop: 0.5 #e7e7e7, stop: 1.0 #fafafa); } QTabBar::tab:selected { border-color: #9B9B9B; border-bottom-color: #C2C7CB; } QTabBar::tab:!selected { margin-top: 2px; }";
    tabs->setStyleSheet(style);

    // Properties
    setWindowTitle(tr("Preferences - Mango"));
    setFixedSize(600, 400);
    setLayout(mainLayout);
    submitButton->setFocus(Qt::OtherFocusReason);

    // Connections
    connect(buttonOpenDir, SIGNAL(clicked()), this, SLOT(chooseDirDownload()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(submitPreferences()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

// Methods

QString PreferencesWindow::checkHomePage()
{
    QString urlHome;
    QString url = urlHomePage->text();
    bool isAValidUrl = false;
    if (!url.isEmpty())
    {
        isAValidUrl = true;
        if (url.left(7) != "http://" && url.left(8) != "https://")
        {
            url = "http://" + url;
        }
    }
    if (!isAValidUrl)
    {
        urlHome = "http://www.google." + tr("us");
    }
    else
    {
        urlHome = url;
    }
    return urlHome;
}

QString PreferencesWindow::checkDefaultSearchEngine()
{
    QString searchEngines[4];
    QString nameDefaultSearchEngine;
    searchEngines[0] = "Google";
    searchEngines[1] = "Bing";
    searchEngines[2] = "Yahoo";
    searchEngines[3] = "Wikipedia";
    bool isInArray = false;
    for (int i=0; i < 4; i++)
    {
        if (searchEngines[i] == searchEngineComboBox->currentText())
        {
            isInArray = true;
        }
    }
    if (searchEngineComboBox->currentText().isEmpty() || !isInArray)
    {
        nameDefaultSearchEngine = "Google";
    }
    else
    {
        nameDefaultSearchEngine = searchEngineComboBox->currentText();
    }
    return nameDefaultSearchEngine;
}

QString PreferencesWindow::checkDownloadPath()
{
    QString downloadDirPath;
    if (urlDownloadPath->text().isEmpty())
    {
        downloadDirPath = QDir::homePath().replace("/", "\\"); // Windows
    }
    else
    {
        downloadDirPath = urlDownloadPath->text();
    }
    return downloadDirPath;
}

bool PreferencesWindow::isZoomTextOnlyEnabled()
{
    bool zoomTextOnlyEnabled;
    if (zoomCheckBox->checkState() == Qt::Checked)
    {
        zoomTextOnlyEnabled = true;
    }
    else
    {
        zoomTextOnlyEnabled = false;
    }
    return zoomTextOnlyEnabled;
}

// Privacy slots

bool PreferencesWindow::isJsEnabled()
{
    bool jsEnabled;
    if (disableJsCheckBox->checkState() == Qt::Checked)
    {
        jsEnabled = true;
    }
    else
    {
        jsEnabled = false;
    }
    return jsEnabled;
}

bool PreferencesWindow::isFlashEnabled()
{
    bool flashEnabled;
    if (disableFlashCheckBox->checkState() == Qt::Checked)
    {
        flashEnabled = true;
    }
    else
    {
        flashEnabled = false;
    }
    return flashEnabled;
}


// Slots

void PreferencesWindow::chooseDirDownload()
{
    QString downloadDirPath = QFileDialog::getExistingDirectory(this, tr("Choose a download path"), QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks | QFileDialog::HideNameFilterDetails);
    if (downloadDirPath.isEmpty())
    {
        //downloadDirPath = QDir::homePath(); // Linux
        downloadDirPath = QDir::homePath().replace("/", "\\"); // Windows
    }
    //urlDownloadPath->setText(downloadDirPath); // Linux
    urlDownloadPath->setText(downloadDirPath.replace("/", "\\")); // Windows
}

void PreferencesWindow::submitPreferences()
{
    QFile configFile(QCoreApplication::applicationDirPath() + "/data/config/config.ini");
    if(!configFile.exists())
    {
        QMessageBox::critical(NULL, tr("Error"), tr("Configuration file missing ! Please try to reinstall."));
    }
    else
    {
        QString zoomTextEnabledString;
        QString flashEnabledString;
        QString jsEnabledString;
        if (isZoomTextOnlyEnabled())
        {
            zoomTextEnabledString = "true";
        }
        else
        {
            zoomTextEnabledString = "false";
        }
        if (isFlashEnabled())
        {
            flashEnabledString = "true";
        }
        else
        {
            flashEnabledString = "false";
        }
        if (isJsEnabled())
        {
            jsEnabledString = "true";
        }
        else
        {
            jsEnabledString = "false";
        }
        configFile.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream flux(&configFile);
        flux << checkHomePage() << endl << checkDefaultSearchEngine() << endl << checkDownloadPath() << endl << zoomTextEnabledString << endl << jsEnabledString << endl << flashEnabledString;
        configFile.close();
    }
    this->close();
}
