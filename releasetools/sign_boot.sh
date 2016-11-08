#!/sbin/sh

set -e

# shell variables
block=/dev/block/by-name/boot;

# dump boot
dump_boot() {
  dd if=$block of=/tmp/old_boot.img;
  /tmp/install/bin/unmkbootimg /tmp/old_boot.img;
  echo "BOOT DUMPED TO /tmp!";
}

# append certificate and write image
write_boot() {
  /tmp/install/bin/mkbootimg --kernel kernel.gz --ramdisk initramfs.cpio.gz --cmdline "init=/init pci=noearly console=logk0 loglevel=0 vmalloc=256M androidboot.hardware=mofd_v1 watchdog.watchdog_thresh=60 androidboot.spid=xxxx:xxxx:xxxx:xxxx:xxxx:xxxx androidboot.serialno=01234567890123456789 gpt snd_pcm.maximum_substreams=8 ptrace.ptrace_can_access=1 panic=15 ip=50.0.0.2:50.0.0.1::255.255.255.0::usb0:on debug_locks=0 n_gsm.mux_base_conf=\"ttyACM0,0 ttyXMM0,1\" bootboost=1 androidboot.selinux=permissive" --base 0x10000000 --pagesize 2048 --ramdisk_offset 0x01000000 --tags_offset 0x00000100 --second second.gz -o /tmp/boot-new.img;

cat /tmp/boot-new.img /tmp/install/bin/boot.sig > /tmp/boot.img;
dd if=/tmp/boot.img of=$block;

}

dump_boot;
write_boot;



