#pragma once

#include <QtWidgets>
#include <sane/sane.h>

#include "SaneListDevices.hpp"

class SaneDeviceSelector : public QDialog
{
    Q_OBJECT

public:
    // Will initiate Scan if devices is nullptr
    SaneDeviceSelector(const SANE_Device **devices = nullptr, QWidget *parent = nullptr);

private:
    void scanDevices();

    SaneListDevicesModel *deviceList;
};