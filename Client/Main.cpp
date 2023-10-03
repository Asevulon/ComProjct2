#include<iostream>
#include"Interfaces.h"
using namespace std;

//typedef IUnknown* (*CREATEINSTANCEPROC)();


void OutListData(ICollection* IC, IEnumerator* IE)
{
	cout << "\n\nList data: \n\n";

	IE->Reset();
	UINT size = 0;
	IC->GetCount(&size);
	for (int i = 0; i < size; i++)
	{
		Object temp;
		IE->GetCurrent(&temp);
		if (temp.Type == otInt) cout << "Int: " << temp.Value.Int << endl;
		else
			if (temp.Type == otDouble)cout << "Double: " << temp.Value.Double << endl;
			else
			{
				for (int j = 0; j < temp.Value.Array->Count; j++)
				{
					if (temp.Value.Array->Data[j].Type == otInt) cout << "Int: " << temp.Value.Array->Data[j].Value.Int << endl;
					else
					if (temp.Value.Array->Data[j].Type == otDouble) cout << "Double: " << temp.Value.Array->Data[j].Value.Double << endl;

				}
			}
		int pos;
		IE->MoveNext(&pos);
	}
}

void OutArrayData(ObjectArray* OA)
{
	cout << "\n\nArray data: \n\n";
	for (int i = 0; i < OA->Count; i++)
	{
		if (OA->Data[i].Type == otInt) cout << "Int: " << OA->Data[i].Value.Int << endl;
		else
			if (OA->Data[i].Type == otDouble)cout << "Double: " << OA->Data[i].Value.Double << endl;
			else
			{
				for (int j = 0; j < OA->Data[i].Value.Array->Count; j++)
				{
					if (OA->Data[i].Value.Array->Data[j].Type == otInt) cout << "Int: " << OA->Data[i].Value.Array->Data[j].Value.Int << endl;
					else
						if (OA->Data[i].Value.Array->Data[j].Type == otDouble) cout << "Double: " << OA->Data[i].Value.Array->Data[j].Value.Double << endl;

				}
			}
	}
}

void main()
{
	HRESULT hr;
	HMODULE hMod = LoadLibrary(L"C:\\Users\\asevu\\source\\repos\\Asevulon\\ComProjct2\\x64\\Debug\\ServerDll.dll");
	CREATEINSTANCEPROC InitInstance = (CREATEINSTANCEPROC)GetProcAddress(hMod, "CreateInstance");
	IUnknown* IUnknwn = InitInstance();
	
	ICollection* IC = nullptr;
	hr = IUnknwn->QueryInterface(IID_ICollection, (void**)&IC); 
	IEnumerator* IE = nullptr;
	hr = IUnknwn->QueryInterface(IID_IEnumerator, (void**)&IE);

	Object obj;
	obj.Type = otInt;
	obj.Value.Int = 1;
	hr = IC->Add(obj);

	obj.Type = otDouble;
	obj.Value.Double = 2.5;
	hr = IC->Add(obj);

	obj.Type = otArray;
	obj.Value.Array = new ObjectArray;

	obj.Value.Array->Count = 3;
	obj.Value.Array->Data = new Object[3];

	obj.Value.Array->Data[0].Type = otInt;
	obj.Value.Array->Data[0].Value.Int = 4;

	obj.Value.Array->Data[1].Type = otInt;
	obj.Value.Array->Data[1].Value.Int = 5;

	obj.Value.Array->Data[2].Type = otInt;
	obj.Value.Array->Data[2].Value.Int = 6;

	hr = IC->Add(obj);

	delete obj.Value.Array->Data;

	OutListData(IC, IE);

	ObjectArray* OA;
	IC->ToArray(&OA);
	OutArrayData(OA);

	int pos = 0;
	IE->Reset();
	IE->MoveNext(&pos);

	IE->GetCurrent(&obj);
	IC->Remove(obj);

	IE->GetCurrent(&obj);
	IC->Remove(obj);

	OutListData(IC, IE);
	
	cout << "\n\nRefs left: " << IE->Release() << endl;
	cout << "Refs left: " << IC->Release() << endl;

	FreeLibrary(hMod);
}