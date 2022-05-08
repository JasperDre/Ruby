#include "FrameworkPCH.h"

#include "Utility/CPPList.h"

#if _DEBUG
// Undefine the 'new' defined by '#define new new(__FILE__, __LINE__)' in Memory.h.
// So 'new' simply means 'new' in this file.
#undef new

#define newtype_regular 1
#define newtype_array 2

// Assert when 'new' has been called this many times.
#define CountToAssertOn UINT_MAX

class MemObject : public CPPListNode
{
public:
    const char* myFile;
    unsigned long myLine;
    unsigned int myType;
    unsigned int mySize;
    unsigned int myCount;

    MemObject()
        : myFile(nullptr)
        , myLine(0)
        , myType(0)
        , mySize(0)
        , myCount(0)
    {}
};

CPPListHead g_Allocations;
unsigned int g_AllocationCount = 0;
size_t g_AllocationBytes = 0;

void MyMemory_ForgetAllPreviousAllocations()
{
    while (g_Allocations.GetHead())
        g_Allocations.RemHead();
}

void MyMemory_ValidateAllocations(bool anIsBreakForLeaksEnabled)
{
    OutputMessage("\\/\\/\\/\\/\\/\\/ Start of memory leak dump \\/\\/\\/\\/\\/\\/ \n");
    for (const CPPListNode* pNode = g_Allocations.HeadNode.Next; pNode->Next; pNode = pNode->Next)
    {
        const auto* memObject = reinterpret_cast<const MemObject*>(pNode);
        assert(memObject->myType == newtype_regular || memObject->myType == newtype_array);
        assert(memObject->Next);
        assert(memObject->Prev);

        OutputMessage("%s(%d): %d bytes unreleased. Count(%d) %s\n", memObject->myFile, memObject->myLine, memObject->mySize, memObject->myCount, memObject->myType == newtype_regular ? "" : "Array Allocation");
    }

    OutputMessage("/\\/\\/\\/\\/\\/\\ End of memory leak dump /\\/\\/\\/\\/\\/\\ \n");

    if (anIsBreakForLeaksEnabled && g_Allocations.GetHead())
        __debugbreak();
}

//===========================================================================================
// Overrides for new/delete with file/line numbers
//===========================================================================================
void* operator new(size_t aSize, const char* aFile, unsigned long aLine)
{
    assert(CountToAssertOn == UINT_MAX || g_AllocationCount != CountToAssertOn);
    assert(aSize > 0);

    const auto memObject = static_cast<MemObject*>(malloc(aSize + sizeof(MemObject)));
    memObject->myFile = aFile;
    memObject->myLine = aLine;
    memObject->myType = newtype_regular;
    memObject->mySize = aSize;
    memObject->myCount = g_AllocationCount++;
    g_AllocationBytes += aSize;
    g_Allocations.AddTail(memObject);

    return reinterpret_cast<char*>(memObject) + sizeof(MemObject);
}

void* operator new[](size_t aSize, const char* aFile, unsigned long aLine)
{
    assert(CountToAssertOn == UINT_MAX || g_AllocationCount != CountToAssertOn);
    assert(aSize > 0);

    const auto memObject = static_cast<MemObject*>(malloc(aSize + sizeof(MemObject)));
    memObject->myFile = aFile;
    memObject->myLine = aLine;
    memObject->myType = newtype_array;
    memObject->mySize = aSize;
    memObject->myCount = g_AllocationCount++;
    g_AllocationBytes += aSize;

    g_Allocations.AddTail(memObject);

    return reinterpret_cast<char*>(memObject) + sizeof(MemObject);
}

void operator delete(void* aPtr, const char* /*aFile*/, unsigned long /*aLine*/)
{
    if (!aPtr)
        return;

    const auto memObject = reinterpret_cast<MemObject*>(static_cast<char*>(aPtr) - sizeof(MemObject));
    assert(memObject->myType == newtype_regular);
    g_AllocationBytes -= memObject->mySize;
    memObject->Remove();

    free(memObject);
}

void operator delete[](void* aPtr, const char* /*aFile*/, unsigned long /*aLine*/)
{
    if (!aPtr)
        return;

    const auto memObject = reinterpret_cast<MemObject*>(static_cast<char*>(aPtr) - sizeof(MemObject));
    assert(memObject->myType == newtype_array);
    g_AllocationBytes -= memObject->mySize;
    memObject->Remove();

    free(memObject);
}

//===========================================================================================
// Overrides for global new/delete
//===========================================================================================
void* operator new(size_t aSize)
{
    return operator new(aSize, "File not defined", 0);
}

void* operator new[](size_t aSize)
{
    return operator new[](aSize, "File not defined", 0);
}

void operator delete(void* aPtr)
{
    operator delete(aPtr, nullptr, 0);
}

void operator delete[](void* aPtr)
{
    operator delete[](aPtr, nullptr, 0);
}
#endif //_DEBUG