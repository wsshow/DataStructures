#ifndef INCLUDE_WS_UTILITIES_HPP
#define INCLUDE_WS_UTILITIES_HPP

#pragma once
#include <cassert>
#include <crtdbg.h>

#ifdef _DEBUG
#define DEBUG_CHECK_MEMORY_LEAKS (_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CHECK_MEMORY_LEAKS
#endif // check memory leaks

/// <summary>
/// �ڴ濽������(��Ч�����ڴ��ص�����)
/// </summary>
/// <param name="dst">Ŀ���ַ</param>
/// <param name="src">ԭ��ַ</param>
/// <param name="size">ԭ�ڴ��С</param>
/// <returns>dst�׵�ַ</returns>
void* ws_memmove(void* dst, const void* src, size_t size)
{
    assert(nullptr != src && nullptr != dst);

    char* tmpDst = (char*)dst;
    const char* tmpSrc = (const char*)src;

    if (tmpDst <= tmpSrc || tmpDst >= tmpSrc + size)
    {
        while (size--)
        {
            *tmpDst++ = *tmpSrc++;
        }
    }
    else
    {
        tmpDst += size;
        tmpSrc += size;
        while (size--)
        {
            *--tmpDst = *--tmpSrc;
        }
    }

    return dst;
}

/// <summary>
/// �ڴ濽������(���ڴ��ص�����)
/// </summary>
/// <param name="dst">Ŀ���ַ</param>
/// <param name="src">ԭ��ַ</param>
/// <param name="size">ԭ�ڴ��С</param>
/// <returns>dst�׵�ַ</returns>
void* ws_memcpy(void* dst, const void* src, size_t size)
{
    assert(nullptr != src && nullptr != dst);

    char* tmpDst = (char*)dst;
    const char* tmpSrc = (const char*)src;

    while (size--)
    {
        *tmpDst++ = *tmpSrc++;
    }
        
    return dst;
}

#include <random>
/// <summary>
/// ����ָ����Χ�ڵ������
/// </summary>
/// <param name="b">��������</param>
/// <param name="e">��������</param>
/// <returns></returns>
int ws_random(int b, int e)
{
    std::random_device sd;
    std::minstd_rand linearRan(sd());
    std::uniform_int_distribution<int> dis(b, e);
    return dis(linearRan);
}

#endif // INCLUDE_WS_UTILITIES_HPP