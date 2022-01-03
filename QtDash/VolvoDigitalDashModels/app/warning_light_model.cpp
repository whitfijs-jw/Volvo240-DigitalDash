#include "warning_light_model.h"

WarningLightModel::WarningLightModel(QObject *parent) :
    QAbstractListModel(parent),
    mOn(false), mFlipped(false), mWarningText(""), mLightColor(0,0,0)
{

}

QHash<int, QByteArray> WarningLightModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[WarningLightRoles::onRole] = "warningLightOn";
    roles[WarningLightRoles::flippedRole] = "warningLightFlipped";
    roles[WarningLightRoles::textRole] = "warningLightText";
    roles[WarningLightRoles::colorRole] = "warningLightColor";
    return roles;
}

QVariant WarningLightModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == WarningLightRoles::onRole)
    {
        return QVariant("warningLightOn");
    }
    else if (role == WarningLightRoles::flippedRole)
    {
        return QVariant("warningLightFlipped");
    }
    else if (role == WarningLightRoles::textRole)
    {
        return QVariant("warningLightText");
    }
    else if (role == WarningLightRoles::colorRole)
    {
        return QVariant("warningLightColor");
    }
    return QVariant("");
}

int WarningLightModel::rowCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant WarningLightModel::data(const QModelIndex &index, int role) const
{
    if (role == WarningLightRoles::onRole)
    {
        return mOn;
    }
    else if (role == WarningLightRoles::flippedRole)
    {
        return mFlipped;
    }
    else if (role == WarningLightRoles::textRole)
    {
        return mWarningText;
    }
    else if (role == WarningLightRoles::colorRole)
    {
        return mLightColor;
    }
    // Default return:
    return mOn;
}

bool WarningLightModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == WarningLightRoles::onRole)
    {
        mOn = value.toBool();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << WarningLightRoles::onRole);
        emit onChanged();
    }
    else if (role == WarningLightRoles::flippedRole)
    {
        mFlipped = value.toBool();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << WarningLightRoles::flippedRole);
        emit onFlipped();
    }
    else if (role == WarningLightRoles::textRole)
    {
        mWarningText = value.toString();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << WarningLightRoles::textRole);
        emit onTextChanged();
    }
    else if (role == WarningLightRoles::colorRole)
    {
        mLightColor = value.value<QColor>();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << WarningLightRoles::colorRole);
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
    return Qt::ItemIsEditable;
}

bool WarningLightModel::on()
{
    return mOn;
}

bool WarningLightModel::flipped()
{
    return mFlipped;
}

QString WarningLightModel::warningText()
{
    return mWarningText;
}

QColor WarningLightModel::lightColor()
{
    return mLightColor;
}

void WarningLightModel::setOn(bool on)
{
    mOn = on;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << WarningLightRoles::onRole);
    emit onChanged();
}

void WarningLightModel::setFlipped(bool flipped)
{
    mFlipped = flipped;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << WarningLightRoles::flippedRole);
    emit onFlipped();
}

void WarningLightModel::setText(QString text)
{
    mWarningText = text;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << WarningLightRoles::textRole);
    emit onTextChanged();
}

void WarningLightModel::setLightColor(QColor color)
{
    mLightColor = color;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << WarningLightRoles::colorRole);
    emit onLightColorChanged();
}
