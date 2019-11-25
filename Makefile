

all:
	make logfind

clear: 
	rm -fR logfind

et: all
	py.test  logfind_et_tests.py
