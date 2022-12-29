 #pragma once
#include "ThirdPartyHeadersBegin.h"
#  include <boost/shared_ptr.hpp>
#include "ThirdPartyHeadersEnd.h"
#include "AltTecUtil.h"
namespace tecplot { namespace ___3931 { typedef boost::shared_ptr<class ___1350> FieldDataPtr; class ___1350 { public: ___1350(___37* tecUtil, ___1170 zone, ___1170 ___4334, bool writable = false, bool ___962 = false); ___1350() : m_tecUtil(0) , m_fieldData(0) , m_rawDataPtr(0) , m_getFieldValue(0) , m_setFieldValue(0) , ___2457(___1367) , ___2667(___4327) , ___2666(0) , m_allocated(false) {} ~___1350() { if (m_allocated) free(m_rawDataPtr); } void allocate( FieldDataType_e ___1361, ValueLocation_e ___4324, ___2225 ___4323); bool ___2065() const { return (VALID_REF(m_tecUtil) && ___2666 > 0 && (m_fieldData != NULL || m_rawDataPtr != NULL) && VALID_ENUM(___2457, FieldDataType_e)); } double ___1778(___2225 index) const; ValueLocation_e ___1784() const { return ___2667; } FieldDataType_e getValueType() const { return ___2457; } ___2225 ___1781() const { return ___2666; } void ___3502(___2225 index, double ___4312); void ___1757(double* minVal, double* maxVal) const; void* getRawPointer() const { ENSURE(VALID_REF_OR_NULL(m_rawDataPtr)); return m_rawDataPtr; } private: ___1350 RawValuePtrGetReadableOrWritablePtr( ___1170 zone, ___1170 ___4334, ___372  getWritable, ___372  getDerived); ___37* m_tecUtil; ___1359 m_fieldData; void* m_rawDataPtr; ___1381 m_getFieldValue; ___1382 m_setFieldValue; FieldDataType_e ___2457; ValueLocation_e ___2667; ___2225 ___2666; bool m_allocated; }; inline double ___1350::___1778(___2225 index) const { REQUIRE(0 < index && index <= ___2666); double ___4312; ___476(VALID_REF_OR_NULL(m_rawDataPtr)); if (m_rawDataPtr != NULL) { switch(___2457) { case FieldDataType_Float: ___4312 = (double)(((float *)m_rawDataPtr)[index - 1]); break; case FieldDataType_Double: ___4312 = ((double *)m_rawDataPtr)[index - 1]; break; case FieldDataType_Int32: ___4312 = (double)(((int32_t *)m_rawDataPtr)[index - 1]); break; case FieldDataType_Int16: ___4312 = (double)(((int16_t *)m_rawDataPtr)[index - 1]); break; case FieldDataType_Byte: ___4312 = (double)(((uint8_t *)m_rawDataPtr)[index - 1]); break; case ___1363: ___4312 = (double)((((uint8_t *)m_rawDataPtr)[(index - 1) / 8] >> ((index - 1) % 8)) & (uint8_t)0x1); break; default: ___476(___1303); ___4312 = 0.0; break; } } else { ___476(VALID_FN_REF(m_getFieldValue)); ___4312 = m_getFieldValue(m_fieldData, index - 1); } return ___4312; } inline void ___1350::___3502(___2225 index, double ___4312) { REQUIRE(0 < index && index <= ___2666); ___476(VALID_REF_OR_NULL(m_rawDataPtr)); if (m_rawDataPtr != NULL) { switch (___2457) { case FieldDataType_Float: ((float *)(m_rawDataPtr))[index - 1] = ___648(___4312); break; case FieldDataType_Double: ((double *)(m_rawDataPtr))[index - 1] = ___487(___4312); break; case FieldDataType_Int32: ((___2225 *)(m_rawDataPtr))[index - 1] = ___650(___4312);
break; case FieldDataType_Int16: ((short *)(m_rawDataPtr))[index - 1] = ___649(___4312); break; case FieldDataType_Byte: ((uint8_t *)(m_rawDataPtr))[index - 1] = CONVERT_DOUBLE_TO_UINT8(___4312); break; case ___1363: { ___2225 byteOffset = (index - 1) / 8; uint8_t    bitMask = (uint8_t)(01 << ((index - 1) % 8)); if (___4312 < 1.0) ((uint8_t *)(m_rawDataPtr))[byteOffset] &= ~bitMask; else ((uint8_t *)(m_rawDataPtr))[byteOffset] |= bitMask; } break; default: ___476(___1303); } } else { ___476(VALID_FN_REF(m_setFieldValue)); m_setFieldValue(m_fieldData, index - 1, (double)(___4312)); } } }}