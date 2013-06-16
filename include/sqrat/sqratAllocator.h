//
// SqratAllocator: Custom Class Allocation/Deallocation
//

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

#if !defined(_SCRAT_ALLOCATOR_H_)
#define _SCRAT_ALLOCATOR_H_

#include <squirrel.h>
#include <string.h>

#include "sqratObject.h"
#include "sqratTypes.h"

namespace Sqrat {

//
// DefaultAllocator
//

template<class C>
class DefaultAllocator {

    static SQInteger setInstance(HSQUIRRELVM vm, C* instance)
    {
        sq_setinstanceup(vm, 1, instance);
        sq_setreleasehook(vm, 1, &Delete);
        return 0;
    }
    
public:
    
    static SQInteger New(HSQUIRRELVM vm) {
        C* instance = new C();
        setInstance(vm, instance);
        return 0;
    }

    template <int count>
    static SQInteger iNew(HSQUIRRELVM vm) {
        return New(vm);
    }
    
   // following New functions are used only if constructors are bound via Ctor() in class    

    template <typename A1>
    static SQInteger iNew(HSQUIRRELVM vm) {
        return setInstance(vm, new C(
            Var<A1>(vm, 2).value
            ));
    }
    template <typename A1,typename A2>
    static SQInteger iNew(HSQUIRRELVM vm) {
        return setInstance(vm, new C(
            Var<A1>(vm, 2).value,
            Var<A2>(vm, 3).value
            ));
    }
    template <typename A1,typename A2,typename A3>
    static SQInteger iNew(HSQUIRRELVM vm) {
        return setInstance(vm, new C(
            Var<A1>(vm, 2).value,
            Var<A2>(vm, 3).value,
            Var<A3>(vm, 4).value
            ));
    }
    template <typename A1,typename A2,typename A3,typename A4>
    static SQInteger iNew(HSQUIRRELVM vm) {
        return setInstance(vm, new C(
            Var<A1>(vm, 2).value,
            Var<A2>(vm, 3).value,
            Var<A3>(vm, 4).value,
            Var<A4>(vm, 5).value
            ));
    }
    template <typename A1,typename A2,typename A3,typename A4,typename A5>
    static SQInteger iNew(HSQUIRRELVM vm) {
        return setInstance(vm, new C(
            Var<A1>(vm, 2).value,
            Var<A2>(vm, 3).value,
            Var<A3>(vm, 4).value,
            Var<A4>(vm, 5).value,
            Var<A5>(vm, 6).value
            ));
    }
    template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
    static SQInteger iNew(HSQUIRRELVM vm) {
        return setInstance(vm, new C(
            Var<A1>(vm, 2).value,
            Var<A2>(vm, 3).value,
            Var<A3>(vm, 4).value,
            Var<A4>(vm, 5).value,
            Var<A5>(vm, 6).value,
            Var<A6>(vm, 7).value
            ));
    }
    template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7>
    static SQInteger iNew(HSQUIRRELVM vm) {
        return setInstance(vm, new C(
            Var<A1>(vm, 2).value,
            Var<A2>(vm, 3).value,
            Var<A3>(vm, 4).value,
            Var<A4>(vm, 5).value,
            Var<A5>(vm, 6).value,
            Var<A6>(vm, 7).value,
            Var<A7>(vm, 8).value
            ));
    }
    template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8>
    static SQInteger iNew(HSQUIRRELVM vm) {
        return setInstance(vm, new C(
            Var<A1>(vm, 2).value,
            Var<A2>(vm, 3).value,
            Var<A3>(vm, 4).value,
            Var<A4>(vm, 5).value,
            Var<A5>(vm, 6).value,
            Var<A6>(vm, 7).value,
            Var<A7>(vm, 8).value,
            Var<A8>(vm, 9).value
            ));
    }
    template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9>
    static SQInteger iNew(HSQUIRRELVM vm) {
        return setInstance(vm, new C(
            Var<A1>(vm, 2).value,
            Var<A2>(vm, 3).value,
            Var<A3>(vm, 4).value,
            Var<A4>(vm, 5).value,
            Var<A5>(vm, 6).value,
            Var<A6>(vm, 7).value,
            Var<A7>(vm, 8).value,
            Var<A8>(vm, 9).value,
            Var<A9>(vm, 10).value
            ));
    }

public:
    
    static SQInteger Copy(HSQUIRRELVM vm, SQInteger idx, const void* value) {
        C* instance = new C(*static_cast<const C*>(value));
        sq_setinstanceup(vm, idx, instance);
        sq_setreleasehook(vm, idx, &Delete);
        return 0;
    }

    static SQInteger Delete(SQUserPointer ptr, SQInteger size) {
        C* instance = reinterpret_cast<C*>(ptr);
        delete instance;
        return 0;
    }
};

//
// NoConstructorAllocator
//

class NoConstructor {
public:
    static SQInteger New(HSQUIRRELVM) {
        return 0;
    }
    static SQInteger Copy(HSQUIRRELVM, SQInteger, const void*) {
        return 0;
    }
    static SQInteger Delete(SQUserPointer, SQInteger) {
        return 0;
    }
};

//
// CopyOnly
//

template<class C>
class CopyOnly {
public:
    static SQInteger New(HSQUIRRELVM) {
        return 0;
    }
    static SQInteger Copy(HSQUIRRELVM vm, SQInteger idx, const void* value) {
        C* instance = new C(*static_cast<const C*>(value));
        sq_setinstanceup(vm, idx, instance);
        sq_setreleasehook(vm, idx, &Delete);
        return 0;
    }
    static SQInteger Delete(SQUserPointer ptr, SQInteger size) {
        C* instance = reinterpret_cast<C*>(ptr);
        delete instance;
        return 0;
    }
};


//
// NoCopy
//

template<class C>
class NoCopy {
public:
    static SQInteger New(HSQUIRRELVM vm) {
        C* instance = new C();
        sq_setinstanceup(vm, 1, instance);
        sq_setreleasehook(vm, 1, &Delete);
        return 0;
    }

    static SQInteger Copy(HSQUIRRELVM vm, SQInteger idx, const void* value) {
        return 0;
    }

    static SQInteger Delete(SQUserPointer ptr, SQInteger size) {
        C* instance = reinterpret_cast<C*>(ptr);
        delete instance;
        return 0;
    }
};

}

#endif
