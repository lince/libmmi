LIBS= -L../ -lmmi
OPTS= -g -O0
PROGRAMS= client server keyparser comm-server virtualdevice

ALL:  $(PROGRAMS)

test1: test1.cpp
	g++ test1.cpp -o test1 $(LIBS) $(OPTS) 
	
client: client-tcp.cpp
	g++ client-tcp.cpp -o client $(LIBS) $(OPTS) 

server: server-tcp.cpp
	g++ server-tcp.cpp -o server $(LIBS) $(OPTS) 
	
keyparser: keyParser.cpp
	g++ keyParser.cpp -o keyparser $(LIBS) $(OPTS) 
	
comm-server: comm-server.cpp
	g++ comm-server.cpp -o comm-server $(LIBS) $(OPTS) 

virtualdevice: virtualdevice.cpp
	g++ virtualdevice.cpp -o virtualdevice $(LIBS) $(OPTS) 
	
clean:
	rm -f $(PROGRAMS)
