#include "BrowserApplication.h"

BrowserApplication::BrowserApplication(int argc, char *argv[]) : QApplication(argc, argv)
{
    // Default style
    setStyle(new QPlastiqueStyle);

    // Properties
    setApplicationName("Mango");
    setOrganizationName("MangoDevTeam");
    setApplicationVersion("1.2");
    setOrganizationDomain("thomasutc.fr");

    // Main Window
    MainWindow *main = new MainWindow();
    main->show();
}
