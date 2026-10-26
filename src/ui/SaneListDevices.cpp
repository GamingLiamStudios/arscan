#include "SaneListDevices.hpp"

void SaneListDevicesModel::setDevices(const SANE_Device **devices)
{
    beginResetModel();

    m_devices.clear();
    if (devices)
    {
        for (int i = 0; devices[i] != nullptr; i++)
        {
            m_devices.push_back(SaneDeviceInfo(devices[i]));
        }
    }

    endResetModel();
}

const SaneDeviceInfo &SaneListDevicesModel::getDevice(size_t index)
{
    if (index < this->m_devices.size()) { return this->m_devices[index]; }
    return SaneDeviceInfo::INVALID_DEVICE;
}

int SaneListDevicesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return static_cast<int>(this->m_devices.size());
}

QVariant SaneListDevicesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= static_cast<int>(m_devices.size())) return {};

    const SaneDeviceInfo &device = m_devices[index.row()];

    switch (role)
    {
    case Qt::DisplayRole: return QString("%1 %2").arg(device.vendor, device.model);
    case Qt::ToolTipRole:
    case DeviceRoles::Name: return device.name;
    case DeviceRoles::Vendor: return device.vendor;
    case DeviceRoles::Model: return device.model;
    case DeviceRoles::Type: return device.type;

    default: return {};
    }
}

void SaneListDeviceDelegate::paint(
  QPainter                   *painter,
  const QStyleOptionViewItem &option,
  const QModelIndex          &index) const
{
    painter->save();

    QRect outerRect = option.rect;

    if (option.state & QStyle::State_Selected)
    {
        painter->fillRect(option.rect, option.palette.highlight());
        painter->setPen(option.palette.highlightedText().color());
    }
    else
    {
        QBrush brush = option.backgroundBrush;
        painter->fillRect(outerRect, brush);
    }

    QString vendor = index.data(SaneListDevicesModel::DeviceRoles::Vendor).toString();
    QString model  = index.data(SaneListDevicesModel::DeviceRoles::Model).toString();
    QString name   = index.data(SaneListDevicesModel::DeviceRoles::Name).toString();

    QRect innerRect = outerRect.marginsRemoved(OUTER_MARGINS);

    QRect nameRect(innerRect.left(), innerRect.top(), innerRect.width(), NAME_HEIGHT);
    painter->setFont(NAME_FONT);
    painter->drawText(
      nameRect,
      Qt::AlignLeft | Qt::AlignVCenter,
      QString("%1 %2").arg(vendor, model));

    QRect identRect(
      innerRect.left(),
      nameRect.bottom() + IDENT_VPAD,
      innerRect.width(),
      IDENT_HEIGHT);
    painter->setFont(IDENT_FONT);
    painter->drawText(identRect, Qt::AlignLeft | Qt::AlignVCenter, name);

    painter->restore();
}

QSize SaneListDeviceDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index)
  const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    return QSize(
      200,
      NAME_HEIGHT + IDENT_HEIGHT + IDENT_VPAD + OUTER_MARGINS.top() + OUTER_MARGINS.bottom());
}