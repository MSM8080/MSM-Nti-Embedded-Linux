SUMMARY = "recipe to build calculator library"
DESCRIPTION = "library libcalc"

# LICENSE = "CLOSED"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

# ----------------------------------------------------------------------------------------
# ------ fetch & unpack

FILESEXTRAPATHS:prepend := "${THISDIR}:"
SRC_URI = "file://libcalc.c \
           file://libcalc.h"
# ----------------------------------------------------------------------------------------
# ------ compile

# position-independent -fPIC in ${CC}
#            code,  suitable  for dynamic linking and avoiding any limit on the
#            size of the global offset table.  This option makes  a  difference
#            on AArch64, m68k, PowerPC and SPARC.

# soft link
#     libclac.so.1.0 
#     $ ln -sf libclac.so.1.0 ${B}/libclac.so

do_compile(){
    ${CC} ${CFLAGS} ${LDFLAGS} -fPIC -shared ${WORKDIR}/libcalc.c -o ${B}/libcalc.so.1.0 -I${WORKDIR}
    ln -sf libcalc.so.1.0 ${B}/libcalc.so
}
# ----------------------------------------------------------------------------------------
# ------ install

do_install(){
    # ${bindir} = /usr/bin
    install -d ${D}${libdir}
    install -m 0755 ${B}/libcalc.so.1.0 ${D}${libdir}
    
    ln -sf libcalc.so.1.0 ${D}${libdir}/libcalc.so
    
    install -d ${D}${includedir}
    install -m 0644 ${WORKDIR}/libcalc.h ${D}${includedir}
}

# ----------------------------------------------------------------------------------------
# ------  QA

FILES:${PN} = "${libdir}/libcalc.so*"

# if i want to develop on the board 
FILES:${PN}-dev = "${libdir}/libcalc.so ${includedir}/libcalc.h"
