#include <pulse_counter.h>

int PulseCounter::getFrequency() const {
    // read the nano second spacing variable
    std::string fullPath = mPath + PULSE_SPACING_AVG;
    std::ifstream ifs(fullPath, std::ios::in);
    if (!ifs.is_open()) {
        std::cout << "Error opening pulse spacing file" << std::endl;
        return -1.0;
    }

    std::string val;
    std::getline(ifs, val);
    ifs.close();

    int spacingNano = 0;
    try {
        spacingNano = std::stoi(val);
    } catch (std::invalid_argument& e) {
        std::cout << "tach input, invalid argument -- rpm will be 0 -- " << e.what() <<  std::endl;
    } catch (std::out_of_range& e) {
        std::cout << "tach input, out of range -- rpm will be 0 -- " << e.what() <<  std::endl;
    }

    if (spacingNano != 0) {
        return 1.0e9 / ((float)spacingNano);
    } else {
        return 0;
    }
}

int PulseCounter::getPulseCount() const {
    std::string fullPath = mPath + PULSE_COUNT_ATTR;
    std::ifstream ifs(fullPath, std::ios::in);
    if (!ifs.is_open()) {
        std::cout << "Error opening pulse count file" << std::endl;
        return -1.0;
    }

    std::string val;
    std::getline(ifs, val);
    ifs.close();

    int count = 0;
    try {
        count = std::stoi(val);
    } catch (std::invalid_argument& e) {
        std::cout << "tach input, invalid argument -- count will be 0 -- " << e.what() << std::endl;
    } catch (std::out_of_range& e) {
        std::cout << "tach input, out of range -- count will be 0 -- " << e.what() << std::endl;
    }

    return count;
}

int PulseCounter::setMaxFrequency(qreal freq)  {
    int nsec = (int) std::round(1.0 / freq * 1.0e9);

    return writeAttribute(PULSE_SPACING_MIN, nsec);
}

int PulseCounter::setNumSamplesToAvg(int num) {
    return writeAttribute(PULSE_SPACING_AVG_NUM_SAMPLES, num);
}

int PulseCounter::writeAttribute(const std::string& attr, int value) {
    // read the nano second spacing variable
    std::string fullPath = mPath + attr;
    std::ofstream ofs(fullPath, std::ofstream::out);
    if (!ofs.is_open()) {
        std::cout << "Error opening " << attr << std::endl;
        return -1.0;
    }

    ofs << value;
    ofs.close();

    std::cout << attr << " set to: " << value <<  std::endl;

    return value;
}
