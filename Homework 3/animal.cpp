#include <iostream>
#include <string>
using namespace std;

class Animal
{
public:
  Animal(string type);
  virtual ~Animal();
  virtual string name() const;
  string type() const;
  virtual string moveAction() const;
  virtual void speak() const = 0;
private:
  string m_name;
};

class Pig : public Animal
{
public:
  Pig(string name, int weight);
  ~Pig();
  void speak() const;
private:
  string m_speak;
};

class Cat : public Animal
{
public:
  Cat(string name);
  ~Cat();
  void speak() const;
private:
  string m_name;
};

class Duck : public Animal
{
public:
  Duck(string name);
  ~Duck();
  void speak() const;
  string moveAction() const;
private:
  string m_name;
};

Animal::Animal(string name) : m_name(name)
{}

Animal::~Animal()
{}

string Animal::moveAction() const
{
  return "walk";
}

string Animal::name() const
{
  return m_name;
}

Pig::Pig(string name, int weight) : Animal(name)
{
  if(weight <= 0)
    {
      cerr << "Cannot create a pig of weight " << weight << endl;
      exit(1);
    }
  if(weight < 160)
    m_speak = "Oink";
  else
    m_speak = "Grunt";
}

Pig::~Pig()
{
  cout << "Destroying " << name() << " the pig" << endl;
}

void Pig::speak() const
{
  cout << m_speak;
}

Cat::Cat(string name) : Animal(name)
{}

Cat::~Cat()
{
  cout << "Destroying " << name() << " the cat" << endl;
}

void Cat::speak() const
{
  cout << "Meow";
}

Duck::Duck(string name) : Animal("duck"), m_name(name)
{}

Duck::~Duck()
{
  cout << "Destroying " << name() << " the duck" << endl;
}
void Duck::speak() const
{
  cout << "Quack";
}

string Duck::moveAction() const
{
  return "swim";
}

void animate(const Animal* a)
{
  a->speak();
  cout << "!  My name is " << a->name()
         << ".  Watch me " << a->moveAction() << "!\n";
}

int main()
{
    Animal* animals[4];
    animals[0] = new Cat("Fluffy");
      // Pigs have a name and a weight in pounds.  Pigs under 160
      // pounds oink; pigs weighing at least 160 pounds grunt.
    animals[1] = new Pig("Napoleon", 190);
    animals[2] = new Pig("Wilbur", 50);
    animals[3] = new Duck("Daffy");

    cout << "Here are the animals." << endl;
    for (int k = 0; k < 4; k++)
        animate(animals[k]);

      // Clean up the animals before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete animals[k];
}
