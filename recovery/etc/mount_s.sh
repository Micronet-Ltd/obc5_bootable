busybox --install /sbin
while : ; do
    [[ -d "/mnt/shell/emulated/0" ]] && break
    echo "Pausing until file exists."
    sleep 1
done
busybox mount --bind /mnt/shell/emulated/0 /sdcard1
