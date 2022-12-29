 #pragma once
#include "ThirdPartyHeadersBegin.h"
#include <mpi.h>
#include "ThirdPartyHeadersEnd.h"
#include "basicTypes.h"
#include "ZoneWriterFactory.h"
namespace tecplot { namespace ___3931 { class ___37; class ZoneInfoCache; class ___4707; class ItemSetIterator; }} namespace tecplot { namespace teciompi { class ZoneWriterFactoryMPI : public ___3931::___4709 { public: ZoneWriterFactoryMPI( ___3931::ZoneInfoCache& zoneInfoCache, ___3931::___37&    ___36, MPI_Comm              communicator, int                   mainProcess); boost::shared_ptr<___3931::___4707> ___4706( ___3931::ItemSetIterator&       varIter, ___3931::___4634            zone, ___3931::___4634            ___341, std::vector<___372> const& ___4562, ___372                     ___4497); private: MPI_Comm m_communicator; int m_mainProcess; }; }}
