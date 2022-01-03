#include "accessory_gauge_model.h"

AccessoryGaugeModel::AccessoryGaugeModel(QObject *parent) :
    QAbstractListModel(parent),
    mMinValue(0),
    mMaxValue(1),
    mCurrentValue(0),
    mUnits("")
{

}

QHash<int, QByteArray> AccessoryGaugeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[AccessoryGaugeRoles::MinValueRole] = "gaugeMin";
    roles[AccessoryGaugeRoles::MaxValueRole] = "gaugeMax";
    roles[AccessoryGaugeRoles::CurrentValueRole] = "currentValue";
    roles[AccessoryGaugeRoles::UnitsRole] = "gaugeUnits";
    roles[AccessoryGaugeRoles::LowAlarmRole] = "gaugeLowAlarm";
    roles[AccessoryGaugeRoles::HighAlarmRole] = "gaugeHighAlarm";
    return roles;
}

QVariant AccessoryGaugeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == AccessoryGaugeRoles::MinValueRole)
    {
        return QVariant("gaugeMin");
    }
    else if(role == AccessoryGaugeRoles::MaxValueRole)
    {
        return QVariant("gaugeMax");
    }
    else if(role == AccessoryGaugeRoles::CurrentValueRole)
    {
        return QVariant("currentValue");
    }
    else if(role == AccessoryGaugeRoles::UnitsRole)
    {
        return QVariant("gaugeUnits");
    }
    else if(role == AccessoryGaugeRoles::LowAlarmRole)
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
    return 1;
}

QVariant AccessoryGaugeModel::data(const QModelIndex &index, int role) const
{
    if (role == AccessoryGaugeRoles::MinValueRole)
    {
        return mMinValue;
    }
    else if(role == AccessoryGaugeRoles::MaxValueRole)
    {
        return mMaxValue;
    }
    else if(role == AccessoryGaugeRoles::CurrentValueRole)
    {
        return mCurrentValue;
    }
    else if(role == AccessoryGaugeRoles::UnitsRole)
    {
        return mUnits;
    }
    else if(role == AccessoryGaugeRoles::LowAlarmRole)
    {
        return mLowAlarm;
    }
    else if(role == AccessoryGaugeRoles::HighAlarmRole)
    {
        return mHighAlarm;
    }
    // Default return:
    return mCurrentValue;
}

bool AccessoryGaugeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == AccessoryGaugeRoles::MinValueRole)
    {
        mMinValue = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << AccessoryGaugeRoles::MinValueRole);
        emit minValueChanged();
    }
    else if(role == AccessoryGaugeRoles::MaxValueRole)
    {
        mMaxValue = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << AccessoryGaugeRoles::MaxValueRole);
        emit maxValueChanged();
    }
    else if(role == AccessoryGaugeRoles::CurrentValueRole)
    {
        mCurrentValue = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << AccessoryGaugeRoles::CurrentValueRole);
        emit currentValueChanged();
    }
    else if(role == AccessoryGaugeRoles::UnitsRole)
    {
        mUnits = value.toString();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << AccessoryGaugeRoles::UnitsRole);
        emit unitsChanged();
    }
    else if(role == AccessoryGaugeRoles::LowAlarmRole)
    {
        mLowAlarm = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << AccessoryGaugeRoles::LowAlarmRole);
        emit lowAlarmChanged();
    }
    else if(role == AccessoryGaugeRoles::HighAlarmRole)
    {
        mHighAlarm = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << AccessoryGaugeRoles::HighAlarmRole);
        emit highAlarmChanged();
    }
    else
    {
        emit layoutChanged();
    }
    return true;
}

Qt::ItemFlags AccessoryGaugeModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable;
}

qreal AccessoryGaugeModel::minValue()
{
    return mMinValue;
}

qreal AccessoryGaugeModel::maxValue()
{
    return mMaxValue;
}

qreal AccessoryGaugeModel::currentValue()
{
    return mCurrentValue;
}

QString AccessoryGaugeModel::units()
{
    return mUnits;
}

qreal AccessoryGaugeModel::lowAlarm()
{
    return mLowAlarm;
}

qreal AccessoryGaugeModel::highAlarm()
{
    return mHighAlarm;
}

void AccessoryGaugeModel::setMinValue(qreal minValue)
{
    mMinValue = minValue;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << AccessoryGaugeRoles::MinValueRole);
    emit minValueChanged();
}

void AccessoryGaugeModel::setMaxValue(qreal maxValue)
{
    mMaxValue = maxValue;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << AccessoryGaugeRoles::MaxValueRole);
    emit maxValueChanged();
}

void AccessoryGaugeModel::setCurrentValue(qreal currentValue)
{
    mCurrentValue = currentValue;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << AccessoryGaugeRoles::CurrentValueRole);
    emit currentValueChanged();
}

void AccessoryGaugeModel::setUnits(QString units)
{
    mUnits = units;
    emit dataChanged(createIndex(0, 0),
                     createIndex(1, 0),
                     QVector<int>() << AccessoryGaugeRoles::UnitsRole);
    emit unitsChanged();
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
