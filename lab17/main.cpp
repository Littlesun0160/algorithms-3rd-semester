#include <iostream>
#include <string>

struct Node 
{
    int Peak;
    Node* LeftNode;
    Node* RightNode;
};

class BinarySearchTree
{
private:
    Node* Root; // ������ ������ (�.�. ��������� ����)
    Node* m_Add(Node* Current, int Value, bool& check)
    {
        if (Current == nullptr) //���� ������ ������, �� ������� ������ ���� �� ��������� Value
        {
            Node* newNode = new Node;
            newNode->Peak = Value;
            newNode->LeftNode = nullptr;
            newNode->RightNode = nullptr;
            return newNode;
        }
        if (Value == Current->Peak)
        {
            std::cout << "������! � �������� ������ ������ �� ����� ���� ���������� �����. ��������� ���� ������\n";
            check = false;
            return Current;
        }
        if (Value < Current->Peak) //���� ����������� �������� ������ ��� ��������������� ����, �� ��������� ��� � ����� ���������
        {
            Current->LeftNode = m_Add(Current->LeftNode, Value, check);
        }
        else if (Value > Current->Peak) //���� ������, �� � ������ ���������
        {
            Current->RightNode = m_Add(Current->RightNode, Value, check);
        }
        return Current;
    }

    Node* m_Remove(Node* Current, int Value) 
    {
        if (Current == nullptr)
        {
            return Current;
        }
        if (Value < Current->Peak) //�������� ���������� �� ����� ������, ���� �� ������ ����������� ��������
        {
            Current->LeftNode = m_Remove(Current->LeftNode, Value);
        }
        else if (Value > Current->Peak)
        {
            Current->RightNode = m_Remove(Current->RightNode, Value);
        }
        else  
        {
            // ���� �� ����� ����, � �� ����� 1 ��� 0 ��������, �� ������� ���(��� ������� ������� ������ ������� �� ����� ���������� �������)
            if (Current->LeftNode == nullptr) 
            {
                Node* Inter = Current->RightNode;
                delete Current;
                return Inter;
            }
            else if (Current->RightNode == nullptr)
            {
                Node* Inter = Current->LeftNode;
                delete Current;
                return Inter;
            }

            // ���� �� ����� ����, � �� ����� 2 ��������, �� ������ ���������� �� ������� ��������� ���� � �������� �� ����� ����������
            // ������ �� �������? ������ ��� � ������ � ��� �������� ������ ����������, � ������ ������� ������
            Node* minRight = FindMin(Current->RightNode);
            Current->Peak = minRight->Peak;
            Current->RightNode = m_Remove(Current->RightNode, minRight->Peak);
        }
        return Current;
    }
    Node* FindMin(Node* Current) //��������������� ����� ��� ���������� ������������ ����
    {
        while (Current->LeftNode != nullptr)
        {
            Current = Current->LeftNode;
        }
        return Current;
    }

    bool m_Find(Node* Current, int Value) //������ ���������, ���� �� ����� ��������, ���������� ������� ����� ��� ����
    {
        if (Current == nullptr)
        {
            return false;
        }
        if (Current->Peak == Value) 
        {
            return true;
        }
        if (Value < Current->Peak)
        {
            return m_Find(Current->LeftNode, Value);
        }
        else 
        {
            return m_Find(Current->RightNode, Value);
        }
    }
    void m_Display(Node* currentNode)
    {
        if (currentNode != nullptr) //���� � ��� ���� ����, ������� ��� �������� � ���������, ���� �� � ���� ����������
        {
            std::cout << currentNode->Peak;
            bool LeftCheck = (currentNode->LeftNode != nullptr);
            bool RigthCheck = (currentNode->RightNode != nullptr);
            if (LeftCheck || RigthCheck) //���� ���� ��������� � ����, ������ ������������� ����� ���� ���������
            {
                std::cout << " (";
                if (LeftCheck)
                {
                    m_Display(currentNode->LeftNode);
                }
                if (RigthCheck)
                {
                    if (LeftCheck)std::cout << ", ";
                    m_Display(currentNode->RightNode);
                }
                std::cout << ")";
            }
        }
    }

public:
    BinarySearchTree() : Root(nullptr) {}
    void Add(int value, bool& check)
    {
        Root = m_Add(Root, value, check); //������ ������ ������ ��� ������ ������������ ���������� ������ m_Add
    }
    void Remove(int Value)
    {
        Root = m_Remove(Root, Value);
    }
    bool Find(int Value)
    {
        return m_Find(Root, Value);
    }
    void Display()
    {
        std::cout << "(";
        m_Display(this->Root); //���������� ������� ������ � ���������� ����������� �����
        std::cout << ")\n";
    }
};




int main() 
{
    setlocale(LC_ALL, "rus");
    BinarySearchTree Derevo;

    while (true) 
    {
        std::cout << "�������� ��������:\n1.�������� ����\n2.������� ����\n3.����� ����\n4.������� ������ �� �����\n5.����� �� ����\n";
        int Choice;
        bool Check = true;
        std::cin >> Choice;

        switch (Choice)
        {
        default:
            std::cout << "������ �������� �� ����������, ���������� �����\n";
            break;
        case 1:
            int Value1;
            std::cout << "������� �������� ��� ����������: ";
            std::cin >> Value1;
            Derevo.Add(Value1, Check);
            if (Check) std::cout << "�������� ���������\n";
            break;
        case 2:
            int Value2;
            std::cout << "������� �������� ��� ��������: ";
            std::cin >> Value2;
            Derevo.Remove(Value2);
            std::cout << "�������� �������\n";
            break;
        case 3:
            int Value3;
            std::cout << "������� �������� ��� ������: ";
            std::cin >> Value3;
            if (Derevo.Find(Value3))
            {
                std::cout << "���� �� ��������� " << Value3 << " ������ � ������\n";
            }
            else
            {
                std::cout << "���� �� ��������� " << Value3 << " �� ������ � ������\n";
            }
            break;
        case 4:
            std::cout << "�������� ������ ������ �������� ���: ";
            Derevo.Display();
            break;
        case 5:
            std::cout << "����������� ����� �� ���������. ������ ����� ���: ";
            Derevo.Display();
            break;
        }
    }
}