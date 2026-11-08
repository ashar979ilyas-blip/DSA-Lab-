
#include <iostream>
#include <string>
using namespace std;

struct Action
{
    char character;
    int type;
};

template <typename T>
class Stack
{
private:
    T arr[1000];
    int topIndex;

public:
    Stack()
    {
        topIndex = -1;
    }

    bool isEmpty()
    {
        return topIndex == -1;
    }

    bool isFull()
    {
        return topIndex == 999;
    }

    void push(T value)
    {
        if (!isFull())
        {
            topIndex++;
            arr[topIndex] = value;
        }
        else
        {
            cout << "Stack is full.\n";
        }
    }

    T pop()
    {
        if (isEmpty())
            return T();

        T value = arr[topIndex];
        topIndex--;

        return value;
    }

    void clear()
    {
        topIndex = -1;
    }
};

int main()
{
    Stack<Action> undoStack;
    Stack<Action> redoStack;

    string text = "";
    int choice;
    char ch;
    Action action;

    do
    {
        cout << "\n--- TEXT EDITOR MENU ---\n";
        cout << "1. Type a character\n";
        cout << "2. Delete last character\n";
        cout << "3. Undo\n";
        cout << "4. Redo\n";
        cout << "5. Display current text\n";
        cout << "6. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter character: ";
            cin >> ch;

            text = text + ch;

            action.character = ch;
            action.type = 1;

            undoStack.push(action);
            redoStack.clear();

            cout << "Character added.\n";
            break;

        case 2:
            if (text.empty())
            {
                cout << "There is no character to delete.\n";
            }
            else
            {
                ch = text[text.length() - 1];

                text.erase(text.length() - 1);

                action.character = ch;
                action.type = 2;

                undoStack.push(action);
                redoStack.clear();

                cout << "Last character deleted.\n";
            }
            break;

        case 3:
            if (undoStack.isEmpty())
            {
                cout << "Nothing to undo.\n";
            }
            else
            {
                action = undoStack.pop();

                if (action.type == 1)
                {
                    text.erase(text.length() - 1);
                }
                else
                {
                    text = text + action.character;
                }

                redoStack.push(action);

                cout << "Undo completed.\n";
            }
            break;

        case 4:
            if (redoStack.isEmpty())
            {
                cout << "Nothing to redo.\n";
            }
            else
            {
                action = redoStack.pop();

                if (action.type == 1)
                {
                    text = text + action.character;
                }
                else
                {
                    text.erase(text.length() - 1);
                }

                undoStack.push(action);

                cout << "Redo completed.\n";
            }
            break;

        case 5:
            cout << "Current text: " << text << endl;
            break;

        case 6:
            cout << "Text editor closed.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 6);

    return 0;
}
