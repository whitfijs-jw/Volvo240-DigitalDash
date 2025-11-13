#include <can_frame_config.h>

CanFrameConfig::CanFrameConfig(uint32_t frameId, uint8_t offset,
                               uint8_t size, bool sign, QString units,
                               QString name, QString gaugeName) :
    mFrameId(frameId), mOffset(offset), mSize(size), mSigned(sign),
    mName(name), mUnits(units), mGaugeName(gaugeName) {

}

int CanFrameConfig::addOperation(OperationType type, qreal value) {
    Operation_t op;
    op.type = type;
    op.value = value;

    mOperations.append(op);

    return mOperations.length();
}

qreal CanFrameConfig::getValue(QByteArray payload){
    QDataStream ds(payload);
    qreal ret = 0;
    // move to offset (minus 1?)
    if (ds.skipRawData(mOffset) < 0) {
        return qQNaN();
    }

    // get value
    switch (mSize) {
    case 1: {
        if (mSigned) {
            int8_t value;
            ds >> value;
            ret = (qreal)value;
        } else {
            uint8_t value;
            ds >> value;
            ret = (qreal)value;
        }
    }
    break;
    case 2: {
        if (mSigned) {
            int16_t value;
            ds >> value;
            ret = (qreal)value;
        } else {
            uint16_t value;
            ds >> value;
            ret = (qreal)value;
        }
    }
    break;
    case 4:{
        if (mSigned) {
            int32_t value;
            ds >> value;
            ret = (qreal)value;
        } else {
            uint32_t value;
            ds >> value;
            ret = (qreal)value;
        }
    }
    break;
    default:
        // empty
    break;
    }

    for (Operation_t ops : mOperations) {
        switch ((int)ops.type) {
        case (int)OperationType::MULTIPLY:
            ret *= ops.value;
            break;
        case (int) OperationType::DIVIDE:
            ret /= ops.value;
            break;
        case (int) OperationType::ADD:
            ret += ops.value;
            break;
        }
    }

    return ret;
}
