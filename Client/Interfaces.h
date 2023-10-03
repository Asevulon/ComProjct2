#pragma once
#include <objbase.h>

//////////////////////////////////////////////////////////////////////////
// “ип объекта

enum ObjectType
{
	// целый
	otInt,

	// вещественный
	otDouble,

	// массив
	otArray
};

//////////////////////////////////////////////////////////////////////////
// ќбъект - значение произвольного типа (предварительное объ€вление)

struct Object;

//////////////////////////////////////////////////////////////////////////
// ObjectArray - ћассив значений Object

struct ObjectArray
{
	// элементы массива
	Object *Data = nullptr;

	// количество элементов массива
	unsigned Count = 0;
};

//////////////////////////////////////////////////////////////////////////
// ќбъект - значение произвольного типа

struct Object
{
	// тип объекта
	ObjectType Type;

	union
	{
		// значение целого типа
		int Int;

		// значение вещественного типа
		double Double;

		// значение типа "массив"
		ObjectArray *Array;
	} Value;
	friend bool operator ==(Object const& lhs, Object const& rhs);
	
};

//////////////////////////////////////////////////////////////////////////
// »нтерфейс коллекции
// {37F7727A-0174-4F2B-ADE9-271B949AA229}

static const GUID IID_ICollection = 
{ 0x81fa2ea, 0xd489, 0x4ddd, { 0x84, 0x74, 0x52, 0x2b, 0xd4, 0x0, 0x3f, 0x1d } };

interface ICollection : public IUnknown
{
	// добавить элемент в коллекцию
	virtual HRESULT __stdcall Add(Object obj) = 0;

	// удалить элемент из коллекции
	virtual HRESULT __stdcall Remove(Object obj) = 0;

	// получить количество элементов коллекции
	virtual HRESULT __stdcall GetCount(unsigned *count) = 0;

	// преобразовать коллекцию в массив
	virtual HRESULT __stdcall ToArray(ObjectArray **arr) = 0;
};


//////////////////////////////////////////////////////////////////////////
// »нтерфейс перечислител€
// {7BAAB13D-AC13-484C-A1A0-132B28136425}

static const GUID IID_IEnumerator =
{ 0x579611f2, 0x5a35, 0x4f5f, { 0x86, 0x25, 0x94, 0x90, 0x65, 0x7, 0x65, 0xf5 } };

interface IEnumerator : public IUnknown
{
	// возврат в исходное состо€ние
	virtual HRESULT __stdcall Reset() = 0;

	// переход к следующему элементу
	virtual HRESULT __stdcall MoveNext(int *result) = 0;

	// получить текущий элемент
	virtual HRESULT __stdcall GetCurrent(Object *obj) = 0;
};


//////////////////////////////////////////////////////////////////////////
// “ип функции создани€ экземпл€ра компонента

typedef IUnknown* (*CREATEINSTANCEPROC)();


//////////////////////////////////////////////////////////////////////////
// Ёкспортируема€ функци€ создани€ экземпл€ра компонента

extern "C" __declspec(dllexport) IUnknown* CreateInstance();
