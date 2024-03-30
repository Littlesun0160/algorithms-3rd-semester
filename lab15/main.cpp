#include <iostream>
#include <string>

//���� ��������� ������
struct Node
{
    int Peak;
    Node* LeftNode;  //���� ������ ���������
    Node* RightNode; //���� ������� ���������

    Node(int value) : Peak(value), LeftNode(nullptr), RightNode(nullptr) {}
};

//������������ �������-��������� ������ � ������
Node* buildTreeFromString(const std::string& Derevo, int& Index) 
{
    if (Derevo.empty() || Index >= Derevo.size())
    {
        return nullptr;
    }

    int Usel = 0; //���������� ��� ����������� ����
    while (Index < Derevo.size() && isdigit(Derevo[Index])) //�����, ������������ � Index, ��������� ��� ���� ������, ��������� ��� �� ������
    {
        Usel = Usel * 10 + (Derevo[Index]-'0');
        Index++;
    }
    Node* newNode = new Node(Usel);

    if (Index < Derevo.size() && Derevo[Index] == '(')
    {
        Index++;
        newNode->LeftNode = buildTreeFromString(Derevo, Index); //���� ��������� ������, �� ������� �� ��� ����� ����� ����� ����� 
                                                                //��� ������
                                                                //�������� ���������� �������� ������ ���������
    }
    if (Index < Derevo.size() && Derevo[Index] == '(')  //���� ����� �������� ������ ��������� ��������� ������, �� ���������� 
                                                        //������� ������ ���������
    {
        Index++;
        newNode->RightNode = buildTreeFromString(Derevo, Index);
    }
    Index++; // ������� � ���������� ������� ����� ����������� ������ ')'
    return newNode;
}


// ������� ��� ������ ��������� ������ � ������ �������(pre-order) : ������� � ����� ��������� � ������ ���������
void preOrder(Node* RootOfDerevo) 
{
    if (RootOfDerevo == nullptr)
    {
        return;
    }
    std::cout << RootOfDerevo->Peak << " ";  // ����� ������� ������/���������
    preOrder(RootOfDerevo->LeftNode);   // ���������� � ������ ��������� ����������
    preOrder(RootOfDerevo->RightNode);  // ���������� � ������� ��������� ����������
}

// ������� ��� ������ ��������� ������ � ����������� �������(in-order): ����� ��������� � ������� � ������ ��������� 
void inOrder(Node* RootOfDerevo)
{
    if (RootOfDerevo == nullptr)
    {
        return;
    }
    inOrder(RootOfDerevo->LeftNode);    // ���������� � ������ ��������� ����������
    std::cout << RootOfDerevo->Peak << " ";  // ����� ������� ������/���������
    inOrder(RootOfDerevo->RightNode);   // ���������� � ������� ��������� ����������
}

// ������� ��� ������ ��������� ������ � �������� �������(post-order): ����� ��������� � ������ ��������� � �������
void postOrder(Node* RootOfDerevo)
{
    if (RootOfDerevo == nullptr)
    {
        return;
    }
    postOrder(RootOfDerevo->LeftNode);   // ���������� � ������ ��������� ����������
    postOrder(RootOfDerevo->RightNode);  // ���������� � ������� ��������� ����������
    std::cout << RootOfDerevo->Peak << " ";   // ����� ������� ������/���������
}


int main() 
{
    setlocale(LC_ALL, "rus");
    std::string treeString = "1(2(3)(4(5)(6(7))))(8(9)(10))";
    int index = 0;
    Node* root = buildTreeFromString(treeString, index);

    std::cout << "����� � ������ �������: ";
    preOrder(root);
    std::cout << "\n";

    std::cout << "����� � ����������� �������: ";
    inOrder(root);
    std::cout << "\n";

    std::cout << "����� � �������� �������: ";
    postOrder(root);
    std::cout << "\n";
}