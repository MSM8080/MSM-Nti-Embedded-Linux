# Recipe created by recipetool
# This is the basis of a recipe and may need further editing in order to be fully functional.
# (Feel free to remove these comments when editing.)

# Unable to find any files that looked like license statements. Check the accompanying
# documentation and source headers and set LICENSE and LIC_FILES_CHKSUM accordingly.
#
# NOTE: LICENSE is being set to "CLOSED" to allow you to at least start building - if
# this is not accurate with respect to the licensing of the software being built (it
# will not be in most cases) you must specify the correct value before using this
# recipe for anything other than initial testing/development!
LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""

SRC_URI = "git://github.com/MSM8080/msm-project.git;protocol=https;branch=v.1.0"

# Modify these as desired
PV = "1.0+git${SRCPV}"
SRCREV = "c61270cc913f14d97ee414dba6f557f6ea78ad89"

DEPENDS:append = " qtbase qttools qtdeclarative-native qtwayland qtquick3d qtmultimedia qtsvg qtcharts cups qtserialport"
RDEPENDS:${PN} = " qtbase qttools qtdeclarative qtwayland qtquick3d qtmultimedia qtsvg qtcharts cups qtserialport python3"

S = "${WORKDIR}/git"

# NOTE: unable to map the following CMake package dependencies: Qt6
inherit qt6-cmake

# Specify any options you want to pass to cmake using EXTRA_OECMAKE:
EXTRA_OECMAKE = ""

