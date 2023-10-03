#pragma once
#include <objbase.h>

//////////////////////////////////////////////////////////////////////////
// ��� �������

enum ObjectType
{
	// �����
	otInt,

	// ������������
	otDouble,

	// ������
	otArray
};

//////////////////////////////////////////////////////////////////////////
// ������ - �������� ������������� ���� (��������������� ����������)

struct Object;

//////////////////////////////////////////////////////////////////////////
// ObjectArray - ������ �������� Object

struct ObjectArray
{
	// �������� �������
	Object *Data = nullptr;

	// ���������� ��������� �������
	unsigned Count = 0;
};

//////////////////////////////////////////////////////////////////////////
// ������ - �������� ������������� ����

struct Object
{
	// ��� �������
	ObjectType Type;

	union
	{
		// �������� ������ ����
		int Int;

		// �������� ������������� ����
		double Double;

		// �������� ���� "������"
		ObjectArray *Array;
	} Value;
	friend bool operator ==(Object const& lhs, Object const& rhs);
	
};

//////////////////////////////////////////////////////////////////////////
// ��������� ���������
// {37F7727A-0174-4F2B-ADE9-271B949AA229}

static const GUID IID_ICollection = 
{ 0x81fa2ea, 0xd489, 0x4ddd, { 0x84, 0x74, 0x52, 0x2b, 0xd4, 0x0, 0x3f, 0x1d } };

interface ICollection : public IUnknown
{
	// �������� ������� � ���������
	virtual HRESULT __stdcall Add(Object obj) = 0;

	// ������� ������� �� ���������
	virtual HRESULT __stdcall Remove(Object obj) = 0;

	// �������� ���������� ��������� ���������
	virtual HRESULT __stdcall GetCount(unsigned *count) = 0;

	// ������������� ��������� � ������
	virtual HRESULT __stdcall ToArray(ObjectArray **arr) = 0;
};


//////////////////////////////////////////////////////////////////////////
// ��������� �������������
// {7BAAB13D-AC13-484C-A1A0-132B28136425}

static const GUID IID_IEnumerator =
{ 0x579611f2, 0x5a35, 0x4f5f, { 0x86, 0x25, 0x94, 0x90, 0x65, 0x7, 0x65, 0xf5 } };

interface IEnumerator : public IUnknown
{
	// ������� � �������� ���������
	virtual HRESULT __stdcall Reset() = 0;

	// ������� � ���������� ��������
	virtual HRESULT __stdcall MoveNext(int *result) = 0;

	// �������� ������� �������
	virtual HRESULT __stdcall GetCurrent(Object *obj) = 0;
};


//////////////////////////////////////////////////////////////////////////
// ��� ������� �������� ���������� ����������

typedef IUnknown* (*CREATEINSTANCEPROC)();


//////////////////////////////////////////////////////////////////////////
// �������������� ������� �������� ���������� ����������

extern "C" __declspec(dllexport) IUnknown* CreateInstance();
