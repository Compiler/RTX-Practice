#include "TextureManager.h"

namespace reach{

    std::unordered_map<uint64_t, int32_t> TextureManager::_hashToGLID;
    std::unordered_map<uint64_t, int32_t> TextureManager::_hashToSlot;
    uint64_t* TextureManager::_textureSlots;
    int32_t TextureManager::_availableSlots;
    uint16_t TextureManager::_currentIndex;

}