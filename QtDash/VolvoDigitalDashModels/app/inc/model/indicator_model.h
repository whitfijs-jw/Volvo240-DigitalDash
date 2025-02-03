#ifndef INDICATOR_MODEL_H
#define INDICATOR_MODEL_H

#include <QObject>
#include <QAbstractListModel>

class IndicatorModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(bool on READ on WRITE setOn NOTIFY onChanged)
    Q_PROPERTY(bool flipped READ flipped WRITE setFlipped NOTIFY onFlipped)

public:
    enum IndicatorRoles {
        onRole        = Qt::UserRole + 1,
        flippedRole   = Qt::UserRole + 2,
    };

    explicit IndicatorModel(QObject *parent = nullptr);

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

    bool on() const;
    bool flipped() const;

private:
    bool mOn {false};
    bool mFlipped {false};

signals:
    void onChanged();
    void onFlipped();

public slots:
    void setOn(bool on);
    void setFlipped(bool flipped);
};

#endif // INDICATOR_MODEL_H
