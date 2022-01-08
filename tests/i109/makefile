CXX           = ppc-amigaos-g++
APP_CXXFLAGS  = -athread=native
LINK          = ppc-amigaos-g++
APP_LFLAGS    = -use-dynld -Wl,--export-dynamic -Wl,--no-undefined -athread=native

APP_OBJECTS = main.o
SOBJ_OBJECTS = sobj.o

app: $(APP_OBJECTS) sobj.so  
	$(LINK) $(APP_LFLAGS) -o app $(APP_OBJECTS) sobj.so

sobj.so: $(SOBJ_OBJECTS)
	$(LINK) -shared -fPIC -Wl,--version-script,sobj.version -o sobj.so $(SOBJ_OBJECTS)

sobj.o: sobj.cpp sobj.h
	$(CXX) -c -fPIC -o sobj.o sobj.cpp

main.o: main.cpp sobj.h
	$(CXX) -c -o main.o main.cpp

.PHONY: clean
clean:
	rm -f *.o *.so app