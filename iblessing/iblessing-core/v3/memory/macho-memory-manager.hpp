//
//  macho-memory-manager.hpp
//  macho-memory-manager
//
//  Created by Soulghost on 2021/10/17.
//  Copyright © 2021 soulghost. All rights reserved.
//

#ifndef macho_memory_manager_hpp
#define macho_memory_manager_hpp

#include <iblessing-core/v2/common/ibtypes.h>
#include <iblessing-core/v2/vendor/unicorn/unicorn.h>
#include <set>

NS_IB_BEGIN

#define IB_STACK_START          0x300000000
#define IB_STACK_END            0x400000000
#define IB_STACK_SIZE           0x100000
#define IB_STACK_MASK           (IB_STACK_SIZE-1)
#define IB_SMALLHEAP_START      0x500000000
#define IB_SMALLHEAP_SIZE       0x100000000

class MachOMemoryManager {
public:
    MachOMemoryManager(uc_engine *uc);
    
    uint64_t alloc(size_t size, std::string tag = "");
    uint64_t allocPath(std::string path);
    void dealloc(uint64_t addr);
    
    uint64_t stackNew();
    void stackDelete(uint64_t addr_in_stack);
    uint64_t stackPush(uint64_t *stackTop, size_t size);
    uint64_t stackPop(uint64_t *stackTop, size_t size);
    
    void *mmapSharedMem(uint64_t guest_addr, size_t size, int prot);
    void *mmapWrapper(uint64_t guest_addr, size_t size, int prot, int flags, int fd, off_t off);

    
private:
    uc_engine *uc;
    uint64_t allocatedCur;
    uint64_t allocateBegin;
    uint64_t allocateEnd;
    
    uint64_t stackBegin;
    uint64_t stackEnd;
    
    std::set<uint64_t> usedStackStarts;
    
    bool use_shared;
};

NS_IB_END

#endif /* macho_memory_manager_hpp */
