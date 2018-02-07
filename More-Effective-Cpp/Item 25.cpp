// Item 25: Virtualizing constructors and non-member functions.
// Example: Class for writing newsletters, which can contain textual and graphical parts.

class NLComponent // Abstract base class (contains at least 1 pure virtual function).
{
public:
	// ...
};

class TextBlock : public NLComponent
{
public:
	// ...
};

class Graphic : public NLComponent
{
public:
	// ...
};

class NewsLetter
{
public:
	// ...
	
private:
	list<NLComponent*> components; // A list behaves like a doubly linked list.
};

// **********************************************************************************
// Concept 1: Virtual constructors. 
// Idea: A function that, depending on its input, creates objects of different types.
// **********************************************************************************

// Let's say that NewsLetter objects must be created by reading components from a file.
class NewsLetter
{
public:
	NewsLetter(istream& str);
	// ...
	
private:
	// Read the data for the next NLComponent from str, create the component and return a pointer to it.
	// This is the virtual constructor: the type of the object it creates depends on its input.
	static NLComponent * readComponent(istream& str);
	// ...
};

NewsLetter::NewsLetter(istream& str)
{
	while (str)
	{
		components.push_back(readComponent(str));
	}
}

// ***************************************************************************************************************
// Concept 2: Virtual copy constructors.
// Idea: How do you copy a derived object through a base class pointer? You do it with a virtual copy constructor.
// ***************************************************************************************************************

class NLComponent
{
public:
	// This is the virtual copy constructor.
	virtual NLComponent * clone() const = 0;
	// ...
};

class TextBlock : public NLComponent
{
public:
	virtual NLComponent * clone() const // Could also be declared with the return type TextBlock.
	{
		return new TextBlock(*this);
	}
	// ...
};

class Graphic : public NLComponent
{
public:
	virtual NLComponent * close() const // Could also be declared with the return type Graphic.
	{
		return new Graphic(*this);
	}
	// ...
};

// Now that the components have virtual copy constructors, we can easily write a copy constructor for NewsLetter.
class NewsLetter
{
public:
	NewsLetter(const NewsLetter& rhs);
	// ...

private:
	list<NLComponent*> components;
};

NewsLetter::NewsLetter(const NewsLetter& rhs)
{
	for (list<NLComponent*>::const_iterator it = rhs.components.begin(); it != rhs.components.end(); ++it)
	{
		components.push_back((*it)->clone());
	}
}

// ***************************************************
// Concept 3: Making non-member functions act virtual.
// Idea: Non-member function calls virtual member function.
// ***************************************************

// Let's say we wanted to implement output operators for the newsletter components.
// We could do it like this:

class NLComponent
{
public:
	// Unconventional declaration of operator<<
	virtual ostream& operator<<(ostream& s) const = 0;
	// ...
};

class TextBlock : public NLComponent
{
public:
	virtual ostream& operator<<(ostream& s) const;
	// ...
};

class Graphic : public NLComponent
{
public:
	virtual ostream& operator<<(ostream& s) const;
	// ...	
};

TextBlock t;
Graphic g;

// Unconventional declaration of operator<< requires us to specify the ostream object on the right side of the call.
t << cout;
g << cout;

// Clearly, operator<< needs to be a non-member function, but we need its behaviour to change depending on who invokes it.

class NLComponent
{
public:
	virtual ostream& print(ostream& s) const = 0;
	// ...
};

class TextBlock : public NLComponent
{
	public:
	virtual ostream& print(ostream& s) const;
	// ...
};

class Graphic : public NLComponent
{
	public:
	virtual ostream& print(ostream& s) const;
	// ...
};

// Non-member function calls virtual member function.
inline ostream& operator<<(ostream& s, const NLComponent& c)
{
	return c.print(s);
}
