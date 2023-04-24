# Package summary
SUMMARY = "Measure package"
# License
LICENSE = "MIT"
# License checksum file is always required
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

# Measure.cpp from local file
SRC_URI = "file://measurecpp \
           file://measure.service \  
    "

inherit systemd

SYSTEMD_SERVICE:${PN} = "measure.service"

# Set LDFLAGS options provided by the build system
TARGET_CC_ARCH += "${LDFLAGS}"

# Change source directory to workdirectory where measure.cpp is
S = "${WORKDIR}"

# Compile measure from sources, no Makefile
do_compile() {
    ${CXX} -Wall measurecpp -o measure
}

# Install binary to final directory /usr/bin
do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${WORKDIR}/measure ${D}${bindir}

    install -d ${D}${systemd_unitdir}/system
    install -c -m 0644 ${WORKDIR}/measure.service ${D}${systemd_unitdir}/system
}

FILES:${PN} += " \
            ${systemd_unitdir}/system \
            ${bindir}measure \
        "