#include <QtWidgets>
#include <QDebug>

#include "ui/MainWindow.hpp"
#include "ui/AuthModal.hpp"
#include "ui/SaneDevicesModel.hpp"

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
    // In your MainWindow or ScanSettingsPanel
    QDialog devicesDialog;

    SaneDevicesModel *model    = new SaneDevicesModel(&devicesDialog);
    QListView        *listView = new QListView(&devicesDialog);

    listView->setModel(model);

    // Load detected SANE devices into the model
    const SANE_Device **sane_devs = nullptr;
    if (sane_get_devices(&sane_devs, SANE_FALSE) == SANE_STATUS_GOOD)
    {
        model->setDevices(sane_devs);
    }

    // Handle device selection
    QObject::connect(
      listView->selectionModel(),
      &QItemSelectionModel::currentChanged,
      &devicesDialog,
      [model](const QModelIndex &current, const QModelIndex &previous)
      {
          const SaneDeviceInfo &selectedDev = model->getDevice(current.row());
          if (selectedDev != SaneDeviceInfo::INVALID_DEVICE)
          {
              qDebug() << "Selected scanner:" << selectedDev.name;
              // Proceed with sane_open(selectedDev->name, &handle)
          }
      });

    devicesDialog.setWindowTitle("Available Devices");
    devicesDialog.show();

    MainWindow mainWindow;
    mainWindow.show();

    qInfo() << "Hello World!";

    return app.exec();
}