#include "MainWindow.h"

MainWindow::MainWindow() : QMainWindow()
{
    // Constructor

    // Creation of the main window's elements
    createActions();
    createMenu();
    createToolbar();
    createStatusBar();
    getPreferences();

    // Creation of the tabsystem
    tabs = new TabNav();
    tabs->addTab(createNewTabWeb(fileHomePage), "");
    setCentralWidget(tabs);

    // Tab connections
    connect(tabs, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    connect(tabs, SIGNAL(currentChanged(int)), this, SLOT(switchTabs(int)));
    connect(tabs->getButtonNewTab(), SIGNAL(clicked()), this, SLOT(newTab()));

    // Definition of the windows properties
    showMaximized();
    setWindowIcon(QIcon(QCoreApplication::applicationDirPath() + "/data/logo/logo.png"));
    setFont(QFont("Trebuchet MS", 10));

    // Plugins and options (according to the config.ini file)
    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, isFlashEnabled);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavaEnabled, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptEnabled, isJsEnabled);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::ZoomTextOnly, isZoomEnabled);

    // Initializations
    isDownloading = false;
}

// GUI METHODS

void MainWindow::createActions()
{
    // Creates the window actions

    // File menu
    actionNewTab = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/data/newTab.png"), tr("&New Tab"), this);
    actionNewTab->setShortcut(QKeySequence::AddTab);
    connect(actionNewTab, SIGNAL(triggered()), this, SLOT(newTab()));

    actionCloseTab = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/data/closeTab.png"), tr("&Close Tab"), this);
    actionCloseTab->setShortcut(tr("Ctrl+F4"));
    connect(actionCloseTab, SIGNAL(triggered()), this, SLOT(closeTab()));

    actionPrintPreview = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/data/printPreview.png"), tr("&Print preview"), this);
    connect(actionPrintPreview, SIGNAL(triggered()), this, SLOT(printPreview()));

    actionPrintPage = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/data/print.png"), tr("&Print..."), this);
    actionPrintPage->setShortcut(QKeySequence::Print);
    connect(actionPrintPage, SIGNAL(triggered()), this, SLOT(printPage()));

    actionExit = new QAction(tr("&Exit"), this);
    actionExit->setShortcut(tr("Ctrl+Q"));
    connect(actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));

    actionSaveCurrentPage = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/data/save.png"), tr("&Save..."), this);
    actionSaveCurrentPage->setShortcut(QKeySequence::Save);
    connect(actionSaveCurrentPage, SIGNAL(triggered()), this, SLOT(saveCurrentPage()));

    // Edit menu
    actionCut = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/data/cut.png"), tr("Cut"), this);
    actionCut->setShortcut(QKeySequence::Cut);
    connect(actionCut, SIGNAL(triggered()), this, SLOT(cut()));

    actionCopy = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/data/copy.png"), tr("Copy"), this);
    actionCopy->setShortcut(QKeySequence::Copy);
    connect(actionCopy, SIGNAL(triggered()), this, SLOT(copy()));

    actionPaste = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/data/paste.png"), tr("Paste"), this);
    actionPaste->setShortcut(QKeySequence::Paste);
    connect(actionPaste, SIGNAL(triggered()), this, SLOT(paste()));

    actionSelectAll = new QAction(tr("Select all"), this);
    actionSelectAll->setShortcut(QKeySequence::SelectAll);
    connect(actionSelectAll, SIGNAL(triggered()), this, SLOT(selectAllWebView()));

    actionHighlighText = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/data/magnifyingGlass.png"), tr("&Find..."), this);
    actionHighlighText->setShortcut(tr("Ctrl+F"));
    actionHighlighText->setCheckable(true);
    connect(actionHighlighText, SIGNAL(triggered()), this, SLOT(toggleWindowFindText()));

    // Browse menu
    actionBack = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/data/back.png"), tr("&Back"), this);
    actionBack->setShortcut(QKeySequence::Back);
    connect(actionBack, SIGNAL(triggered()), this, SLOT(back()));
    actionBack->setEnabled(false);

    actionForward = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/data/forward.png"), tr("&Forward"), this);
    actionForward->setShortcut(QKeySequence::Forward);
    connect(actionForward, SIGNAL(triggered()), this, SLOT(forward()));
    actionForward->setEnabled(false);

    actionReload = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/data/reload.png"), tr("&Reload"), this);
    actionReload->setShortcut(QKeySequence::Refresh);
    connect(actionReload, SIGNAL(triggered()), this, SLOT(reload()));

    actionStop = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/data/stop.png"), tr("S&top"), this);
    connect(actionStop, SIGNAL(triggered()), this, SLOT(stop()));
    actionStop->setEnabled(false);

    actionHome = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/data/home.png"), tr("H&ome"), this);
    connect(actionHome, SIGNAL(triggered()), this, SLOT(home()));

    actionGo = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/data/go.png"), tr("G&o to"), this);
    connect(actionGo, SIGNAL(triggered()), this, SLOT(loadPage()));

    actionSourceCode = new QAction(tr("Show source"), this);
    actionSourceCode->setShortcut(tr("Ctrl+Alt+U"));
    connect(actionSourceCode, SIGNAL(triggered()), this, SLOT(getSourceCode()));

    // View Menu
    actionZoom = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/data/zoom.png"), tr("Zoom +"), this);
    actionZoom->setShortcut(QKeySequence::ZoomIn);
    connect(actionZoom, SIGNAL(triggered()), this, SLOT(zoom()));

    actionUnZoom = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/data/unZoom.png"), tr("Zoom -"), this);
    actionUnZoom->setShortcut(QKeySequence::ZoomOut);
    connect(actionUnZoom, SIGNAL(triggered()), this, SLOT(unZoom()));

    actionFullScreen = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/data/fullScreen.png"), tr("Full Screen"), this);
    actionFullScreen->setShortcut(Qt::Key_F11);
    actionFullScreen->setCheckable(true);
    connect(actionFullScreen, SIGNAL(triggered()), this, SLOT(toggleFullScreen()));

    actionDefaultZoom = new QAction(tr("Default zoom"), this);
    actionDefaultZoom->setShortcut(tr("Ctrl+0"));
    connect(actionDefaultZoom, SIGNAL(triggered()), this, SLOT(setDefaultZoom()));

    // Tools Menu
    actionPrivateBrowsing = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/data/privateBrowsingOff.png"), tr("Private browsing"), this);
    actionPrivateBrowsing->setCheckable(true);
    connect(actionPrivateBrowsing, SIGNAL(triggered()), this, SLOT(togglePrivateBrowsing()));

    actionPreferences = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/data/tools.png"), tr("Preferences..."), this);
    connect(actionPreferences, SIGNAL(triggered()), this, SLOT(showPreferences()));

    // ? Menu
    actionAbout = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/data/about.png"), tr("&About..."), this);
    actionAbout->setShortcut(QKeySequence::HelpContents);
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(about()));

    actionAboutQt = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/data/qt.png"), tr("About &Qt..."), this);
    connect(actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenu()
{
    // Creates the window menu

    // Menu "File"
    QMenu *menuFile = menuBar()->addMenu(tr("&File"));
    menuFile->addAction(actionNewTab);
    menuFile->addAction(actionCloseTab);
    menuFile->addSeparator();
    menuFile->addAction(actionSaveCurrentPage);
    menuFile->addSeparator();
    menuFile->addAction(actionPrintPreview);
    menuFile->addAction(actionPrintPage);
    menuFile->addSeparator();
    menuFile->addAction(actionExit);

    // Menu "Edit"
    QMenu *menuEdit = menuBar()->addMenu(tr("Edit"));
    menuEdit->addAction(actionCut);
    menuEdit->addAction(actionCopy);
    menuEdit->addAction(actionPaste);
    menuEdit->addAction(actionSelectAll);
    menuEdit->addSeparator();
    menuEdit->addAction(actionHighlighText);

    // Menu "Browse"
    QMenu *menuBrowsing = menuBar()->addMenu(tr("&Browse"));
    menuBrowsing->addAction(actionBack);
    menuBrowsing->addAction(actionForward);
    menuBrowsing->addAction(actionReload);
    menuBrowsing->addAction(actionStop);
    menuBrowsing->addAction(actionHome);
    menuBrowsing->addSeparator();
    menuBrowsing->addAction(actionSourceCode);

    // Menu "View"
    QMenu *menuView = menuBar()->addMenu(tr("&View"));
    menuView->addAction(actionZoom);
    menuView->addAction(actionUnZoom);
    menuView->addAction(actionDefaultZoom);
    menuView->addSeparator();
    menuView->addAction(actionFullScreen);

    // Menu "Tools"
    QMenu *menuTools = menuBar()->addMenu(tr("Tools"));
    menuTools->addAction(actionPrivateBrowsing);
    menuTools->addSeparator();
    menuTools->addAction(actionPreferences);

    // Menu "?"
    QMenu *menuHelp = menuBar()->addMenu(tr("&?"));
    menuHelp->addAction(actionAbout);
    menuHelp->addAction(actionAboutQt);
}

void MainWindow::createToolbar()
{
    // Creates the window toolbar

    // URL Field
    addressField = new AddressField();
    connect(addressField, SIGNAL(returnPressed()), this, SLOT(loadPage()));

    // Toolbar
    QToolBar *toolBarBrowsing = addToolBar(tr("Browse"));
    toolBarBrowsing->addAction(actionBack);
    toolBarBrowsing->addAction(actionForward);
    toolBarBrowsing->addAction(actionReload);
    toolBarBrowsing->addAction(actionStop);
    toolBarBrowsing->addAction(actionHome);
    toolBarBrowsing->addWidget(addressField);
    toolBarBrowsing->addAction(actionGo);
    toolBarBrowsing->addAction(actionPreferences);
    toolBarBrowsing->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
}

void MainWindow::createStatusBar()
{
    // Creates the window statusBar

    // Progression bar
    progressionBar = new QProgressBar(this);
    progressionBar->setMaximumHeight(15);
    progressionBar->setVisible(false);

    // Find text widgets
    findLabel = new QLabel(this);
    findLabel->setText(tr("Find in text : "));
    findLabel->setStyleSheet("QLabel { padding: 3px; } ");
    findLabel->setFixedSize(120, 20);
    findLabel->setVisible(false);

    findTextField = new QLineEdit(this);
    findTextField->setVisible(false);
    findTextField->setFixedSize(250, 20);

    buttonSubmitFind = new QPushButton(this);
    buttonSubmitFind->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/data/magnifyingGlass.png"));
    buttonSubmitFind->setText(tr("Find"));
    buttonSubmitFind->setFixedSize(80, 20);
    buttonSubmitFind->setVisible(false);

    nothingFound = new QPushButton(this);
    nothingFound->setText(tr("No occurences"));
    nothingFound->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/data/notFound.png"));
    nothingFound->setFlat(true);
    nothingFound->setFixedSize(130, 20);
    nothingFound->setVisible(false);

    // Private browsing image
    privateBrowsingIcon = new QLabel(this);
    privateBrowsingIcon->setPixmap(QPixmap::fromImage(QImage(QCoreApplication::applicationDirPath() + "/data/privateBrowsingOn.png")));
    privateBrowsingIcon->setVisible(false);

    // Connections
    connect(findTextField, SIGNAL(returnPressed()), this, SLOT(highlightText()));
    connect(buttonSubmitFind, SIGNAL(clicked()), this, SLOT(highlightText()));

    // Add to the statusBar
    statusBar()->setFont(QFont("Calibri", 9));
    statusBar()->addWidget(progressionBar, 1);
    statusBar()->addPermanentWidget(findLabel);
    statusBar()->addPermanentWidget(findTextField);
    statusBar()->addPermanentWidget(buttonSubmitFind);
    statusBar()->addPermanentWidget(nothingFound);
    statusBar()->addPermanentWidget(privateBrowsingIcon);
}

void MainWindow::getPreferences()
{
    // Initializes the variables coming from the config.ini file

    QFile configFile(QCoreApplication::applicationDirPath() + "/data/config/config.ini");
    QString fileZoomTextOnly;
    QString fileJs;
    QString fileFlash;
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
}

QWidget *MainWindow::createNewTabWeb(QString url)
{
    // This method creates a new web tab which loads the parameter "url"

    // QWebView
    WebPage *webPage = new WebPage(url);

    getPreferences(); // updates parameters such as flash/js
    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, isFlashEnabled);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptEnabled, isJsEnabled);

    // Main widget
    QWidget *tabPage = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(webPage);
    tabPage->setLayout(layout);

    // Connections

    // QWebView connections
    connect(webPage, SIGNAL(titleChanged(QString)), this, SLOT(changeTitle(QString)));
    connect(webPage, SIGNAL(urlChanged(QUrl)), this, SLOT(changeUrl(QUrl)));
    connect(webPage, SIGNAL(iconChanged()), this, SLOT(changeIcon()));
    connect(webPage, SIGNAL(loadStarted()), this, SLOT(loadBegin()));
    connect(webPage, SIGNAL(loadProgress(int)), this, SLOT(loading(int)));
    connect(webPage, SIGNAL(loadFinished(bool)), this, SLOT(loadComplete(bool)));
    // Zoom
    connect(webPage, SIGNAL(zoomRequired()), this, SLOT(zoom()));
    connect(webPage, SIGNAL(unZoomRequired()), this, SLOT(unZoom()));

    // QWebPage connections
    connect(webPage->page(), SIGNAL(linkHovered(QString, QString, QString)), this, SLOT(showLink(QString, QString, QString)));
    connect(webPage->page(), SIGNAL(linkClicked(QUrl)), this, SLOT(openLink(QUrl)));
    // Download support
    connect(webPage->page(), SIGNAL(unsupportedContent(QNetworkReply *)), this, SLOT(downloadFileAuto(QNetworkReply *)));
    // Error handler
    connect(webPage->page()->networkAccessManager(), SIGNAL(finished(QNetworkReply*)), this, SLOT(checkError(QNetworkReply *)));

    return tabPage;
}

