#include "ZoneWriterFactoryMPI.h"
#include "ThirdPartyHeadersBegin.h"
#include <boost/make_shared.hpp>
#include <boost/ref.hpp>
#include "ThirdPartyHeadersEnd.h"
#include "AltTecUtil.h"
#include "ItemSetIterator.h"
#include "SZLFEPartitionedZoneWriterMPI.h"
#include "SZLOrderedPartitionedZoneWriterMPI.h"
#include "zoneUtil.h"
using namespace tecplot::___3931; namespace tecplot { namespace teciompi { ZoneWriterFactoryMPI::ZoneWriterFactoryMPI( ZoneInfoCache& zoneInfoCache, ___37&    ___36, MPI_Comm       communicator, int            mainProcess) : ___4709(zoneInfoCache, ___36) , m_communicator(communicator) , m_mainProcess(mainProcess) {} boost::shared_ptr<___4707> ZoneWriterFactoryMPI::___4706( ItemSetIterator&              varIter, ___4634                   zone, ___4634                   ___341, std::vector<___372> const& ___4562, ___372                     ___4497) { REQUIRE(0 <= zone && ___2335.___4636(zone + 1)); REQUIRE(0 <= ___341 && ___341 <= zone); REQUIRE(varIter.___2810() == static_cast<___4350>(___4562.size())); REQUIRE(VALID_BOOLEAN(___4497)); ZoneType_e ___4690 = ___2335.___4618(zone + 1); if (zoneIsPartitioned(___2335, zone)) { if (___4690 == ___4702) { return boost::make_shared<SZLOrderedPartitionedZoneWriterMPI>( boost::ref(varIter), zone, ___341, boost::ref(___4562), ___4497, boost::ref(___2335), boost::ref(___2678), m_communicator, m_mainProcess); } else { ___476(___4690 == ___4699 || ___4690 == ___4693); return boost::make_shared<SZLFEPartitionedZoneWriterMPI>( boost::ref(varIter), zone, ___341, boost::ref(___4562), ___4497, boost::ref(___2335), boost::ref(___2678), m_communicator, m_mainProcess); } } else { return ___4709::___4706(varIter, zone, ___341, ___4562, ___4497); } } }}
