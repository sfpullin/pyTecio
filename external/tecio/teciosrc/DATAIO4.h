 #pragma once
#include "ThirdPartyHeadersBegin.h"
#include <set>
#include <utility>
#include <vector>
#include "ThirdPartyHeadersEnd.h"
#include "TecplotFileZoneFormat.h"
 #if defined EXTERN
 #undef EXTERN
 #endif
 #if defined ___854
 #define EXTERN
 #else
 #define EXTERN extern
 #endif
EXTERN double ___1760(___1403    *___1399, FieldDataType_e  ___1362, double           ___2468, double           ___2344, ___372       *___2038); template <typename SRC_INT_TYPE> EXTERN SRC_INT_TYPE ___1748( ___1403* ___1398, short         pltFileVersion, SRC_INT_TYPE  minValue, SRC_INT_TYPE  maxValue, ___372*    ___2037); EXTERN void ___3275(___1403 *___1399, ___372     ___1097, uint8_t       *___417, ___2225     ___3683, ___2225     ___2840, ___372    *___2038); EXTERN void ___3288(___1403 *___1399, ___372     ___1097, int16_t      *___417, ___2225     ___3683, ___2225     ___2840, ___372    *___2038); EXTERN void ___3289(___1403 *___1399, ___372     ___1097, int32_t      *___417, ___2225     ___3683, ___2225     ___2840, ___372    *___2038); EXTERN void ___3290(___1403 *___1399, ___372     ___1097, int32_t      *___417, ___2225     ___3683, ___2225     ___2840, ___372    *___2038); EXTERN void ReadInt64Block(___1403 *___1399, ___372     ___1097, int64_t      *___417, ___2225     ___3683, ___2225     ___2840, ___372    *___2038); EXTERN void ___3294(___1403   *___1399, ___372       ___1097, void           *___417, FieldDataType_e ___1362, ___2225       ___3683, ___2225       ___2840, ___372      *___2038); EXTERN void ___3274(___1403   *___1399, ___1359    ___1350, ___372       ___1097, FieldDataType_e ___1365, ___2225       ___3683, ___2225       EndIndex, ___372      *___2038); EXTERN void ___3276(___1403    *___841, ___1359     ___1350, FieldDataType_e  ___1365, ___2225        ___2808, ___2225        ___2813, ___2225        ___2816, ___372       *___2038); EXTERN ___372 ___3285(___1403   *___1399, short           ___2102, char          **___901, DataFileType_e *___1406, int            *NumVars, ___3837  *___4364); EXTERN ___372 ___3293( ___1403*                ___1399, TecplotFileZoneFormat const& tecplotFileZoneFormat, ___4681&                  ___4675, ___3499                       ___2073, ___1170                   NumVars, ___90                   ___263, ___372*                   ___2051, ___2225*                   ___1439); EXTERN ___372 ___3284(___1403  *___1399, short          ___2102, ___372      ___2866, ___3837 *___789); EXTERN ___372 ___3292( ___1403* ___1399, short         ___2102, char**        ___4283); EXTERN ___372 ___3283(___1403 *___1399, short         ___2102, ___264    ___230); EXTERN ___372 ___3286(___1403 *___1399, short         ___2102, ___372     ___2866, ___1630       *G, ___2225     ___2364); EXTERN ___372 ___3291(___1403 *___1399,
short         ___2102, ___372     ___2866, ___4116       *T, ___2225     ___2385); EXTERN ___372 ___3170(char  *___690, char  *___359, char **___2454); EXTERN short ___1747(___1403 *___1399); EXTERN ___372 ___4487( ___1403*  ___1399, uint8_t const* ___1961, ___2225      ___2840, ___372      ___4331); EXTERN ___372 ___4489( ___1403*  ___1399, uint8_t const* ___1966, ___2225      ___2840, ___372      ___4331); EXTERN ___372 WriteBinaryInt64BlockUnaligned( ___1403*  ___1399, uint8_t const* Int64Values, ___2225      ___2840, ___372      ___4331); EXTERN ___372 ___4484( ___1403*  ___1399, uint8_t const* ___428, ___2225      ___2840); EXTERN ___372 ___4486(___1403 *___1399, int16_t       ___4313); EXTERN ___372 ___4488(___1403 *___1399, int32_t       ___4313); EXTERN ___372 WriteBinaryInt64(___1403 *___1399, int64_t       ___4313); EXTERN ___372 ___4491(___1403    *___1399, double           ___3423, FieldDataType_e  ___1362); EXTERN ___372 ___4511(___1403    *___1399, FieldDataType_e  ___1308, ___372        ___4483); EXTERN ___372 ___4485( ___1403* ___1399, ___1359  ___1350, ___2225     ___3684, ___2225     ___2840); EXTERN ___372 ___4493(___1403 *___1399, ___1359  ___1350, ___372     ___2041, ___2225     ___2807, ___2225     ___2812, ___2225     ___2815, ___372     ___4483, int32_t   ___200); EXTERN ___372 ___1129(___1403 *___1399, const char   *S, ___372     ___4483); bool ___1130(___1403* ___1399, ___1630 const* ___1554, ___372     ___4483, ___372     ___4523); bool ___1131(___1403* ___1399, ___4116 const* Text, ___372     ___4483, ___372     ___4523); EXTERN ___372 ___1128(___1403  *___1399, ___372      ___4483, ___3837  ___2168); EXTERN ___372 ___4490(___1403 *___1399); bool ___4492(___1403& ___1398, int           ___4407);