#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <memory_resource>
#include <stdexcept>

class MemoryResource : public std::pmr::memory_resource {
public:
    explicit MemoryResource(size_t totalSize)
        : 
        m_TotalSize(totalSize),
        m_Data(new char[totalSize]),
        m_Used(0) 
    {}
    ~MemoryResource() {
        Reset(); 
        delete[] m_Data;
    }
protected:
    void* do_allocate(size_t bytes, size_t alignment) override {
        size_t offset = reinterpret_cast<size_t>(m_Data + m_Used) % alignment;
        if (offset != 0) {
            offset = alignment - offset;
        }

        size_t used = m_Used + offset + bytes;
        if (used > m_TotalSize) {
            throw std::bad_alloc(); 
        }

        void *result = m_Data + m_Used + offset;
        m_Blocks[result] = bytes; 
        m_Used = used;
        return result;
    }
    void do_deallocate(void *ptr, size_t bytes, size_t alignment) override {
        auto it = m_Blocks.find(ptr);
        if (it == m_Blocks.end() || it->second != bytes) {
            throw std::invalid_argument("Trying to deallocate invalid memory block");
        }

        m_FreeBlocks.emplace_back(ptr,bytes);
        m_Blocks.erase(it);
    }
    bool do_is_equal(const std::pmr::memory_resource &other) const noexcept override {
        return this == &other;
    }
private:
    void Reset() {
        m_Blocks.clear();
        m_FreeBlocks.clear();
        m_Used = 0;
    }
private:
    size_t m_TotalSize;
    char* m_Data;
    size_t m_Used;
    std::map<void*, size_t> m_Blocks;
    std::vector<std::pair<void *, size_t>> m_FreeBlocks;
};