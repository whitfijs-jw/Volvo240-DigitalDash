#include <map_test.h>
#include <config_test.h>
#include <QTest>

int main(int argc, char *argv[])
{
    int status = 0;
    auto ASSERT_TEST = [&status, argc, argv](QObject* obj) {
      status |= QTest::qExec(obj, argc, argv);
      delete obj;
    };

    ASSERT_TEST(new MapTest());
    ASSERT_TEST(new ConfigTest());
}
