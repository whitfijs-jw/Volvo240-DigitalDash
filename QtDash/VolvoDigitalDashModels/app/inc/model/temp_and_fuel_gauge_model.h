#ifndef TEMP_AND_FUEL_GAUGE_MODEL_H
#define TEMP_AND_FUEL_GAUGE_MODEL_H

#include <QObject>
#include <QAbstractItemModel>

class TempAndFuelGaugeModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(qreal maxTemp READ maxTemp WRITE setMaxTemp NOTIFY maxTempChanged)
    Q_PROPERTY(qreal minTemp READ minTemp WRITE setMinTemp NOTIFY minTempChanged)
    Q_PROPERTY(qreal currentTemp READ currentTemp WRITE setCurrentTemp NOTIFY currentTempChanged)
    Q_PROPERTY(QString tempUnits READ tempUnits WRITE setTempUnits NOTIFY tempUnitsChanged)
    Q_PROPERTY(qreal fuelLevel READ fuelLevel WRITE setFuelLevel NOTIFY fuelLevelChanged)
    Q_PROPERTY(qreal highTempAlarm READ highTempAlarm WRITE setHighTempAlarm NOTIFY highTempAlarmChanged)
    Q_PROPERTY(qreal lowFuelAlarm READ lowFuelAlarm WRITE setLowFuelAlarm NOTIFY lowFuelAlarmChanged)

public:
    static constexpr char TEMP_FUEL_CLUSTER_MODEL_NAME[] = "tempFuelModel";

    enum class TempAndFuelGaugeModelRoles {
        MaxTempRole         = Qt::UserRole + 1,
        MinTempRole         = Qt::UserRole + 2,
        CurrentTempRole     = Qt::UserRole + 3,
        TempUnitsRole       = Qt::UserRole + 4,
        FuelLevelRole       = Qt::UserRole + 5,
        HighTempAlarmRole   = Qt::UserRole + 6,
        LowFuelAlarmRole    = Qt::UserRole + 7,
    };

    explicit TempAndFuelGaugeModel(QObject *parent = nullptr);

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

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override {
        (void)row;
        (void)column;
        (void)parent;
        return createIndex(0,0);
    };

    QModelIndex parent(const QModelIndex& = QModelIndex()) const override {
        return QModelIndex();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        (void)parent;
        return 1;
    }


    qreal maxTemp() const;
    qreal minTemp() const;
    qreal currentTemp() const;
    QString tempUnits() const;
    qreal fuelLevel() const;
    qreal highTempAlarm() const;
    qreal lowFuelAlarm() const;

private:
    qreal mMaxTemp {1.0};
    qreal mMinTemp {0.0};
    qreal mCurrentTemp {1.0};
    QString mTempUnits {""};
    qreal mFuelLevel {1.0};
    qreal mHighTempAlarm {1.0};
    qreal mLowFuelAlarm {0.0};

signals:
    void maxTempChanged();
    void minTempChanged();
    void currentTempChanged();
    void tempUnitsChanged();
    void fuelLevelChanged();
    void highTempAlarmChanged();
    void lowFuelAlarmChanged();

public slots:
    void setMaxTemp(qreal maxTemp);
    void setMinTemp(qreal minTemp);
    void setCurrentTemp(qreal currentTemp);
    void setTempUnits(QString units);
    void setFuelLevel(qreal fuelLevel);
    void setHighTempAlarm(qreal highTempAlarm);
    void setLowFuelAlarm(qreal lowFuelAlarm);
};

#endif // TEMP_AND_FUEL_GAUGE_MODEL_H
