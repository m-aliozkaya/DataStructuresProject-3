#include <string>
using namespace std;

struct StudentNode
{
	string number;
	string name;
	string surName;
	StudentNode* leftNode;
	StudentNode* rightNode;
};
