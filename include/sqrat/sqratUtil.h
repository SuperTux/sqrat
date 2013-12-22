//
// SqratUtil: Squirrel Utilities
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

#if !defined(_SCRAT_UTIL_H_)
#define _SCRAT_UTIL_H_

#include <cassert>
#include <squirrel.h>
#include <string.h>


namespace Sqrat {

typedef std::basic_string<SQChar> string;

#ifdef SQUNICODE

/* from http://stackoverflow.com/questions/15333259/c-stdwstring-to-stdstring-quick-and-dirty-conversion-for-use-as-key-in,
   only works for ASCII chars */
/**
* Convert a std::string into a std::wstring
*/
static std::wstring ascii_string_to_wstring(const std::string& str)
{
    return std::wstring(str.begin(), str.end());
}

/**
* Convert a std::wstring into a std::string
*/
static std::string ascii_wstring_to_string(const std::wstring& wstr)
{
    return std::string(wstr.begin(), wstr.end());
}

static std::wstring (*string_to_wstring)(const std::string& str) = ascii_string_to_wstring;
static std::string (*wstring_to_string)(const std::wstring& wstr) = ascii_wstring_to_string;
#endif // SQUNICODE


class DefaultVM {
private:
    static HSQUIRRELVM& staticVm() {
        static HSQUIRRELVM vm;
        return vm;
    }
public:
    static HSQUIRRELVM Get() {
        return staticVm();
    }
    static void Set(HSQUIRRELVM vm) {
        staticVm() = vm;
    }
};

#if !defined (SCRAT_NO_ERROR_CHECKING)
class Error {
public:
    static Error& Instance() {
        static Error instance;
        return instance;
    }
    static string FormatTypeError(HSQUIRRELVM vm, SQInteger idx, const string& expectedType) {
        string err = _SC("wrong type (") + expectedType + _SC(" expected");
        if (SQ_SUCCEEDED(sq_typeof(vm, idx))) {
            const SQChar* actualType;
            sq_tostring(vm, -1);
            sq_getstring(vm, -1, &actualType);
            sq_pop(vm, 1);
            err = err + _SC(", got ") + actualType + _SC(")");
        } else {
            err = err + _SC(", got unknown)");
        }
        sq_pop(vm, 1);
        return err;
    }
    void Clear(HSQUIRRELVM vm) {
        //TODO: use mutex to lock errMap in multithreaded environment
        errMap.erase(vm);
    }
    string Message(HSQUIRRELVM vm) {
        //TODO: use mutex to lock errMap in multithreaded environment
        string err = errMap[vm];
        errMap.erase(vm);
        return err;
    }
    bool Occurred(HSQUIRRELVM vm) {
        //TODO: use mutex to lock errMap in multithreaded environment
        return errMap.find(vm) != errMap.end();
    }
    void Throw(HSQUIRRELVM vm, const string& err) {
        //TODO: use mutex to lock errMap in multithreaded environment
        if (errMap.find(vm) == errMap.end()) {
            errMap[vm] = err;
        }
    }

private:
    Error() {}

