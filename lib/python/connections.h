#ifndef __lib_python_connections_h
#define __lib_python_connections_h

#include <libsig_comp.h>

#include <lib/python/python.h>

class PSignal
{
protected:
	ePyObject m_list;
public:
	PSignal();
	~PSignal();
	void callPython(SWIG_PYOBJECT(ePyObject) tuple);
#ifndef SWIG
	PyObject *getSteal(bool clear=false);
#endif
	PyObject *get();
};

inline PyObject *PyFrom(int v)
{
	return PyInt_FromLong(v);
}

inline PyObject *PyFrom(const char *c)
{
	return PyString_FromString(c);
}

template <class R>
class PSignal0; //not implemented

template <>
class PSignal0<void>: public PSignal, public Signal0<void>
{
public:
	void operator()()
	{
		Signal0<void>::operator()();
		if (m_list)
		{
			PyObject *pArgs = PyTuple_New(0);
			callPython(pArgs);
			Org_Py_DECREF(pArgs);
		}
	}
};

template <class R, class V0>
class PSignal1; //not implemented

template <class V0>
class PSignal1<void, V0>: public PSignal, public Signal1<void,V0>
{
public:
	void operator()(V0 a0)
	{
		Signal1<void,V0>::operator()(a0);
		if (m_list)
		{
			PyObject *pArgs = PyTuple_New(1);
			PyTuple_SET_ITEM(pArgs, 0, PyFrom(a0));
			callPython(pArgs);
			Org_Py_DECREF(pArgs);
		}
	}
};

template <class R, class V0, class V1>
class PSignal2; //not implemented

template <class V0, class V1>
class PSignal2<void, V0, V1>: public PSignal, public Signal2<void,V0,V1>
{
public:
	void operator()(V0 a0, V1 a1)
	{
		Signal2<void,V0,V1>::operator()(a0, a1);
		if (m_list)
		{
			PyObject *pArgs = PyTuple_New(2);
			PyTuple_SET_ITEM(pArgs, 0, PyFrom(a0));
			PyTuple_SET_ITEM(pArgs, 1, PyFrom(a1));
			callPython(pArgs);
			Org_Py_DECREF(pArgs);
		}
	}
};

template <class R, class V0, class V1, class V2>
class PSignal3; //not implemented

template <class V0, class V1, class V2>
class PSignal3<void, V0, V1, V2>: public PSignal, public Signal3<void,V0,V1,V2>
{
public:
	void operator()(V0 a0, V1 a1, V2 a2)
	{
		Signal3<void,V0,V1,V2>::operator()(a0, a1, a2);
		if (m_list)
		{
			PyObject *pArgs = PyTuple_New(3);
			PyTuple_SET_ITEM(pArgs, 0, PyFrom(a0));
			PyTuple_SET_ITEM(pArgs, 1, PyFrom(a1));
			PyTuple_SET_ITEM(pArgs, 2, PyFrom(a2));
			callPython(pArgs);
			Org_Py_DECREF(pArgs);
		}
	}
};

#endif
