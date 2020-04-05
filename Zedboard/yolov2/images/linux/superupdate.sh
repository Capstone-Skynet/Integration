cd ../../
petalinux-build
petalinux-package --boot --fsbl images/linux/zynq_fsbl.elf --fpga --u-boot --force
cd images/linux/
source update.sh
