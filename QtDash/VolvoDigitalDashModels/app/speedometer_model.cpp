#include "speedometer_model.h"

SpeedometerModel::SpeedometerModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

QHash<int, QByteArray> SpeedometerModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[SpeedometerModelRoles::MinValueRole] = "minValue";
    roles[SpeedometerModelRoles::MaxValueRole] = "maxValue";
    roles[SpeedometerModelRoles::CurrentValueRole] = "currentValue";
    roles[SpeedometerModelRoles::UnitsRole] = "speedUnits";
    roles[SpeedometerModelRoles::TopValueRole] = "valueTop";
    roles[SpeedometerModelRoles::TopUnitsRole] = "valueTopUnits";
    return roles;
}

QVariant SpeedometerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == SpeedometerModelRoles::MinValueRole)
    {
        return QVariant("minValue");
    }
    else if(role == SpeedometerModelRoles::MaxValueRole)
    {
        return QVariant("maxValue");
    }
    else if(role == SpeedometerModelRoles::CurrentValueRole)
    {
        return QVariant("currentValue");
    }
    else if(role == SpeedometerModelRoles::UnitsRole)
    {
        return QVariant("speedUnits");
    }
    else if(role == SpeedometerModelRoles::TopValueRole)
    {
        return QVariant("valueTop");
    }
    else if(role == SpeedometerModelRoles::TopUnitsRole)
    {
        return QVariant("valueTopUnits");
    }
    return QVariant("");
}

int SpeedometerModel::rowCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant SpeedometerModel::data(const QModelIndex &index, int role) const
{
    if (role == SpeedometerModelRoles::MinValueRole)
    {
        return mMinValue;
    }
    else if(role == SpeedometerModelRoles::MaxValueRole)
    {
        return mMaxValue;
    }
    else if(role == SpeedometerModelRoles::CurrentValueRole)
    {
        return mCurrentValue;
    }
    else if(role == SpeedometerModelRoles::UnitsRole)
    {
        return mUnits;
    }
    else if(role == SpeedometerModelRoles::TopValueRole)
    {
        return mTopValue;
    }
    else if(role == SpeedometerModelRoles::TopUnitsRole)
    {
        return mTopUnits;
    }
    // Default return:
    return mCurrentValue;
}

bool SpeedometerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == SpeedometerModelRoles::MinValueRole)
    {
        mMinValue = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << SpeedometerModelRoles::MinValueRole);
        emit minValueChanged();
    }
    else if(role == SpeedometerModelRoles::MaxValueRole)
    {
        mMaxValue = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << SpeedometerModelRoles::MaxValueRole);
        emit maxValueChanged();
    }
    else if(role == SpeedometerModelRoles::CurrentValueRole)
    {
        mCurrentValue = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << SpeedometerModelRoles::CurrentValueRole);
        emit currentValueChanged();
    }
    else if(role == SpeedometerModelRoles::UnitsRole)
    {
        mUnits = value.toString();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << SpeedometerModelRoles::UnitsRole);
        emit unitsChanged();
    }
    else if(role == SpeedometerModelRoles::TopValueRole)
    {
        mTopValue = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << SpeedometerModelRoles::TopValueRole);
        emit topValueChanged();
    }
    else if(role == SpeedometerModelRoles::TopUnitsRole)
    {
        mTopUnits = value.toString();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << SpeedometerModelRoles::TopUnitsRole);
        emit topUnitsChanged();
    }
    else
    {
        emit layoutChanged();
    }
    return true;
}

Qt::ItemFlags SpeedometerModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable;
}

qreal SpeedometerModel::minValue()
{
    return mMinValue;
}

qreal SpeedometerModel::maxValue()
{
    return mMaxValue;
}

qreal SpeedometerModel::currentValue()
{
    return mCurrentValue;
}

QString SpeedometerModel::units()
{
    return mUnits;
}

qreal SpeedometerModel::topValue()
{
    return mTopValue;
}

QString SpeedometerModel::topUnits()
{
    return mTopUnits;
}

void SpeedometerModel::setMinValue(qreal minValue)
{
    mMinValue = minValue;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << SpeedometerModelRoles::MinValueRole);
    emit minValueChanged();
}

void SpeedometerModel::setMaxValue(qreal maxValue)
{
    mMaxValue = maxValue;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << SpeedometerModelRoles::MaxValueRole);
    emit maxValueChanged();
}

void SpeedometerModel::setCurrentValue(qreal currentValue)
{
    mCurrentValue = currentValue;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << SpeedometerModelRoles::CurrentValueRole);
    emit currentValueChanged();
}

void SpeedometerModel::setUnits(QString units)
{
    mUnits = units;
    emit dataChanged(createIndex(0, 0),
                     createIndex(1, 0),
                     QVector<int>() << SpeedometerModelRoles::UnitsRole);
    emit unitsChanged();
}

void SpeedometerModel::setTopValue(qreal topValue)
{
    mTopValue = topValue;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << SpeedometerModelRoles::TopValueRole);
    emit topValueChanged();
}

void SpeedometerModel::setTopUnits(QString topUnits)
{
    mTopUnits = topUnits;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << SpeedometerModelRoles::TopUnitsRole);
    emit topUnitsChanged();
}
