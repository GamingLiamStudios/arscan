#include "SaneDevicesModel.hpp"

#include <sane/sane.h>

void SaneDevicesModel::setDevices(const SANE_Device **devices)
{
    beginResetModel();

    m_devices.clear();
    if (devices)
    {
        for (int i = 0; devices[i] != nullptr; i++)
        {
            SaneDeviceInfo deviceInfo(
              QString(devices[i]->name),
              QString(devices[i]->vendor),
              QString(devices[i]->model),
              QString(devices[i]->type));
            m_devices.push_back(deviceInfo);
        }
    }

    endResetModel();
}

const SaneDeviceInfo &SaneDevicesModel::getDevice(size_t index)
{
    if (index < this->m_devices.size()) { return this->m_devices[index]; }
    return SaneDeviceInfo::INVALID_DEVICE;
}

int SaneDevicesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return static_cast<int>(this->m_devices.size());
}

QVariant SaneDevicesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= static_cast<int>(m_devices.size())) return {};

    const SaneDeviceInfo &device = m_devices[index.row()];

    switch (role)
    {
    case Qt::DisplayRole: return QString("%1 %2").arg(device.vendor, device.model);
    case Qt::ToolTipRole:
    case DeviceRoles::DeviceName: return device.name;
    case DeviceRoles::DeviceVendor: return device.vendor;
    case DeviceRoles::DeviceModel: return device.model;
    case DeviceRoles::DeviceType: return device.type;

    default: return {};
    }
}