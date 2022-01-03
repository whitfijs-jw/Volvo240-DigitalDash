#ifndef SPEEDOMETER_MODEL_H
#define SPEEDOMETER_MODEL_H

#include <QObject>
#include <QAbstractListModel>

class SpeedometerModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(qreal minValue READ minValue WRITE setMinValue NOTIFY minValueChanged)
    Q_PROPERTY(qreal maxValue READ maxValue WRITE setMaxValue NOTIFY maxValueChanged)
    Q_PROPERTY(qreal currentValue READ currentValue WRITE setCurrentValue NOTIFY currentValueChanged)
    Q_PROPERTY(QString units READ units WRITE setUnits NOTIFY unitsChanged)
    Q_PROPERTY(qreal topValue READ topValue WRITE setTopValue NOTIFY topValueChanged)
    Q_PROPERTY(QString topUnits READ topUnits WRITE setTopUnits NOTIFY topUnitsChanged)

public:
    enum SpeedometerModelRoles{
        MinValueRole        = Qt::UserRole + 1,
        MaxValueRole        = Qt::UserRole + 2,
        CurrentValueRole    = Qt::UserRole + 3,
        UnitsRole           = Qt::UserRole + 4,
        TopValueRole        = Qt::UserRole + 5,
        TopUnitsRole        = Qt::UserRole + 6,
    };

    explicit SpeedometerModel(QObject *parent = nullptr);

    /**
     * Provides the header data for given params.
     *
     * @param section section of data
     * @param orientation orientation of data
     * @param role role of data
     * @return
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    /**
     * Returns the row count for given index.
     *
     * @param parent
     * @return
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * Provides the data found at given index and role.
     *
     * @param index
     * @param role
     * @return
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * Sets data value for given index and role
     *
     * @param index
     * @param value
     * @param role
     * @return
     */
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    /**
     * Returns the flags for model.
     *
     * @param index index to consider when providing flags
     */
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    /**
     * Enables integration with QML by providing names for use as refs in QML.
     *
     * @return hash map of role (int) -> name
     */
    QHash<int, QByteArray> roleNames() const override;


    qreal minValue();
    qreal maxValue();
    qreal currentValue();
    QString units();

    qreal topValue();
    QString topUnits();

private:
    qreal mMinValue;
    qreal mMaxValue;
    qreal mCurrentValue;
    QString mUnits;
    qreal mTopValue;
    QString mTopUnits;

signals:
    void minValueChanged();
    void maxValueChanged();
    void currentValueChanged();
    void unitsChanged();
    void topValueChanged();
    void topUnitsChanged();

public slots:
    void setMinValue(qreal minValue);
    void setMaxValue(qreal maxValue);
    void setCurrentValue(qreal currentValue);
    void setUnits(QString units);
    void setTopValue(qreal topValue);
    void setTopUnits(QString topUnits);
};

#endif // SPEEDOMETER_MODEL_H
