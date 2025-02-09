#ifndef ODOMETER_MODEL_H
#define ODOMETER_MODEL_H

#include <QAbstractListModel>
#include <QObject>

class OdometerModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(qreal odometerValue READ odometerValue WRITE setOdometerValue NOTIFY odometerValueChanged)
    Q_PROPERTY(qreal tripAValue READ tripAValue WRITE setTripAValue NOTIFY tripAValueChanged)
    Q_PROPERTY(qreal tripBValue READ tripBValue WRITE setTripBValue NOTIFY tripBValueChanged)

public:
    static constexpr char ODOMETER_MODEL_NAME[] = "odometerModel";

    enum class OdometerModelRoles{
        OdoValueRole      = Qt::UserRole + 1,
        TripAValueRole    = Qt::UserRole + 2,
        TripBValueRole    = Qt::UserRole + 3,
    };

    explicit OdometerModel(QObject *parent = nullptr);

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

    qreal odometerValue() const;
    qreal tripAValue() const;
    qreal tripBValue() const;

private:
    qreal mOdometerValue {0.0};
    qreal mTripAValue {0.0};
    qreal mTripBValue {0.0};

signals:
    void odometerValueChanged();
    void tripAValueChanged();
    void tripBValueChanged();

public slots:
    void setOdometerValue(qreal odoValue);
    void setTripAValue(qreal tripAValue);
    void setTripBValue(qreal tripBValue);
};

#endif // ODOMETER_MODEL_H
