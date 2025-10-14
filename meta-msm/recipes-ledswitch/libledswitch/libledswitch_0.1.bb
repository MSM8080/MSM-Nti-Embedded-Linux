SUMMARY = "recipe to build led-switch library"
DESCRIPTION = "library libledswitch"

# LICENSE = "CLOSED"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

# ----------------------------------------------------------------------------------------
# ------ fetch & unpack

FILESEXTRAPATHS:prepend := "${THISDIR}:"
SRC_URI = "file://led-switch.cpp \
           file://led-switch.h"
# ----------------------------------------------------------------------------------------
# ------ compile

# position-independent -fPIC in ${CC}
#            code,  suitable  for dynamic linking and avoiding any limit on the
#            size of the global offset table.  This option makes  a  difference
#            on AArch64, m68k, PowerPC and SPARC.

# soft link
#     libclac.so.1.0 
#     $ ln -sf libclac.so.1.0 ${B}/libclac.so



PROVIDES = "libledswitch"
RPROVIDES:${PN} += "rlibledswitch"

TARGET_CFLAGS:append = " -march=armv8-a -mtune=cortex-a53"
TARGET_LDFLAGS:append = " "

do_compile(){
    ${CXX} ${CFLAGS} ${TARGET_CFLAGS} -c -fPIC ${WORKDIR}/led-switch.cpp -I ${WORKDIR} -o ${B}/libledswitch.o
    ${CXX} ${LDFLAGS} ${TARGET_LDFLAGS} -fPIC -shared -Wl,-soname,libledswitch.so.1 -o ${B}/libledswitch.so.1.0 ${B}/libledswitch.o
    ln -sf ${B}/libledswitch.so.1.0 ${B}/libledswitch.so.1
    ln -sf ${B}/libledswitch.so.1 ${B}/libledswitch.so
    
}

# ----------------------------------------------------------------------------------------
# ------ configure

do_configure:append() {
    cp ${WORKDIR}/led-switch.h ${S}/
}

# ----------------------------------------------------------------------------------------
# ------ install

do_install(){
    # ${bindir} = /usr/bin
    install -d ${D}${libdir}
    install -m 0755 ${B}/libledswitch.so.1.0 ${D}${libdir}
    
    ln -sf libledswitch.so.1.0 ${D}${libdir}/libledswitch.so
    
    
    install -d ${D}${includedir}
    # install -m 0644 ${WORKDIR}/led-switch.h ${D}${includedir}
    install -m 0644 ${S}/led-switch.h ${D}${includedir}
}

# ----------------------------------------------------------------------------------------
# ------  QA

FILES:${PN} = "${libdir}/libledswitch.so.* "

# if i want to develop on the board 
FILES:${PN}-dev = "${libdir}/libledswitch.so ${includedir}/led-switch.h"
