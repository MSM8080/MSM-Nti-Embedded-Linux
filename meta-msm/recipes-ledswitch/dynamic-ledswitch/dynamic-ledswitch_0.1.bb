SUMMARY = "recipe to build CPP dynamic led-switch app"
DESCRIPTION = "led-switch app"

# LICENSE = "CLOSED"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/main.cpp;md5=76520b47b9e89a1829ffd7d8ea8f89dd"


# ----------------------------------------------------------------------------------------
# ------ fetch & unpack

FILESEXTRAPATHS:prepend := "${THISDIR}:"
SRC_URI = "file://main.cpp"

# ----------------------------------------------------------------------------------------
# ------ compile


DEPENDS += "libledswitch"
RDEPENDS:${PN} += "rlibledswitch"




TARGET_CFLAGS:append = " -march=armv8-a -mtune=cortex-a53"
TARGET_LDFLAGS:append = " "

do_compile(){
    ${CXX} ${CFLAGS} ${LDFLAGS} ${TARGET_CFLAGS} ${WORKDIR}/main.cpp -I${STAGING_INCDIR} -L${STAGING_LIBDIR} -lledswitch -o ${B}/dynamic-ledswitch
}
# ----------------------------------------------------------------------------------------
# ------ install

do_install(){
    
    # ${bindir} = /usr/bin
    install -d ${D}${bindir}
    install -m 0755 ${B}/dynamic-ledswitch ${D}${bindir}
}
# ----------------------------------------------------------------------------------------
# ------  QA

FILES:${PN} = "${bindir}/dynamic-ledswitch"