WebPage *MainWindow::currentPage()
{
    // This method allows to know in which QWebView the user is

    return tabs->currentWidget()->findChild<WebPage *>();
}

QIcon MainWindow::getFavicon()
{
    // This method returns the page's favicon

    return QWebSettings::iconForUrl(QUrl(currentPage()->url()));
}

void MainWindow::prepareButtons()
{
    // This method enables or disables the back and forward buttons (according to the history)
    // It is called when the page has finished loading

    actionBack->setEnabled(!currentPage()->history()->backItem().url().isEmpty());
    actionForward->setEnabled(!currentPage()->history()->forwardItem().url().isEmpty());
    actionNewTab->setEnabled(true);
    actionStop->setEnabled(false);
    actionReload->setEnabled(true);
}

void MainWindow::newTab(QString url)
{
    // This method adds a new tab and sets the focus on the address field

    int indexNewTab = tabs->addTab(createNewTabWeb(url), "");
    tabs->setCurrentIndex(indexNewTab);
    addressField->setText("");
    addressField->setFocus(Qt::OtherFocusReason);
}

void MainWindow::openLink(QUrl url)
{
    // This method opens a link...

    getPreferences(); // updates parameters such as flash/js
    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, isFlashEnabled);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptEnabled, isJsEnabled);

    if (currentPage()->isCtrlPressed() || currentPage()->isWheelClicked())
        // ... in a new tab with a url parameter if the user has clicked on the middle bouton (wheelButton) or has pressed the ctrl button
    {
        QString urlString = url.toString();
        newTab(urlString);
    }
    else
        // else, in the current webpage
    {
        currentPage()->load(url);
    }
}

