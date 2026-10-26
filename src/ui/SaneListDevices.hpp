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
    SaneDeviceInfo(const SANE_Device *device)
    {
        this->name   = QString(device->name);
        this->vendor = QString(device->vendor);
        this->model  = QString(device->model);
        this->type   = QString(device->type);
    }

    bool operator==(const SaneDeviceInfo &) const = default;
};

inline const SaneDeviceInfo SaneDeviceInfo::INVALID_DEVICE({}, {}, {}, {});

// Assume SANE is already initalized; likely UB if not
class SaneListDevicesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum DeviceRoles
    {
        Name = Qt::UserRole + 1,
        Vendor,
        Model,
        Type,
    };

    explicit SaneListDevicesModel(QWidget *parent = nullptr) : QAbstractListModel(parent) { }

    void                  setDevices(const SANE_Device **devices);
    const SaneDeviceInfo &getDevice(size_t index);

    int      rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    std::vector<SaneDeviceInfo> m_devices;
};

class SaneListDeviceDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit SaneListDeviceDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) { }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index)
      const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    const QMargins OUTER_MARGINS = QMargins(8, 8, 8, 8);

    const int   NAME_HEIGHT = 20;
    const QFont NAME_FONT   = QFont("Arial", 10, QFont::Medium);

    const int   IDENT_HEIGHT = 10;
    const int   IDENT_VPAD   = 6;
    const QFont IDENT_FONT   = QFont("Arial", 8, QFont::Thin);
};