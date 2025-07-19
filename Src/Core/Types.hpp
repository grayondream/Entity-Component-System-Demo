#pragma once
#include <cstdint>
#include <bitset>

using Entity = std::uint32_t;
constexpr static inline std::size_t kMaxEntities = 4096;

using ComponentType = std::uint8_t;
constexpr static inline ComponentType kMaxComponents = 128;
using Signature = std::bitset<kMaxComponents>;