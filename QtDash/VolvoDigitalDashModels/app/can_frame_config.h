#ifndef CAN_FRAME_CONFIG_H
#define CAN_FRAME_CONFIG_H

#include <QString>
#include <QDataStream>

/**
 * @brief The CAN Frame configuration
 */
class CanFrameConfig {
public:
    /**
     * @brief Frame value operations
     */
    enum class OperationType {
        MULTIPLY,
        DIVIDE,
        ADD
    };

    /**
     * @brief Operation to perform on
     */
    using Operation_t = struct Operation {
        OperationType type;
        qreal value;
    };

    /**
     * @brief CAN Frame config constructor
     * @param frameId Frame ID
     * @param offset Frame offset in bytes
     * @param size Size of the data
     * @param sign sign/unsigned
     * @param units Units for the data
     * @param name Data Name
     * @param gaugeName Gauge name to route data to
     */
    CanFrameConfig(uint32_t frameId, uint8_t offset,
                   uint8_t size, bool sign, QString units,
                   QString name, QString gaugeName = "none");

    /**
     * @brief getFrameId
     * @return frame ID
     */
    uint32_t getFrameId() const {
        return mFrameId;
    }

    /**
     * @brief Get frame offset
     * @return frame offset in bytes
     */
    uint8_t getOffset() const {
        return mOffset;
    }

    /**
     * @brief Get frame data size
     * @return frame data size in bytes
     */
    uint8_t getSize() const {
        return mSize;
    }

    /**
     * @brief Frame data name
     * @return frame data name
     */
    QString getName() const {
        return mName;
    }

    /**
     * @brief Get the frame data units
     * @return frame data units
     */
    QString getUnits() const {
        return mUnits;
    }

    /**
     * @brief Data sign
     * @return true if data is signed, false if unsigned
     */
    bool isSigned() const {
        return mSigned;
    }

    /**
     * @brief Get gauge name
     * @return gauge name
     */
    QString getGauge() const {
        return mGaugeName;
    }

    /**
     * @brief addOperation
     * @param type
     * @param value
     * @return
     */
    int addOperation(OperationType type, qreal value);

    /**
     * @brief Get value from raw frame data
     * @param payload raw frame data
     * @return frame data value
     */
    qreal getValue(QByteArray payload);

private:
    uint32_t mFrameId; //!< Frame ID
    uint8_t mOffset; //!< Frame data offset in bytes
    uint8_t mSize; //!< Frame data size in bytes
    bool mSigned; //!< Data sign
    QString mName; //!< Data name
    QString mUnits; //!< Data units
    QVector<Operation_t> mOperations; //!< operations to perform on the data
    QString mGaugeName; //!< Gauge to route data to
};

#endif // CAN_FRAME_CONFIG_H
