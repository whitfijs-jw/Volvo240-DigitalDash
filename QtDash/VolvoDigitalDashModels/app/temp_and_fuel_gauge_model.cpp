#include "temp_and_fuel_gauge_model.h"

TempAndFuelGaugeModel::TempAndFuelGaugeModel(QObject *parent) :
    QAbstractListModel(parent)
{

}
QHash<int, QByteArray> TempAndFuelGaugeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TempAndFuelGaugeModelRoles::MinTempRole] = "tempMin";
    roles[TempAndFuelGaugeModelRoles::MaxTempRole] = "tempMax";
    roles[TempAndFuelGaugeModelRoles::CurrentTempRole] = "currentTemp";
    roles[TempAndFuelGaugeModelRoles::TempUnitsRole] = "tempUnits";
    roles[TempAndFuelGaugeModelRoles::FuelLevelRole] = "currentFuelLevel";
    roles[TempAndFuelGaugeModelRoles::HighTempAlarmRole] = "alarmHighTemp";
    roles[TempAndFuelGaugeModelRoles::LowFuelAlarmRole] = "alarmLowFuel";
    return roles;
}

QVariant TempAndFuelGaugeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == TempAndFuelGaugeModelRoles::MinTempRole)
    {
        return QVariant("tempMin");
    }
    else if(role == TempAndFuelGaugeModelRoles::MaxTempRole)
    {
        return QVariant("tempMax");
    }
    else if(role == TempAndFuelGaugeModelRoles::CurrentTempRole)
    {
        return QVariant("currentTemp");
    }
    else if(role == TempAndFuelGaugeModelRoles::TempUnitsRole)
    {
        return QVariant("tempUnits");
    }
    else if(role == TempAndFuelGaugeModelRoles::FuelLevelRole)
    {
        return QVariant("currentFuelLevel");
    }
    else if(role == TempAndFuelGaugeModelRoles::HighTempAlarmRole)
    {
        return QVariant("alarmHighTemp");
    }
    else if(role == TempAndFuelGaugeModelRoles::LowFuelAlarmRole)
    {
        return QVariant("alarmLowFuel");
    }
    return QVariant("");
}

int TempAndFuelGaugeModel::rowCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant TempAndFuelGaugeModel::data(const QModelIndex &index, int role) const
{
    if (role == TempAndFuelGaugeModelRoles::MinTempRole)
    {
        return mMinTemp;
    }
    else if(role == TempAndFuelGaugeModelRoles::MaxTempRole)
    {
        return mMaxTemp;
    }
    else if(role == TempAndFuelGaugeModelRoles::CurrentTempRole)
    {
        return mCurrentTemp;
    }
    else if(role == TempAndFuelGaugeModelRoles::TempUnitsRole)
    {
        return mTempUnits;
    }
    else if(role == TempAndFuelGaugeModelRoles::FuelLevelRole)
    {
        return mFuelLevel;
    }
    else if(role == TempAndFuelGaugeModelRoles::HighTempAlarmRole)
    {
        return mHighTempAlarm;
    }
    else if(role == TempAndFuelGaugeModelRoles::LowFuelAlarmRole)
    {
        return mLowFuelAlarm;
    }
    // Default return:
    return mCurrentTemp;
}

bool TempAndFuelGaugeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == TempAndFuelGaugeModelRoles::MinTempRole)
    {
        mMinTemp = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << TempAndFuelGaugeModelRoles::MinTempRole);
        emit minTempChanged();
    }
    else if(role == TempAndFuelGaugeModelRoles::MaxTempRole)
    {
        mMaxTemp = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << TempAndFuelGaugeModelRoles::MaxTempRole);
        emit maxTempChanged();
    }
    else if(role == TempAndFuelGaugeModelRoles::CurrentTempRole)
    {
        mCurrentTemp = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << TempAndFuelGaugeModelRoles::CurrentTempRole);
        emit currentTempChanged();
    }
    else if(role == TempAndFuelGaugeModelRoles::TempUnitsRole)
    {
        mTempUnits = value.toString();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << TempAndFuelGaugeModelRoles::TempUnitsRole);
        emit tempUnitsChanged();
    }
    else if(role == TempAndFuelGaugeModelRoles::FuelLevelRole)
    {
        mFuelLevel = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << TempAndFuelGaugeModelRoles::FuelLevelRole);
        emit fuelLevelChanged();
    }
    else if(role == TempAndFuelGaugeModelRoles::HighTempAlarmRole)
    {
        mHighTempAlarm = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << TempAndFuelGaugeModelRoles::HighTempAlarmRole);
        emit highTempAlarmChanged();
    }
    else if(role == TempAndFuelGaugeModelRoles::LowFuelAlarmRole)
    {
        mLowFuelAlarm = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << TempAndFuelGaugeModelRoles::LowFuelAlarmRole);
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
    return Qt::ItemIsEditable;
}

qreal TempAndFuelGaugeModel::maxTemp()
{
    return mMaxTemp;
}

qreal TempAndFuelGaugeModel::minTemp()
{
    return mMinTemp;
}

qreal TempAndFuelGaugeModel::currentTemp()
{
    return mCurrentTemp;
}

QString TempAndFuelGaugeModel::tempUnits()
{
    return mTempUnits;
}

qreal TempAndFuelGaugeModel::fuelLevel()
{
    return mFuelLevel;
}

qreal TempAndFuelGaugeModel::highTempAlarm()
{
    return mHighTempAlarm;
}

qreal TempAndFuelGaugeModel::lowFuelAlarm()
{
    return mLowFuelAlarm;
}

void TempAndFuelGaugeModel::setMaxTemp(qreal maxTemp)
{
    mMaxTemp = maxTemp;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << TempAndFuelGaugeModelRoles::MaxTempRole);
    emit maxTempChanged();
}

void TempAndFuelGaugeModel::setMinTemp(qreal minTemp)
{
    mMinTemp = minTemp;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << TempAndFuelGaugeModelRoles::MinTempRole);
    emit minTempChanged();
}

void TempAndFuelGaugeModel::setCurrentTemp(qreal currentTemp)
{
    mCurrentTemp = currentTemp;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << TempAndFuelGaugeModelRoles::CurrentTempRole);
    emit currentTempChanged();
}

void TempAndFuelGaugeModel::setTempUnits(QString units)
{
    mTempUnits = units;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << TempAndFuelGaugeModelRoles::TempUnitsRole);
    emit tempUnitsChanged();
}

void TempAndFuelGaugeModel::setFuelLevel(qreal fuelLevel)
{
    mFuelLevel = fuelLevel;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << TempAndFuelGaugeModelRoles::FuelLevelRole);
    emit fuelLevelChanged();
}

void TempAndFuelGaugeModel::setHighTempAlarm(qreal highTempAlarm)
{
    mHighTempAlarm = highTempAlarm;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << TempAndFuelGaugeModelRoles::HighTempAlarmRole);
    emit highTempAlarmChanged();
}

void TempAndFuelGaugeModel::setLowFuelAlarm(qreal lowFuelAlarm)
{
    mLowFuelAlarm = lowFuelAlarm;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << TempAndFuelGaugeModelRoles::LowFuelAlarmRole);
    emit lowFuelAlarmChanged();
}
