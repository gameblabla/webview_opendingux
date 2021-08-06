/*
 * Copyright (C) 2012 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CopyVisitorInlines_h
#define CopyVisitorInlines_h

#include "CopyVisitor.h"
#include "Heap.h"

namespace JSC {

inline bool CopyVisitor::checkIfShouldCopy(void* oldPtr)
{
    if (!oldPtr)
        return false;
    CopiedBlock* block = CopiedSpace::blockFor(oldPtr);
    if (block->isOversize() || block->isPinned())
        return false;
    return true;
}

inline void* CopyVisitor::allocateNewSpace(size_t bytes)
{
    void* result = 0; // Compilers don't realize that this will be assigned.
    if (LIKELY(m_copiedAllocator.tryAllocateDuringCopying(bytes, &result)))
        return result;
    
    result = allocateNewSpaceSlow(bytes);
    ASSERT(result);
    return result;
}       

inline void* CopyVisitor::allocateNewSpaceSlow(size_t bytes)
{
    CopiedBlock* newBlock = 0;
    m_heap.m_storageSpace.doneFillingBlock(m_copiedAllocator.resetCurrentBlock(), &newBlock);
    m_copiedAllocator.setCurrentBlock(newBlock);

    void* result = 0;
    CheckedBoolean didSucceed = m_copiedAllocator.tryAllocateDuringCopying(bytes, &result);
    ASSERT(didSucceed);
    return result;
}

inline void CopyVisitor::didCopy(void* ptr, size_t bytes)
{
    CopiedBlock* block = CopiedSpace::blockFor(ptr);
    ASSERT(!block->isOversize());
    ASSERT(!block->isPinned());

    block->didEvacuateBytes(bytes);
}

} // namespace JSC

#endif // CopyVisitorInlines_h
