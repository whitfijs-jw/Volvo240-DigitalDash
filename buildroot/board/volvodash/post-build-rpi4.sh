#!/bin/sh

set -u
set -e

echo "we are here: $PWD"
echo "host dir is: ${HOST_DIR}"

BUILDROOT_DIR="${PWD}"
PROJECT_DIR="../QtDash"
QT_PROJECT_DIR="${PROJECT_DIR}/VolvoDigitalDashModels"
QMAKE_CMD="${HOST_DIR}/bin/qmake"
QT_PROJECT_FILE=""
QT_BUILD_CMD="${QMAKE_CMD} ${QT_PROJECT_DIR}/subdirs.pro -spec devices/linux-buildroot-g++ CONFIG+=debug CONFIG+=qml_debug CONFIG+=RPI && /usr/bin/make qmake_all"
QT_BUILD_DIR="${QT_PROJECT_DIR}/build-RPI3/"
QT_EXEC_DIR="${QT_PROJECT_DIR}/build-RPI3/app/VolvoDigitalDashModels"
QT_FONTS_DIR="${QT_PROJECT_DIR}/app/HandelGothReg.ttf"
QT_EXEC_TARGET_DIR="${TARGET_DIR}/opt"
QT_FONTS_TARGET_DIR="${TARGET_DIR}/usr/lib/fonts"
BOARD_DIR="$(dirname $0)"
BOARD_NAME="$(basename ${BOARD_DIR})"

# Add a console on tty1
#if [ -e ${TARGET_DIR}/etc/inittab ]; then
#    grep -qE '^tty1::' ${TARGET_DIR}/etc/inittab || \
#	sed -i '/GENERIC_SERIAL/a\
#tty1::respawn:/sbin/getty -L  tty1 0 vt100 # HDMI console' ${TARGET_DIR}/etc/inittab
#fi

echo "Create Qt App build directory"
mkdir -p "${QT_BUILD_DIR}"

echo "Building Qt App (qmake + make)"
cd "${QT_BUILD_DIR}"
${QMAKE_CMD} ../subdirs.pro -spec devices/linux-buildroot-g++ CONFIG+=debug CONFIG+=qml_debug CONFIG+=RPI && /usr/bin/make qmake_all

make

echo "Copying QtDash executable to /opt"
cd "${BUILDROOT_DIR}"
cp "${QT_EXEC_DIR}" "${QT_EXEC_TARGET_DIR}"

echo "Copy custom config.txt"
cp "${BOARD_DIR}/config-rpi4.txt" "${BINARIES_DIR}/rpi-firmware/config.txt"

echo "Copy custom cmdline.txt"
cp "${BOARD_DIR}/cmdline.txt" "${BINARIES_DIR}/rpi-firmware"

echo "Copying mcp3208 dtb"
cp "${BOARD_DIR}/mcp3208.dtbo" "${BINARIES_DIR}/rpi-firmware/overlays"

echo "Copying Config from QtDash"
cp "${PROJECT_DIR}/config.ini" "${QT_EXEC_TARGET_DIR}"

echo "Copying Gauge Config from QtDash"
cp "${PROJECT_DIR}/config_gauges.ini" "${QT_EXEC_TARGET_DIR}"

echo "Copying Odo Config from QtDash"
cp "${PROJECT_DIR}/config_odo.ini" "${QT_EXEC_TARGET_DIR}"
