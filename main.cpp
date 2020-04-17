/*
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class Shape
{
public:
    Shape(const char* id, const char* name)
    {
        shapeName = new char[strlen(name) + strlen(id)];
        strcpy(shapeName, name);
        strcpy(shapeName + strlen(name), id);
    }

    ~Shape()
    {
        if (shapeName != nullptr)
        {
            delete [] shapeName;
            shapeName = nullptr;
        }
        cout << "1" << endl;
    }

    const char * getName()
    {
        return shapeName;
    }

private:
    char* shapeName;
};


void PrintShape(Shape* shape)
{
    cout << "name: " << shape->getName() << endl;
}

void TestTheShapeClass()
{
    vector<Shape> shapes;
    shapes.push_back(Shape("1", "Rect: "));
    //shapes.push_back(Shape("2", "Circle: "));

    for (size_t i = 0; i < shapes.size(); ++i)
    {
        PrintShape(&shapes[i]);
    }

    shapes.clear();
}

int main()
{
    TestTheShapeClass();

    return 0;
}
*/

// constructing vectors
#include <iostream>
#include <map>

using namespace std;

int main ()
{
    map<char, int> one;
    one.insert(pair<char, int> ('a', 1));
    one.insert(pair<char, int> ('b', 2));
    one.insert(pair<char, int> ('c', 3));

    map<char, int>::iterator it = one.begin();
    map<char, int> two;
    two.insert(it, pair<char, int> ('b', 2));
    two.insert(it, pair<char, int> ('c', 3));

    map<char, int> three;
    three.insert(one.begin(), one.find('c'));

    cout << "Second map:" << endl;
    for(it = three.begin(); it != three.end(); ++it)
        cout << it->first << "=>" << it->second << endl;


    return 0;
}




