void MainWindow::closeTab(int index)
{
    // This method closes the tab at index (or the current tab if index is undefined, or the program itself if it's the last tab)

    if (index == -1)
    {
        index = tabs->currentIndex();
    }
    if (tabs->count() > 1)
    {
        tabs->removeTab(index);
		delete currentPage();
    }
    else
    {
        actionExit->trigger();
    }
}

void MainWindow::loadPage(QString url)
{
    // This methods loads page using either the url parameter or the text in the address field

    getPreferences(); // updates parameters such as flash/js
    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, isFlashEnabled);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptEnabled, isJsEnabled);

    if (url.isEmpty())
    {
        url = addressField->text();
    }

    bool urlWithoutHttp = (url.left(7) != "http://" && url.left(8) != "https://" && url.left(6) != "ftp://") && (url.right(4).left(1) == "." || url.right(3).left(1) == ".");
    bool searchQuery = (url.left(7) != "http://" && url.left(8) != "https://") && (url.right(4).left(1) != "." && url.right(3).left(1) != ".");
    if (urlWithoutHttp)
    {
        url = "http://" + url;
    }
    else if (searchQuery)
    {
        getPreferences(); // updates the default search engine
        // If there's no "." in the query, we can assume the user has tried to launch a google query
        if (fileSearchEngine == "Google")
        {
            url = "http://www.google.com/search?ie=UTF-8&q=" + url;
        }
        else if (fileSearchEngine == "Bing")
        {
            url = "http://www.bing.com/search?q=" + url;
        }
        else if (fileSearchEngine == "Yahoo")
        {
            url = "http://search.yahoo.com/search?p=" + url;
        }
        else if (fileSearchEngine == "Wikipedia")
        {
            url = "http://www.wikipedia.org/wiki/" + url;
        }
        else
        {
            url = "http://www.google.com/search?ie=UTF-8&q=" + url;
        }
    }
    addressField->setText(url);
    currentPage()->load(QUrl(url));
}

