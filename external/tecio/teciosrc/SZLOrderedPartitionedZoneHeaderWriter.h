 #pragma once
#include "SzlFileLoader.h"
#include "ZoneHeaderWriterAbstract.h"
namespace tecplot { namespace ___3931 { class ItemSetIterator; class SZLOrderedPartitionedZoneHeaderWriter : public ZoneHeaderWriterAbstract { public: SZLOrderedPartitionedZoneHeaderWriter( ItemSetIterator&                  varIter, ___4634                       zone, ___4634                       ___341, ___37&                       ___36, ___2238<int32_t> const& partitionFileNums, UInt64Array const&                partitionHeaderFilePositions, UInt64Array const&                partitionMinCornerNodes, UInt64Array const&                partitionMaxCornerNodes, VarZoneMinMaxArray const&         varPartitionMinMaxes); virtual ~SZLOrderedPartitionedZoneHeaderWriter(); virtual uint64_t sizeInFile(bool ___2000) const; virtual ___372 write(FileWriterInterface& fileWriter) const; private: ___2238<int32_t> const& m_partitionFileNums; UInt64Array const& m_partitionHeaderFilePositions; UInt64Array const& m_partitionMinNodeNumbers; UInt64Array const& m_partitionMaxCornerNodes; VarZoneMinMaxArray const& m_varPartitionMinMaxes; }; }}