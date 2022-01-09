#!/bin/sh

set -u
set -e

echo "we are here: $PWD"

QT_PROJECT_DIR="../QtDash"
QT_EXEC_DIR="${QT_PROJECT_DIR}/VolvoDigitalDashModels/build-RPI3/app/VolvoDigitalDashModels"
QT_FONTS_DIR="${QT_PROJECT_DIR}/VolvoDigitalDashModels/app/HandelGothReg.ttf"
QT_EXEC_TARGET_DIR="${TARGET_DIR}/opt"
QT_FONTS_TARGET_DIR="${TARGET_DIR}/usr/lib/fonts"
BOARD_DIR="$(dirname $0)"
BOARD_NAME="$(basename ${BOARD_DIR})"

# Add a console on tty1
if [ -e ${TARGET_DIR}/etc/inittab ]; then
    grep -qE '^tty1::' ${TARGET_DIR}/etc/inittab || \
	sed -i '/GENERIC_SERIAL/a\
tty1::respawn:/sbin/getty -L  tty1 0 vt100 # HDMI console' ${TARGET_DIR}/etc/inittab
fi

echo "Copying QtDash executable to /opt"
cp "${QT_EXEC_DIR}" "${QT_EXEC_TARGET_DIR}"

echo "Copy custom config.txt"
cp "${BOARD_DIR}/config.txt" "${BINARIES_DIR}/rpi-firmware"

echo "Copy custom cmdline.txt"
cp "${BOARD_DIR}/cmdline.txt" "${BINARIES_DIR}/rpi-firmware"

echo "Copying mcp3208 dtb"
cp "${BOARD_DIR}/mcp3208.dtbo" "${BINARIES_DIR}/rpi-firmware/overlays"

echo "Copying Config from QtDash"
cp "${QT_PROJECT_DIR}/config.ini" "${QT_EXEC_TARGET_DIR}"
