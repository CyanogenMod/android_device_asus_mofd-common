#!/system/bin/sh

MemTotalStr=`cat /proc/meminfo | grep MemTotal`
MemTotal=${MemTotalStr:16:8}
ZRAM_THRESHOLD=3000000
IsLowMemory=0
((IsLowMemory=MemTotal<ZRAM_THRESHOLD?1:0))
if [ $IsLowMemory -eq 1 ]; then
    setprop ro.config.zram true
fi