void MainWindow::switchTabs(int index)
{
    // This slot is used to update the title and the url of the page when the user is switching tabs

    changeTitle(currentPage()->title());
    changeUrl(currentPage()->url());
    changeIcon();
    if (addressField->text().isEmpty())
    {
        addressField->setFocus(Qt::OtherFocusReason);
    }
    else
    {
        currentPage()->setFocus(Qt::OtherFocusReason);
    }
}

void MainWindow::changeTitle(const QString & fullTitle)
{
    // This slot updates the window's title and the tab's title

    QString shortTitle = fullTitle;
    if (fullTitle.isEmpty())
    {
        setWindowTitle(tr("New Tab - Mango"));
        return;
    }
    else if (fullTitle.size() > 15)
    {
        // We cut the title if it's too long
        shortTitle = fullTitle.left(15) + "...";
    }

    setWindowTitle(fullTitle + " - Mango");
    tabs->setTabText(tabs->currentIndex(), shortTitle);
    tabs->setTabToolTip(tabs->currentIndex(), fullTitle);
}

void MainWindow::changeUrl(const QUrl & url)
{
    // This slot updates the url field

    // Linux
    //if (url.toString() != "file://" + QCoreApplication::applicationDirPath() + "/data/html/newTab.html")
    // Windows
    if (url.toString() != QCoreApplication::applicationDirPath() + "/data/html/newTab.html")
    {
        addressField->setText(url.toString());
        addressField->setCursorPosition(0);
        currentPage()->setFocus(Qt::OtherFocusReason);
    }
    else
    {
        addressField->clear();
        addressField->setFocus(Qt::OtherFocusReason);
    }
}

