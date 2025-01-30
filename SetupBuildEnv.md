
# Setting up Build Environment

## Install Virtual Box
If not already running linux, you can install a virtual machine using VirtualBox. Detailed instructions on setting up Ubuntu using VirtualBox can be found [here](https://ubuntu.com/tutorials/how-to-run-ubuntu-desktop-on-a-virtual-machine-using-virtualbox#1-overview). 

It is recommended to up the drive size from 25GB to 50GB. These instructions assume that you are installing Ubuntu 24.04 LTS

## Cloning the repository
After installing a vanilla version of Ubuntu 24.04 on a virtual box instance, its time to actually clone the repo:

```
sudo apt update
sudo apt upgrade
```
then

```
sudo apt install git git-lfs
```

Cloning the repo, first making sure you're in the home directory and then making a git directory so its not cloned directly in home:

```
cd ~/
mkdir git
cd git
git clone https://github.com/whitfijs-jw/Volvo240-DigitalDash.git --recurse-submodules
```
## Install necessary packages for Buildroot
After the clone you'll need to install the necessary packages for buildroot (from [here](https://buildroot.org/downloads/manual/manual.html#requirement-mandatory), with the exception of python-is-python3):

```
sudo apt install which sed make binutils build-essential diffutils gcc g++ bash patch gzip bzip2 perl tar cpio unzip rsync file bc findutils wget python-is-python3
```

## Configure Buildroot
Navigate into the buildroot directory (from ~/git/)

```
cd Volvo240-DigitalDash/buildroot/
```

Set the current configuration so that we're building for the dash:

For configuring Buildroot to build an image for a Raspberry Pi 4 use:
```
make volvodash_rpi4_defconfig
```

For configuring Buildroot to build an image for a Raspberry Pi 3 use:
```
make volvodash_defconfig
```

## Building the image

Cross your fingers and then run:

```
make
```

This is going to take a while, many hours if you're running it on a laptop or older computer.

## Finding the output image

The output produced from build are located here:

```/buildroot/output/images```

This directory contains the outputs of the buildroot compilation process. After buildroot is done compiling the custom linux image, compiling the specified target packages, and constructing the target rootfs and bootfs, an image that can be flashed on to an SD card is placed here. ```sdcard.img``` can then be flashed on to an SD card to be used on a pi. As a part of the compilation/building the Qt Dash app should be compiled and placed within this image.

## Getting the image out of virtual box



## Flashing the image to an SD card

The easiest way to flash the image (```sdcard.img```) onto an SD card for use on a pi is to use a utility like the [Raspberry Pi Imager](https://www.raspberrypi.com/software/). In the imager utility select the "Choose OS" option, scroll all the way down and select the "Use Custom" option. Navigate to where the repository is cloned then to ```buildroot/output/images```. There should be a file named ```sdcard.img```. After selecting the image file, select your sdcard using the "Choose Storage" option. Hit write and wait.

After writing has completed you can plug the SD card into the pi and boot. The dash app should start up automatically.

