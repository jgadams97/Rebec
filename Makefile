make:
	rm -rf build
	mkdir build
	gcc src/rebec.c -o build/rebec


push:
	git config --global user.name "rmayco"
	git add *
	git commit -m "`date`"
	git push --force -u origin master

