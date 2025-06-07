#ifndef ZTD_HEAP_H
#define ZTD_HEAP_H

#include "ztd/heap/debug_allocator.h"
#include "ztd/heap/fixed_buffer_allocator.h"
#include "ztd/heap/page_allocator.h"

namespace ztd { namespace heap {
    typedef DebugAllocator GeneralPurposeAllocator;
}}

#endif
