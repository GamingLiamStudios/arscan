#include <QtWidgets>
#include <QDebug>

#include "ui/MainWindow.hpp"
#include "ui/AuthModal.hpp"
#include "ui/SaneDeviceSelector.hpp"

#include <sane/sane.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Init SANE
    SANE_Int    version;
    SANE_Status status = sane_init(&version, AuthModal::saneCallback);
    if (status != SANE_STATUS_GOOD)
    {
        qFatal() << "SANE failed to init: " << status;
        return -1;
    }
    if (SANE_VERSION_MAJOR(version) != SANE_CURRENT_MAJOR)
    {
        qFatal() << "SANE has an unsupported version. Expected " << SANE_CURRENT_MAJOR << ", Got "
                 << SANE_VERSION_MAJOR(version);
        return -1;
    }

    // List devices
    // Load detected SANE devices into the model
    const SANE_Device **sane_devs = nullptr;
    sane_get_devices(&sane_devs, SANE_FALSE);

    SaneDeviceSelector selector(sane_devs);

    selector.setWindowTitle("Available Devices");
    selector.setMinimumSize(320, 240);
    selector.show();

    // MainWindow mainWindow;
    // mainWindow.show();

    qInfo() << "Hello World!";

    return app.exec();
}