#include "ClassicFEZoneConnectivityWriter.h"
#include "NodeMap.h"
#include "SzlFileLoader.h"
#include "writeValueArray.h"
namespace tecplot { namespace ___3931 { ClassicFEZoneConnectivityWriter::ClassicFEZoneConnectivityWriter( ___4634 zone, ___4634 ___341, ___37& ___36) : ___2675(zone) , m_baseZone(___341) , ___2335(___36) , m_zoneNumberLabel(SZPLT_ZONE_NUM_DESCRIPTION) {} uint64_t ClassicFEZoneConnectivityWriter::nodeMapHeaderSizeInFile(bool ___2000) { if (___2000) return 2 * valueSizeInFile<uint32_t, false>(___2000); else return 0; } ___372 ClassicFEZoneConnectivityWriter::___4528(FileWriterInterface& file) { ___372 ___2037 = ___4224; REQUIRE(file.___2039()); if ( file.___2000() ) { writeValue<uint32_t, false, 0>(file, "nodeMapMarker*", SZPLT_NODE_MAP_MARKER); writeValue<uint32_t, false, 0>(file, m_zoneNumberLabel.c_str(), (___2675 - m_baseZone + 1)); } ENSURE(VALID_BOOLEAN(___2037)); return ___2037; } uint64_t ClassicFEZoneConnectivityWriter::cellConnectivitySizeInFile(bool ___2000) { ___2722 ___2721(&___2335, ___2675 + 1); size_t ___2793 = static_cast<size_t>(___2721.___1764()) * ___2721.___1762(); return arraySizeInFile<int32_t, false>(___2793, ___2000); } ___372 ClassicFEZoneConnectivityWriter::writeCellConnectivity(FileWriterInterface& fileWriter) { ___2722 ___2721(&___2335, ___2675 + 1); ___1963 nodeMapArray; size_t ___2793 = static_cast<size_t>(___2721.___1764()) * ___2721.___1762(); ___372 ___2037 = ___2721.___2065(); ___2037 = ___2037 && nodeMapArray.alloc(___2793); if (___2037) { for(int32_t ___447 = 0; ___447 < ___2721.___1764(); ++___447) { for(int32_t ___679 = 0; ___679 < ___2721.___1762(); ++___679) { int32_t ___2707 = checked_numeric_cast<int32_t>(___2721.___1761(___447 + 1, ___679 + 1) - 1); nodeMapArray[___447 * ___2721.___1762() + ___679] = ___2707; } } ___2037 = ___2037 && ___4561<int32_t, false, 0>(fileWriter, "NodeMap", ___2743, ___2793, &nodeMapArray[0]); } ENSURE(VALID_BOOLEAN(___2037)); return ___2037; } uint64_t ClassicFEZoneConnectivityWriter::sizeInFile(bool ___2000) { return nodeMapHeaderSizeInFile(___2000) + cellConnectivitySizeInFile(___2000); } ___372 ClassicFEZoneConnectivityWriter::write(FileWriterInterface& fileWriter) { ___372 ___2037 = ___4528(fileWriter) && writeCellConnectivity(fileWriter); return ___2037; } }}