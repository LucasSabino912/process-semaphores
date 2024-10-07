xv6: lab02/Makefile
	cd lab02; make qemu; cd ..

clean: lab02/Makefile
	cd lab02; make clean; cd ..

grade: lab02/Makefile
	cd lab02; make grade; cd ..