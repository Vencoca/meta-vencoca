# Yocto commands
source oe-init-build-env
sudo dd if=build/tmp/deploy/images/raspberrypi3/core-image-base-raspberrypi3.rpi-sdimg of=/dev/sdb status=progress
bitbake core-image-base

# Terminal commands
list of supported filesystems -> cat /proc/filesystems
list of devices -> blkid
utility for partitions -> gparted
fdisk -l
oe-run-native bmap-tools-native bmaptool copy tmp/deploy/images/raspberrypi3/core-image-base-btrfs-raspberrypi3.wic /dev/sdb

udisksctl unmount --block-device /dev/sdb3 <- unmout of btrfs
sudo chmod 666 /dev/sdb <- práva pro disk