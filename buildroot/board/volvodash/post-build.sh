#!/bin/sh

set -u
set -e

QT_PROJECT_DIR="/home/jwhitfield/github/DigitalDash/QtDash/"
QT_EXEC_DIR="${QT_PROJECT_DIR}/build-VolvoDigitalDashModels-RPI3-Debug/VolvoDigitalDashModels"
QT_FONTS_DIR="${QT_PROJECT_DIR}/VolvoDigitalDashModels/ariblk.ttf"
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

echo "Making /usr/lib/fonts directory"
mkdir -p "${QT_FONTS_TARGET_DIR}"

echo "Copying fonts to /usr/lib/fonts"
cp "${QT_FONTS_DIR}" "${QT_FONTS_TARGET_DIR}"

echo "Copying QtDash executable to /opt"
cp "${QT_EXEC_DIR}" "${QT_EXEC_TARGET_DIR}"

echo "Copy custom config.txt"
cp "${BOARD_DIR}/config.txt" "${BINARIES_DIR}/rpi-firmware"
