#include"Component.h"

#include<algorithm>
using namespace std;

// Ìועמהû ICollection
Object* OnAddArray(Object* data)
{
	Object* out = new Object;
	out->Type = otArray;
	out->Value.Array = new ObjectArray;
	out->Value.Array->Count = data->Value.Array->Count;
	out->Value.Array->Data = new Object[data->Value.Array->Count];

	for (int i = 0; i < data->Value.Array->Count; i++)
	{
		if (data->Value.Array->Data[i].Type == otArray)out->Value.Array->Data[i] = *OnAddArray(&data->Value.Array->Data[i]);
		else
			out->Value.Array->Data[i] = data->Value.Array->Data[i];
	}

	return out;
}
HRESULT __stdcall CList::Add(Object obj)
{
	if (obj.Type != otArray)m_l.push_back(obj);
	else
	{
		Object* temp = OnAddArray(&obj);

		m_l.push_back(*temp);
	}
	return S_OK;
}

bool CompareArrays(ObjectArray* left, ObjectArray* right)
{
	if (left->Count != right->Count)return false;
	for (int i = 0; i < left->Count; i++)
	{
		if (!(left->Data[i] == right->Data[i]))return false;
	}
	return true;
}
bool operator==(Object const& left, Object const& right)
{
	if (left.Type != right.Type)return false;
	if (left.Type == otInt)if (left.Value.Int != right.Value.Int)return false;
	if (left.Type == otDouble)if (left.Value.Double != right.Value.Double)return false;
	if (left.Type == otArray)if (!CompareArrays(left.Value.Array, right.Value.Array))return false;
	return true;
}

void DeleteNestedArray(ObjectArray* data)
{
	
	int size = data->Count;
	for (int i = 0; i < size; i++)
	{
		if (data->Data[i].Type == otArray)DeleteNestedArray(data->Data[i].Value.Array);
	}
	delete data;
}
HRESULT __stdcall CList::Remove(Object obj)
{

	m_l.remove(obj);
	if (obj.Type == ObjectType::otArray)
	{
		DeleteNestedArray(obj.Value.Array);
	}
	if (m_Enumerator > m_l.size())CList::Reset();
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
	m_Iterator = m_l.begin();
	return S_OK;
}
HRESULT __stdcall CList::MoveNext(int* result)
{
	if (m_Enumerator >= m_l.size() - 1)
	{
		*result = 0;
		return S_FALSE;
	}
	m_Enumerator++;
	m_Iterator++;
	*result = 1;
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