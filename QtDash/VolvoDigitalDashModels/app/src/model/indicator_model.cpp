#include "indicator_model.h"
#include <utils.h>

IndicatorModel::IndicatorModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

QHash<int, QByteArray> IndicatorModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DashUtils::to_underlying(IndicatorRoles::onRole)] = "indicatorOn";
    roles[DashUtils::to_underlying(IndicatorRoles::flippedRole)] = "indicatorFlipped";
    return roles;
}

QVariant IndicatorModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    (void)section;
    (void)orientation;
    if (role == DashUtils::to_underlying(IndicatorRoles::onRole))
    {
        return QVariant("indicatorOn");
    }
    else if (role == DashUtils::to_underlying(IndicatorRoles::flippedRole))
    {
        return QVariant("indicatorFlipped");
    }
    return QVariant("");
}

int IndicatorModel::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return 1;
}

QVariant IndicatorModel::data(const QModelIndex &index, int role) const
{
    (void)index;
    if (role == DashUtils::to_underlying(IndicatorRoles::onRole))
    {
        return mOn;
    }
    else if (role == DashUtils::to_underlying(IndicatorRoles::flippedRole))
    {
        return mFlipped;
    }
    // Default return:
    return mOn;
}

bool IndicatorModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    (void)index;
    if (role ==  DashUtils::to_underlying(IndicatorRoles::onRole))
    {
        mOn = value.toBool();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() <<  DashUtils::to_underlying(IndicatorRoles::onRole));
        emit onChanged();
    }
    else if (role ==  DashUtils::to_underlying(IndicatorRoles::flippedRole))
    {
        mFlipped = value.toBool();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() <<  DashUtils::to_underlying(IndicatorRoles::flippedRole));
        emit onFlipped();
    }
    else
    {
        emit layoutChanged();
    }
    return true;
}

Qt::ItemFlags IndicatorModel::flags(const QModelIndex &index) const
{
    (void)index;
    return Qt::ItemIsEditable;
}

bool IndicatorModel::on() const
{
    return mOn;
}

bool IndicatorModel::flipped() const
{
    return mFlipped;
}

void IndicatorModel::setOn(bool on)
{
    mOn = on;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() <<  DashUtils::to_underlying(IndicatorRoles::onRole));
    emit onChanged();
}

void IndicatorModel::setFlipped(bool flipped)
{
    mFlipped = flipped;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() <<  DashUtils::to_underlying(IndicatorRoles::flippedRole));
    emit onFlipped();
}
