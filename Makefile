clean:
	rm -rf buildDir
	mkdir buildDir
	meson setup buildDir

runtest:
	meson compile -C buildDir
	./buildDir/testglyph
