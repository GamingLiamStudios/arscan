#pragma once

#include <QtWidgets>
#include <sane/sane.h>

struct SaneDeviceInfo
{
    QString name;
    QString vendor;
    QString model;
    QString type;

    static const SaneDeviceInfo INVALID_DEVICE;
    SaneDeviceInfo(QString name, QString vendor, QString model, QString type)
        : name(name), vendor(vendor), model(model), type(type)
    {
    }

    bool operator==(const SaneDeviceInfo &) const = default;
};

inline const SaneDeviceInfo SaneDeviceInfo::INVALID_DEVICE({}, {}, {}, {});

// Assume SANE is already initalized; likely UB if not
class SaneDevicesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum DeviceRoles
    {
        DeviceName = Qt::UserRole + 1,
        DeviceVendor,
        DeviceModel,
        DeviceType,
    };

    explicit SaneDevicesModel(QWidget *parent = nullptr) : QAbstractListModel(parent) { }

    void                  setDevices(const SANE_Device **devices);
    const SaneDeviceInfo &getDevice(size_t index);

    int      rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    std::vector<SaneDeviceInfo> m_devices;
};