from libcpp cimport bool
from libc.stdint cimport uint8_t
from libcpp.string cimport string
from libcpp.list cimport list

cdef extern from "Controller.h" namespace "apicube":
    cdef cppclass Controller:
        Controller() except +
        bool connectDevice(int i)
        bool on(int x, int y, int z)
        bool off(int x, int y, int z)
        bool toggle(int x, int y, int z)
        bool display()
        bool disconnectDevice()
        bool pilot()
        bool available()
        uint8_t getLuminosity();
        bool setLuminosity(uint8_t v);
        uint8_t *getDeviceInfo();
        uint8_t getDeviceID();
        uint8_t getVersionFirmware();
        bool printMsgScreen(string message, uint8_t sizeMessage) ;
        bool reset();


cdef class PyController:
    cdef Controller *thisptr
    def __cinit__(self):
        self.thisptr = new Controller()
    def __dealloc__(self):
        del self.thisptr
    def on(self, int x, int y, int z):
        return self.thisptr.on(x,y,z)
    def off(self, int x, int y, int z):
        return self.thisptr.off(x,y,z)
    def toggle(self, int x, int y, int z):
        return self.thisptr.toggle(x,y,z)
    def connectDevice(self, int i):
        return self.thisptr.connectDevice(i)
    def display(self):
        return self.thisptr.display()        
    def disconnectDevice(self):
        return self.thisptr.disconnectDevice()
    def pilot(self):
        return self.thisptr.pilot()
    def available(self):       
        return self.thisptr.available()
    def getLuminosity(self):       
        return self.thisptr.getLuminosity()
    def getDeviceInfo(self):       
        return self.thisptr.getDeviceInfo()
    def getDeviceID(self):       
        return self.thisptr.getDeviceID()
    def getVersionFirmware(self):       
        return self.thisptr.getVersionFirmware()
    def setLuminosity(self, uint8_t v):       
        return self.thisptr.setLuminosity(v)
    def printMsgScreen(self, string message, uint8_t sizeMessage):       
        return self.thisptr.printMsgScreen(message,sizeMessage)
    def reset(self):       
        return self.thisptr.reset()