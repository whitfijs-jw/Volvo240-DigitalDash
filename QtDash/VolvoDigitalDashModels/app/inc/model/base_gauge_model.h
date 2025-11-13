#ifndef BASE_GAUGE_MODEL_H
#define BASE_GAUGE_MODEL_H

#include <QObject>
#include <QAbstractListModel>

class BaseGaugeModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(qreal minValue READ minValue WRITE setMinValue NOTIFY minValueChanged)
    Q_PROPERTY(qreal maxValue READ maxValue WRITE setMaxValue NOTIFY maxValueChanged)
    Q_PROPERTY(qreal currentValue READ currentValue WRITE setCurrentValue NOTIFY currentValueChanged)
    Q_PROPERTY(QString units READ units WRITE setUnits NOTIFY unitsChanged)

public:
    enum class BaseGaugeRoles {
        MinValueRole        = Qt::UserRole + 1,
        MaxValueRole        = Qt::UserRole + 2,
        CurrentValueRole    = Qt::UserRole + 3,
        UnitsRole           = Qt::UserRole + 4,
    };

    explicit BaseGaugeModel(QObject * parent = nullptr);

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

    qreal minValue() const;
    qreal maxValue() const;
    qreal currentValue() const;
    QString units() const;

signals:
    void minValueChanged();
    void maxValueChanged();
    void currentValueChanged();
    void unitsChanged();

public slots:
    void setMinValue(qreal minValue);
    void setMaxValue(qreal maxValue);
    void setCurrentValue(qreal currentValue);
    void setUnits(QString units);

private:
    qreal mMinValue {0.0};
    qreal mMaxValue {0.0};
    qreal mCurrentValue {0.0};
    QString mUnits {""};
};

#endif // BASE_GAUGE_MODEL_H
