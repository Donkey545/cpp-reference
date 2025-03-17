#ifndef MEMORY_ALLOCATION_TECHNIQUES_HPP
#define MEMORY_ALLOCATION_TECHNIQUES_HPP

#include <memory>  // For smart pointers
#include <cstdlib> // For malloc/free

// Global variable - stored in data segment, accessible program-wide
int globalVariable = 1;

// File-scoped static variable - visible only in this translation unit
// Each file that includes this header gets its own copy
static int fileLocalVariable = 2;

// External variable declaration - no memory allocated here
// Just informs compiler that variable exists elsewhere
extern int externallyDefinedVariable;

// Volatile variable - tells compiler not to optimize reads/writes
// Used for variables that may change outside program control
volatile int hardwareRegister = 4;

// Constant global variable - typically stored in read-only data section
// Compiler may replace references with the literal value
const int immutableGlobal = 5;

class ResourceManager
{
   // Static class member - single copy shared among all class instances
   // Requires separate definition outside class declaration
   static int sharedInstanceCounter;
   
   // Per-instance constant - each object has its own copy
   // Cannot be modified after initialization
   const int instanceId = 5;

   protected:
      // Regular instance member - each object has its own copy
      int resourceHandle;

   public:
      // Constructor with parameter - used for proper initialization
      ResourceManager(int handle);

   private:
      // Private default constructor - prevents direct default instantiation
      ResourceManager();
};

int memoryAllocationDemo(int stackCopyParam, 
                         const int* readOnlyDataPtr, 
                         int* const fixedAddressPtr, 
                         int& referenceAlias)
{
   // Static local variable - initialized only once, retains value between calls
   static int persistentCounter = 6;
   
   // Stack-allocated array - automatic lifetime, fixed size
   int stackArray[3] = {0, 1}; // Third element implicitly initialized to 0

   // ---- Smart pointer memory techniques ----
   
   // Single allocation for object and control block
   std::shared_ptr<int> efficientSharedInt = std::make_shared<int>(42);
   
   // Two separate allocations (object + control block)
   std::shared_ptr<int> twoStepSharedInt(new int(24));
   
   // Unique ownership smart pointer
   std::unique_ptr<int> exclusiveOwnershipInt = std::make_unique<int>(36);

   // ---- Class allocation techniques ----
   
   // Heap allocation of single object with constructor call
   ResourceManager* singleHeapObject = new ResourceManager(10);
   
   // Heap allocation of array of objects with default constructor calls
   // Note: Would fail compilation if default constructor is private
   ResourceManager* heapObjectArray = new ResourceManager[10];
   
   // C-style allocation - raw memory without constructor calls
   // Objects are not properly initialized!
   ResourceManager* uninitializedMemoryBlock = 
       static_cast<ResourceManager*>(malloc(10 * sizeof(ResourceManager)));
   
   // Stack allocation - automatic lifetime management
   ResourceManager automaticObject(20);

   // ---- Cleanup section ----
   
   // Proper cleanup for different allocation types
   delete singleHeapObject;         // Calls destructor and frees memory
   delete[] heapObjectArray;        // Calls destructors for all objects and frees array
   free(uninitializedMemoryBlock);  // Only frees memory, no destructors called
   
   // Smart pointers clean up automatically when they go out of scope
   
   persistentCounter++;  // Value preserved between function calls
   return stackArray[0];
}

#endif // MEMORY_ALLOCATION_TECHNIQUES_HPP