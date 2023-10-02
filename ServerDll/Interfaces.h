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
	Object *Data;

	// количество элементов массива
	unsigned Count;
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
};

//////////////////////////////////////////////////////////////////////////
// »нтерфейс коллекции
// {37F7727A-0174-4F2B-ADE9-271B949AA229}

static const GUID IID_ICollection = 
{ 0x37f7727a, 0x174, 0x4f2b, { 0xad, 0xe9, 0x27, 0x1b, 0x94, 0x9a, 0xa2, 0x29 } };

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
{ 0x7baab13d, 0xac13, 0x484c, { 0xa1, 0xa0, 0x13, 0x2b, 0x28, 0x13, 0x64, 0x25 } };

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
