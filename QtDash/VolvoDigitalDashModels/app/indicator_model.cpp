#include "indicator_model.h"

IndicatorModel::IndicatorModel(QObject *parent) :
    QAbstractListModel(parent),
    mOn(false), mFlipped(false)
{

}

QHash<int, QByteArray> IndicatorModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IndicatorRoles::onRole] = "indicatorOn";
    roles[IndicatorRoles::flippedRole] = "indicatorFlipped";
    return roles;
}

QVariant IndicatorModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    (void)section;
    (void)orientation;
    if (role == IndicatorRoles::onRole)
    {
        return QVariant("indicatorOn");
    }
    else if (role == IndicatorRoles::flippedRole)
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
    if (role == IndicatorRoles::onRole)
    {
        return mOn;
    }
    else if (role == IndicatorRoles::flippedRole)
    {
        return mFlipped;
    }
    // Default return:
    return mOn;
}

bool IndicatorModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    (void)index;
    if (role == IndicatorRoles::onRole)
    {
        mOn = value.toBool();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << IndicatorRoles::onRole);
        emit onChanged();
    }
    else if (role == IndicatorRoles::flippedRole)
    {
        mFlipped = value.toBool();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << IndicatorRoles::flippedRole);
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

bool IndicatorModel::on()
{
    return mOn;
}

bool IndicatorModel::flipped()
{
    return mFlipped;
}

void IndicatorModel::setOn(bool on)
{
    mOn = on;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << IndicatorRoles::onRole);
    emit onChanged();
}

void IndicatorModel::setFlipped(bool flipped)
{
    mFlipped = flipped;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << IndicatorRoles::flippedRole);
    emit onFlipped();
}
