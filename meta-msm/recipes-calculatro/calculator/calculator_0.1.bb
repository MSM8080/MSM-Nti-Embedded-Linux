SUMMARY = "recipe to build C calculator"
DESCRIPTION = "C Calculator"

# LICENSE = "CLOSED"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/main.c;md5=b724d79a67dc1af0665fb287c9720329"

# ----------------------------------------------------------------------------------------
# ------ fetch & unpack

FILESEXTRAPATHS:prepend := "${THISDIR}:"

SRC_URI = "file://main.c"
# ----------------------------------------------------------------------------------------
# ------ compile

DEPENDS = " libcalc"
RDEPENDS:${PN} = " libcalc"

do_compile(){
    ${CC} ${CFLAGS} ${LDFLAGS} -shared -I${STAGING_INCDIR} -L${STAGING_LIBDIR} -lcalc ${WORKDIR}/main.c -o ${B}/calculator 
    # -I[include location ?] -L[lib location ? ]
}
# ----------------------------------------------------------------------------------------
# ------ install

do_install(){
    # ${bindir} = /usr/bin
    install -d ${D}${bindir}
    install -m 0755 ${B}/calculator ${D}${bindir}
}
# ----------------------------------------------------------------------------------------
# ------  QA

FILES:${PN} = "${bindir}/calculator"


