SUMMARY = "recipe to build qt-led service"
DESCRIPTION = "qt-led service"

LICENSE = "CLOSED"

#LICENSE = "MIT"
#LIC_FILES_CHKSUM = "file://${WORKDIR}/main.cpp;md5=ee40819773f1a8124f459f8512a22894"

# ----------------------------------------------------------------------------------------
# ------ fetch & unpack

FILESEXTRAPATHS:prepend := "${THISDIR}:"
SRC_URI = "file://qt-led.service"
SYSTEMD_AUTO_ENABLE = "enable"
inherit cmake systemd

# ----------------------------------------------------------------------------------------
# ------ install

do_install(){
    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${B}/qt-led.service ${D}${systemd_system_unitdir}
}

# ----------------------------------------------------------------------------------------
# ------  QA

FILES:${PN} = "${bindir}/static-ledswitch"





