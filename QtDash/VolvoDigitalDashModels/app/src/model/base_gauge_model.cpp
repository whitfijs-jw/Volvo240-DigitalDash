#include <base_gauge_model.h>

BaseGaugeModel::BaseGaugeModel(QObject * parent) : QAbstractListModel(parent) {

}

QHash<int, QByteArray> BaseGaugeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[BaseGaugeRoles::MinValueRole] = "gaugeMin";
    roles[BaseGaugeRoles::MaxValueRole] = "gaugeMax";
    roles[BaseGaugeRoles::CurrentValueRole] = "currentValue";
    roles[BaseGaugeRoles::UnitsRole] = "gaugeUnits";
    return roles;
}

QVariant BaseGaugeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    (void)section;
    (void)orientation;
    if (role == BaseGaugeRoles::MinValueRole)
    {
        return QVariant("gaugeMin");
    }
    else if(role == BaseGaugeRoles::MaxValueRole)
    {
        return QVariant("gaugeMax");
    }
    else if(role == BaseGaugeRoles::CurrentValueRole)
    {
        return QVariant("currentValue");
    }
    else if(role == BaseGaugeRoles::UnitsRole)
    {
        return QVariant("gaugeUnits");
    }
    return QVariant::fromValue(nullptr);
}

int BaseGaugeModel::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return 1;
}

QVariant BaseGaugeModel::data(const QModelIndex &index, int role) const
{
    (void)index;
    if (role == BaseGaugeRoles::MinValueRole)
    {
        return mMinValue;
    }
    else if(role == BaseGaugeRoles::MaxValueRole)
    {
        return mMaxValue;
    }
    else if(role == BaseGaugeRoles::CurrentValueRole)
    {
        return mCurrentValue;
    }
    else if(role == BaseGaugeRoles::UnitsRole)
    {
        return mUnits;
    }
    // Default return:
    return QVariant::fromValue(nullptr);
}

bool BaseGaugeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    (void)index;
    if (role == BaseGaugeRoles::MinValueRole)
    {
        mMinValue = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << BaseGaugeRoles::MinValueRole);
        emit minValueChanged();
        return true;
    }
    else if(role == BaseGaugeRoles::MaxValueRole)
    {
        mMaxValue = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << BaseGaugeRoles::MaxValueRole);
        emit maxValueChanged();
        return true;
    }
    else if(role == BaseGaugeRoles::CurrentValueRole)
    {
        mCurrentValue = value.toReal();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << BaseGaugeRoles::CurrentValueRole);
        emit currentValueChanged();
        return true;
    }
    else if(role == BaseGaugeRoles::UnitsRole)
    {
        mUnits = value.toString();
        emit dataChanged(createIndex(0,0),
                         createIndex(1, 0),
                         QVector<int>() << BaseGaugeRoles::UnitsRole);
        emit unitsChanged();
        return true;
    }
    else
    {
        emit layoutChanged();
    }
    return false;
}

Qt::ItemFlags BaseGaugeModel::flags(const QModelIndex &index) const
{
    (void)index;
    return Qt::ItemIsEditable;
}

qreal BaseGaugeModel::minValue() const
{
    return mMinValue;
}

qreal BaseGaugeModel::maxValue() const
{
    return mMaxValue;
}

qreal BaseGaugeModel::currentValue() const
{
    return mCurrentValue;
}

QString BaseGaugeModel::units() const
{
    return mUnits;
}

void BaseGaugeModel::setMinValue(qreal minValue)
{
    mMinValue = minValue;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << BaseGaugeRoles::MinValueRole);
    emit minValueChanged();
}

void BaseGaugeModel::setMaxValue(qreal maxValue)
{
    mMaxValue = maxValue;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << BaseGaugeRoles::MaxValueRole);
    emit maxValueChanged();
}

void BaseGaugeModel::setCurrentValue(qreal currentValue)
{
    mCurrentValue = currentValue;
    emit dataChanged(createIndex(0,0),
                     createIndex(1, 0),
                     QVector<int>() << BaseGaugeRoles::CurrentValueRole);
    emit currentValueChanged();
}

void BaseGaugeModel::setUnits(QString units)
{
    mUnits = units;
    emit dataChanged(createIndex(0, 0),
                     createIndex(1, 0),
                     QVector<int>() << BaseGaugeRoles::UnitsRole);
    emit unitsChanged();
}