    std::map< HSQUIRRELVM, string > errMap;
};
#endif

class ErrorHandling {
private:
    static bool& errorHandling() {
        static bool eh = true;
        return eh;
    }
public:
    static bool IsEnabled() {
        return errorHandling();
    }
    static void Enable(bool enable) {
        errorHandling() = enable;
    }
};

inline string LastErrorString( HSQUIRRELVM vm ) {
    const SQChar* sqErr;
    sq_getlasterror(vm);
    if(sq_gettype(vm, -1) == OT_NULL) {
        return string();
    }
    sq_tostring(vm, -1);
    sq_getstring(vm, -1, &sqErr);
    return string(sqErr);
}

template <class T>
class SharedPtr
{
private:
    T*            m_Ptr;
    unsigned int* m_RefCount;
public:
    SharedPtr() :
    m_Ptr     (NULL),
    m_RefCount(NULL)
    {

    }
    SharedPtr(T* ptr)
    {
        Init(ptr);
    }
    template <class U>
    SharedPtr(U* ptr)
    {
        Init(ptr);
    }
    SharedPtr(const SharedPtr<T>& copy)
    {
        if (copy.Get() != NULL)
        {
            m_Ptr = copy.Get();

            m_RefCount = copy.m_RefCount;
            *m_RefCount += 1;
        }
        else
        {
            m_Ptr      = NULL;
            m_RefCount = NULL;
        }
    }
    template <class U>
    SharedPtr(const SharedPtr<U>& copy)
    {
        if (copy.Get() != NULL)
        {
            m_Ptr = static_cast<T*>(copy.Get());

            m_RefCount = copy.m_RefCount;
            *m_RefCount += 1;
        }
        else
        {
            m_Ptr      = NULL;
            m_RefCount = NULL;
        }
    }
    ~SharedPtr()
    {
        Reset();
    }
    SharedPtr<T>& operator=(const SharedPtr<T>& copy)
    {
        if (this != &copy)
        {
            Reset();

            if (copy.Get() != NULL)
            {
                m_Ptr = copy.Get();

                m_RefCount = copy.m_RefCount;
                *m_RefCount += 1;
            }
            else
            {
                m_Ptr      = NULL;
                m_RefCount = NULL;
            }
        }

        return *this;
    }
    template <class U>
    SharedPtr<T>& operator=(const SharedPtr<U>& copy)
    {
        Reset();

        if (copy.Get() != NULL)
        {
            m_Ptr = static_cast<T*>(copy.Get());

            m_RefCount = copy.m_RefCount;
            *m_RefCount += 1;
        }
        else
        {
            m_Ptr      = NULL;
            m_RefCount = NULL;
        }

        return *this;
    }
    void Init(T* ptr)
    {
        Reset();

        m_Ptr = ptr;

        m_RefCount = new unsigned int;
        *m_RefCount = 1;
    }
    template <class U>
    void Init(U* ptr)
    {
        Reset();

        m_Ptr = static_cast<T*>(ptr);

        m_RefCount = new unsigned int;
        *m_RefCount = 1;
    }
    void Reset()
    {
        if (m_Ptr != NULL)
        {
            if (*m_RefCount == 1)
            {
                delete m_Ptr;
                delete m_RefCount;

                m_Ptr      = NULL;
                m_RefCount = NULL;
            }
            else
                *m_RefCount -= 1;
        }
    }
    operator bool() const
    {
        return m_Ptr != NULL;
    }
    bool operator!() const
    {
        return m_Ptr == NULL;
    }
    template <typename U>
    bool operator ==(const SharedPtr<U>& right) const
    {
        return m_Ptr == right.m_Ptr;
    }
    bool operator ==(const SharedPtr<T>& right) const
    {
        return m_Ptr == right.m_Ptr;
    }
    template <typename U>
    bool friend operator ==(const SharedPtr<T>& left, const U* right)
    {
        return left.m_Ptr == right;
    }
    bool friend operator ==(const SharedPtr<T>& left, const T* right)
    {
        return left.m_Ptr == right;
    }
    template <typename U>
    bool friend operator ==(const U* left, const SharedPtr<T>& right)
    {
        return left == right.m_Ptr;
    }
    bool friend operator ==(const T* left, const SharedPtr<T>& right)
    {
        return left == right.m_Ptr;
    }
    template <typename U>
    bool operator !=(const SharedPtr<U>& right) const
    {
        return m_Ptr != right.m_Ptr;
    }
    bool operator !=(const SharedPtr<T>& right) const
    {
        return m_Ptr != right.m_Ptr;
    }
    template <typename U>
    bool friend operator !=(const SharedPtr<T>& left, const U* right)
    {
        return left.m_Ptr != right;
    }
    bool friend operator !=(const SharedPtr<T>& left, const T* right)
    {
        return left.m_Ptr != right;
    }
    template <typename U>
    bool friend operator !=(const U* left, const SharedPtr<T>& right)
    {
        return left != right.m_Ptr;
    }
    bool friend operator !=(const T* left, const SharedPtr<T>& right)
    {
        return left != right.m_Ptr;
    }
    T& operator*() const
    {
        assert(m_Ptr != NULL);
        return *m_Ptr;
    }
    T* operator->() const
    {
        assert(m_Ptr != NULL);
        return m_Ptr;
    }
    T* Get() const
    {
        return m_Ptr;
    }
};

}

#endif
