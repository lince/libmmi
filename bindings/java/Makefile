CC=g++

INCLUDES= 	br_ufscar_lince_mmi_AccelerationEvent.h  \
			br_ufscar_lince_mmi_MMIEventListener.h	\
			br_ufscar_lince_mmi_IDeviceComm.h \
			br_ufscar_lince_mmi_MMIManager.h \
			br_ufscar_lince_mmi_JavaEvent.h  \
			br_ufscar_lince_mmi_KeyEvent.h \
			br_ufscar_lince_mmi_MMIEvent.h \
			EventListenerAdapter.h \
			JavaDeviceAdapter.h \
			JavaEventAdapter.h \
			Util.h

			
SOURCES=	AccelerationEvent.cpp  \
			KeyEvent.cpp  \
			MMIEventListener.cpp \
			IDeviceComm.cpp \
			MMIEvent.cpp\
			MMIManager.cpp

			
ALL: libmmijava.so

libmmijava.so: $(SOURCES) $(INCLUDES)
	$(CC) -o libmmijava.so -shared $(SOURCES) \
		-I$(JAVA_HOME)/include/ -I$(JAVA_HOME)/include/linux/ -L../../ \
		-lmmi
		
clean:
	rm libmmijava.so
	
install: libmmijava.so
	cp libmmijava.so /usr/local/lib
