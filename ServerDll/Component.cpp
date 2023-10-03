#include"Component.h"

#include<algorithm>
using namespace std;

// Ìועמהû ICollection
HRESULT __stdcall CList::Add(Object obj)
{
	if (obj.Type != otArray)m_l.push_back(obj);
	else
	{
		Object temp = { };
		temp.Type = otArray;
		temp.Value.Array = new ObjectArray;
		temp.Value.Array->Count = obj.Value.Array->Count;
		temp.Value.Array->Data = new Object[temp.Value.Array->Count];
		for (int i = 0; i < temp.Value.Array->Count; i++)
		{
			temp.Value.Array->Data[i] = obj.Value.Array->Data[i];
		}
		m_l.push_back(temp);
	}
	return S_OK;
}

bool operator==(Object const& left, Object const& right)
{
	if (left.Type != right.Type)return false;
	if (left.Type == otInt)if (left.Value.Int != right.Value.Int)return false;
	if (left.Type == otDouble)if (left.Value.Double != right.Value.Double)return false;
	if (left.Type == otArray)if (left.Value.Array != right.Value.Array)return false;
	return true;
}
HRESULT __stdcall CList::Remove(Object obj)
{
	m_l.remove(obj);
	if (obj.Type == ObjectType::otArray)
	{
		delete obj.Value.Array->Data;
		delete obj.Value.Array;
	}
	return S_OK;
}
HRESULT __stdcall CList::GetCount(unsigned* count)
{
	*count = m_l.size();
	return S_OK;
}
HRESULT __stdcall CList::ToArray(ObjectArray** arr)
{
	//ObjectArray* arr = nullptr; ToArray(&arr);
	if (m_l.empty())return S_FALSE;

	(*arr) = new ObjectArray;
	(*arr)->Count = m_l.size();
	(*arr)->Data = new Object[(*arr)->Count];

	int i = 0;
	for (auto& iter : m_l)
	{
		(*arr)->Data[i] = iter;
		i++;
	}
	return S_OK;
}


// Ìועמהû IEnumerator
HRESULT __stdcall CList::Reset()
{

	m_Enumerator = 0;
	return S_OK;
}
HRESULT __stdcall CList::MoveNext(int* result)
{
	if (m_Enumerator >= m_l.size() - 1)
	{
		*result = m_Enumerator;
		return S_FALSE;
	}
	m_Enumerator++;
	*result = m_Enumerator;
	return S_OK;
}
HRESULT __stdcall CList::GetCurrent(Object* obj)
{
	if (m_l.empty())return S_FALSE;

	int i = 0;
	for (auto& iter : m_l)
	{
		if (i == m_Enumerator)
		{
			*obj = iter;
			break;
		}
		i++;
	}
	return S_OK;
}


// Ìועמהû IUnknown
HRESULT __stdcall CList::QueryInterface(REFIID iid, void** ppv)
{
	if (iid == IID_ICollection)
	{
		AddRef();
		*ppv = (ICollection*)this;
		return S_OK;
	}
	if (iid == IID_IEnumerator)
	{
		AddRef();
		*ppv = (IEnumerator*)this;
		return S_OK;
	}
	if (iid == IID_IUnknown)
	{
		return E_NOINTERFACE;
	}
	return E_UNEXPECTED;
}
ULONG __stdcall CList::AddRef()
{
	m_cRef++;
	return m_cRef;
}
ULONG __stdcall CList::Release()
{
	m_cRef--;
	if(m_cRef > 0) return m_cRef;

	for (auto& iter : m_l)
	{
		if (iter.Type == otArray)
		{
			delete iter.Value.Array->Data;
			delete iter.Value.Array;
		}
	}
	delete this;
	return 0;
}



extern "C" __declspec(dllexport) IUnknown * CreateInstance()
{
	IUnknown* pCList = static_cast<ICollection*>(new CList);
	return pCList;
}