// Item 26: Limiting the number of objects of a class.
// Example: Printer class.

// ***********************************************************************************
// Concept 1: Allowing 0 objects.
// Idea: To prevent a class from being instantiated, declare its constructors private.
// ***********************************************************************************

class CantBeInstantiated
{
private:
	CantBeInstantiated();
	CantBeInstantiated(const CantBeInstantiated&);
}

// *********************************************************************
// Concept 2: Allowing 1 object.
// Idea: Encapsulate unique instance so that everybody has access to it.
// *********************************************************************

// Option A: Declare the constructors private and encapsulate the unique instance inside a friend function.
//           - Private constructors suppress object creation.
//           - Global function thePrinter is declared a friend function of the class, which allows it to access the constructors.
//           - thePrinter contains a static printer object, which means that we only have 1 instance of the class.

class PrintJob; // Forward declaration.

class Printer
{
public:
	void submitJob(const PrintJob& job);
	void reset();
	void performSelfTest();
	...
	friend Printer& thePrinter();
	
private:
	Printer();
	Printer(const Printer& rhs);
	...
};

Printer& thePrinter()
{
	static Printer p; // Unique instance
	return p;
}

// Using thePrinter looks like this with option A:

class PrintJob
{
public:
	PrintJob(const string& whatToPrint);
	...
};

thePrinter().reset();
thePrinter().submitJob("Hello world!"); // This call implicitly creates a PrintJob object.

// Option B: Declare the constructors private and encapsulate the unique instance inside a public static member function.
//           - You can do this if you don't like the global function used in option A.

class Printer
{
public:
	static Printer& thePrinter();
	...

private:
	Printer();
	Printer(const Printer& rhs);
	...
};

Printer& Printer::thePrinter()
{
	static Printer p;
	return p;
}

// Using thePrinter looks like this with option B:

Printer::thePrinter().reset();
Printer::thePrinter().submitJob("Hello world!"); // This call implicitly creates a PrintJob object.

// Option C: Declare the constructors private and encapsulate the unique instance inside a friend function that belongs to the same namespace as the class.
//           - You can do this if you don't like the global function used in option A.

namespace PrintingStuff
{
	class Printer
	{
	public:
		void submitJob(const PrintJob& job);
		void reset();
		void performSelfTest();
		...
		friend Printer& thePrinter();
	
	private:
		Printer();
		Printer(const Printer& rhs);
		...
	};

	Printer& thePrinter()
	{
		static Printer p; // Unique instance
		return p;
	}
}

// Using thePrinter looks like this with option C:

PrintingStuff::thePrinter().reset();
PrintingStuff::thePrinter().submitJob("Hello world!"); // This call implicitly creates a PrintJob object.

// Notes on options A, B and C:
// The unique printer object must be static inside a function instead of a class.
// A static object inside of a class is always constructed.
// A static object inside of a function is constructed the first time through the function. If the function is never called, it is never created.
// We know when a function static is initialized, but we don't know when a class static/global static is initialized.
// C++ says nothing about the initialization order of static objects in different translation units.

// *********************************************************************
// Concept 3: Counting the number of objects in existence.
// Idea: Encapsulate unique instance so that everybody has access to it.
// *********************************************************************

class Printer
{
public:
	class TooManyObjects{};
	
	Printer();
	~Printer();
	
private:
	static size_t numObjects;
	Printer(const Printer& rhs); // Copying is not allowed because we limit the number of instances of the class to 1.
};

size_t Printer::numObjects = 0; // Obligatory definition of class static

Printer::Printer()
{
	if (numObjects >= 1)
	{
		throw TooManyObjects;
	}
	
	// Proceed with normal construction
	
	++numObjects;
}

Printer::~Printer()
{
	// Proceed with normal destruction
	
	--numObjects;
}

// ****************************************************************************************************************
// Concept 4: Counting the number of objects in existence while limiting the contexts in which they can be created.
// Idea: Only allow objects to exist on their own, and limit those kinds of instantiations.
// ****************************************************************************************************************

// Problems with concept 3:
// Printer objects can exist in 3 different contexts:
// 1) On their own.
// 2) As base class parts of more derived objects.
// 3) Embedded inside larger objects.

// So, what does it mean to keep track of the number of objects in existence?
// Often, you will want to only allow objects to exist on their own, and you will want to limit those kinds of instantiations.

// Classes with private constructors can't be used as base classes, nor can they be embedded inside other objects.
// So, to prevent derivation you can declare constructors private and use pseudo-constructors:

class FSA
{
public:
	static FSA * makeFSA();
	static FSA * makeFSA(const FSA& rhs);
	~FSA();
	...
private:
	FSA();
	FSA(const FSA& rhs);
};

FSA * FSA::makeFSA()
{
	return new FSA();
}

FSA * FSA::makeFSA(const FSA& rhs)
{
	return new FSA(rhs);
}

// Clients must call delete unless they use smart pointers

std::unique_ptr<FSA> pFiniteStateAgent1(FSA::makeFSA());
std::unique_ptr<FSA> pFiniteStateAgent2(FSA::makeFSA(*pFiniteStateAgent1));

