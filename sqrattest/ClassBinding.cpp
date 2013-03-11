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
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source
//  distribution.
//

#include <gtest/gtest.h>
#include <sqrat.h>
#include "Vector.h"
#include "Fixture.h"

using namespace Sqrat;

const Sqrat::string Vec2ToString(const Vec2* v) {
    std::basic_stringstream<SQChar> out;
    out << _SC("Vec2(") << v->x << _SC(", ") << v->y << _SC(")");
    return out.str();
}

TEST_F(SqratTest, SimpleClassBinding) {
    DefaultVM::Set(vm);

    Class<Vec2> vec2;

    vec2
    // Variables
    .Var(_SC("x"), &Vec2::x)
    .Var(_SC("y"), &Vec2::y)

    // Operators
    .Func(_SC("_add"), &Vec2::operator +)
    .Func(_SC("_mul"), &Vec2::operator *)
    .Func(_SC("_div"), &Vec2::operator /)

    // Function Disambiguation
    .Func<Vec2 (Vec2::*)(void) const>(_SC("_unm"), &Vec2::operator -)
    .Func<Vec2 (Vec2::*)(const Vec2&) const>(_SC("_sub"), &Vec2::operator -)

    // Member Functions
    .Func(_SC("Length"), &Vec2::Length)
    .Func(_SC("Distance"), &Vec2::Distance)
    .Func(_SC("Normalize"), &Vec2::Normalize)
    .Func(_SC("Dot"), &Vec2::Dot)

    // Global Static Function bound as a member function
    .GlobalFunc(_SC("_tostring"), &Vec2ToString)
    ;

    RootTable().Bind(_SC("Vec2"), vec2);

    Script script;

    try {
        script.CompileString(_SC(" \
			v <- Vec2(); \
			v.x = 1.2; \
			v.y = 3.4; \
			v *= 2.0; \
			gTest.EXPECT_FLOAT_EQ(2.4, v.x); \
			gTest.EXPECT_FLOAT_EQ(v.x, 2.4); \
	        gTest.EXPECT_INT_EQ(2, v.x); \
	        gTest.EXPECT_TRUE(v.x); \
	        gTest.EXPECT_INT_EQ(v.x, 2); \
	        gTest.EXPECT_TRUE(v.y); \
	        gTest.EXPECT_INT_EQ(6, v.y); \
			gTest.EXPECT_FLOAT_EQ(6.8, v.y); \
			gTest.EXPECT_STR_EQ(\"\" + v, \"Vec2(2.4, 6.8)\"); \
			gTest.EXPECT_FLOAT_EQ(v.Length(), 7.211103); \
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

class Animal {
public:
    virtual string Speak() {
        return _SC("[Silent]");
    }
};

class Cat : public Animal {
public:
    virtual string Speak() {
        return _SC("Meow!");
    }
};

class Dog : public Animal {
public:
    virtual string Speak() {
        return _SC("Woof!");
    }
};

string MakeSpeak(Animal* a) {
    return a->Speak();
}

TEST_F(SqratTest, InheritedClassBinding) {
    DefaultVM::Set(vm);

    // Defining class definitions inline
    RootTable().Bind(_SC("Animal"),
                     Class<Animal>()
                     .Func(_SC("Speak"), &Animal::Speak)
                    );

    RootTable().Bind(_SC("Cat"),
                     DerivedClass<Cat, Animal>()
                     .Func(_SC("Speak"), &Cat::Speak)
                    );

    RootTable().Bind(_SC("Dog"),
                     DerivedClass<Dog, Animal>()
                     .Func(_SC("Speak"), &Dog::Speak)
                    );

    RootTable().Func(_SC("MakeSpeak"), &MakeSpeak);

    Script script;

    try {
        script.CompileString(_SC(" \
			class Mouse extends Animal { \
				function Speak() { \
					return \"Squeak!\"; \
				} \
			} \
			\
			c <- Cat(); \
			d <- Dog(); \
			m <- Mouse(); \
			\
			gTest.EXPECT_STR_EQ(c.Speak(), \"Meow!\"); \
			gTest.EXPECT_STR_EQ(d.Speak(), \"Woof!\"); \
			gTest.EXPECT_STR_EQ(m.Speak(), \"Squeak!\"); \
			\
			gTest.EXPECT_STR_EQ(MakeSpeak(c), \"Meow!\"); \
			gTest.EXPECT_STR_EQ(MakeSpeak(d), \"Woof!\"); \
			/*gTest.EXPECT_STR_EQ(MakeSpeak(m), \"Squeak!\");*/ /* This will fail! Classes overridden in squirrel will be exposed as their base native class to C++ */ \
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

class NativeObj {
public:
    int Id() {
        return 42;
    }
};

TEST_F(SqratTest, WeakRef) {
    //
    // Ensure that weak referenceing work with Sqrat-bound classes
    // Created in response to a bug reported by emeyex
    //

    DefaultVM::Set(vm);

    // Defining class definitions inline
    RootTable().Bind(_SC("NativeObj"),
                     Class<NativeObj>()
                     .Func(_SC("Id"), &NativeObj::Id)
                    );

    Script script;

    try {
        script.CompileString(_SC(" \
			class SqObj { \
				function Id() { \
					return 3.14; \
				} \
			} \
			\
			local obj1 = SqObj(); \
			local ref1 = obj1.weakref(); \
			local obj2 = NativeObj(); \
			local ref2 = obj2.weakref(); \
			\
			gTest.EXPECT_FLOAT_EQ(3.14, ref1.ref().Id()); \
			gTest.EXPECT_INT_EQ(42, ref2.ref().Id()); \
			"));
    } catch(Exception ex) {
        FAIL() << _SC("Script Compile Failed: ") << ex.Message();
    }

    try {
        script.Run();
    } catch(Exception ex) {
        FAIL() << _SC("Script Run Failed: ") << ex.Message();
    }
}

class NumTypes 
{
public:
    int g_int() 
    {
        return 3;
    }
    double g_float() 
    {
        return 7.8;
    }
    
    bool g_true() 
    {
        return true;
    }
    
    bool g_false()
    {
        return false;
    }
    
};

static const char *num_conversions = "\
    local numtypes = NumTypes();\
    local i = numtypes.g_int();\
    local d = numtypes.g_float();\
    local t = numtypes.g_true();\
    local f = numtypes.g_false();\
	gTest.EXPECT_TRUE(i); \
	gTest.EXPECT_INT_EQ(i, 3); \
	gTest.EXPECT_FLOAT_EQ(i, 3.0); \
	gTest.EXPECT_INT_EQ(3, i); \
	gTest.EXPECT_FLOAT_EQ(3.0, i); \
    \
	gTest.EXPECT_TRUE(d); \
	gTest.EXPECT_INT_EQ(d, 7); \
	gTest.EXPECT_FLOAT_EQ(d, 7.8); \
	gTest.EXPECT_INT_EQ(7, d); \
	gTest.EXPECT_FLOAT_EQ(7.8, d); \
    \
	gTest.EXPECT_TRUE(t); \
	gTest.EXPECT_INT_EQ(t, 1); \
	gTest.EXPECT_FLOAT_EQ(t, 1.0); \
	gTest.EXPECT_INT_EQ(1, t); \
    \
	gTest.EXPECT_FALSE(f); \
	gTest.EXPECT_INT_EQ(f, 0); \
	gTest.EXPECT_FLOAT_EQ(f, 0.0); \
	gTest.EXPECT_INT_EQ(0, f); \
	gTest.EXPECT_FLOAT_EQ(0.0, f); \
    \
    ";
    
TEST_F(SqratTest, NumConversion)
{
    DefaultVM::Set(vm);
    
    Sqrat::Class<NumTypes> numtypes(vm);
    
    numtypes.Func("g_int", &NumTypes::g_int);
    numtypes.Func("g_float", &NumTypes::g_float);
    numtypes.Func("g_true", &NumTypes::g_true);
    numtypes.Func("g_false", &NumTypes::g_false);

    Sqrat::RootTable(vm).Bind("NumTypes", numtypes);
            
    Script script;
    try {
        script.CompileString(_SC(num_conversions));
    } catch(Exception ex) {
        FAIL() << _SC("Compile Failed: ") << ex.Message();
    }

    try {
        script.Run();
    } catch(Exception ex) {
        FAIL() << _SC("Run Failed: ") << ex.Message();
    }
}

class F 
{
public:
    static int bar;
};

/*
enum  foo { bar = 123 };

TEST_F(SqratTest, CEnumBinding)
{
    DefaultVM::Set(vm);
    Class<F> f_class(vm);
    int i = (int) bar;
    f_class.SetStaticValue("bar", i);
    ASSERT_TRUE(1);    
    f_class.SetStaticValue("bar", bar);
    ASSERT_TRUE(1);    
    

    RootTable().Bind(_SC("F"), f_class);

    Script script;
    

    try {
        script.CompileString(_SC(" \
			gTest.EXPECT_INT_EQ(F.bar, 123); \
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
*/ /* work in progress */