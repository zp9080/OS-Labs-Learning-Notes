rm pmtest.com
nasm pmtest8.asm -o pmtest.com
sudo mount -o loop pm.img /mnt/floppy/
sudo cp pmtest.com /mnt/floppy/ -v
sudo umount /mnt/floppy/