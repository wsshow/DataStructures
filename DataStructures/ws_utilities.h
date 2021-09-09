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
/// 内存拷贝操作(有效避免内存重叠问题)
/// </summary>
/// <param name="dst">目标地址</param>
/// <param name="src">原地址</param>
/// <param name="size">原内存大小</param>
/// <returns>dst首地址</returns>
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
/// 内存拷贝操作(有内存重叠问题)
/// </summary>
/// <param name="dst">目标地址</param>
/// <param name="src">原地址</param>
/// <param name="size">原内存大小</param>
/// <returns>dst首地址</returns>
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
/// 返回指定范围内的随机数
/// </summary>
/// <param name="b">区间下限</param>
/// <param name="e">区间上限</param>
/// <returns></returns>
int ws_random(int b, int e)
{
    std::random_device sd;
    std::minstd_rand linearRan(sd());
    std::uniform_int_distribution<int> dis(b, e);
    return dis(linearRan);
}

#endif // INCLUDE_WS_UTILITIES_HPP