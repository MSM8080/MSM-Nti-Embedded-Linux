SUMMARY = "recipe to build CPP static led-switch app"
DESCRIPTION = "led-switch app"

# LICENSE = "CLOSED"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/main.cpp;md5=383272c1608d11cd823a37a0e8dd5ced"


# ----------------------------------------------------------------------------------------
# ------ fetch & unpack

FILESEXTRAPATHS:prepend := "${THISDIR}:"
SRC_URI = "file://main.cpp \
           file://led-switch.cpp \
           file://led-switch.h"

# ----------------------------------------------------------------------------------------
# ------ compile

do_compile(){
    ${CXX} --static ${WORKDIR}/led-switch.cpp ${WORKDIR}/main.cpp -o ${B}/static-ledswitch -I ${WORKDIR} -std=c++20
}
# ----------------------------------------------------------------------------------------
# ------ install

do_install(){
    
    # ${bindir} = /usr/bin
    install -d ${D}${bindir}
    install -m 0755 ${B}/static-ledswitch ${D}${bindir}
}
# ----------------------------------------------------------------------------------------
# ------  QA

FILES:${PN} = "${bindir}/static-ledswitch"


