#
# This file is the mlprog recipe.
#

SUMMARY = "Simple mlprog application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://yolov2.h \
           file://stb_image.h \
           file://stb_image_write.h \
           file://xconv_hw.h \
           file://mlprog.cpp \
           file://Makefile \
		  "

S = "${WORKDIR}"

do_compile() {
	     oe_runmake
}

do_install() {
	     install -d ${D}${bindir}
	     install -m 0755 mlprog ${D}${bindir}
}
