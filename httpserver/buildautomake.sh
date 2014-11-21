rm -rf autom4te.cache/ config.* depcomp install-sh missing stamp-h1 
rm -rf Makefile Makefile.in

aclocal
autoheader
automake --add-missing
autoconf
