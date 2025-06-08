#ifndef ZTA_HEAP_H
#define ZTA_HEAP_H

#include "zta/heap/debug_allocator.h"
#include "zta/heap/fixed_buffer_allocator.h"
#include "zta/heap/page_allocator.h"

namespace zta { namespace heap {
    typedef DebugAllocator GeneralPurposeAllocator;
}}

#endif
