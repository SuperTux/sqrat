include $(top_srcdir)/makerules

ORIGPATH=$(sqrat_srcdir)

noinst_libdir = $(sqrat_builddir)
noinst_bindir = $(sqrat_builddir)

noinst_bin_PROGRAMS = sq_interp import_test \
    class_binding 

sq_interp_SOURCES = $(sqrat_srcdir)/sq/sq.c
sq_interp_LDADD = -L$(sqrat_builddir) -lsqratimport $(LDADD) -ldl

noinst_lib_LIBRARIES = libgtest.a libsqratimport.a libsqrattestmain.a
libgtest_a_SOURCES = $(ORIGPATH)/gtest-1.3.0/src/gtest-all.cc
libgtest_a_CXXFLAGS = -I$(ORIGPATH)/gtest-1.3.0/ -I$(ORIGPATH)/gtest-1.3.0/include/

libsqratimport_a_SOURCES = $(ORIGPATH)/sqimport/sqratimport.cpp
libsqrattestmain_a_SOURCES = $(ORIGPATH)/sqrattest/Main.cpp $(ORIGPATH)/sqrattest/Vector.cpp
libsqrattestmain_a_CXXFLAGS = -I$(ORIGPATH)/gtest-1.3.0/include/ -I$(ORIGPATH)/sqrattest $(AM_CXXFLAGS)

import_test_SOURCES = $(sqrat_srcdir)/sqrattest/ImportTest.cpp 
import_test_CXXFLAGS = -I$(ORIGPATH)/gtest-1.3.0/ -I$(ORIGPATH)/gtest-1.3.0/include/ $(AM_CXXFLAGS)
import_test_LDADD = -L$(sqrat_builddir) -lsqrattestmain -lgtest -lsqratimport $(LDADD) -ldl


class_binding_SOURCES = $(sqrat_srcdir)/sqrattest/ClassBinding.cpp 
class_binding_CXXFLAGS = -I$(ORIGPATH)/sqrattest -I$(ORIGPATH)/gtest-1.3.0/include/ $(AM_CXXFLAGS)
class_binding_LDADD = -L$(sqrat_builddir) -lsqrattestmain -lgtest $(LDADD) 