void MainWindow::changeIcon()
{
    // This slot updates the tab icon with the favicon

    QIcon icon = this->getFavicon();
    tabs->setTabIcon(tabs->currentIndex(), icon.pixmap(16, 16));
}

// Browsing slots

void MainWindow::back()
{
    currentPage()->back();
}

void MainWindow::forward()
{
    currentPage()->forward();
}

void MainWindow::stop()
{
    currentPage()->stop();
}

void MainWindow::reload()
{
    currentPage()->reload();
}

void MainWindow::home()
{
    getPreferences();  // Updates the home page url and js/flash
    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, isFlashEnabled);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptEnabled, isJsEnabled);
    currentPage()->load(QUrl(fileHomePage));
}

// About Mango

void MainWindow::about()
{
    aboutWindow = new AboutMango(this);
    connect(aboutWindow->getLabelAboutMango(), SIGNAL(linkActivated(QString)), this, SLOT(newTab(QString)));
    aboutWindow->exec();
}

// Print slots

void MainWindow::printPreview()
{
    // This slot displays a print preview of the page

    QPrintPreviewDialog *dialog = new QPrintPreviewDialog(this);
    connect(dialog, SIGNAL(paintRequested(QPrinter*)), currentPage(), SLOT(print(QPrinter*)));
    dialog->exec();
}

void MainWindow::printPage()
{
    // This slot opens the standard print dialog to print the page

    QPrinter printer;
    QPrintDialog *printDialog = new QPrintDialog(&printer, this);
    if (printDialog->exec() != QDialog::Accepted)
    {
        return;
    }
    currentPage()->page()->mainFrame()->print(&printer);
}

// Source code

void MainWindow::getSourceCode()
{
    // This slot is called to get the page's source code

    QNetworkAccessManager *accessManager = currentPage()->page()->networkAccessManager();
    QNetworkRequest request(currentPage()->url());
    QNetworkReply *reply = accessManager->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(showSourceCode()));
}

