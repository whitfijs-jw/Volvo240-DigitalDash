#include "odometer_model.h"

OdometerModel::OdometerModel(QObject *parent) : QAbstractListModel{parent}
{

}

QHash<int, QByteArray> OdometerModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[OdometerModelRoles::OdoValueRole] = "odometerValue";
    roles[OdometerModelRoles::TripAValueRole] = "tripAValue";
    roles[OdometerModelRoles::TripBValueRole] = "tripBValue";
    return roles;
}

QVariant OdometerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    (void)section;
    (void)orientation;
    if (role == OdometerModelRoles::OdoValueRole)
    {
        return QVariant("odometerValue");
    }
    else if(role == OdometerModelRoles::TripAValueRole)
    {
        return QVariant("tripAValue");
    }
    else if(role == OdometerModelRoles::TripBValueRole)
    {
        return QVariant("tripBValue");
    }
    return QVariant("");
}

int OdometerModel::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return 1;
}

QVariant OdometerModel::data(const QModelIndex &index, int role) const
{
    (void)index;
    if (role == OdometerModelRoles::OdoValueRole) {
        return mOdometerValue;
    } else if(role == OdometerModelRoles::TripAValueRole) {
        return mTripAValue;
    } else if(role == OdometerModelRoles::TripBValueRole) {
        return mTripBValue;
    }
    return mOdometerValue;
}

bool OdometerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    (void)index;
    if (role == OdometerModelRoles::OdoValueRole) {
        setOdometerValue(value.toReal());
    } else if(role == OdometerModelRoles::TripAValueRole) {
        setTripAValue(value.toReal());
    } else if(role == OdometerModelRoles::TripBValueRole) {
        setTripBValue(value.toReal());
    } else {
        emit layoutChanged();
    }
    return true;
}

Qt::ItemFlags OdometerModel::flags(const QModelIndex &index) const {
    (void)index;
    return Qt::ItemIsEditable;
}

qreal OdometerModel::odometerValue() const {
    return mOdometerValue;
}

qreal OdometerModel::tripAValue() const{
    return mTripAValue;
}

qreal OdometerModel::tripBValue() const {
    return mTripBValue;
}

void OdometerModel::setOdometerValue(qreal odoValue) {
    mOdometerValue = odoValue;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << OdometerModelRoles::OdoValueRole);
    emit odometerValueChanged();
}

void OdometerModel::setTripAValue(qreal tripAValue) {
    mTripAValue = tripAValue;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << OdometerModelRoles::TripAValueRole);
    emit tripAValueChanged();
}

void OdometerModel::setTripBValue(qreal tripBValue) {
    mTripBValue = tripBValue;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << OdometerModelRoles::TripBValueRole);
    emit tripBValueChanged();
}
