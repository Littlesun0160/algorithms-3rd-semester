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
    Node* Root; // Корень дерева (т.е. наивысший узел)
    Node* m_Add(Node* Current, int Value, bool& check)
    {
        if (Current == nullptr) //Если дерево пустое, то создаем первый узел со значением Value
        {
            Node* newNode = new Node;
            newNode->Peak = Value;
            newNode->LeftNode = nullptr;
            newNode->RightNode = nullptr;
            return newNode;
        }
        if (Value == Current->Peak)
        {
            std::cout << "Ошибка! В бинарном дереве поиска не может быть одинаковых узлов. Повторите свой запрос\n";
            check = false;
            return Current;
        }
        if (Value < Current->Peak) //Если необходимое значение меньше чем рассматриваемый узел, то добавляем его в левое поддерево
        {
            Current->LeftNode = m_Add(Current->LeftNode, Value, check);
        }
        else if (Value > Current->Peak) //Если больше, то в правое поддерево
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
        if (Value < Current->Peak) //Проходим рекурсивно по узлам дерева, пока не найдем необходимое значение
        {
            Current->LeftNode = m_Remove(Current->LeftNode, Value);
        }
        else if (Value > Current->Peak)
        {
            Current->RightNode = m_Remove(Current->RightNode, Value);
        }
        else  
        {
            // Если мы нашли узел, и он имеет 1 или 0 потомков, то удаляем его(при наличии потомка ставим потомка на место удаляемого объекта)
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

            // Если мы нашли узел, и он имеет 2 потомков, то найдем наименьший из правого поддерева узел и поставим на место удаляемого
            // Почему из правого? Потому что в правом у нас элементы больше удаляемого, и замена пройдет быстро
            Node* minRight = FindMin(Current->RightNode);
            Current->Peak = minRight->Peak;
            Current->RightNode = m_Remove(Current->RightNode, minRight->Peak);
        }
        return Current;
    }
    Node* FindMin(Node* Current) //Вспомогательный метод для нахождения минимального узла
    {
        while (Current->LeftNode != nullptr)
        {
            Current = Current->LeftNode;
        }
        return Current;
    }

    bool m_Find(Node* Current, int Value) //Просто проверяем, есть ли такое значение, рекурсивно проходя через все узлы
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
        if (currentNode != nullptr) //Если у нас есть узел, выводим его значение и проверяем, есть ли у него поддеревья
        {
            std::cout << currentNode->Peak;
            bool LeftCheck = (currentNode->LeftNode != nullptr);
            bool RigthCheck = (currentNode->RightNode != nullptr);
            if (LeftCheck || RigthCheck) //Если есть поддерево у узла, значит рассматриваем левый узел поддерева
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
        Root = m_Add(Root, value, check); //Меняем корень дерева при помощи рекурсивного приватного метода m_Add
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
        m_Display(this->Root); //Раскрываем внешние скобки и начинается рекурсивный вывод
        std::cout << ")\n";
    }
};




int main() 
{
    setlocale(LC_ALL, "rus");
    BinarySearchTree Derevo;

    while (true) 
    {
        std::cout << "Выберите действие:\n1.Добавить узел\n2.Удалить узел\n3.Найти узел\n4.Вывести дерево на экран\n5.Выйти из меню\n";
        int Choice;
        bool Check = true;
        std::cin >> Choice;

        switch (Choice)
        {
        default:
            std::cout << "Такого действия не существует, попробуйте снова\n";
            break;
        case 1:
            int Value1;
            std::cout << "Введите значение для добавления: ";
            std::cin >> Value1;
            Derevo.Add(Value1, Check);
            if (Check) std::cout << "Значение добавлено\n";
            break;
        case 2:
            int Value2;
            std::cout << "Введите значение для удаления: ";
            std::cin >> Value2;
            Derevo.Remove(Value2);
            std::cout << "Значение удалено\n";
            break;
        case 3:
            int Value3;
            std::cout << "Введите значение для поиска: ";
            std::cin >> Value3;
            if (Derevo.Find(Value3))
            {
                std::cout << "Узел со значением " << Value3 << " найден в дереве\n";
            }
            else
            {
                std::cout << "Узел со значением " << Value3 << " не найден в дереве\n";
            }
            break;
        case 4:
            std::cout << "Бинарное дерево поиска выглядит так: ";
            Derevo.Display();
            break;
        case 5:
            std::cout << "Выполняется выход из программы. Дерево имеет вид: ";
            Derevo.Display();
            break;
        }
    }
}