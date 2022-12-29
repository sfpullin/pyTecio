 #pragma once
#include "SzlFileLoader.h"
static uint16_t const MAX_REFS_FOR_2_BIT_COMPRESSION = 4; static uint16_t const MAX_REFS_FOR_4_BIT_COMPRESSION = 1+0xF; static uint16_t const MAX_REFS_FOR_8_BIT_COMPRESSION = 1+0xFF; namespace tecplot { namespace ___3931 { template <typename ReferencedType> void gather2BitOffsets( uint8_t* offsets, ReferencedType const* references, uint64_t numReferences, ReferencedType const* referencedItems, uint64_t numReferencedItems) { REQUIRE(0 < numReferencedItems && numReferencedItems <= MAX_REFS_FOR_2_BIT_COMPRESSION); ReferencedType const* first = &referencedItems[0]; ReferencedType const* last = &referencedItems[numReferencedItems - 1] + 1; for(uint64_t i = 0; i < numReferences / 4; ++i) { uint8_t combinedOffsets = 0; for(uint64_t ___2103 = 0; ___2103 < 4; ++___2103) { ReferencedType const ref = references[i * 4 + ___2103]; ReferencedType const* current = std::lower_bound(first, last, ref); ___476(*current == ref); size_t const ___2863 = std::distance(first, current); ___476(___2863 < MAX_REFS_FOR_2_BIT_COMPRESSION); combinedOffsets = (combinedOffsets << 2) | static_cast<uint8_t>(___2863); } offsets[i] = combinedOffsets; } uint64_t leftovers = numReferences % 4; if (leftovers != 0) { uint8_t combinedOffsets = 0; uint64_t ___3679 = (numReferences / 4) * 4; for(uint64_t ___2103 = 0; ___2103 < leftovers; ++___2103) { ReferencedType const ref = references[___3679 + ___2103]; ReferencedType const* current = std::lower_bound(first, last, ref); ___476(*current == ref); size_t const ___2863 = std::distance(first, current); ___476(___2863 < MAX_REFS_FOR_2_BIT_COMPRESSION); combinedOffsets = (combinedOffsets << 2) | static_cast<uint8_t>(___2863); } for(uint64_t ___2103 = leftovers; ___2103 < 4; ++___2103) { combinedOffsets = (combinedOffsets << 2); } offsets[numReferences / 4] = combinedOffsets; } } template <typename ReferencedType> void gather4BitOffsets( uint8_t* offsets, ReferencedType const* references, uint64_t numReferences, ReferencedType const* referencedItems, uint64_t numReferencedItems) { REQUIRE(MAX_REFS_FOR_2_BIT_COMPRESSION < numReferencedItems && numReferencedItems <= MAX_REFS_FOR_4_BIT_COMPRESSION); ReferencedType const* first = &referencedItems[0]; ReferencedType const* last = &referencedItems[numReferencedItems - 1] + 1; for(uint64_t i = 0; i < numReferences / 2; ++i) { ReferencedType const ref1 = references[i * 2]; ReferencedType const* current = std::lower_bound(first, last, ref1); ___476(*current == ref1); size_t const offset1 = std::distance(first, current); ___476(offset1 <= 0xF); ReferencedType const ref2 = references[i * 2 + 1]; current = std::lower_bound(first, last, ref2); ___476(*current == ref2); size_t const offset2 = std::distance(first, current); ___476(offset2 <= 0xF); offsets[i] = uint8_t(offset1 << 4) | uint8_t(offset2); } if (numReferences % 2 == 1) { ReferencedType const ref1 = references[numReferences - 1]; ReferencedType const* current = std::lower_bound(first, last, ref1); ___476(*current == ref1); size_t const offset1 = std::distance(first, current); ___476(offset1 <= 0xF); size_t const offset2 = 0; offsets[numReferences / 2] = uint8_t(offset1 << 4) | uint8_t(offset2);
} } template <typename OffsetType, typename ReferencedType> void gatherOffsets( OffsetType* offsets, ReferencedType const* references, uint64_t numReferences, ReferencedType const* referencedItems, uint64_t numReferencedItems) { REQUIRE(numReferences > 0); REQUIRE(numReferencedItems > MAX_REFS_FOR_4_BIT_COMPRESSION); ReferencedType const* first = &referencedItems[0]; ReferencedType const* last = &referencedItems[numReferencedItems - 1] + 1; for(uint64_t i = 0; i < numReferences; ++i) { ReferencedType const reference = references[i]; ReferencedType const* current = std::lower_bound(first, last, reference); ___476(*current == reference); size_t const ___2863 = std::distance(first, current); ___476(___2863 <= (OffsetType)(-1)); offsets[i] = (OffsetType)(___2863); } } }}