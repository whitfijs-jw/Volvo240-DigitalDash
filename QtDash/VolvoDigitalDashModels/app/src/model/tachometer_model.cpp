#include "tachometer_model.h"
#include <utils.h>

TachometerModel::TachometerModel(QObject *parent) :
    QAbstractItemModel(parent)
{

}

QHash<int, QByteArray> TachometerModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DashUtils::to_underlying(TachometerRoles::RpmRole)] = "rpm";
    roles[DashUtils::to_underlying(TachometerRoles::RedLineRole)] = "redLine";
    roles[DashUtils::to_underlying(TachometerRoles::MaxRpmRole)] = "maxRpm";
    return roles;
}

QVariant TachometerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    (void)section;
    (void)orientation;
    if (role == DashUtils::to_underlying(TachometerRoles::RpmRole))
    {
        return QVariant("rpm");
    }
    else if(role == DashUtils::to_underlying(TachometerRoles::RedLineRole))
    {
        return QVariant("redLine");
    }
    else if(role == DashUtils::to_underlying(TachometerRoles::MaxRpmRole))
    {
        return QVariant("maxRpm");
    }
    return QVariant("");
}

int TachometerModel::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return 1;
}

QVariant TachometerModel::data(const QModelIndex &index, int role) const
{
    (void)index;
    if (role == DashUtils::to_underlying(TachometerRoles::RpmRole))
    {
        return mRpm;
    }
    else if (role == DashUtils::to_underlying(TachometerRoles::RedLineRole))
    {
        return mRedLine;
    }
    else if (role == DashUtils::to_underlying(TachometerRoles::MaxRpmRole))
    {
        return mMaxRpm;
    }
    // Default return:
    return mRpm;
}

bool TachometerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    (void)index;
    if (role == DashUtils::to_underlying(TachometerRoles::RpmRole))
    {
        mRpm = value.toInt();
        emit dataChanged(
            createIndex(0,0),
            createIndex(1, 0),
            QVector<int>() << DashUtils::to_underlying(TachometerRoles::RpmRole));
        emit rpmChanged();
    }
    else if (role == DashUtils::to_underlying(TachometerRoles::RedLineRole))
    {
        mRedLine = value.toInt();
        emit dataChanged(
            createIndex(0,0),
            createIndex(1, 0),
            QVector<int>() << DashUtils::to_underlying(TachometerRoles::RedLineRole));
        emit redLineChanged();
    }
    else if (role == DashUtils::to_underlying(TachometerRoles::MaxRpmRole))
    {
        mMaxRpm = value.toInt();
        emit dataChanged(
            createIndex(0,0),
            createIndex(1, 0),
            QVector<int>() << DashUtils::to_underlying(TachometerRoles::MaxRpmRole));
        emit redLineChanged();
    }
    else
    {
        emit layoutChanged();
    }
    return true;
}

Qt::ItemFlags TachometerModel::flags(const QModelIndex &index) const
{
    (void)index;
    return Qt::ItemIsEditable;
}

void TachometerModel::setRpm(int rpm)
{
    mRpm = rpm;
    emit dataChanged(
        createIndex(0,0),
        createIndex(1, 0),
        QVector<int>() <<
            DashUtils::to_underlying(TachometerRoles::RpmRole));
    emit rpmChanged();
}

int TachometerModel::rpm() const
{
    return mRpm;
}

void TachometerModel::setRedLine(int redLine)
{
    mRedLine = redLine;
    emit dataChanged(
        createIndex(0,0),
        createIndex(1, 0),
        QVector<int>() <<
            DashUtils::to_underlying(TachometerRoles::RedLineRole));
    emit redLineChanged();
}

int TachometerModel::redLine() const
{
    return mRedLine;
}

void TachometerModel::setMaxRpm(int maxRpm)
{
    mMaxRpm = maxRpm;
    emit dataChanged(
        createIndex(0,0),
        createIndex(1, 0),
        QVector<int>() <<
            DashUtils::to_underlying(TachometerRoles::MaxRpmRole));
    emit redLineChanged();
}

int TachometerModel::maxRpm() const
{
    return mMaxRpm;
}
