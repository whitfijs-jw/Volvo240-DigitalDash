#include <sensor_utils.h>

qreal SensorUtils::convert(qreal value, QString to, QString from) {
    if (from.compare(to, Qt::CaseInsensitive) == 0) {
        return value;
    }

    qreal val = value;
    // Check sensor type
    if (from.compare(Units::UNITS_C, Qt::CaseInsensitive) == 0 ||
        from.compare(Units::UNITS_F, Qt::CaseInsensitive) == 0 ||
        from.compare(Units::UNITS_K, Qt::CaseInsensitive) == 0 ) {
        // temperature sensor
        val = SensorUtils::convertTemperature(value,
                                              Units::getTempUnits(to),
                                              Units::getTempUnits(from));

    } else if (from.compare(Units::UNITS_PSI, Qt::CaseInsensitive) == 0 ||
               from.compare(Units::UNITS_BAR, Qt::CaseInsensitive) == 0 ||
               from.compare(Units::UNITS_KPA, Qt::CaseInsensitive) == 0 ) {
        // pressure sensor
        val = SensorUtils::convertPressure(value,
                                           Units::getPressureUnits(to),
                                           Units::getPressureUnits(from)
                                           );
    } else if (from.compare(Units::UNITS_MPH, Qt::CaseInsensitive) == 0 ||
               from.compare(Units::UNITS_KPH, Qt::CaseInsensitive) == 0||
               from.compare(Units::UNITS_KMH, Qt::CaseInsensitive) == 0 ||
               from.compare(Units::UNITS_METERS_PER_SECOND, Qt::CaseInsensitive) == 0) {
        // speed sensor
        val = SensorUtils::convertSpeed(value,
                                        Units::getSpeedUnits(to),
                                        Units::getSpeedUnits(from)
                                        );
    } else if (from.compare(Units::UNITS_MILE, Qt::CaseInsensitive) == 0 ||
               from.compare(Units::UNITS_KILOMETER, Qt::CaseInsensitive) == 0 ||
               from.compare(Units::UNITS_METER, Qt::CaseInsensitive) == 0 ||
               from.compare(Units::UNITS_CENTIMETER, Qt::CaseInsensitive) == 0||
               from.compare(Units::UNITS_MILLIMETER, Qt::CaseInsensitive) == 0 ||
               from.compare(Units::UNITS_INCH, Qt::CaseInsensitive) == 0 ||
               from.compare(Units::UNITS_FOOT, Qt::CaseInsensitive) == 0 ||
               from.compare(Units::UNITS_YARD, Qt::CaseInsensitive) == 0) {
        val = SensorUtils::convertDistance(value,
                                           Units::getDistanceUnits(to),
                                           Units::getDistanceUnits(from)
                                           );
    }

    return val;
}

QList<qreal> SensorUtils::polynomialRegression(QList<qreal> x, QList<qreal> y, int order) {
    if (x.length() != y.length()) {
        // problem
    }

    Eigen::MatrixXd X(x.size(), order + 1);
    Eigen::MatrixXd Beta(x.size(), 1);
    Eigen::MatrixXd Y(y.size(), 1);

    // populate X and Y matrices
    for (int r = 0; r < x.size(); r++) {
        for (int c = 0; c <= order; c++) {
            X(r, c) = qPow(x.at(r), c);
        }

        Y(r) = y.at(r);
    }

    // intermediates
    Eigen::MatrixXd XtX = X.transpose() * X;
    Eigen::MatrixXd XtXinv = XtX.inverse();

    // do it
    Beta = XtXinv * X.transpose() * Y;

    // output coefficients (should be x^0 to x^order)
    QList<qreal> coeff;
    for (int i = 0; i < (order + 1); i++) {
        coeff.push_back(Beta(i));
    }

    return coeff;
}

qreal SensorUtils::polynomialValue(qreal x, QList<qreal> coeff) {
    qreal sum = 0;
    // sum terms
    for (int i = 0; i < coeff.size(); i++) {
        sum += qPow(x, i) * coeff.at(i);
    }

    return sum;
}
