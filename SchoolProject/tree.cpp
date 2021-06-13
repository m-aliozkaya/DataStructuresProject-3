
#include "tree.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>

// A�ac� olu�turan methot. LoadTree() metodunu kullanarak .txt dosyas�ndan verileri okur ve a�ac� olu�turur.
void StudentTree::CreateTree(string path)
{
	root = NULL;
	filePath = path;
	nodeSize = 0;
	LoadTree();
}

// .txt dosyas�ndan ��renciyi okur ve addNode() metodunu kullanarak a�aca bu ��renciyi ekler.
void StudentTree::LoadTree()
{
	ifstream fileReader(filePath);

	string line = "";
	if (fileReader.is_open())
	{
		while (getline(fileReader, line)) {

			int numberIndex = 0;
			int nameIndex = line.find("\t") + 1;
			int surNameIndex = line.find_last_of(" ", line.length() - 3) + 1;

			StudentNode* addedNode = new StudentNode;
			addedNode->name = line.substr(nameIndex, surNameIndex - nameIndex - 1);
			addedNode->surName = line.substr(surNameIndex);;
			addedNode->number = line.substr(numberIndex, nameIndex - numberIndex - 1);
			AddNode(addedNode);
		}
		fileReader.close();
	}
	else {
		cout << "FileReader A��lamname�" << endl;
	}
}

// Kendisine verilen ��renciyi a�aca ekler.
void StudentTree::AddNode(StudentNode* addedStudent)
{
	StudentNode* rootPtr = root;
	int result;
	bool isAdded = false;
	addedStudent->rightNode = NULL;
	addedStudent->leftNode = NULL;
	if (root == NULL)
	{
		root = addedStudent;
		nodeSize++;
		return;
	}
	while ((rootPtr != NULL) && (!isAdded))
	{
		result = strcmp(addedStudent->number.c_str(), rootPtr->number.c_str());
		if (result < 0)
		{
			if (rootPtr->leftNode != NULL)
			{
				rootPtr = rootPtr->leftNode;
			}
			else
			{
				rootPtr->leftNode = addedStudent;
				isAdded = true;
			}
		}
		else if (result > 0)
		{
			if (rootPtr->rightNode != NULL)
			{
				rootPtr = rootPtr->rightNode;
			}
			else
			{
				rootPtr->rightNode = addedStudent;
				isAdded = true;
			}
		}
		else
		{
			std::cout << "A�a� veri yap�s�na ayn� veri eklenemez.";
		}
		if (isAdded)
		{
			nodeSize++;
		}
	}
}

// ��rencilerin nas�l listelenece�ini se�tirir. Ona g�re InOrdered, PreOrdered veya PostOrdered �ekilde ��rencileri ekrana yazd�r�r. 
void StudentTree::ListStudents() {
	int selection = 0;;
	cout << "Nasil Listelemek Istersiniz?" << endl;
	cout << "1- InOrdered" << endl;
	cout << "2- PreOrdered" << endl;
	cout << "3- PostOrdered" << endl;
	cin >> selection;

	switch (selection)
	{
	case 1: ListInOrdered(root);
		break;
	case 2: ListPreOrdered(root);
		break;
	case 3: ListPostOrdered(root);
		break;
	default:
		cout << "Yanlis secim yaptiniz! Varsayilan olarak InOrdered siralaniyor..." << endl << endl;
		ListInOrdered(root);
		break;
	}

}

// In Order ile ��rencileri ekrana yazd�r�r.
void StudentTree::ListInOrdered(StudentNode* root)
{
	if (root)
	{
		ListInOrdered(root->leftNode);
		cout << root->number << " " << root->name << " " << root->surName << endl;
		ListInOrdered(root->rightNode);
	}
}

// Pre Order ile ��rencileri ekrana yazd�r�r.
void StudentTree::ListPreOrdered(StudentNode* root)
{
	if (root)
	{
		cout << root->number << " " << root->name << " " << root->surName << endl;
		ListPreOrdered(root->leftNode);
		ListPreOrdered(root->rightNode);
	}
}

// Post Order ile ��rencileri ekrana yazd�r�r.
void StudentTree::ListPostOrdered(StudentNode* root)
{
	if (root)
	{
		ListPostOrdered(root->leftNode);
		ListPostOrdered(root->rightNode);
		cout << root->number << " " << root->name << " " << root->surName << endl;
	}
}

// Kendisine verilen ��renci numaras�na g�re bulur ve ��renciyi a�a�tan DeleteNode() methodu ile siler.
void StudentTree::DeleteStudent()
{
	string number;
	cout << "Silinecek ogrencinin numarasini giriniz." << endl;
	cin >> number;

	StudentNode* rootPtr = root, * upper = NULL;
	bool bulundu = false;
	char direction = 'k';
	while (rootPtr && !bulundu)
	{
		int result = strcmp(number.c_str(), rootPtr->number.c_str());
		if (result < 0)
		{
			upper = rootPtr;
			direction = 'l';
			rootPtr = rootPtr->leftNode;
		}
		else if (result > 0)
		{
			upper = rootPtr;
			direction = 'r';
			rootPtr = rootPtr->rightNode;
		}
		else
			bulundu = true;
		if (bulundu)
		{
			if (direction == 'l')
			{
				DeleteNode(&upper->leftNode);
			}
			else if (direction == 'r')
			{
				DeleteNode(&upper->rightNode);
			}
			else
				cout << "Silinecek kayit bulunamadi\n";
		}
	}
}

