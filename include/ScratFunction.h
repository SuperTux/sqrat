//
// SqObject: Referenced Squirrel Object Wrapper
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

#if !defined(_SCRAT_SQFUNC_H_)
#define _SCRAT_SQFUNC_H_

#include <squirrel.h>
#include "ScratObject.h"

namespace Scrat {

	template <class R>
	class Function  {
		friend class Table;
	private:
		HSQUIRRELVM vm;
		HSQOBJECT env, obj;

		Function(HSQUIRRELVM v, HSQOBJECT e, HSQOBJECT o) : vm(v), env(e), obj(o) {
			sq_addref(vm, &env);
			sq_addref(vm, &obj);
		}

	public:
		Function() {
			sq_resetobject(&env);
			sq_resetobject(&obj);
		}

		Function(const Function& sf) : vm(sf.vm), env(sf.env), obj(sf.obj) {
			sq_addref(vm, &env);
			sq_addref(vm, &obj);
		}

		~Function() {
			Release();
		}

		Function& operator=(const Function& sf) {
			Release();
			vm = sf.vm;
			env = sf.env;
			obj = sf.obj;
			sq_addref(vm, &env);
			sq_addref(vm, &obj);
		}


		HSQOBJECT& GetEnv() {
			return env;
		}

		HSQOBJECT& GetFunc() {
			return obj;
		}

		HSQUIRRELVM& GetVM() {
			return vm;
		}

		void Release() {
			sq_release(vm, &env);
			sq_release(vm, &obj);
		}

		R operator()() {
			sq_pushobject(vm, obj);
			sq_pushobject(vm, env);

			sq_call(vm, 1, true, false);
			R ret = Var<R>(vm, -1).value;
			sq_pop(vm, 1);
			return ret;
		}

		template <class A1>
		R operator()(A1 a1) {
			sq_pushobject(vm, obj);
			sq_pushobject(vm, env);

			PushVar(vm, a1);

			sq_call(vm, 2, true, false);
			Var<R> ret(vm, -1);
			sq_pop(vm, 1);
			return ret.value;
		}

		template <class A1, class A2>
		R operator()(A1 a1, A2 a2) {
			sq_pushobject(vm, obj);
			sq_pushobject(vm, env);

			PushVar(vm, a1);
			PushVar(vm, a2);

			sq_call(vm, 3, true, false);
			R ret = Var<R>(vm, -1).value;
			sq_pop(vm, 1);
			return ret;
		}

		template <class A1, class A2, class A3>
		R operator()(A1 a1, A2 a2, A3 a3) {
			sq_pushobject(vm, obj);
			sq_pushobject(vm, env);

			PushVar(vm, a1);
			PushVar(vm, a2);
			PushVar(vm, a3);

			sq_call(vm, 4, true, false);
			R ret = Var<R>(vm, -1).value;
			sq_pop(vm, 1);
			return ret;
		}

		template <class A1, class A2, class A3, class A4>
		R operator()(A1 a1, A2 a2, A3 a3, A4 a4) {
			sq_pushobject(vm, obj);
			sq_pushobject(vm, env);

			PushVar(vm, a1);
			PushVar(vm, a2);
			PushVar(vm, a3);
			PushVar(vm, a4);

			sq_call(vm, 5, true, false);
			R ret = Var<R>(vm, -1).value;
			sq_pop(vm, 1);
			return ret;
		}

		
		template <class A1, class A2, class A3, class A4, class A5>
		R operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) {
			sq_pushobject(vm, obj);
			sq_pushobject(vm, env);

			PushVar(vm, a1);
			PushVar(vm, a2);
			PushVar(vm, a3);
			PushVar(vm, a4);
			PushVar(vm, a5);

			sq_call(vm, 6, true, false);
			R ret = Var<R>(vm, -1).value;
			sq_pop(vm, 1);
			return ret;
		}

