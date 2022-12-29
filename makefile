tecio/libtecplotreader.so : lib/libtecplotreader.so
	cp lib/libtecplotreader.so tecio/libtecplotreader.so

lib/libtecplotreader.so : lib/tecplotreader.o lib/reader_ctypes.o lib/libtecio.a
	g++ -shared -o lib/libtecplotreader.so lib/tecplotreader.o lib/reader_ctypes.o lib/libtecio.a

lib/tecplotreader.o : src/tecplotReader.cpp src/tecplotReader.h src/TECIO.h src/tecio_Exports.h src/StandardIntegralTypes.h
	g++ -c -fPIC src/tecplotReader.cpp -o lib/tecplotreader.o

lib/reader_ctypes.o : src/reader_ctypes.cpp
	g++ -c -fPIC src/reader_ctypes.cpp -o lib/reader_ctypes.o


# This should handle recompiling library if new version of tecio is installed

TECIOSRC = external/tecio/teciosrc/

SRCS =${TECIOSRC}/arrlist.cpp \
       ${TECIOSRC}/AsciiOutputInfo.cpp \
       ${TECIOSRC}/auxdata.cpp \
       ${TECIOSRC}/checkPercentDone.cpp \
       ${TECIOSRC}/ClassicFEZoneConnectivityWriter.cpp \
       ${TECIOSRC}/ClassicFEZoneFaceNeighborGenerator.cpp \
       ${TECIOSRC}/ClassicFEZoneWriter.cpp \
       ${TECIOSRC}/ClassicOrderedZoneFaceNeighborGenerator.cpp \
       ${TECIOSRC}/ClassicOrderedZoneWriter.cpp \
       ${TECIOSRC}/ClassicZoneFaceNeighborWriter.cpp \
       ${TECIOSRC}/ClassicZoneHeaderWriter.cpp \
       ${TECIOSRC}/ClassicZoneVariableWriter.cpp \
       ${TECIOSRC}/ClassicZoneWriterAbstract.cpp \
       ${TECIOSRC}/dataio4.cpp \
       ${TECIOSRC}/dataio.cpp \
       ${TECIOSRC}/dataset0.cpp \
       ${TECIOSRC}/dataset.cpp \
       ${TECIOSRC}/DataSetWriter.cpp \
       ${TECIOSRC}/datautil.cpp \
       ${TECIOSRC}/exportSubzonePlt.cpp \
       ${TECIOSRC}/FaceNeighborGeneratorAbstract.cpp \
       ${TECIOSRC}/FECellSubzoneCompressor.cpp \
       ${TECIOSRC}/FieldData.cpp \
       ${TECIOSRC}/FieldData_s.cpp \
       ${TECIOSRC}/FileIOStream.cpp \
       ${TECIOSRC}/FileStreamReader.cpp \
       ${TECIOSRC}/FileStreamWriter.cpp \
       ${TECIOSRC}/filestream.cpp \
       ${TECIOSRC}/FileSystem.cpp \
       ${TECIOSRC}/fileStuff.cpp \
       ${TECIOSRC}/geom2.cpp \
       ${TECIOSRC}/Geom_s.cpp \
       ${TECIOSRC}/IJKSubzoneInfo.cpp \
       ${TECIOSRC}/IJKZoneInfo.cpp \
       ${TECIOSRC}/importSzPltFile.cpp \
       ${TECIOSRC}/IntervalTree.cpp \
       ${TECIOSRC}/MinMaxTree.cpp \
       ${TECIOSRC}/NodeMap.cpp \
       ${TECIOSRC}/NodeToElemMap_s.cpp \
       ${TECIOSRC}/ORBFESubzonePartitioner.cpp \
       ${TECIOSRC}/OrthogonalBisection.cpp \
       ${TECIOSRC}/PartitionTecUtilDecorator.cpp \
       ${TECIOSRC}/q_msg.cpp \
       ${TECIOSRC}/readValueArray.cpp \
       ${TECIOSRC}/Scanner.cpp \
       ${TECIOSRC}/set.cpp \
       ${TECIOSRC}/strlist.cpp \
       ${TECIOSRC}/strutil.cpp \
       ${TECIOSRC}/SZLFEPartitionedZoneHeaderWriter.cpp \
       ${TECIOSRC}/SZLFEPartitionedZoneWriter.cpp \
       ${TECIOSRC}/SZLFEPartitionWriter.cpp \
       ${TECIOSRC}/SZLFEZoneHeaderWriter.cpp \
       ${TECIOSRC}/SZLFEZoneWriter.cpp \
       ${TECIOSRC}/SZLOrderedPartitionedZoneHeaderWriter.cpp \
       ${TECIOSRC}/SZLOrderedPartitionedZoneWriter.cpp \
       ${TECIOSRC}/SZLOrderedPartitionWriter.cpp \
       ${TECIOSRC}/SZLOrderedZoneHeaderWriter.cpp \
       ${TECIOSRC}/SZLOrderedZoneWriter.cpp \
       ${TECIOSRC}/tecio.cpp \
       ${TECIOSRC}/TecioData.cpp \
       ${TECIOSRC}/TecioPLT.cpp \
       ${TECIOSRC}/TecioSZL.cpp \
       ${TECIOSRC}/TecioTecUtil.cpp \
       ${TECIOSRC}/TranslatedString.cpp \
       ${TECIOSRC}/UnicodeStringUtils.cpp \
       ${TECIOSRC}/writeValueArray.cpp \
       ${TECIOSRC}/ZoneHeaderWriterAbstract.cpp \
       ${TECIOSRC}/ZoneInfoCache.cpp \
       ${TECIOSRC}/Zone_s.cpp \
       ${TECIOSRC}/ZoneVarMetadata.cpp \
       ${TECIOSRC}/ZoneWriterAbstract.cpp \
       ${TECIOSRC}/ZoneWriterFactory.cpp



src/TECIO.h : lib/libtecio.a

src/tecio_Exports.h : lib/libtecio.a

src/StandardIntegralTypes.h : lib/libtecio.a

lib/libtecio.a :${SRCS}
	
	cd ${TECIOSRC} && cmake . && make

	cp ${TECIOSRC}/TECIO.h src/
	cp ${TECIOSRC}/tecio_Exports.h src/
	cp ${TECIOSRC}/StandardIntegralTypes.h src/
	cp ${TECIOSRC}/libtecio.a lib/
	

