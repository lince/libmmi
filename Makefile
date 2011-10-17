CC= g++
HEADERS_DIR= /usr/local/include/mmi
LIB_DIR= /usr/local/lib

INCLUDES=	include/AccelerationEvent.h \
			include/AccelerationFactory.h \
			include/KeyEvent.h \
			include/KeyEventFactory.h \
			include/HoldOnEvent.h \
			include/EventBuffer.h \
			include/EventFactory.h \
			include/EventParser.h \
			include/IDeviceComm.h \
			include/MMIEvent.h \
			include/MMIEventListener.h \
			include/MMIManager.h \
			include/Parsable.h
#			include/MMIService.h
			
SOURCES=	src/AccelerationEvent.cpp \
			src/AccelerationFactory.cpp \
			src/KeyEvent.cpp \
			src/HoldOnEvent.cpp \
			src/KeyEventFactory.cpp \
			src/EventBuffer.cpp \
			src/EventParser.cpp \
			src/MMIEvent.cpp \
			src/MMIManager.cpp
#			src/MMIService.cpp
			
LIBS= 		-lcpputil -lxerces-c -lmmiwii -lmmisocket -lmmizeroconf -ljson
			
INCLUDES_WII= \
			include/wii/StateCircularBuffer.h \
			include/wii/WiiButtonReport.h \
			include/wii/WiiDriver.h \
			include/wii/WiiEvent.h \
			include/wii/WiiEventHandler.h \
			include/wii/WiiEventPoster.h \
			include/wii/WiiMote.h \
			include/wii/WiiState.h
			
SOURCES_WII= \
			src/wii/StateCircularBuffer.cpp \
			src/wii/WiiButtonReport.cpp \
			src/wii/WiiDriver.cpp \
			src/wii/WiiEvent.cpp \
			src/wii/WiiEventPoster.cpp \
			src/wii/WiiMote.cpp \
			src/wii/WiiState.cpp
			
LIBS_WII = -lcpputil -lcwiid -lpthread

INCLUDES_SOCKET= \
			include/socketconn/ServerSocketTCP.h \
			include/socketconn/SocketTCP.h \
			include/socketconn/TCPCommServer.h \
			include/socketconn/TCPDevice.h
			
SOURCES_SOCKET= \
			src/socketconn/ServerSocketTCP.cpp \
			src/socketconn/SocketTCP.cpp \
			src/socketconn/TCPCommServer.cpp \
			src/socketconn/TCPDevice.cpp

			
LIBS_SOCKET = -lcpputil -lpthread

INCLUDES_ZEROCONF= \
			include/zeroconf/CommunicationManager.h
			
SOURCES_ZEROCONF= \
			src/zeroconf/CommunicationManager.cpp

			
LIBS_ZEROCONF = -lcpputil -lpthread -lavahi-client

INSTALL_HEADERS = $(INCLUDES)

ALL: libmmi.so

libmmi.so: $(INCLUDES) $(SOURCES) libmmiwii.so libmmisocket.so libmmizeroconf.so
	$(CC) $(SOURCES) $(LIBS)\
		-shared -fPIC -L. -o libmmi.so
		
libmmiwii.so: $(INCLUDES_WII) $(SOURCES_WII)
	$(CC) $(INCLUDES_WII) $(SOURCES_WII) $(LIBS_WII) \
		-shared -fPIC -o libmmiwii.so
		
libmmisocket.so: $(INCLUDES_SOCKET) $(SOURCES_SOCKET)
	$(CC) $(INCLUDES_SOCKET) $(SOURCES_SOCKET) $(LIBS_SOCKET) \
		-shared -fPIC -o libmmisocket.so
		
libmmizeroconf.so: $(INCLUDES_ZEROCONF) $(SOURCES_ZEROCONF)
	$(CC) $(INCLUDES_ZEROCONF) $(SOURCES_ZEROCONF) $(LIBS_ZEROCONF) \
		-shared -fPIC -o libmmizeroconf.so
		
clean:
	rm -f libmmi.so libmmiwii.so libmmisocket.so libmmizeroconf.so
	
uninstall:
	rm -rf $(HEADERS_DIR)
		
install: libmmi.so
	install -d $(HEADERS_DIR) $(HEADERS_DIR)/wii $(HEADERS_DIR)/socketconn \
				$(HEADERS_DIR)/zeroconf
	install -t $(HEADERS_DIR) $(INCLUDES)
	install -t $(HEADERS_DIR)/wii $(INCLUDES_WII)
	install -t $(HEADERS_DIR)/socketconn $(INCLUDES_SOCKET)
	install -t $(HEADERS_DIR)/zeroconf $(INCLUDES_ZEROCONF)
	install -t $(LIB_DIR) libmmi.so libmmiwii.so libmmisocket.so libmmizeroconf.so