#ifndef TACHOMETER_MODEL_H
#define TACHOMETER_MODEL_H
#include <QObject>
#include <QAbstractItemModel>
#include <QTimer>

class TachometerModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int rpm READ rpm WRITE setRpm NOTIFY rpmChanged)
    Q_PROPERTY(int redLine READ redLine WRITE setRedLine NOTIFY redLineChanged)
    Q_PROPERTY(int maxRpm READ maxRpm WRITE setMaxRpm NOTIFY maxRpmChanged)

public:
    static constexpr char TACH_MODEL_NAME[] = "rpmModel";

    enum class TachometerRoles {
        RpmRole     = Qt::UserRole + 1,
        RedLineRole = Qt::UserRole + 2,
        MaxRpmRole  = Qt::UserRole + 3,
    };

    explicit TachometerModel(QObject *parent = nullptr);

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

    int rpm() const;

    int redLine() const;

    int maxRpm() const;


public slots:
    void setRpm(int rpm);

    void setRedLine(int redLine);

    void setMaxRpm(int maxRpm);

signals:
    void rpmChanged();
    void redLineChanged();
    void maxRpmChanged();

private:
    int mRpm {0};
    int mRedLine {1};
    int mMaxRpm {1};

};

#endif // TACHOMETER_MODEL_H
