rm pmtest2.bin
rm a.img

nasm pmtest2.asm -o pmtest2.bin
bximage
dd if=pmtest2.bin of=a.img bs=512 count=1 conv=notrunc
