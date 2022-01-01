#ifndef NTC_H
#define NTC_H

#include <QtMath>

class Ntc {
public:
    Ntc(qreal beta, qreal vdd, qreal rBalance, float alpha) :
        mBeta(beta), mVdd(vdd), mRBalance(rBalance), mAlpha(alpha) {
    }

    qreal calculateTemp(qreal volts) {
        qreal rNtc = mRBalance / ((mVdd / volts) - 1.0);
        qreal tKelvin = 1 / ((qLn(rNtc / mRBalance) / mBeta) + INV_T25_K);
        qreal tF = (tKelvin - T0_K) * C_CONST + T0_F;

        return tF;
    }

    qreal calculateAvgTemp(qreal volts) {
        qreal temp = calculateTemp(volts);

        if (mAcc != 0) {
            mAcc = temp * mAlpha + (1 - mAlpha) * mAcc;
        } else {
            mAcc = temp;
        }
        return mAcc;
    }
private:
    static constexpr qreal T25_K = 298.15;
    static constexpr qreal INV_T25_K = 1.0 / T25_K;
    static constexpr qreal C_CONST = 9.0 / 5.0;
    static constexpr qreal T0_K = 273.15;
    static constexpr qreal T0_F = 32.0;

    qreal mBeta = 0;
    qreal mVdd = 5.0;
    qreal mRBalance = 1000.0;

    qreal mAcc = 0;
    qreal mAlpha = 0.75;
};

#endif // NTC_H