void MainWindow::showSourceCode()
{
    // This slot is used after getSourceCode() and display the page's source code.
    // Do not use this before getSourceCode()

    QNetworkReply *reply = qobject_cast<QNetworkReply*>(const_cast<QObject*>(sender()));
    reply->deleteLater();
    QTextEdit *textEdit = new QTextEdit();
    textEdit->setAttribute(Qt::WA_DeleteOnClose);
    textEdit->setWindowIcon(QIcon(QCoreApplication::applicationDirPath()+"/data/logo/logo.png"));
    textEdit->setWindowTitle(tr("Source : ") + currentPage()->url().toString() + " - Mango");
    textEdit->resize(600, 400);
    textEdit->setPlainText(reply->readAll());
    textEdit->show();
}

void MainWindow::toggleFullScreen()
{
    // This slot enables or disables fullscreen mode

    if (this->isFullScreen())
    {
        showMaximized();
    }
    else
    {
        showFullScreen();
    }
}

// Save page slot

void MainWindow::saveCurrentPage()
{
    QString pageTitle = currentPage()->title();
    QString path = QFileDialog::getSaveFileName(this, tr("Save a web page"), pageTitle, tr("Web Page, only HTML content (*.html);;Web Page (*.htm)"));
    QFile fichier(path);
    fichier.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream flux(&fichier);
    flux << currentPage()->page()->mainFrame()->toHtml().toLocal8Bit();
    fichier.close();
    if (fichier.exists())
    {
        QMessageBox::information(NULL, tr("Success"), tr("<p>The page <strong>") + pageTitle + tr("</strong> was successfully saved.</p>"));
    }
}

// Zoom

void MainWindow::zoom()
{
    // This slot is used to zoom in the QWebView

    getPreferences(); // updates zoom text only setting
    QWebSettings::globalSettings()->setAttribute(QWebSettings::ZoomTextOnly, isZoomEnabled);
    currentPage()->setZoomFactor(currentPage()->zoomFactor() + 0.1);
}

void MainWindow::unZoom()
{
    // This slot is used to unzoom in the QWebView

    getPreferences(); // updates zoom text only setting
    QWebSettings::globalSettings()->setAttribute(QWebSettings::ZoomTextOnly, isZoomEnabled);
    currentPage()->setZoomFactor(currentPage()->zoomFactor() - 0.1);
}

void MainWindow::setDefaultZoom()
{
    // This slot set's the zoom level of the QWebView to 1 (default)

    getPreferences(); // updates zoom text only setting
    QWebSettings::globalSettings()->setAttribute(QWebSettings::ZoomTextOnly, isZoomEnabled);
    currentPage()->setZoomFactor(1);
}

// Download support

void MainWindow::downloadFileAuto(QNetworkReply *reply)
{
    // This slot is called when the unSupportedContent signal is emitted by the browser

    if (isDownloading)
    {
        // You can't download more than one file
        QMessageBox::critical(this, tr("Error"), tr("You are already downloading a file ! Please wait before downloading another."));
        return;
    }
    getPreferences(); // We update the config parameters
    if (fileDownloadPath.isEmpty())
    {
        // We check if the read parameter is correct
        fileDownloadPath = QDir::homePath();
    }
    if (fileDownloadPath.right(1) == "\\")
    {
        fileDownloadPath = fileDownloadPath.left(fileDownloadPath.length()-1);
    }
    if (!QDir(fileDownloadPath).exists())
    {
        QDir().mkpath(fileDownloadPath);
    }
    downloadedFileName = QFileInfo(reply->url().toString()).fileName();
    fileToDownload.setFileName(fileDownloadPath + "/" + downloadedFileName);
    if (fileToDownload.exists())
    {
        // If the file already exists, we ask the user if he wants to replace it
        int answer = QMessageBox::question(this, tr("Download - Mango"), tr("This file already exists. Do you want to replace it ?"), QMessageBox::Yes | QMessageBox::No);
        if (answer == QMessageBox::No)
        {
            // If he doesn't we cancel everything
            hasCanceledDownload = true;
            loadComplete(true);
            isDownloading = false;
            reply->abort();
            return;
        }
    }

    // Start download
    isDownloading = true;
    this->reply = reply;

    // ProgressDialog
    downloadDialog = new QProgressDialog("<p>" + tr("Downloading ") + "<strong>" + downloadedFileName + "</strong>...</p>", tr("Cancel"), 0, 100, this);
    downloadDialog->setWindowTitle(tr("Download - Mango"));
    downloadDialog->setFixedSize(345, 160);
    downloadDialog->setFocus(Qt::OtherFocusReason);

    // Connections
    connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(downloading(qint64, qint64)));
    connect(downloadDialog, SIGNAL(canceled()), this, SLOT(cancelDownload()));
    connect(reply, SIGNAL(finished()), this, SLOT(downloadFinished()));

    // Initialize the window
    progressionBar->setVisible(false);
    tabs->setTabIcon(tabs->currentIndex(), this->getFavicon());
    statusBar()->showMessage(tr("Downloading ") + downloadedFileName);
}

