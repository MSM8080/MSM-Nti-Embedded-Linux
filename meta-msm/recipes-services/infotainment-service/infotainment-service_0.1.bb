
LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""

SRC_URI = "file://msm-project.service \
           file://msm-launcher.sh \
          "

S = "${WORKDIR}/git"

inherit systemd

RDEPENDS:${PN}:append = " python3"


EXTRA_OECMAKE = ""


do_install() {
    # Install the compiled C++ binary
    install -d ${D}${bindir}
    install -m 0755 ${B}/appmsm_project ${D}${bindir}/appmsm_project

    # Copy QML files if any
    install -d ${D}${datadir}/msm-project
    cp -r ${S}/*.qml ${D}${datadir}/msm-project/ || true

    # Install Python and C++ apps if they exist in repo
    if [ -f ${S}/my_python_app.py ]; then
        install -m 0755 ${S}/my_python_app.py ${D}${bindir}/my_python_app.py
    fi

    if [ -f ${S}/my_cpp_app ]; then
        install -m 0755 ${S}/my_cpp_app ${D}${bindir}/my_cpp_app
    fi

    # Install launcher script
    install -m 0755 ${WORKDIR}/msm-launcher.sh ${D}${bindir}/msm-launcher.sh

    # Install systemd service
    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/msm-project.service ${D}${systemd_unitdir}/system/msm-project.service
}

FILES:${PN} += " \
    ${datadir}/msm-project \
    ${systemd_unitdir}/system/msm-project.service \
"

SYSTEMD_SERVICE:${PN} = "msm-project.service"
SYSTEMD_AUTO_ENABLE:${PN} = "enable"