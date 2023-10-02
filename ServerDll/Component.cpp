#include"Component.h"



HRESULT __stdcall CList::Add(Object obj)
{
	if (counter == 0)
	{
		first = new Node;
		first->obj = obj;
	}
	else
	{
		Node* cur = first;
		for (int i = 0; i < counter; i++)
		{
			cur = cur->next;
		}
		cur->next = new Node;
		cur->next->obj = obj;
	}
}
HRESULT __stdcall CList::Remove(Object obj)
{

}
HRESULT __stdcall CList::GetCount(unsigned* count)
{

}
HRESULT __stdcall CList::ToArray(ObjectArray** arr)
{

}