// ************************************************************************************************************
// Concept 5: Only allow a single instance to exist at a time, but allow instances to be created and destroyed.
// Idea: Combine object-counting with pseudo-constructors to limit the number of instances of a class
//       while allowing clients to construct/destruct them.
// ************************************************************************************************************

// Options A, B and C limit us to a single instance. What if we wanted to destroy that unique instance and create a new one?

	Create Printer object p1;
	Use p1;
	Destroy p1;

	Create Printer object p2;
	Use p2;
	Destroy p2;

// Only a single instance exists at a time, but options A, B and C do not allow us to do this. How can we achieve this functionality?
// We can do it by mixing object-counting with pseudo-constructors:

class Printer
{
public:
	class TooManyObjects{};

	static Printer * makePrinter();
	~Printer();                  // Decreases numObjects.

	void submitJob(const PrintJob& job);
	void reset();
	void performSelfTest();
	...
	
private:
	static size_t numObjects;

	Printer();
	Printer(const Printer& rhs); // We do not define this since copying cannot be supported when only
                                 // a single instance of an object is supposed to exist at a time.
};

size_t Printer::numObjects = 0;  // Obligatory definition of class static

Printer::Printer()
{
	if (numObjects >= 1)
	{
		throw TooManyObjects;    // You could return a nullptr in makePrinter instead of throwing an exception if you wanted
	}

	Proceed with normal object construction here;

	++numObjects;
}

Printer * Printer::makePrinter()
{
	return new Printer;
}

// Now the following is allowed:

Printer p1; 			                 // Error. Constructor is private.
Printer * p2 = Printer::makePrinter();   // Correct.
Printer * p3 = *p2;                      // Error. Copy constructor is private and not defined.
p2->reset();                             // Correct.
delete p2;                               // Correct.

// We can generalize this technique to allow a specific number of objects to exist simultaneously.
// Let's say we only wanted to allow 10 instances of the Printer class to exist at a time:

class Printer
{
public:
	class TooManyObjects{};
	
	static Printer * makePrinter();
	static Printer * makePrinter(const Printer& rhs);
	~Printer();                          // Decreases numObjects.
	
	...
	
private:
	static size_t numObjects;
	static const size_t maxObjects = 10; // Initializing a static const member of integral type (int, char, enum, size_t, ...)
										 // If this gives you trouble, you will need to omit the initialization value and include the line
										 // commented below in the implementation file. 
										 // You could also use the enum hack: enum {maxObjects = 10};
	
	Printer();
	Printer(const Printer& rhs);
};

// Obligatory definitions of class statics
size_t Printer::numObjects = 0;
const size_t Printer::maxObjects;        // Include this if the line with the long comment above doesn't give you any trouble.
//const size_t Printer::maxObjects = 10; // Include this if the line with the long comment above gives you trouble.

Printer::Printer()
{
	if (numObjects >= maxObjects)
	{
		throw TooManyObjects;
	}
	
	Proceed with normal object construction here;
	
	++numObjects;
}

Printer * Printer::makePrinter()
{
	return new Printer;
}

Printer * Printer::makePrinter(const Printer& rhs)
{
	return new Printer(rhs);
}

// ***********************************************************
// Concept 6: An object-counting base class
// Idea: Encapsulate the object-counting code in a base class. 
// ***********************************************************

// The base class will contain numObjects. This variable must be unique for each class that inherits from it.
// How can we achieve that? With templates!

template<class BeingCounted>
class Counted
{
public:
	class TooManyObjects{};
	
	static int objectCount() { return numObjects; }
	
protected:
	Counted();                   // Constructors and destructors are protected so that the class can be used as a base class.
	Counted(const Counted& rhs);
	~Counted();
	
private:
	static size_t numObjects;
	static const size_t maxObjects;
	
	void init();                 // The function init avoids code duplication.
};

template<class BeingCounted>
Counted::Counted()
{
	init();
}

template<class BeingCounted>
Counted::Counted(const Counted& rhs)
{
	init();
}

template<class BeingCounted>
Counted::~Counted()
{
	--numObjects;
}

template<class BeingCounted>
void Counted::init()
{
	if (numObjects >= maxObjects)
	{
		throw TooManyObjects;
	}
	
	++numObjects;
}

// Now the Printer class looks like this:

class Printer : private Counted
{
public:
	static Printer * makePrinter();
	static Printer * makePrinter(const Printer& rhs);
	~Printer();                             // Decreases numObjects.
	
    void submitJob(const PrintJob& job);
	void reset();
	void performSelfTest();
	...
	
	using Counted<Printer>::objectCount;    // Public in Counted, but private in Printer because of the private inheritance. 
	using Counted<Printer>::TooManyObjects; // We add these using statements to restore the public accessibility.
	
private:
	Printer();
	Printer(const Printer& rhs);
};

// We don't have to worry about object counting!
Printer::Printer()
{
	Proceed with normal object construction;
}

// What about the mandatory definitions of the statics inside counted?

// numObjects goes inside Counted's implementation file, since it is initially equal to zero. 
template<class BeingCounted>
int Counted<BeingCounted>::numObjects;

// The value of maxObjects depends on the user, so the user must include it in the implementation file of the class she wishes to count.
const size_t Counted<Printer>::maxObjects = 10;
