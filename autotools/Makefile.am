include $(top_srcdir)/makerules

    
noinst_libdir = $(sqrat_builddir)
noinst_bindir = $(sqrat_builddir)
ORIGPATH=$(sqrat_srcdir)

BUILT_SOURCES = scripts
CLEANFILES = scripts
scripts: Makefile
	-ln -s $(ORIGPATH)/sqrattest/scripts $(sqrat_builddir)
    
nobase_include_HEADERS = $(ORIGPATH)/include/sqmodule.h\
    $(ORIGPATH)/include/sqrat.h $(ORIGPATH)/include/sqratimport.h\
    $(ORIGPATH)/include/sqrat/sqratAllocator.h\
    $(ORIGPATH)/include/sqrat/sqratArray.h\
    $(ORIGPATH)/include/sqrat/sqratClass.h\
    $(ORIGPATH)/include/sqrat/sqratClassType.h\
    $(ORIGPATH)/include/sqrat/sqratConst.h\
    $(ORIGPATH)/include/sqrat/sqratFunction.h\
    $(ORIGPATH)/include/sqrat/sqratGlobalMethods.h\
    $(ORIGPATH)/include/sqrat/sqratMemberMethods.h\
    $(ORIGPATH)/include/sqrat/sqratObject.h\
    $(ORIGPATH)/include/sqrat/sqratOverloadMethods.h\
    $(ORIGPATH)/include/sqrat/sqratScript.h\
    $(ORIGPATH)/include/sqrat/sqratTable.h\
    $(ORIGPATH)/include/sqrat/sqratTypes.h\
    $(ORIGPATH)/include/sqrat/sqratUtil.h\
    $(ORIGPATH)/include/sqrat/sqratVM.h 

TESTS = import_test \
    class_binding class_instances class_properties const_bindings function_overload\
    script_loading squirrel_functions table_binding function_params run_stack_handling suspend_vm sqrat_vm \
    null_pointer_return func_input_argument_type array_binding unique_object
    
noinst_PROGRAMS = sq_interp $(TESTS)

sq_interp_SOURCES = $(sqrat_srcdir)/sq/sq.c
sq_interp_LDADD = -L$(sqrat_builddir) -lsqratimport $(LDADD) -ldl

noinst_LIBRARIES = libgtest.a libsqratimport.a libsqrattestmain.a
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

class_instances_SOURCES = $(sqrat_srcdir)/sqrattest/ClassInstances.cpp 
class_instances_CXXFLAGS = -I$(ORIGPATH)/sqrattest -I$(ORIGPATH)/gtest-1.3.0/include/ $(AM_CXXFLAGS)
class_instances_LDADD = -L$(sqrat_builddir) -lsqrattestmain -lgtest $(LDADD) 

class_properties_SOURCES = $(sqrat_srcdir)/sqrattest/ClassProperties.cpp 
class_properties_CXXFLAGS = -I$(ORIGPATH)/sqrattest -I$(ORIGPATH)/gtest-1.3.0/include/ $(AM_CXXFLAGS)
class_properties_LDADD = -L$(sqrat_builddir) -lsqrattestmain -lgtest $(LDADD) 

const_bindings_SOURCES = $(sqrat_srcdir)/sqrattest/ConstBindings.cpp 
const_bindings_CXXFLAGS = -I$(ORIGPATH)/sqrattest -I$(ORIGPATH)/gtest-1.3.0/include/ $(AM_CXXFLAGS)
const_bindings_LDADD = -L$(sqrat_builddir) -lsqrattestmain -lgtest $(LDADD) 

function_overload_SOURCES = $(sqrat_srcdir)/sqrattest/FunctionOverload.cpp 
function_overload_CXXFLAGS = -I$(ORIGPATH)/sqrattest -I$(ORIGPATH)/gtest-1.3.0/include/ $(AM_CXXFLAGS)
function_overload_LDADD = -L$(sqrat_builddir) -lsqrattestmain -lgtest $(LDADD) 

script_loading_SOURCES = $(sqrat_srcdir)/sqrattest/ScriptLoading.cpp 
script_loading_CXXFLAGS = -I$(ORIGPATH)/sqrattest -I$(ORIGPATH)/gtest-1.3.0/include/ $(AM_CXXFLAGS)
script_loading_LDADD = -L$(sqrat_builddir) -lsqrattestmain -lgtest $(LDADD) 

squirrel_functions_SOURCES = $(sqrat_srcdir)/sqrattest/SquirrelFunctions.cpp 
squirrel_functions_CXXFLAGS = -I$(ORIGPATH)/sqrattest -I$(ORIGPATH)/gtest-1.3.0/include/ $(AM_CXXFLAGS)
squirrel_functions_LDADD = -L$(sqrat_builddir) -lsqrattestmain -lgtest $(LDADD) 