		template <class A1, class A2, class A3, class A4, class A5, class A6>
		R operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) {
			sq_pushobject(vm, obj);
			sq_pushobject(vm, env);

			PushVar(vm, a1);
			PushVar(vm, a2);
			PushVar(vm, a3);
			PushVar(vm, a4);
			PushVar(vm, a5);
			PushVar(vm, a6);

			sq_call(vm, 7, true, false);
			R ret = Var<R>(vm, -1).value;
			sq_pop(vm, 1);
			return ret;
		}

		template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
		R operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) {
			sq_pushobject(vm, obj);
			sq_pushobject(vm, env);

			PushVar(vm, a1);
			PushVar(vm, a2);
			PushVar(vm, a3);
			PushVar(vm, a4);
			PushVar(vm, a5);
			PushVar(vm, a6);
			PushVar(vm, a7);

			sq_call(vm, 8, true, false);
			R ret = Var<R>(vm, -1).value;
			sq_pop(vm, 1);
			return ret;
		}

		template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
		R operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) {
			sq_pushobject(vm, obj);
			sq_pushobject(vm, env);

			PushVar(vm, a1);
			PushVar(vm, a2);
			PushVar(vm, a3);
			PushVar(vm, a4);
			PushVar(vm, a5);
			PushVar(vm, a6);
			PushVar(vm, a7);
			PushVar(vm, a8);

			sq_call(vm, 9, true, false);
			R ret = Var<R>(vm, -1).value;
			sq_pop(vm, 1);
			return ret;
		}

		template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
		R operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) {
			sq_pushobject(vm, obj);
			sq_pushobject(vm, env);

			PushVar(vm, a1);
			PushVar(vm, a2);
			PushVar(vm, a3);
			PushVar(vm, a4);
			PushVar(vm, a5);
			PushVar(vm, a6);
			PushVar(vm, a7);
			PushVar(vm, a8);
			PushVar(vm, a9);

			sq_call(vm, 10, true, false);
			R ret = Var<R>(vm, -1).value;
			sq_pop(vm, 1);
			return ret;
		}
	};

	template <>
	class Function<void>  {
	private:
		HSQUIRRELVM vm;
		HSQOBJECT env, obj;

	public:
		Function() {
			sq_resetobject(&env);
			sq_resetobject(&obj);
		}

		Function(const Function& sf) : vm(sf.vm), env(sf.env), obj(sf.obj) {
			sq_addref(vm, &env);
			sq_addref(vm, &obj);
		}

		Function(HSQUIRRELVM v, HSQOBJECT e, HSQOBJECT o) : vm(v), env(e), obj(o) {
			sq_addref(vm, &env);
			sq_addref(vm, &obj);
		}

		Function(const Object& e, const SQChar* slot) : vm(e.GetVM()), env(e.GetObject()) {
			sq_addref(vm, &env);
			Object so = e.GetSlot(slot);
			obj = so.GetObject();
			sq_addref(vm, &obj);
		}

		~Function() {
			Release();
		}

		Function& operator=(const Function& sf) {
			Release();
			vm = sf.vm;
			env = sf.env;
			obj = sf.obj;
			sq_addref(vm, &env);
			sq_addref(vm, &obj);
			return *this;
		}


		HSQOBJECT& GetEnv() {
			return env;
		}

		HSQOBJECT& GetFunc() {
			return obj;
		}

		HSQUIRRELVM& GetVM() {
			return vm;
		}

		void Release() {
			sq_release(vm, &env);
			sq_release(vm, &obj);
		}

		void operator()() {
			sq_pushobject(vm, obj);
			sq_pushobject(vm, env);

			sq_call(vm, 1, false, false);
		}

		template <class A1>
		void operator()(A1 a1) {
			sq_pushobject(vm, obj);
			sq_pushobject(vm, env);

			PushVar(vm, a1);

			sq_call(vm, 2, false, false);
		}

		template <class A1, class A2>
		void operator()(A1 a1, A2 a2) {
			sq_pushobject(vm, obj);
			sq_pushobject(vm, env);

			PushVar(vm, a1);
			PushVar(vm, a2);

			sq_call(vm, 3, false, false);
		}

		template <class A1, class A2, class A3>
		void operator()(A1 a1, A2 a2, A3 a3) {
			sq_pushobject(vm, obj);
			sq_pushobject(vm, env);

			PushVar(vm, a1);
			PushVar(vm, a2);
			PushVar(vm, a3);

			sq_call(vm, 4, false, false);
		}

		template <class A1, class A2, class A3, class A4>
		void operator()(A1 a1, A2 a2, A3 a3, A4 a4) {
			sq_pushobject(vm, obj);
			sq_pushobject(vm, env);

			PushVar(vm, a1);
			PushVar(vm, a2);
			PushVar(vm, a3);
			PushVar(vm, a4);

			sq_call(vm, 5, false, false);
		}

		
		template <class A1, class A2, class A3, class A4, class A5>
		void operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) {
			sq_pushobject(vm, obj);
			sq_pushobject(vm, env);

			PushVar(vm, a1);
			PushVar(vm, a2);
			PushVar(vm, a3);
			PushVar(vm, a4);
			PushVar(vm, a5);

			sq_call(vm, 6, false, false);
		}

		template <class A1, class A2, class A3, class A4, class A5, class A6>
		void operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) {
			sq_pushobject(vm, obj);
			sq_pushobject(vm, env);

			PushVar(vm, a1);
			PushVar(vm, a2);
			PushVar(vm, a3);
			PushVar(vm, a4);
			PushVar(vm, a5);
			PushVar(vm, a6);

			sq_call(vm, 7, false, false);
		}

		template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
		void operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) {
			sq_pushobject(vm, obj);
			sq_pushobject(vm, env);

			PushVar(vm, a1);
			PushVar(vm, a2);
			PushVar(vm, a3);
			PushVar(vm, a4);
			PushVar(vm, a5);
			PushVar(vm, a6);
			PushVar(vm, a7);

			sq_call(vm, 8, false, false);
		}

		template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
		void operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) {
			sq_pushobject(vm, obj);
			sq_pushobject(vm, env);

			PushVar(vm, a1);
			PushVar(vm, a2);
			PushVar(vm, a3);
			PushVar(vm, a4);
			PushVar(vm, a5);
			PushVar(vm, a6);
			PushVar(vm, a7);
			PushVar(vm, a8);

			sq_call(vm, 9, false, false);
		}

		template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
		void operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) {
			sq_pushobject(vm, obj);
			sq_pushobject(vm, env);

			PushVar(vm, a1);
			PushVar(vm, a2);
			PushVar(vm, a3);
			PushVar(vm, a4);
			PushVar(vm, a5);
			PushVar(vm, a6);
			PushVar(vm, a7);
			PushVar(vm, a8);
			PushVar(vm, a9);

			sq_call(vm, 10, false, false);
		}
	};
}

#endif