void MainWindow::cancelDownload()
{
    // This slot is called when the user has pressed cancel on the QProgressDialog

    fileToDownload.remove();
    downloadDialog->close();
    loadComplete(true);
    statusBar()->showMessage(tr("Ready"), 2000);
    isDownloading = false;
    hasCanceledDownload = false;
    reply->abort();
}

void MainWindow::downloading(qint64 downloaded, qint64 total)
{
    // This slot updates the progressBar in the QProgressDialog

    if (total != -1)
    {
        downloadDialog->setRange(0, total);
        downloadDialog->setValue(downloaded);
    }
}

void MainWindow::downloadFinished()
{
    // This slot is called when the download is finished (including when the user has cancelled)

    if (!isDownloading)
    {
        // if the user has cancelled
        return;
    }
    this->reply = qobject_cast<QNetworkReply *>(sender());
    if (reply)
    {
        reply->deleteLater();
        fileToDownload.remove();
        fileToDownload.open(QIODevice::WriteOnly | QIODevice::Truncate);
        fileToDownload.write(reply->readAll());
        fileToDownload.close();
        statusBar()->showMessage(tr("Download finished"), 2000);
        int answer = QMessageBox::question(this, tr("Download - Mango"), tr("<p>Your download is finished.</p><p>Do you want to open <strong>") + downloadedFileName + tr("</strong> now ?</p>"), QMessageBox::Yes | QMessageBox::No);
        if (answer == QMessageBox::Yes)
        {
            // If the user chose to open the file, we open it with the default application
            QDesktopServices::openUrl(fileToDownload.fileName());
        }
        // Reset stuff
        loadComplete(true);
        isDownloading = false;
        hasCanceledDownload = false;
    }
}

// Error handler

void MainWindow::checkError(QNetworkReply *reply)
{
}

// Edit actions

void MainWindow::selectAllWebView()
{
    currentPage()->pageAction(QWebPage::SelectAll)->trigger();
}

void MainWindow::copy()
{
    currentPage()->pageAction(QWebPage::Copy)->trigger();
}

void MainWindow::paste()
{
    currentPage()->pageAction(QWebPage::Paste)->trigger();
}

void MainWindow::cut()
{
    currentPage()->pageAction(QWebPage::Cut)->trigger();
}


// Find text

void MainWindow::toggleWindowFindText()
{
    // This slot displays or hides the FindText bar

    if (findTextField->isVisible())
    {
        hideWindowFindText();
    }
    else
    {
        showWindowFindText();
    }
}

void MainWindow::showWindowFindText()
{
    // This slot displays and initializes the FindText bar

    statusBar()->showMessage("");
    progressionBar->setVisible(false);
    findLabel->setVisible(true);
    findTextField->setVisible(true);
    buttonSubmitFind->setVisible(true);
    findTextField->setFocus(Qt::OtherFocusReason);
    findTextField->selectAll();
}

void MainWindow::hideWindowFindText()
{
    // This slot hides the FindText bar and initializes the StatusBar

    findLabel->setVisible(false);
    findTextField->setVisible(false);
    buttonSubmitFind->setVisible(false);
    nothingFound->setVisible(false);
    statusBar()->showMessage(tr("Ready"), 2000);
    actionHighlighText->setChecked(false);
    currentPage()->page()->findText("", QWebPage::FindWrapsAroundDocument);
}

void MainWindow::highlightText()
{
    // This slot is called when the user wants to find a text on the page

    findTextField->selectAll();
    currentPage()->page()->findText("", QWebPage::FindWrapsAroundDocument); // always clean the selection to delete previous highlighted stuff
    nothingFound->setVisible(!currentPage()->page()->findText(findTextField->text(), QWebPage::FindWrapsAroundDocument));
}

// Preferences

void MainWindow::showPreferences()
{
    // This slot creates the preferences window and displays it

    PreferencesWindow *preferencesWindow = new PreferencesWindow(this);
    preferencesWindow->exec();
}

