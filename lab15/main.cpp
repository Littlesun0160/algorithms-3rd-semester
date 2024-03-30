#include <iostream>
#include <string>

//Узел бинарного дерева
struct Node
{
    int Peak;
    Node* LeftNode;  //узел левого поддерева
    Node* RightNode; //узел правого поддерева

    Node(int value) : Peak(value), LeftNode(nullptr), RightNode(nullptr) {}
};

//Переделываем линейно-скобочную запись в дерево
Node* buildTreeFromString(const std::string& Derevo, int& Index) 
{
    if (Derevo.empty() || Index >= Derevo.size())
    {
        return nullptr;
    }

    int Usel = 0; //переменная для определения узла
    while (Index < Derevo.size() && isdigit(Derevo[Index])) //Число, начинающееся с Index, принимаем как узел дерева, считываем его по цифрам
    {
        Usel = Usel * 10 + (Derevo[Index]-'0');
        Index++;
    }
    Node* newNode = new Node(Usel);

    if (Index < Derevo.size() && Derevo[Index] == '(')
    {
        Index++;
        newNode->LeftNode = buildTreeFromString(Derevo, Index); //Если встречаем скобку, то стоящее за ним число будет новым узлом 
                                                                //или листом
                                                                //Проводим рекурсивно создание левого поддерева
    }
    if (Index < Derevo.size() && Derevo[Index] == '(')  //Если после создания левого поддерева встречаем скобку, то рекурсивно 
                                                        //создаем правое поддерево
    {
        Index++;
        newNode->RightNode = buildTreeFromString(Derevo, Index);
    }
    Index++; // Переход к следующему символу после закрывающей скобки ')'
    return newNode;
}


// Функция для обхода бинарного дерева в прямом порядке(pre-order) : вершина – левое поддерево – правое поддерево
void preOrder(Node* RootOfDerevo) 
{
    if (RootOfDerevo == nullptr)
    {
        return;
    }
    std::cout << RootOfDerevo->Peak << " ";  // Пишем вершину дерева/поддерева
    preOrder(RootOfDerevo->LeftNode);   // Обращаемся к левому поддереву рекурсивно
    preOrder(RootOfDerevo->RightNode);  // Обращаемся к правому поддереву рекурсивно
}

// Функция для обхода бинарного дерева в центральном порядке(in-order): левое поддерево – вершина – правое поддерево 
void inOrder(Node* RootOfDerevo)
{
    if (RootOfDerevo == nullptr)
    {
        return;
    }
    inOrder(RootOfDerevo->LeftNode);    // Обращаемся к левому поддереву рекурсивно
    std::cout << RootOfDerevo->Peak << " ";  // Пишем вершину дерева/поддерева
    inOrder(RootOfDerevo->RightNode);   // Обращаемся к правому поддереву рекурсивно
}

// Функция для обхода бинарного дерева в концевом порядке(post-order): левое поддерево – правое поддерево – вершина
void postOrder(Node* RootOfDerevo)
{
    if (RootOfDerevo == nullptr)
    {
        return;
    }
    postOrder(RootOfDerevo->LeftNode);   // Обращаемся к левому поддереву рекурсивно
    postOrder(RootOfDerevo->RightNode);  // Обращаемся к правому поддереву рекурсивно
    std::cout << RootOfDerevo->Peak << " ";   // Пишем вершину дерева/поддерева
}


int main() 
{
    setlocale(LC_ALL, "rus");
    std::string treeString = "1(2(3)(4(5)(6(7))))(8(9)(10))";
    int index = 0;
    Node* root = buildTreeFromString(treeString, index);

    std::cout << "Обход в прямом порядке: ";
    preOrder(root);
    std::cout << "\n";

    std::cout << "Обход в центряльном порядке: ";
    inOrder(root);
    std::cout << "\n";

    std::cout << "Обход в концевом порядке: ";
    postOrder(root);
    std::cout << "\n";
}