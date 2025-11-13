#include "temp_and_fuel_gauge_model.h"
#include <utils.h>

TempAndFuelGaugeModel::TempAndFuelGaugeModel(QObject *parent) :
    QAbstractItemModel(parent)
{

}
QHash<int, QByteArray> TempAndFuelGaugeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DashUtils::to_underlying(TempAndFuelGaugeModelRoles::MinTempRole)] = "tempMin";
    roles[DashUtils::to_underlying(TempAndFuelGaugeModelRoles::MaxTempRole)] = "tempMax";
    roles[DashUtils::to_underlying(TempAndFuelGaugeModelRoles::CurrentTempRole)] = "currentTemp";
    roles[DashUtils::to_underlying(TempAndFuelGaugeModelRoles::TempUnitsRole)] = "tempUnits";
    roles[DashUtils::to_underlying(TempAndFuelGaugeModelRoles::FuelLevelRole)] = "currentFuelLevel";
    roles[DashUtils::to_underlying(TempAndFuelGaugeModelRoles::HighTempAlarmRole)] = "alarmHighTemp";
    roles[DashUtils::to_underlying(TempAndFuelGaugeModelRoles::LowFuelAlarmRole)] = "alarmLowFuel";
    return roles;
}

QVariant TempAndFuelGaugeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    (void)section;
    (void)orientation;
    if (role == DashUtils::to_underlying(TempAndFuelGaugeModelRoles::MinTempRole))
    {
        return QVariant("tempMin");
    }
    else if(role == DashUtils::to_underlying(TempAndFuelGaugeModelRoles::MaxTempRole))
    {
        return QVariant("tempMax");
    }
    else if(role == DashUtils::to_underlying(TempAndFuelGaugeModelRoles::CurrentTempRole))
    {
        return QVariant("currentTemp");
    }
    else if(role == DashUtils::to_underlying(TempAndFuelGaugeModelRoles::TempUnitsRole))
    {
        return QVariant("tempUnits");
    }
    else if(role == DashUtils::to_underlying(TempAndFuelGaugeModelRoles::FuelLevelRole))
    {
        return QVariant("currentFuelLevel");
    }
    else if(role == DashUtils::to_underlying(TempAndFuelGaugeModelRoles::HighTempAlarmRole))
    {
        return QVariant("alarmHighTemp");
    }
    else if(role == DashUtils::to_underlying(TempAndFuelGaugeModelRoles::LowFuelAlarmRole))
    {
        return QVariant("alarmLowFuel");
    }
    return QVariant("");
}

int TempAndFuelGaugeModel::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return 1;
}

QVariant TempAndFuelGaugeModel::data(const QModelIndex &index, int role) const
{
    (void)index;
    if (role == DashUtils::to_underlying(TempAndFuelGaugeModelRoles::MinTempRole))
    {
        return mMinTemp;
    }
    else if(role == DashUtils::to_underlying(TempAndFuelGaugeModelRoles::MaxTempRole))
    {
        return mMaxTemp;
    }
    else if(role == DashUtils::to_underlying(TempAndFuelGaugeModelRoles::CurrentTempRole))
    {
        return mCurrentTemp;
    }
    else if(role == DashUtils::to_underlying(TempAndFuelGaugeModelRoles::TempUnitsRole))
    {
        return mTempUnits;
    }
    else if(role == DashUtils::to_underlying(TempAndFuelGaugeModelRoles::FuelLevelRole))
    {
        return mFuelLevel;
    }
    else if(role == DashUtils::to_underlying(TempAndFuelGaugeModelRoles::HighTempAlarmRole))
    {
        return mHighTempAlarm;
    }
    else if(role == DashUtils::to_underlying(TempAndFuelGaugeModelRoles::LowFuelAlarmRole))
    {
        return mLowFuelAlarm;
    }
    // Default return:
    return mCurrentTemp;
}

