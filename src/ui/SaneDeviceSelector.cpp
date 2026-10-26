#include "SaneDeviceSelector.hpp"

SaneDeviceSelector::SaneDeviceSelector(const SANE_Device **devices, QWidget *parent)
    : QDialog(parent)
{
    // Configure layouts
    QVBoxLayout *globalLayout = new QVBoxLayout(this);

    QHBoxLayout *devicesLayout = new QHBoxLayout();
    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    globalLayout->addLayout(devicesLayout);
    globalLayout->addLayout(buttonsLayout);

    // Device Selector
    SaneListDevicesModel *devicesModel = new SaneListDevicesModel(this);
    QListView            *listView     = new QListView(this);

    listView->setModel(devicesModel);
    listView->setItemDelegate(new SaneListDeviceDelegate(this));
    listView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    devicesLayout->addWidget(listView, 2);

    // Device info
    devicesLayout->addStretch(1);    // TODO: Implement device info

    // Buttons
    QPushButton *selectButton = new QPushButton("Select", this);
    buttonsLayout->addWidget(selectButton, 0, Qt::AlignRight | Qt::AlignVCenter);
    // TODO: Fix sizing of Select button & add 'refresh' button + selector for local

    QItemSelectionModel *selectionModel = listView->selectionModel();
    selectButton->setEnabled(selectionModel->hasSelection());
    connect(
      selectionModel,
      &QItemSelectionModel::selectionChanged,
      selectButton,
      [selectButton,
       selectionModel](const QItemSelection &selected, const QItemSelection &deselected)
      {
          Q_UNUSED(deselected);
          Q_UNUSED(selected);
          selectButton->setEnabled(selectionModel->hasSelection());
      });
    connect(selectButton, &QPushButton::pressed, this, &QDialog::accept);

    devicesModel->setDevices(devices);    // TODO: Async Scan devices if nullptr
}