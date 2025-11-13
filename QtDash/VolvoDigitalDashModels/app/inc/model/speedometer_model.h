#ifndef SPEEDOMETER_MODEL_H
#define SPEEDOMETER_MODEL_H

#include <QObject>
#include <base_gauge_model.h>
#include <QDebug>

class SpeedometerModel : public BaseGaugeModel
{
    Q_OBJECT
    Q_PROPERTY(qreal topValue READ topValue WRITE setTopValue NOTIFY topValueChanged)
    Q_PROPERTY(QString topUnits READ topUnits WRITE setTopUnits NOTIFY topUnitsChanged)

public:
    static constexpr char SPEEDO_MODEL_NAME[] = "speedoModel";

    enum class SpeedometerModelRoles{
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


    qreal topValue() const;
    QString topUnits() const;

private:
    qreal mTopValue {0.0};
    QString mTopUnits {""};

signals:
    void topValueChanged();
    void topUnitsChanged();

public slots:
    void setTopValue(qreal topValue);
    void setTopUnits(QString topUnits);
};

#endif // SPEEDOMETER_MODEL_H
