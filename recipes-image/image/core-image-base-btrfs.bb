require recipes-core/images/core-image-minmal.bb

IMAGE_INSTALL:append = " scriptz"
IMAGE_FEATURES:remove = "splash"

MKUBIFS_ARGS = " -m 512 -e 15360 -c 12000 "
UBINIZE_ARGS = " -p 512KiB -m 4096 -s 4096 "
WKS_FILE = "core-image-base-btrfs.wic"
IMAGE_FSTYPES = "wic wic.bmap"