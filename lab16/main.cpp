#include <iostream>
#include <stack>
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
Node* TreeFromString(const std::string& Derevo)
{
    std::stack<Node*> Stek;
    Node* Root = nullptr; //������ ������
    Node* Variable = nullptr; //���������� ��� ����������� �� ������
    bool leftCheck = false; //���, ������� ������, ���� �� ����� ��������� ��� ���

    for (char Symbol : Derevo) //���� �� ������� ������� �� ������
    {
        if (Symbol == '(')
        {
            Stek.push(Variable); //���� ����������� ������, �� ��������� ������� ����� ������� ������� � ����
            leftCheck = true; //�������, ��� ���� ����� ���������
        }
        else if (Symbol == ')') 
        {
            Stek.pop(); //������� �� ����� �������, ������� ����� �������
        }
        else 
        {
            Variable = new Node(Symbol); //���������� ���������� �����
            if (Root == nullptr)
            {
                Root = Variable; // ������ ������ ���������� ���������� �� �������� �������
            }
            else 
            {
                if (leftCheck) //���� �� �������, ��� ����� ��������� ����, �� ���� �� �������� ����� ����������� ���� ������ 
                               //���������
                {
                    Stek.top()->LeftNode = Variable;
                    leftCheck = false;
                }
                else 
                {
                    Stek.top()->RightNode = Variable; // ���� ����� ��������� �����������, � ��� ���, �� �������� ����� �������� 
                                                        //������ ���������
                }
            }
        }
    }
    return Root;
}

// ������� ��� ������� ������ ��������� ������ ��� ������������� ��������
// ������ ����� - ��� ����� �� �������: ������� � ����� ��������� � ������ ���������

void PreOrder(Node* Root)
{
    std::stack<Node*> Stek;
    Node* Variable = Root; // ���������� ��� ����������� �� ������

    while (Variable != nullptr || !Stek.empty()) 
    {
        while (Variable != nullptr)
        {
            std::cout << static_cast<char>(Variable->Peak) << " "; // �������� ����
            Stek.push(Variable);
            Variable = Variable->LeftNode; // ��������� �����
        }
        Variable = Stek.top();
        Stek.pop();
        Variable = Variable->RightNode; // ��������� ������
    }
}

int main() 
{
    std::string Derevo = "7(2(3)(4(6)(5)))(1)";
    int Index = 0;
    Node* Root = TreeFromString(Derevo);
    PreOrder(Root);
}