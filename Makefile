clean:
	rm -rf builddir
	mkdir builddir
	meson setup builddir

runtest:
	meson compile -C builddir 
	./builddir/testglyph