table_binding_SOURCES = $(sqrat_srcdir)/sqrattest/TableBinding.cpp 
table_binding_CXXFLAGS = -I$(ORIGPATH)/sqrattest -I$(ORIGPATH)/gtest-1.3.0/include/ $(AM_CXXFLAGS)
table_binding_LDADD = -L$(sqrat_builddir) -lsqrattestmain -lgtest $(LDADD) 

function_params_SOURCES = $(sqrat_srcdir)/sqrattest/FunctionParams.cpp 
function_params_CXXFLAGS = -I$(ORIGPATH)/sqrattest -I$(ORIGPATH)/gtest-1.3.0/include/ $(AM_CXXFLAGS)
function_params_LDADD = -L$(sqrat_builddir) -lsqrattestmain -lgtest $(LDADD) 

run_stack_handling_SOURCES = $(sqrat_srcdir)/sqrattest/RunStackHandling.cpp 
run_stack_handling_CXXFLAGS = -I$(ORIGPATH)/sqrattest -I$(ORIGPATH)/gtest-1.3.0/include/ $(AM_CXXFLAGS)
run_stack_handling_LDADD = -L$(sqrat_builddir) -lsqrattestmain -lgtest $(LDADD) 

suspend_vm_SOURCES = $(sqrat_srcdir)/sqrattest/SuspendVM.cpp 
suspend_vm_CXXFLAGS = -I$(ORIGPATH)/sqrattest -I$(ORIGPATH)/gtest-1.3.0/include/ $(AM_CXXFLAGS)
suspend_vm_LDADD = -L$(sqrat_builddir) -lsqrattestmain -lgtest $(LDADD) 

sqrat_vm_SOURCES = $(sqrat_srcdir)/sqrattest/SqratVM.cpp $(sqrat_srcdir)/sqrattest/SqratVM2.cpp
sqrat_vm_CXXFLAGS = -I$(ORIGPATH)/sqrattest -I$(ORIGPATH)/gtest-1.3.0/include/ $(AM_CXXFLAGS)
sqrat_vm_LDADD = -L$(sqrat_builddir) -lsqrattestmain -lgtest $(LDADD) 

null_pointer_return_SOURCES = $(sqrat_srcdir)/sqrattest/SqratVM.cpp $(sqrat_srcdir)/sqrattest/NullPointerReturn.cpp
null_pointer_return_CXXFLAGS = -I$(ORIGPATH)/sqrattest -I$(ORIGPATH)/gtest-1.3.0/include/ $(AM_CXXFLAGS)
null_pointer_return_LDADD = -L$(sqrat_builddir) -lsqrattestmain -lgtest $(LDADD) 

func_input_argument_type_SOURCES = $(sqrat_srcdir)/sqrattest/SqratVM.cpp $(sqrat_srcdir)/sqrattest/FuncInputArgumentType.cpp
func_input_argument_type_CXXFLAGS = -I$(ORIGPATH)/sqrattest -I$(ORIGPATH)/gtest-1.3.0/include/ $(AM_CXXFLAGS)
func_input_argument_type_LDADD = -L$(sqrat_builddir) -lsqrattestmain -lgtest $(LDADD) 

array_binding_SOURCES = $(sqrat_srcdir)/sqrattest/ArrayBinding.cpp 
array_binding_CXXFLAGS = -I$(ORIGPATH)/sqrattest -I$(ORIGPATH)/gtest-1.3.0/include/ $(AM_CXXFLAGS)
array_binding_LDADD = -L$(sqrat_builddir) -lsqrattestmain -lgtest $(LDADD) 

unique_object_SOURCES = $(sqrat_srcdir)/sqrattest/UniqueObject.cpp 
unique_object_CXXFLAGS = -I$(ORIGPATH)/sqrattest -I$(ORIGPATH)/gtest-1.3.0/include/ $(AM_CXXFLAGS)
unique_object_LDADD = -L$(sqrat_builddir) -lsqrattestmain -lgtest $(LDADD) 

if HAVE_DOXYGEN
directory = $(sqrat_builddir)/docs/man/man3/

dist_man_MANS = $(directory)/man_page_1.3 $(directory)/man_page_2.3
$(directory)/man_page_1.3: doxyfile.stamp
$(directory)/man_page_2.3: doxyfile.stamp

doxyfile.stamp:
	$(DOXYGEN) $(sqrat_builddir)/docs/Doxyfile
	echo Timestamp > doxyfile.stamp

CLEANFILES += doxyfile.stamp

all-local: doxyfile.stamp
clean-local:
	rm -rf $(sqrat_builddir)/docs
endif 

