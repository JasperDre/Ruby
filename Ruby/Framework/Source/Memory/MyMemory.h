#pragma once

#if _DEBUG
void MyMemory_ForgetAllPreviousAllocations();
void MyMemory_ValidateAllocations(bool anIsBreakForLeaksEnabled);

void* operator new(size_t aSize, const char* aFile, unsigned long aLine);
void* operator new[](size_t aSize, const char* aFile, unsigned long aLine);
void operator delete(void* ptr, const char* file, unsigned long line);
void operator delete[](void* ptr, const char* file, unsigned long line);

void* operator new(size_t size);
void* operator new[](size_t size);
void operator delete(void* ptr);
void operator delete[](void* ptr);

#define new new(__FILE__, __LINE__)
#endif //_DEBUG