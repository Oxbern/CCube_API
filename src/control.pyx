from libcpp cimport bool
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