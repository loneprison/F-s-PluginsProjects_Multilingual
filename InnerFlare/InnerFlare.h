//-----------------------------------------------------------------------------------
/*
	InnerFlare for VS2026
*/
//-----------------------------------------------------------------------------------

#pragma once
#ifndef InnerFlare_N_H
#define InnerFlare_N_H

#include "..\_NFLib\AE_SDK.h"

#include "NF_Target.h" //これを最初にincludeすること

#include "..\_NFLib\NF_AE.h"
#include "..\_NFLib\NF_ParamsSetup.h"

#include "..\_NFLib\fx\NF_Mult.h"
#include "..\_NFLib\fx\NF_Minmax.h"
#include "..\_NFLib\fx\NF_blur.h"
//#include "..\_NFLib\fx\debug_font.h"
//#include "..\_NFLib\fx\NF_Paint.h"
//#include "..\_NFLib\fx\NF_Noise.h"
//#include "..\_NFLib\fx\NF_Draw.h"
#include "..\_NFLib\fx\NF_AlphaHyperbolic.h"
#include "..\_NFLib\fx\NF_Blend.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>

#include "AlphaCopy.h"
#include "AlphaCopyR.h"

//ユーザーインターフェースのID
//ParamsSetup関数とRender関数のparamsパラメータのIDになる
enum {
	ID_INPUT = 0,	// default input layer

	ID_COLOR,
	ID_MINMAX,
	ID_BLUR,
	ID_HYPERBOLIC,
	ID_REVERCE,
	ID_WHITE,
	ID_BLEND,
	ID_NUM_PARAMS
};

//UIの表示文字列
#define	L10N_BLUR			"blur"
#define	L10N_MINMAX			"max"
#define	L10N_HYPERBOLIC		"hyperbolic"
#define	L10N_REVERCE			"reverce"
#define	L10N_COLOR			"color"
#define	L10N_WHITE			"Treat White as Transparent"
#define	L10N_BLEND			"Blend with original"


//UIのパラメータ
typedef struct ParamInfo {
	A_long				blur;
	A_long				minmax;
	PF_FpLong			hyperbolic;
	PF_Boolean			reverce;
	PF_Pixel			color;
	PF_Boolean			isWhite;
	PF_Boolean			isBlend;

} ParamInfo, *ParamInfoP, **ParamInfoH;

//-------------------------------------------------------


//-----------------------------------------------------------------------------------
extern "C" {

DllExport
PF_Err PluginDataEntryFunction2(
	PF_PluginDataPtr inPtr,
	PF_PluginDataCB2 inPluginDataCallBackPtr,
	SPBasicSuite* inSPBasicSuitePtr,
	const char* inHostName,
	const char* inHostVersion);

DllExport 
PF_Err 
EffectMain(
	PF_Cmd			cmd,
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	void			*extra);
}
#endif // InnerFlare_H

