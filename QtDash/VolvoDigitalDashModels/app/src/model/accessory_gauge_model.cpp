#include "accessory_gauge_model.h"

AccessoryGaugeModel::AccessoryGaugeModel(QObject *parent) :
    BaseGaugeModel(parent)
{

}

QHash<int, QByteArray> AccessoryGaugeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles = BaseGaugeModel::roleNames();
    roles[AccessoryGaugeRoles::LowAlarmRole] = "gaugeLowAlarm";
    roles[AccessoryGaugeRoles::HighAlarmRole] = "gaugeHighAlarm";
    return roles;
}

QVariant AccessoryGaugeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (auto variant = BaseGaugeModel::headerData(section, orientation, role); !variant.isNull()) {
        return variant;
    }

    if(role == AccessoryGaugeRoles::LowAlarmRole)
    {
        return QVariant("gaugeLowAlarm");
    }
    else if(role == AccessoryGaugeRoles::HighAlarmRole)
    {
        return QVariant("gaugeHighAlarm");
    }
    return QVariant("");
}

int AccessoryGaugeModel::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return 1;
}

QVariant AccessoryGaugeModel::data(const QModelIndex &index, int role) const
{
    if (auto variant = BaseGaugeModel::data(index, role); !variant.isNull()) {
        return variant;
    }

    if(role == AccessoryGaugeRoles::LowAlarmRole)
    {
        return mLowAlarm;
    }
    else if(role == AccessoryGaugeRoles::HighAlarmRole)
    {
        return mHighAlarm;
    }
    // Default return:
    return QVariant::fromValue(nullptr);
}

bool AccessoryGaugeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (BaseGaugeModel::setData(index, value, role) == true) {
        return true;
    }

    if(role == AccessoryGaugeRoles::LowAlarmRole)
    {
        mLowAlarm = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << AccessoryGaugeRoles::LowAlarmRole);
        emit lowAlarmChanged();
        return true;
    }
    else if(role == AccessoryGaugeRoles::HighAlarmRole)
    {
        mHighAlarm = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << AccessoryGaugeRoles::HighAlarmRole);
        emit highAlarmChanged();
        return true;
    }
    else
    {
        emit layoutChanged();
    }
    return false;
}

Qt::ItemFlags AccessoryGaugeModel::flags(const QModelIndex &index) const
{
    (void)index;
    return Qt::ItemIsEditable;
}

qreal AccessoryGaugeModel::lowAlarm() const
{
    return mLowAlarm;
}

qreal AccessoryGaugeModel::highAlarm() const
{
    return mHighAlarm;
}

void AccessoryGaugeModel::setLowAlarm(qreal lowAlarm)
{
    mLowAlarm = lowAlarm;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << AccessoryGaugeRoles::LowAlarmRole);
    emit lowAlarmChanged();
}

void AccessoryGaugeModel::setHighAlarm(qreal highAlarm)
{
    mHighAlarm = highAlarm;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << AccessoryGaugeRoles::HighAlarmRole);
    emit highAlarmChanged();
}