void MainWindow::togglePrivateBrowsing()
{
    // This slot enabled/disables private browsing

    getPreferences(); // updates the user settings
    if (actionPrivateBrowsing->isChecked())
    {
        int answer = QMessageBox::question(this, tr("Private Browsing - Mango"), tr("<p><h3>Are you sure you want to turn on private browsing ?</h3></p><br/><p>You will lose your opened tabs.</p>"), QMessageBox::Yes | QMessageBox::No);
        if (answer == QMessageBox::Yes)
        {
            QWebSettings::globalSettings()->setAttribute(QWebSettings::PrivateBrowsingEnabled, true);
            newTab("");
            for (int i = tabs->count()-2; i >= 0; i--)
            {
                tabs->removeTab(i);
            }
            actionPrivateBrowsing->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/data/privateBrowsingOn.png"));
            privateBrowsingIcon->setVisible(true);
        }
        else
        {
            QWebSettings::globalSettings()->setAttribute(QWebSettings::PrivateBrowsingEnabled, false);
            actionPrivateBrowsing->setChecked(false);
            actionPrivateBrowsing->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/data/privateBrowsingOff.png"));
            privateBrowsingIcon->setVisible(false);
        }
    }
    else
    {
        QWebSettings::globalSettings()->setAttribute(QWebSettings::PrivateBrowsingEnabled, false);
        newTab(fileHomePage);
        for (int i = tabs->count()-2; i >= 0; i--)
        {
            tabs->removeTab(i);
        }
        actionPrivateBrowsing->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/data/privateBrowsingOff.png"));
        privateBrowsingIcon->setVisible(false);
    }
}

// Statusbar slots

void MainWindow::loadBegin()
{
    // This slot is called when the page begins loading

    progressionBar->setVisible(true);
    actionStop->setEnabled(true);
    actionReload->setEnabled(false);
    currentPage()->setZoomFactor(1);
    tabs->setTabIcon(tabs->currentIndex(), QIcon(QCoreApplication::applicationDirPath()+ "/data/loading.gif"));
}

void MainWindow::loading(int pourcentage)
{
    // This slot is called while the page is loading

    progressionBar->setVisible(true);
    progressionBar->setValue(pourcentage);
    tabs->setTabIcon(tabs->currentIndex(), QIcon(QCoreApplication::applicationDirPath()+ "/data/loading.gif"));
}

void MainWindow::loadComplete(bool ok)
{
    // This slot is called when the page is loaded

    if (ok)
    {
        // If the page is fully loaded
        if (addressField->text().isEmpty())
        {
            addressField->setFocus(Qt::OtherFocusReason);
        }
        else
        {
            addressField->setCursorPosition(0);
            currentPage()->setFocus(Qt::OtherFocusReason);
        }
    }
    else if (!ok && hasCanceledDownload)
    {
        // If the page is not fully loaded because the user has canceled a download
        addressField->setCursorPosition(0);
        currentPage()->setFocus(Qt::OtherFocusReason);
    }
    else
    {
        // If the page is not fully loaded
        if (isDownloading)
        {
            // if the user is downloading a file
            addressField->setCursorPosition(0);
            currentPage()->setFocus(Qt::OtherFocusReason);
        }
    }
    // Reset buttons and set favicon
    progressionBar->setVisible(false);
    prepareButtons();
    statusBar()->showMessage(tr("Ready"), 2000);
    tabs->setTabIcon(tabs->currentIndex(), this->getFavicon());
}

void MainWindow::showLink(const QString & link, const QString & title, const QString & textContent)
{
    // This slot displays the links in the statusbar

    progressionBar->setVisible(false);
    statusBar()->showMessage(link);
}

// Events

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // This reimplementation is to enable ctrl + tab tabs' switch all over the window
    // and Escape press to exit fullscreen mode

    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Tab)
    {
        tabs->keyPressEvent(event);
        event->accept();
    }
    else if (event->key() == Qt::Key_Escape && this->isFullScreen())
    {
        this->showMaximized();
        actionFullScreen->setChecked(false);
    }
    else if (event->key() == Qt::Key_Escape && findTextField->isVisible())
    {
        hideWindowFindText();
    }
    else if (event->key() == Qt::Key_F5)
    {
        actionReload->trigger();
    }
    else
    {
        event->ignore();
    }
    QMainWindow::keyPressEvent(event);
}
