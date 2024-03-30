#include <iostream>
#include <stack>
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
Node* TreeFromString(const std::string& Derevo)
{
    std::stack<Node*> Stek;
    Node* Root = nullptr; //Корень дерева
    Node* Variable = nullptr; //Переменная для перемещения по строке
    bool leftCheck = false; //Бул, который следит, есть ли левое поддерево или нет

    for (char Symbol : Derevo) //Идем по каждому символу из дерева
    {
        if (Symbol == '(')
        {
            Stek.push(Variable); //Если открывается скобка, то добавляем стоящий ПЕРЕД скобкой элемент в стек
            leftCheck = true; //Говорим, что есть левое поддерево
        }
        else if (Symbol == ')') 
        {
            Stek.pop(); //Удаляем из стэка элемент, стоящий перед скобкой
        }
        else 
        {
            Variable = new Node(Symbol); //Переменная становится узлом
            if (Root == nullptr)
            {
                Root = Variable; // Корнем дерева становится переменная от нулевого символа
            }
            else 
            {
                if (leftCheck) //Если мы говорим, что левое поддерево есть, то узлу из верхушки стека добавляется узел левого 
                               //поддерева
                {
                    Stek.top()->LeftNode = Variable;
                    leftCheck = false;
                }
                else 
                {
                    Stek.top()->RightNode = Variable; // Если левое поддерево закончилось, и его нет, то верхушка стека обретает 
                                                        //правое поддерево
                }
            }
        }
    }
    return Root;
}

// Функция для прямого обхода бинарного дерева без использования рекурсии
// Прямой обход - это обход по порядку: вершина – левое поддерево – правое поддерево

void PreOrder(Node* Root)
{
    std::stack<Node*> Stek;
    Node* Variable = Root; // Переменная для перемещения по дереву

    while (Variable != nullptr || !Stek.empty()) 
    {
        while (Variable != nullptr)
        {
            std::cout << static_cast<char>(Variable->Peak) << " "; // посещаем узел
            Stek.push(Variable);
            Variable = Variable->LeftNode; // двигаемся влево
        }
        Variable = Stek.top();
        Stek.pop();
        Variable = Variable->RightNode; // двигаемся вправо
    }
}

int main() 
{
    std::string Derevo = "7(2(3)(4(6)(5)))(1)";
    int Index = 0;
    Node* Root = TreeFromString(Derevo);
    PreOrder(Root);
}