bool TempAndFuelGaugeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    (void)index;
    if (role == DashUtils::to_underlying(TempAndFuelGaugeModelRoles::MinTempRole))
    {
        mMinTemp = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << DashUtils::to_underlying(TempAndFuelGaugeModelRoles::MinTempRole));
        emit minTempChanged();
    }
    else if(role == DashUtils::to_underlying(TempAndFuelGaugeModelRoles::MaxTempRole))
    {
        mMaxTemp = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << DashUtils::to_underlying(TempAndFuelGaugeModelRoles::MaxTempRole));
        emit maxTempChanged();
    }
    else if(role == DashUtils::to_underlying(TempAndFuelGaugeModelRoles::CurrentTempRole))
    {
        mCurrentTemp = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << DashUtils::to_underlying(TempAndFuelGaugeModelRoles::CurrentTempRole));
        emit currentTempChanged();
    }
    else if(role == DashUtils::to_underlying(TempAndFuelGaugeModelRoles::TempUnitsRole))
    {
        mTempUnits = value.toString();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << DashUtils::to_underlying(TempAndFuelGaugeModelRoles::TempUnitsRole));
        emit tempUnitsChanged();
    }
    else if(role == DashUtils::to_underlying(TempAndFuelGaugeModelRoles::FuelLevelRole))
    {
        mFuelLevel = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << DashUtils::to_underlying(TempAndFuelGaugeModelRoles::FuelLevelRole));
        emit fuelLevelChanged();
    }
    else if(role == DashUtils::to_underlying(TempAndFuelGaugeModelRoles::HighTempAlarmRole))
    {
        mHighTempAlarm = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << DashUtils::to_underlying(TempAndFuelGaugeModelRoles::HighTempAlarmRole));
        emit highTempAlarmChanged();
    }
    else if(role == DashUtils::to_underlying(TempAndFuelGaugeModelRoles::LowFuelAlarmRole))
    {
        mLowFuelAlarm = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << DashUtils::to_underlying(TempAndFuelGaugeModelRoles::LowFuelAlarmRole));
        emit lowFuelAlarmChanged();
    }
    else
    {
        emit layoutChanged();
    }
    return true;
}

Qt::ItemFlags TempAndFuelGaugeModel::flags(const QModelIndex &index) const
{
    (void)index;
    return Qt::ItemIsEditable;
}

qreal TempAndFuelGaugeModel::maxTemp() const
{
    return mMaxTemp;
}

qreal TempAndFuelGaugeModel::minTemp() const
{
    return mMinTemp;
}

qreal TempAndFuelGaugeModel::currentTemp() const
{
    return mCurrentTemp;
}

QString TempAndFuelGaugeModel::tempUnits() const
{
    return mTempUnits;
}

qreal TempAndFuelGaugeModel::fuelLevel() const
{
    return mFuelLevel;
}

qreal TempAndFuelGaugeModel::highTempAlarm() const
{
    return mHighTempAlarm;
}

qreal TempAndFuelGaugeModel::lowFuelAlarm() const
{
    return mLowFuelAlarm;
}

void TempAndFuelGaugeModel::setMaxTemp(qreal maxTemp)
{
    mMaxTemp = maxTemp;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << DashUtils::to_underlying(TempAndFuelGaugeModelRoles::MaxTempRole));
    emit maxTempChanged();
}

void TempAndFuelGaugeModel::setMinTemp(qreal minTemp)
{
    mMinTemp = minTemp;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << DashUtils::to_underlying(TempAndFuelGaugeModelRoles::MinTempRole));
    emit minTempChanged();
}

void TempAndFuelGaugeModel::setCurrentTemp(qreal currentTemp)
{
    mCurrentTemp = currentTemp;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << DashUtils::to_underlying(TempAndFuelGaugeModelRoles::CurrentTempRole));
    emit currentTempChanged();
}

void TempAndFuelGaugeModel::setTempUnits(QString units)
{
    mTempUnits = units;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << DashUtils::to_underlying(TempAndFuelGaugeModelRoles::TempUnitsRole));
    emit tempUnitsChanged();
}

void TempAndFuelGaugeModel::setFuelLevel(qreal fuelLevel)
{
    mFuelLevel = fuelLevel;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << DashUtils::to_underlying(TempAndFuelGaugeModelRoles::FuelLevelRole));
    emit fuelLevelChanged();
}

void TempAndFuelGaugeModel::setHighTempAlarm(qreal highTempAlarm)
{
    mHighTempAlarm = highTempAlarm;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << DashUtils::to_underlying(TempAndFuelGaugeModelRoles::HighTempAlarmRole));
    emit highTempAlarmChanged();
}

void TempAndFuelGaugeModel::setLowFuelAlarm(qreal lowFuelAlarm)
{
    mLowFuelAlarm = lowFuelAlarm;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << DashUtils::to_underlying(TempAndFuelGaugeModelRoles::LowFuelAlarmRole));
    emit lowFuelAlarmChanged();
}
