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
    const char* m_file;
    unsigned long m_line;
    unsigned int m_type;
    unsigned int m_size;
    unsigned int m_count;

    MemObject()
        : m_file(nullptr)
        , m_line(0)
        , m_type(0)
        , m_size(0)
        , m_count(0)
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

void MyMemory_ValidateAllocations(bool breakIfThereAreLeaks)
{
    OutputMessage("\\/\\/\\/\\/\\/\\/ Start of memory leak dump \\/\\/\\/\\/\\/\\/ \n");
    for (const CPPListNode* pNode = g_Allocations.HeadNode.Next; pNode->Next; pNode = pNode->Next)
    {
        const auto* memObject = static_cast<const MemObject*>(pNode);
        assert(memObject->m_type == newtype_regular || memObject->m_type == newtype_array);
        assert(memObject->Next);
        assert(memObject->Prev);

        OutputMessage("%s(%d): %d bytes unreleased. Count(%d) %s\n", memObject->m_file, memObject->m_line, memObject->m_size, memObject->m_count, memObject->m_type == newtype_regular ? "" : "Array Allocation");
    }

    OutputMessage("/\\/\\/\\/\\/\\/\\ End of memory leak dump /\\/\\/\\/\\/\\/\\ \n");

    if (breakIfThereAreLeaks && g_Allocations.GetHead())
        __debugbreak();
}

//===========================================================================================
// Overrides for new/delete with file/line numbers
//===========================================================================================
void* operator new(size_t size, const char* file, unsigned long line)
{
    assert(CountToAssertOn == UINT_MAX || g_AllocationCount != CountToAssertOn);
    assert(size > 0);

    const auto memObject = static_cast<MemObject*>(malloc(size + sizeof(MemObject)));
    memObject->m_file = file;
    memObject->m_line = line;
    memObject->m_type = newtype_regular;
    memObject->m_size = size;
    memObject->m_count = g_AllocationCount++;
    g_AllocationBytes += size;
    g_Allocations.AddTail(memObject);

    return reinterpret_cast<char*>(memObject) + sizeof(MemObject);
}

void* operator new[](size_t size, const char* file, unsigned long line)
{
    assert(CountToAssertOn == UINT_MAX || g_AllocationCount != CountToAssertOn);
    assert(size > 0);

    const auto memObject = static_cast<MemObject*>(malloc(size + sizeof(MemObject)));
    memObject->m_file = file;
    memObject->m_line = line;
    memObject->m_type = newtype_array;
    memObject->m_size = size;
    memObject->m_count = g_AllocationCount++;
    g_AllocationBytes += size;

    g_Allocations.AddTail(memObject);

    return reinterpret_cast<char*>(memObject) + sizeof(MemObject);
}

void operator delete(void* ptr, const char* file, unsigned long line)
{
    if (!ptr)
        return;

    const auto memObject = reinterpret_cast<MemObject*>(static_cast<char*>(ptr) - sizeof(MemObject));
    assert(memObject->m_type == newtype_regular);
    g_AllocationBytes -= memObject->m_size;
    memObject->Remove();

    free(memObject);
}

void operator delete[](void* ptr, const char* file, unsigned long line)
{
    if (!ptr)
        return;

    const auto memObject = reinterpret_cast<MemObject*>(static_cast<char*>(ptr) - sizeof(MemObject));
    assert(memObject->m_type == newtype_array);
    g_AllocationBytes -= memObject->m_size;
    memObject->Remove();

    free(memObject);
}

//===========================================================================================
// Overrides for global new/delete
//===========================================================================================
void* operator new(size_t size)
{
    return operator new(size, "File not defined", 0);
}

void* operator new[](size_t size)
{
    return operator new[](size, "File not defined", 0);
}

void operator delete(void* ptr)
{
    operator delete(ptr, nullptr, 0);
}

void operator delete[](void* ptr)
{
    operator delete[](ptr, nullptr, 0);
}
#endif //_DEBUG