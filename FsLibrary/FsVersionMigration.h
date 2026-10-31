#pragma once

#include "AE_Macros.h"

// 旧工程ではオン、新規適用・リセットではオフの旧版チェックボックスを登録する。
#define FS_ADD_LEGACY_CHECKBOX(NAME, ID) \
	do { \
		PF_Err priv_err = PF_Err_NONE; \
		def.param_type = PF_Param_CHECKBOX; \
		PF_STRNNCPY(def.name, (NAME), sizeof(def.name)); \
		def.u.bd.u.nameptr = ""; \
		def.u.bd.value = TRUE; \
		def.u.bd.dephault = FALSE; \
		def.flags = PF_ParamFlag_USE_VALUE_FOR_OLD_PROJECTS; \
		def.uu.id = (ID); \
		if ((priv_err = PF_ADD_PARAM(in_data, -1, &def)) != PF_Err_NONE) return priv_err; \
	} while (0)