// Kendisine verilen node' u a�a� yap�s�ndan siler. 
void StudentTree::DeleteNode(StudentNode** deletedNode)
{
	StudentNode* deletedNodePtr = *deletedNode, * q;
	if (deletedNodePtr == NULL)
	{
		*deletedNode = deletedNodePtr->leftNode;
		delete deletedNodePtr;
	}
	else if (deletedNodePtr->leftNode == NULL)
	{
		*deletedNode = deletedNodePtr->rightNode;
		delete deletedNodePtr;
	}
	else
	{
		for (q = deletedNodePtr->rightNode; q->leftNode; q = q->leftNode);
		q->leftNode = deletedNodePtr->leftNode;
		*deletedNode = deletedNodePtr->rightNode;
		delete deletedNodePtr;
	}
}

// ��rencinin numaras�n� al�r ve nas�l bir arama yap�lmak istedi�i se�tirilir. �lk geni�lik veya ilk derinlik ile arama yap�l�r.
void StudentTree::SearchStudent() {
	string studentNumber;

	cout << "Ogrenci numarasini giriniz" << endl;
	cin >> studentNumber;

	int selection = 0;;
	cout << "Nasil Aramak Istersiniz?" << endl;
	cout << "1- Ilk Derinlik Ara" << endl;
	cout << "2- Ilk Genislik Ara" << endl;
	cin >> selection;

	switch (selection)
	{
	case 1: SearchDepthFirst(studentNumber);
		break;
	case 2: SearchBreadthFirst(studentNumber);
		break;
	default:
		cout << "Yanlis secim yaptiniz! Varsayilan olarak Ilk Derinlik araniyor..." << endl << endl;
		SearchDepthFirst(studentNumber);
		break;
	}

	cout << "Yazdirma Bitti";
}

// �lk derinlik arama ile ��renciyi arar
void StudentTree::SearchDepthFirst(string number)
{
	int counter = 0;
	StudentNode* studentNode;
	stack<StudentNode*> studentStack;
	studentStack.push(root);
	while (!studentStack.empty())
	{
		counter++;
		studentNode = studentStack.top();
		studentStack.pop();
		if (strcmp(number.c_str(), studentNode->number.c_str()) == 0)
		{
			cout << studentNode->number << " " << studentNode->name << " " << studentNode->surName << endl;
			cout << counter << " Kere islem yapildi \n";
			return;
		}
		if (studentNode->rightNode)
		{
			studentStack.push(studentNode->rightNode);
		}
		if (studentNode->leftNode)
		{
			studentStack.push(studentNode->leftNode);
		}
	}
}

// �lk geni�lik arama ile ��renciyi arar
void StudentTree::SearchBreadthFirst(string number)
{
	queue<StudentNode*> queue;
	StudentNode* p;
	int counter = 0;
	queue.push(root);
	while (!queue.empty())
	{
		counter++;
		p = queue.front();
		queue.pop();
		if (strcmp(number.c_str(), p->number.c_str()) == 0)
		{
			cout << p->number << " " << p->name << " " << p->surName << endl;
			cout << counter << " kere islem yapildi \n";
			return;
		}
		if (p->rightNode)
		{
			queue.push(p->rightNode);
		}
		if (p->leftNode)
		{
			queue.push(p->leftNode);
		}
	}
}

// E�er k�k� verirsek a�a� i�in bellekte ayr�lm�� t�m yerleri siler. 
void StudentTree::ClearTree(StudentNode* root)
{
	if (root)
	{
		if (root->leftNode != NULL)
		{
			ClearTree(root->leftNode);
			root->leftNode = NULL;
		}
		if (root->rightNode != NULL)
		{
			ClearTree(root->rightNode);
			root->rightNode = NULL;
		}
		delete root;
	}
}

// A�ac�m�z� bir .txt dosyas�na Pre Order' a g�re kaydediyoruz.
void StudentTree::SaveTree()
{
	string number = filePath.substr(4);

	fileWriter.open("tree" + number);
	if (fileWriter.is_open())
	{
		WritePreOrdered(root);
		fileWriter.close();
	}

}

void StudentTree::WritePreOrdered(StudentNode* root) {

	if (root)
	{
		if (fileWriter.is_open())
		{
			fileWriter << root->number << " " << root->name << " " << root->surName << endl;
		}
		WritePreOrdered(root->leftNode);
		WritePreOrdered(root->rightNode);
	}
}

// A�ac� kaydetme metodunu �al��t�r�yoruz, a�ac� bellekten siliyoruz ve kapat�yoruz.
void StudentTree::CloseTree()
{
	SaveTree();
	ClearTree(root);
}

