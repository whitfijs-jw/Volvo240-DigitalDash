#include "speedometer_model.h"
#include <QDebug>
#include <utils.h>

SpeedometerModel::SpeedometerModel(QObject *parent) :
    BaseGaugeModel(parent)
{

}

QHash<int, QByteArray> SpeedometerModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles = BaseGaugeModel::roleNames();

    roles[DashUtils::to_underlying(SpeedometerModelRoles::TopValueRole)] = "valueTop";
    roles[DashUtils::to_underlying(SpeedometerModelRoles::TopUnitsRole)] = "valueTopUnits";
    roles[DashUtils::to_underlying(SpeedometerModelRoles::CurrentGearRole)] = "currentGear";
    return roles;
}

QVariant SpeedometerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (auto variant = BaseGaugeModel::headerData(section, orientation, role); !variant.isNull()) {
        return variant;
    }

    if(role == DashUtils::to_underlying(SpeedometerModelRoles::TopValueRole))
    {
        return QVariant("valueTop");
    }
    else if(role == DashUtils::to_underlying(SpeedometerModelRoles::TopUnitsRole))
    {
        return QVariant("valueTopUnits");
    }
    else if (role == DashUtils::to_underlying(SpeedometerModelRoles::CurrentGearRole))
    {
        return QVariant("currentGear");
    }
    return QVariant("");
}

int SpeedometerModel::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return 1;
}

QVariant SpeedometerModel::data(const QModelIndex &index, int role) const
{
    if (auto variant = BaseGaugeModel::data(index, role); !variant.isNull()) {
        return variant;
    }

    if(role == DashUtils::to_underlying(SpeedometerModelRoles::TopValueRole))
    {
        return mTopValue;
    }
    else if(role == DashUtils::to_underlying(SpeedometerModelRoles::TopUnitsRole))
    {
        return mTopUnits;
    }
    else if (role == DashUtils::to_underlying(SpeedometerModelRoles::CurrentGearRole))
    {
        return mCurrentGear;
    }
    // Default return:
    return QVariant::fromValue(nullptr);
}

bool SpeedometerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (BaseGaugeModel::setData(index, value, role) == true) {
        return true;
    }

    if(role == DashUtils::to_underlying(SpeedometerModelRoles::TopValueRole))
    {
        mTopValue = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << DashUtils::to_underlying(SpeedometerModelRoles::TopValueRole));
        emit topValueChanged();
        return true;
    }
    else if(role == DashUtils::to_underlying(SpeedometerModelRoles::TopUnitsRole))
    {
        mTopUnits = value.toString();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << DashUtils::to_underlying(SpeedometerModelRoles::TopUnitsRole));
        emit topUnitsChanged();
        return true;
    }
    else if (role == DashUtils::to_underlying(SpeedometerModelRoles::CurrentGearRole))
    {
        mCurrentGear = value.toInt();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << DashUtils::to_underlying(SpeedometerModelRoles::CurrentGearRole));
        emit currentGearChanged();
        return true;
    }
    else
    {
        emit layoutChanged();
    }
    return false;
}

Qt::ItemFlags SpeedometerModel::flags(const QModelIndex &index) const
{
    (void)index;
    return Qt::ItemIsEditable;
}

qreal SpeedometerModel::topValue() const
{
    return mTopValue;
}

QString SpeedometerModel::topUnits() const
{
    return mTopUnits;
}

int SpeedometerModel::currentGear() const
{
    return mCurrentGear;
}

void SpeedometerModel::setTopValue(qreal topValue)
{
    mTopValue = topValue;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << DashUtils::to_underlying(SpeedometerModelRoles::TopValueRole));
    emit topValueChanged();
}

void SpeedometerModel::setTopUnits(QString topUnits)
{
    mTopUnits = topUnits;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << DashUtils::to_underlying(SpeedometerModelRoles::TopUnitsRole));
    emit topUnitsChanged();
}

void SpeedometerModel::setCurrentGear(int gear) {
    mCurrentGear = gear;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << DashUtils::to_underlying(SpeedometerModelRoles::CurrentGearRole));
    emit currentGearChanged();
}
