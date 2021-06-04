MAJOR_VERSION:=$(word 1, $(subst ., , $(VERSION)))

FEATURES=\
	--enable-languages=c,c++  \
	--enable-haifa            \
	--enable-sjlj-exceptions  \
	--disable-libstdcxx-pch \
	--disable-tls

# Check, if major version is greater than or equals to 8
ifeq ($(shell test $(MAJOR_VERSION) -ge 8; echo $$?), 0)
FEATURES+=--enable-threads=amigaos --enable-lto

# Check, if major version is greater than or equals to 11
ifeq ($(shell test $(MAJOR_VERSION) -ge 11; echo $$?), 0)
FEATURES+=--disable-c++tools
endif
endif
