SUMMARY = "recipe to build dash"
DESCRIPTION = "Dash shell"
LICENSE = "CLOSED"
# ----------------------------------------------------------------------------------------
# fetch & unpack:

#SRC_URI = "<schema>://[source code];branch;protocol"
#            |--> local file (file)
#            |--> file from net (http)
#            |--> file from github (git)
#SRC_URI used insted of do_fetch(){}
SRC_URI = "git://github.com/danishprakash/dash.git;branch=master;protocol=https"

#SRCREV = SHA of commite from branch you entered in SRC_URI
SRCREV = "a9481f4a453f0ad25d9c9068c7b6e47253532deb"
# ----------------------------------------------------------------------------------------
# do_configure(){
#    write configuration for this recipe {target}
# }
# ----------------------------------------------------------------------------------------
do_compile(){
    # to compile with Makefile
    oe_runmake -C ${WORKDIR}/git CC="${CC}" CFLAGS="${CFLAGS}" LDFLAGS="${LDFLAGS}"
}
# ----------------------------------------------------------------------------------------
do_install(){
    # create directory
    install -d ${D}${bindir} 
    # set execution file mode 755 to destination/usr/msm
    install -m 0755 ${WORKDIR}/git/dash ${D}${bindir}
}
# ----------------------------------------------------------------------------------------
#   QA
# to escap error
INSANE_SKIP:${PN} += "ldflags"
FILES:${PN} += "${bindir} ${bindir}/dash"
