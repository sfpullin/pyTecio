#include "MPICommunicationCache.h"
#include "ThirdPartyHeadersBegin.h"
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/variant.hpp>
#include <sstream>
#include <vector>
#include "ThirdPartyHeadersEnd.h"
#include "CodeContract.h"
#include "basicTypes.h"
#include "MinMax.h"
namespace tecplot { namespace teciompi { namespace { enum DataType_e { DataType_char, DataType_uint8_t, DataType_int16_t, DataType_uint16_t, DataType_int32_t, DataType_uint32_t, DataType_int64_t, DataType_uint64_t, DataType_float, DataType_double, DataType_MinMax }; template <typename T> struct encodedDataType {}; template<> struct encodedDataType<char>     { static DataType_e const m_dataType = DataType_char; }; template<> struct encodedDataType<uint8_t>  { static DataType_e const m_dataType = DataType_uint8_t; }; template<> struct encodedDataType<uint16_t> { static DataType_e const m_dataType = DataType_uint16_t; }; template<> struct encodedDataType<int32_t>  { static DataType_e const m_dataType = DataType_int32_t; }; template<> struct encodedDataType<uint32_t> { static DataType_e const m_dataType = DataType_uint32_t; }; template<> struct encodedDataType<int64_t>  { static DataType_e const m_dataType = DataType_int64_t; }; template<> struct encodedDataType<uint64_t> { static DataType_e const m_dataType = DataType_uint64_t; }; template<> struct encodedDataType<float>    { static DataType_e const m_dataType = DataType_float; }; template<> struct encodedDataType<double>   { static DataType_e const m_dataType = DataType_double; }; template<> struct encodedDataType<___2477>   { static DataType_e const m_dataType = DataType_MinMax; }; } struct MPICommunicationCache::Impl { typedef boost::variant<char, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t, float, double, ___2477, SimpleVector<uint8_t> > VariantType; struct TypeSize : public boost::static_visitor<int32_t> { template <typename T> int32_t operator()(T) const { return sizeof(T); } int32_t operator()(SimpleVector<uint8_t> const& ___4289) const { return ___4289.size(); } }; struct ValueEncoder : public boost::static_visitor<void> { uint8_t& m_destination; explicit ValueEncoder(uint8_t& destination) : m_destination(destination) {} template <typename T> void operator()(T scalar) const { reinterpret_cast<T&>(m_destination) = scalar; } void operator()(SimpleVector<uint8_t> const& ___4289) const { memcpy(&m_destination, ___4289.begin(), ___4289.size()); } }; struct DataItem { int32_t m_tag; DataType_e m_dataType; int32_t m_length; VariantType m_data; DataItem() {} explicit DataItem(uint8_t const* encodedItem) { REQUIRE(VALID_REF(encodedItem)); int index = 0; m_tag = reinterpret_cast<int32_t const&>(encodedItem[index]); index += sizeof(int32_t); m_dataType = static_cast<DataType_e>(reinterpret_cast<int32_t const&>(encodedItem[index])); index += sizeof(int32_t); m_length = reinterpret_cast<int32_t const&>(encodedItem[index]); index += sizeof(int32_t); if (m_length == 0) { switch (m_dataType) { case DataType_char: m_data = reinterpret_cast<char const&>(encodedItem[index]); break; case DataType_uint8_t: m_data = reinterpret_cast<uint8_t const&>(encodedItem[index]); break; case DataType_int16_t: m_data = reinterpret_cast<int16_t const&>(encodedItem[index]); break; case DataType_uint16_t: m_data = reinterpret_cast<uint16_t const&>(encodedItem[index]);
break; case DataType_int32_t: m_data = reinterpret_cast<int32_t const&>(encodedItem[index]); break; case DataType_uint32_t: m_data = reinterpret_cast<uint32_t const&>(encodedItem[index]); break; case DataType_int64_t: m_data = reinterpret_cast<int64_t const&>(encodedItem[index]); break; case DataType_uint64_t: m_data = reinterpret_cast<uint64_t const&>(encodedItem[index]); break; case DataType_float: m_data = reinterpret_cast<float const&>(encodedItem[index]); break; case DataType_double: m_data = reinterpret_cast<double const&>(encodedItem[index]); break; case DataType_MinMax: m_data = reinterpret_cast<___2477 const&>(encodedItem[index]); break; default: throw Error("Encountered unsupported data type."); break; } } else { m_data = SimpleVector<uint8_t>(&encodedItem[index], m_length); } } int32_t encodedSize() { int32_t ___3356 = 3 * sizeof(uint32_t); ___3356 += boost::apply_visitor(TypeSize(), m_data); return ___3356; } void encode(uint8_t* encodedItem) { REQUIRE(VALID_REF(encodedItem)); int index = 0; reinterpret_cast<int32_t&>(encodedItem[index]) = m_tag; index += sizeof(int32_t); reinterpret_cast<int32_t&>(encodedItem[index]) = static_cast<int32_t>(m_dataType); index += sizeof(int32_t); reinterpret_cast<int32_t&>(encodedItem[index]) = m_length; index += sizeof(int32_t); boost::apply_visitor(ValueEncoder(encodedItem[index]), m_data); } }; typedef boost::shared_ptr<DataItem> DataItemPtr; template <typename T> DataItemPtr addItem(int32_t tag, int32_t length) { DataItemPtr ___3356 = boost::make_shared<DataItem>(); ___3356->m_tag = tag; ___3356->m_dataType = encodedDataType<T>::m_dataType; ___3356->m_length = length; m_dataItems.push_back(___3356); return ___3356; } template <typename T> DataItemPtr addScalarItem(T ___4296, int32_t tag) { DataItemPtr ___3356 = addItem<T>(tag, 0); ___3356->m_data = ___4296; return ___3356; } template <typename T> DataItemPtr addVectorItem(SimpleVector<T> const& vec, int32_t tag) { int32_t length = vec.size() * static_cast<int>(sizeof(T)); DataItemPtr ___3356 = addItem<T>(tag, length); ___3356->m_data = SimpleVector<uint8_t>(reinterpret_cast<uint8_t const*>(vec.begin()), length); return ___3356; } DataItemPtr addEncodedItem(uint8_t const* encodedItem) { DataItemPtr ___3356 = boost::make_shared<DataItem>(encodedItem); m_dataItems.push_back(___3356); return ___3356; } template <typename T> DataItemPtr nextItem(int32_t tag) { if (m_dataItems.empty()) { std::ostringstream ___2890; ___2890 << "MPICommunicationCache: tag " << tag << " not found."; throw Error(___2890.str()); } else if (m_dataItems[m_index]->m_tag != tag) { std::ostringstream ___2890; ___2890 << "MPICommunicationCache: tag " << tag << " is not the next sequential tag in the cache."; throw Error(___2890.str()); } else if (m_dataItems[m_index]->m_dataType != encodedDataType<T>::m_dataType) { std::ostringstream ___2890; ___2890 << "MPICommunicationCache: MPI data type " << m_dataItems[m_index]->m_dataType << " found for next item of tag " << tag << ". Type " << encodedDataType<T>::m_dataType << " was requested.";
throw Error(___2890.str()); } else { return m_dataItems[m_index++]; } } template <typename T> T const& retrieveDataValue(int32_t tag, VariantType const& variantValue) { try { return boost::get<T>(variantValue); } catch (boost::bad_get const&) { std::ostringstream ___2890; ___2890 << "MPICommunicationCache: Mismatched type used to retrieve tag " << tag << "."; throw Error(___2890.str()); } } void deserializeData(uint8_t const* serializedData, int serializedDataSize) { int index = 0; while (index < serializedDataSize) { DataItemPtr newItem = addEncodedItem(&serializedData[index]); index += newItem->encodedSize(); } } std::vector<DataItemPtr> m_dataItems; int m_index; Impl() : m_index(0) {} }; MPICommunicationCache::MPICommunicationCache() : m_impl(new Impl) {} MPICommunicationCache::MPICommunicationCache(SimpleVector<uint8_t> const& serializedData) : m_impl(new Impl) { m_impl->deserializeData(serializedData.begin(), serializedData.size()); } MPICommunicationCache::MPICommunicationCache(uint8_t const* serializedData, int serializedDataSize) : m_impl(new Impl) { m_impl->deserializeData(serializedData, serializedDataSize); } MPICommunicationCache::~MPICommunicationCache() {} template <typename T> void MPICommunicationCache::addScalar(T ___4296, int32_t tag) { m_impl->addScalarItem(___4296, tag); } template <typename T> void MPICommunicationCache::retrieveScalar(T& ___4296, int32_t tag) const { Impl::DataItemPtr dataItemPtr = m_impl->nextItem<T>(tag); ___4296 = m_impl->retrieveDataValue<T>(tag, dataItemPtr->m_data); } template <typename T> void MPICommunicationCache::addVector(SimpleVector<T> const& vec, int32_t tag) { m_impl->addVectorItem(vec, tag); } template <typename T> void tecplot::teciompi::MPICommunicationCache::retrieveVector(SimpleVector<T>& vec, int32_t tag) const { Impl::DataItemPtr dataItemPtr = m_impl->nextItem<T>(tag); SimpleVector<uint8_t> const& storedVec = m_impl->retrieveDataValue<SimpleVector<uint8_t> >(tag, dataItemPtr->m_data); vec = SimpleVector<T>(reinterpret_cast<T const*>(storedVec.begin()), storedVec.size() / sizeof(T)); } SimpleVector<uint8_t> MPICommunicationCache::data() const { int32_t vectorSize = 0; for (std::vector<Impl::DataItemPtr>::const_iterator dataItemPtr = m_impl->m_dataItems.begin(); dataItemPtr != m_impl->m_dataItems.end(); ++dataItemPtr) { vectorSize += (*dataItemPtr)->encodedSize(); } SimpleVector<uint8_t> ___3356(vectorSize); int index = 0; for (std::vector<Impl::DataItemPtr>::const_iterator dataItemPtr = m_impl->m_dataItems.begin(); dataItemPtr != m_impl->m_dataItems.end(); ++dataItemPtr) { (*dataItemPtr)->encode(&___3356[index]); index += (*dataItemPtr)->encodedSize(); } return ___3356; }
 #define INSTANTIATE_FOR_TYPE(T) \
 template void MPICommunicationCache::addScalar<T>(T ___4296, int32_t tag); \
 template void MPICommunicationCache::retrieveScalar<T>(T& ___4296, int32_t tag) const; \
 template void MPICommunicationCache::addVector<T>(SimpleVector<T> const& vec, int32_t tag); \
 template void MPICommunicationCache::retrieveVector<T>(SimpleVector<T>& vec, int32_t tag) const;
INSTANTIATE_FOR_TYPE(char) INSTANTIATE_FOR_TYPE(uint8_t) INSTANTIATE_FOR_TYPE(uint16_t) INSTANTIATE_FOR_TYPE(int32_t) INSTANTIATE_FOR_TYPE(uint32_t) INSTANTIATE_FOR_TYPE(int64_t) INSTANTIATE_FOR_TYPE(uint64_t) INSTANTIATE_FOR_TYPE(float) INSTANTIATE_FOR_TYPE(double) INSTANTIATE_FOR_TYPE(___2477) }}