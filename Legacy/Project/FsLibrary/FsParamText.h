#pragma once

#include "AEConfig.h"
#include "AE_Effect.h"
#include "Param_Utils.h"

#ifdef AE_OS_WIN
namespace FsParamText {
PF_Err AddParam(PF_InData* in_data, PF_ParamIndex index, PF_ParamDef* def);
}

#undef PF_ADD_PARAM
#define PF_ADD_PARAM(IN_DATA, INDEX, DEF) \
    FsParamText::AddParam((IN_DATA), (INDEX), (DEF))
#endif

