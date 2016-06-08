from libcpp cimport bool
from libcpp cimport list

cdef extern from "Controller.h" namespace "api":
    cdef cppclass Controller:
        Controller() except +
        bool secure
        #std::list<Device*> devices
        #Device *connectedDevice
        void sayhello()

cdef class PyController:
    cdef Controller *thisptr
    def __cinit__(self):
        self.thisptr = new Controller()
    def __dealloc__(self):
        del self.thisptr
    def sayhello(self):
        return self.thisptr.sayhello()