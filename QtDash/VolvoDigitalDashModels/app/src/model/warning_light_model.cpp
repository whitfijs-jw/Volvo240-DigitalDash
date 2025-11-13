#include "warning_light_model.h"
#include <utils.h>


WarningLightModel::WarningLightModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

QHash<int, QByteArray> WarningLightModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DashUtils::to_underlying(WarningLightRoles::onRole)] = "warningLightOn";
    roles[DashUtils::to_underlying(WarningLightRoles::flippedRole)] = "warningLightFlipped";
    roles[DashUtils::to_underlying(WarningLightRoles::textRole)] = "warningLightText";
    roles[DashUtils::to_underlying(WarningLightRoles::colorRole)] = "warningLightColor";
    return roles;
}

QVariant WarningLightModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    (void)section;
    (void)orientation;
    if (role == DashUtils::to_underlying(WarningLightRoles::onRole))
    {
        return QVariant("warningLightOn");
    }
    else if (role == DashUtils::to_underlying(WarningLightRoles::flippedRole))
    {
        return QVariant("warningLightFlipped");
    }
    else if (role == DashUtils::to_underlying(WarningLightRoles::textRole))
    {
        return QVariant("warningLightText");
    }
    else if (role == DashUtils::to_underlying(WarningLightRoles::colorRole))
    {
        return QVariant("warningLightColor");
    }
    return QVariant("");
}

int WarningLightModel::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return 1;
}

QVariant WarningLightModel::data(const QModelIndex &index, int role) const
{
    (void)index;
    if (role == DashUtils::to_underlying(WarningLightRoles::onRole))
    {
        return mOn;
    }
    else if (role == DashUtils::to_underlying(WarningLightRoles::flippedRole))
    {
        return mFlipped;
    }
    else if (role == DashUtils::to_underlying(WarningLightRoles::textRole))
    {
        return mWarningText;
    }
    else if (role == DashUtils::to_underlying(WarningLightRoles::colorRole))
    {
        return mLightColor;
    }
    // Default return:
    return mOn;
}

bool WarningLightModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    (void)index;
    if (role == DashUtils::to_underlying(WarningLightRoles::onRole))
    {
        mOn = value.toBool();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << DashUtils::to_underlying(WarningLightRoles::onRole));
        emit onChanged();
    }
    else if (role == DashUtils::to_underlying(WarningLightRoles::flippedRole))
    {
        mFlipped = value.toBool();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << DashUtils::to_underlying(WarningLightRoles::flippedRole));
        emit onFlipped();
    }
    else if (role == DashUtils::to_underlying(WarningLightRoles::textRole))
    {
        mWarningText = value.toString();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << DashUtils::to_underlying(WarningLightRoles::textRole));
        emit onTextChanged();
    }
    else if (role == DashUtils::to_underlying(WarningLightRoles::colorRole))
    {
        mLightColor = value.value<QColor>();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << DashUtils::to_underlying(WarningLightRoles::colorRole));
        emit onLightColorChanged();
    }
    else
    {
        emit layoutChanged();
    }
    return true;
}

Qt::ItemFlags WarningLightModel::flags(const QModelIndex &index) const
{
    (void)index;
    return Qt::ItemIsEditable;
}

bool WarningLightModel::on() const
{
    return mOn;
}

bool WarningLightModel::flipped() const
{
    return mFlipped;
}

QString WarningLightModel::warningText() const
{
    return mWarningText;
}

QColor WarningLightModel::lightColor() const
{
    return mLightColor;
}

void WarningLightModel::setOn(bool on)
{
    mOn = on;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << DashUtils::to_underlying(WarningLightRoles::onRole));
    emit onChanged();
}

void WarningLightModel::setFlipped(bool flipped)
{
    mFlipped = flipped;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << DashUtils::to_underlying(WarningLightRoles::flippedRole));
    emit onFlipped();
}

void WarningLightModel::setText(QString text)
{
    mWarningText = text;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << DashUtils::to_underlying(WarningLightRoles::textRole));
    emit onTextChanged();
}

void WarningLightModel::setLightColor(QColor color)
{
    mLightColor = color;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << DashUtils::to_underlying(WarningLightRoles::colorRole));
    emit onLightColorChanged();
}
