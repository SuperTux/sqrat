//
// Copyright (c) 2009 Brandon Jones
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//	1. The origin of this software must not be misrepresented; you must not
//	claim that you wrote the original software. If you use this software
//	in a product, an acknowledgment in the product documentation would be
//	appreciated but is not required.
//
//	2. Altered source versions must be plainly marked as such, and must not be
//	misrepresented as being the original software.
//
//	3. This notice may not be removed or altered from any source
//	distribution.
//

#include <gtest/gtest.h>
#include <sqrat.h>
#include "Fixture.h"

using namespace Sqrat;

int f0()
{
    return 1;
}

int f1(int a1)
{
    return (a1 == 1);
}


int f2(int a1, int a2)
{
    return (a1 == 1) && (a2 == 2);
}


int f3(int a1, int a2, int a3)
{
    return (a1 == 1) && (a2 == 2) && (a3 == 3);
}


int f4(int a1, int a2, int a3, int a4)
{
    return (a1 == 1)&& (a2 == 2) && (a3 == 3) && (a4 == 4);
}



TEST_F(SqratTest, GlobalFunction) {
	DefaultVM::Set(vm);

	RootTable().Func("f0", &f0);
	RootTable().Func("f1", &f1);
	RootTable().Func("f2", &f2);
	RootTable().Func("f3", &f3);
	RootTable().Func("f4", &f4);

	Script script;

	try {
		script.CompileString(_SC(" \
			gTest.EXPECT_INT_EQ(1, f0()); \
			gTest.EXPECT_INT_EQ(1, f1(1)); \
			gTest.EXPECT_INT_EQ(1, f2(1, 2)); \
			gTest.EXPECT_INT_EQ(1, f3(1, 2, 3)); \
			gTest.EXPECT_INT_EQ(1, f4(1, 2, 3, 4)); \
			"));
	} catch(Exception ex) {
		FAIL() << _SC("Compile Failed: ") << ex.Message();
	}
	
	try {
		script.Run();
	} catch(Exception ex) {
		FAIL() << _SC("Run Failed: ") << ex.Message();
	}
}

