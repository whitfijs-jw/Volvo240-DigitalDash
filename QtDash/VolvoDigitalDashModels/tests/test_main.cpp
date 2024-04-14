#include <QTest>

#include <map_test.h>
#include <config_test.h>
#include <ntc_test.h>
#include <sensor_utils_test.h>
#include <sensor_test.h>
#include <can_frame_config_test.h>

int main(int argc, char *argv[])
{
    int status = 0;
    auto ASSERT_TEST = [&status, argc, argv](QObject* obj) {
      status |= QTest::qExec(obj, argc, argv);
      delete obj;
    };

    ASSERT_TEST(new MapTest());
    ASSERT_TEST(new ConfigTest());
    ASSERT_TEST(new NtcTest());
    ASSERT_TEST(new SensorUtilsTest);
    ASSERT_TEST(new SensorTest);
    ASSERT_TEST(new CanFrameConfigTest);
}
