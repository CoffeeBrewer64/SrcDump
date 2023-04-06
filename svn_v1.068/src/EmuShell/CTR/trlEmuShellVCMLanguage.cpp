/**
* @file trlEmuShellVCMLanguage.cpp
* @author zhfang
* @date 2011.03.30
* @brief TRL Emulate For CTR - trlEmuShellVCMLanguage
*/
#include "trlEmuShellVCMLanguage.h"

#if TRL_VCM_LANGFILE_SD
const wchar_t*			g_wzTrlEmuShellLanguagePath[] = {
#if defined REGION_JP
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang"			//CFG_LANGUAGE_RUSSIAN
#elif defined REGION_US
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-French.lang",		//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-Spanish.lang",		//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-Portuguese.lang",	//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang"		//CFG_LANGUAGE_RUSSIAN
#else
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-French.lang",		//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-German.lang",		//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-Italian.lang",		//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-Spanish.lang",		//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-Dutch.lang",		//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-Portuguese.lang",	//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-Russian.lang"		//CFG_LANGUAGE_RUSSIAN
#endif
};

const wchar_t*			g_wzTrlEmuShellLanguageScalePath[] = {
#if defined REGION_JP
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale"		//CFG_LANGUAGE_RUSSIAN
#elif defined REGION_US
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-FR-Scale.scale",	//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-SP-Scale.scale",	//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-PO-Scale.scale",	//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale"		//CFG_LANGUAGE_RUSSIAN
#else
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",	//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",	//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-FR-Scale.scale",	//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-GE-Scale.scale",	//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-IT-Scale.scale",	//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-SP-Scale.scale",	//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",	//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",	//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-DU-Scale.scale",	//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-PO-Scale.scale",	//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-RU-Scale.scale"		//CFG_LANGUAGE_RUSSIAN
#endif
};

const wchar_t*			g_wzTrlEmuShellLanguagePathHVC[] = {
#if defined REGION_JP
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang"			//CFG_LANGUAGE_RUSSIAN
#elif defined REGION_US
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-French.lang",		//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-Spanish.lang",		//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-Portuguese.lang",	//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang"		//CFG_LANGUAGE_RUSSIAN
#else
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-French.lang",		//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-German.lang",		//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-Italian.lang",		//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-Spanish.lang",		//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-Dutch.lang",		//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-Portuguese.lang",	//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-Russian.lang"		//CFG_LANGUAGE_RUSSIAN
#endif
};

const wchar_t*			g_wzTrlEmuShellLanguageScalePathHVC[] = {
#if defined REGION_JP
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale"		//CFG_LANGUAGE_RUSSIAN
#elif defined REGION_US
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-FR-Scale.scale",	//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-SP-Scale.scale",	//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-PO-Scale.scale",	//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale"		//CFG_LANGUAGE_RUSSIAN
#else
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",	//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",	//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-FR-Scale.scale",	//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-GE-Scale.scale",	//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-IT-Scale.scale",	//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-SP-Scale.scale",	//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",	//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",	//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-DU-Scale.scale",	//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-PO-Scale.scale",	//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-RU-Scale.scale"		//CFG_LANGUAGE_RUSSIAN
#endif
};

const wchar_t*			g_wzTrlEmuShellLanguagePathHVCNet[] = {
#if defined REGION_JP
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",		//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang"			//CFG_LANGUAGE_RUSSIAN
#elif defined REGION_US
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-French.lang",		//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-Spanish.lang",		//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-Portuguese.lang",	//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-English.lang"		//CFG_LANGUAGE_RUSSIAN
#else
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-French.lang",		//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-German.lang",		//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-Italian.lang",		//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-Spanish.lang",		//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-Dutch.lang",		//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-Portuguese.lang",	//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-Russian.lang"		//CFG_LANGUAGE_RUSSIAN
#endif
};

const wchar_t*			g_wzTrlEmuShellLanguageScalePathHVCNet[] = {
#if defined REGION_JP
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale"		//CFG_LANGUAGE_RUSSIAN
#elif defined REGION_US
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-FR-Scale.scale",	//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-SP-Scale.scale",	//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-PO-Scale.scale",	//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale"		//CFG_LANGUAGE_RUSSIAN
#else
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",	//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",	//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-FR-Scale.scale",	//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-GE-Scale.scale",	//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-IT-Scale.scale",	//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-SP-Scale.scale",	//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",	//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",	//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-DU-Scale.scale",	//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-PO-Scale.scale",	//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/VCM_DL/lang/EU-RU-Scale.scale"		//CFG_LANGUAGE_RUSSIAN
#endif
};

const wchar_t*			g_wzTrlEmuShellErrLanguagePath[] = {
#if defined REGION_JP
	L"sdmc:/VCM/ERRVCM/lang/Japanese.lang",		//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/ERRVCM/lang/Japanese.lang",		//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/ERRVCM/lang/Japanese.lang",		//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/ERRVCM/lang/Japanese.lang",		//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/ERRVCM/lang/Japanese.lang",		//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/ERRVCM/lang/Japanese.lang",		//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/ERRVCM/lang/Japanese.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/ERRVCM/lang/Japanese.lang",		//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/ERRVCM/lang/Japanese.lang",		//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/ERRVCM/lang/Japanese.lang",		//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/ERRVCM/lang/Japanese.lang"			//CFG_LANGUAGE_RUSSIAN
#elif defined REGION_US
	L"sdmc:/VCM/ERRVCM/lang/US-English.lang",		//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/ERRVCM/lang/US-English.lang",		//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/ERRVCM/lang/US-French.lang",		//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/ERRVCM/lang/US-English.lang",		//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/ERRVCM/lang/US-English.lang",		//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/ERRVCM/lang/US-Spanish.lang",		//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/ERRVCM/lang/US-English.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/ERRVCM/lang/US-English.lang",		//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/ERRVCM/lang/US-English.lang",		//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/ERRVCM/lang/US-Portuguese.lang",	//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/ERRVCM/lang/US-English.lang"		//CFG_LANGUAGE_RUSSIAN
#else
	L"sdmc:/VCM/ERRVCM/lang/EU-English.lang",		//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/ERRVCM/lang/EU-English.lang",		//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/ERRVCM/lang/EU-French.lang",		//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/ERRVCM/lang/EU-German.lang",		//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/ERRVCM/lang/EU-Italian.lang",		//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/ERRVCM/lang/EU-Spanish.lang",		//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/ERRVCM/lang/EU-English.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/ERRVCM/lang/EU-English.lang",		//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/ERRVCM/lang/EU-Dutch.lang",		//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/ERRVCM/lang/EU-Portuguese.lang",	//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/ERRVCM/lang/EU-Russian.lang"		//CFG_LANGUAGE_RUSSIAN
#endif
};

const wchar_t*			g_wzTrlEmuShellErrLanguageScalePath[] = {
#if defined REGION_JP
	L"sdmc:/VCM/ERRVCM/lang/JP-Scale.scale",		//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/ERRVCM/lang/JP-Scale.scale",		//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/ERRVCM/lang/JP-Scale.scale",		//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/ERRVCM/lang/JP-Scale.scale",		//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/ERRVCM/lang/JP-Scale.scale",		//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/ERRVCM/lang/JP-Scale.scale",		//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/ERRVCM/lang/JP-Scale.scale",		//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/ERRVCM/lang/JP-Scale.scale",		//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/ERRVCM/lang/JP-Scale.scale",		//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/ERRVCM/lang/JP-Scale.scale",		//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/ERRVCM/lang/JP-Scale.scale"		//CFG_LANGUAGE_RUSSIAN
#elif defined REGION_US
	L"sdmc:/VCM/ERRVCM/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/ERRVCM/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/ERRVCM/lang/US-FR-Scale.scale",	//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/ERRVCM/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/ERRVCM/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/ERRVCM/lang/US-SP-Scale.scale",	//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/ERRVCM/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/ERRVCM/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/ERRVCM/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/ERRVCM/lang/US-PO-Scale.scale",	//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/ERRVCM/lang/US-EN-Scale.scale"		//CFG_LANGUAGE_RUSSIAN
#else
	L"sdmc:/VCM/ERRVCM/lang/EU-EN-Scale.scale",	//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/ERRVCM/lang/EU-EN-Scale.scale",	//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/ERRVCM/lang/EU-FR-Scale.scale",	//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/ERRVCM/lang/EU-GE-Scale.scale",	//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/ERRVCM/lang/EU-IT-Scale.scale",	//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/ERRVCM/lang/EU-SP-Scale.scale",	//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/ERRVCM/lang/EU-EN-Scale.scale",	//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/ERRVCM/lang/EU-EN-Scale.scale",	//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/ERRVCM/lang/EU-DU-Scale.scale",	//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/ERRVCM/lang/EU-PO-Scale.scale",	//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/ERRVCM/lang/EU-RU-Scale.scale"		//CFG_LANGUAGE_RUSSIAN
#endif
};

const wchar_t*			g_wzTrlEmuShellMessageWindowLanguagePath[] = {
#if defined REGION_JP
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/Japanese.lang",		//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/Japanese.lang",		//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/Japanese.lang",		//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/Japanese.lang",		//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/Japanese.lang",		//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/Japanese.lang",		//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/Japanese.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/Japanese.lang",		//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/Japanese.lang",		//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/Japanese.lang",		//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/Japanese.lang"			//CFG_LANGUAGE_RUSSIAN
#elif defined REGION_US
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/US-English.lang",		//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/US-English.lang",		//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/US-French.lang",		//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/US-English.lang",		//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/US-English.lang",		//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/US-Spanish.lang",		//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/US-English.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/US-English.lang",		//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/US-English.lang",		//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/US-Portuguese.lang",	//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/US-English.lang"		//CFG_LANGUAGE_RUSSIAN
#else
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/EU-English.lang",		//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/EU-English.lang",		//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/EU-French.lang",		//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/EU-German.lang",		//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/EU-Italian.lang",		//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/EU-Spanish.lang",		//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/EU-English.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/EU-English.lang",		//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/EU-Dutch.lang",		//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/EU-Portuguese.lang",	//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/EU-Russian.lang"		//CFG_LANGUAGE_RUSSIAN
#endif
};

const wchar_t*			g_wzTrlEmuShellMessageWindowLanguageScalePath[] = {
#if defined REGION_JP
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/JP-Scale.scale",		//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/JP-Scale.scale",		//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/JP-Scale.scale",		//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/JP-Scale.scale",		//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/JP-Scale.scale",		//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/JP-Scale.scale",		//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/JP-Scale.scale",		//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/JP-Scale.scale",		//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/JP-Scale.scale",		//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/JP-Scale.scale",		//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/JP-Scale.scale"		//CFG_LANGUAGE_RUSSIAN
#elif defined REGION_US
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/US-FR-Scale.scale",	//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/US-SP-Scale.scale",	//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/US-EN-Scale.scale",	//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/US-PO-Scale.scale",	//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/US-EN-Scale.scale"		//CFG_LANGUAGE_RUSSIAN
#else
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/EU-EN-Scale.scale",	//CFG_LANGUAGE_JAPANESE
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/EU-EN-Scale.scale",	//CFG_LANGUAGE_ENGLISH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/EU-FR-Scale.scale",	//CFG_LANGUAGE_FRENCH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/EU-GE-Scale.scale",	//CFG_LANGUAGE_GERMAN
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/EU-IT-Scale.scale",	//CFG_LANGUAGE_ITALIAN
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/EU-SP-Scale.scale",	//CFG_LANGUAGE_SPANISH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/EU-EN-Scale.scale",	//CFG_LANGUAGE_SIMP_CHINESE
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/EU-EN-Scale.scale",	//CFG_LANGUAGE_KOREAN
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/EU-DU-Scale.scale",	//CFG_LANGUAGE_DUTCH
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/EU-PO-Scale.scale",	//CFG_LANGUAGE_PORTUGUESE
	L"sdmc:/VCM/HVCVCM/COMMON_WND/lang/EU-RU-Scale.scale"		//CFG_LANGUAGE_RUSSIAN
#endif
};

#else
const wchar_t*			g_wzTrlEmuShellLanguagePath[] = {
#if defined REGION_JP
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang"			//CFG_LANGUAGE_RUSSIAN
#elif defined REGION_US
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-French.lang",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-Spanish.lang",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-Portuguese.lang",	//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang"		//CFG_LANGUAGE_RUSSIAN
#else
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-French.lang",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-German.lang",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-Italian.lang",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-Spanish.lang",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-Dutch.lang",			//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-Portuguese.lang",	//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-Russian.lang"		//CFG_LANGUAGE_RUSSIAN
#endif
};

const wchar_t*			g_wzTrlEmuShellLanguageScalePath[] = {
#if defined REGION_JP
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale"			//CFG_LANGUAGE_RUSSIAN
#elif defined REGION_US
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-FR-Scale.scale",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-SP-Scale.scale",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-PO-Scale.scale",		//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale"		//CFG_LANGUAGE_RUSSIAN
#else
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-FR-Scale.scale",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-GE-Scale.scale",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-IT-Scale.scale",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-SP-Scale.scale",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-DU-Scale.scale",		//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-PO-Scale.scale",		//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-RU-Scale.scale"		//CFG_LANGUAGE_RUSSIAN								
#endif
};

const wchar_t*			g_wzTrlEmuShellLanguagePathHVC[] = {
#if defined REGION_JP
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang"			//CFG_LANGUAGE_RUSSIAN
#elif defined REGION_US
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-French.lang",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-Spanish.lang",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-Portuguese.lang",	//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang"		//CFG_LANGUAGE_RUSSIAN
#else
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-French.lang",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-German.lang",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-Italian.lang",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-Spanish.lang",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-Dutch.lang",			//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-Portuguese.lang",	//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-Russian.lang"		//CFG_LANGUAGE_RUSSIAN
#endif
};

const wchar_t*			g_wzTrlEmuShellLanguageScalePathHVC[] = {
#if defined REGION_JP
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale"			//CFG_LANGUAGE_RUSSIAN
#elif defined REGION_US
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-FR-Scale.scale",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-SP-Scale.scale",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-PO-Scale.scale",		//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale"		//CFG_LANGUAGE_RUSSIAN
#else
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-FR-Scale.scale",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-GE-Scale.scale",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-IT-Scale.scale",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-SP-Scale.scale",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-DU-Scale.scale",		//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-PO-Scale.scale",		//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-RU-Scale.scale"		//CFG_LANGUAGE_RUSSIAN								
#endif
};

const wchar_t*			g_wzTrlEmuShellLanguagePathHVCNet[] = {
#if defined REGION_JP
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang",			//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/Japanese.lang"			//CFG_LANGUAGE_RUSSIAN
#elif defined REGION_US
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-French.lang",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-Spanish.lang",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang",		//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-Portuguese.lang",	//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-English.lang"		//CFG_LANGUAGE_RUSSIAN
#else
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-French.lang",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-German.lang",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-Italian.lang",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-Spanish.lang",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-English.lang",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-Dutch.lang",			//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-Portuguese.lang",	//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-Russian.lang"		//CFG_LANGUAGE_RUSSIAN
#endif
};

const wchar_t*			g_wzTrlEmuShellLanguageScalePathHVCNet[] = {
#if defined REGION_JP
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale",		//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/JP-Scale.scale"			//CFG_LANGUAGE_RUSSIAN
#elif defined REGION_US
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-FR-Scale.scale",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-SP-Scale.scale",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-PO-Scale.scale",		//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/US-EN-Scale.scale"		//CFG_LANGUAGE_RUSSIAN
#else
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-FR-Scale.scale",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-GE-Scale.scale",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-IT-Scale.scale",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-SP-Scale.scale",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-EN-Scale.scale",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-DU-Scale.scale",		//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-PO-Scale.scale",		//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/VCM_DL/lang/EU-RU-Scale.scale"		//CFG_LANGUAGE_RUSSIAN								
#endif
};

const wchar_t*			g_wzTrlEmuShellErrLanguagePath[] = {
#if defined REGION_JP
	L"rom:/VCM/ERRVCM/lang/Japanese.lang",			//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/ERRVCM/lang/Japanese.lang",			//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/ERRVCM/lang/Japanese.lang",			//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/ERRVCM/lang/Japanese.lang",			//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/ERRVCM/lang/Japanese.lang",			//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/ERRVCM/lang/Japanese.lang",			//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/ERRVCM/lang/Japanese.lang",			//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/ERRVCM/lang/Japanese.lang",			//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/ERRVCM/lang/Japanese.lang",			//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/ERRVCM/lang/Japanese.lang",			//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/ERRVCM/lang/Japanese.lang"			//CFG_LANGUAGE_RUSSIAN
#elif defined REGION_US
	L"rom:/VCM/ERRVCM/lang/US-English.lang",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/ERRVCM/lang/US-English.lang",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/ERRVCM/lang/US-French.lang",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/ERRVCM/lang/US-English.lang",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/ERRVCM/lang/US-English.lang",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/ERRVCM/lang/US-Spanish.lang",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/ERRVCM/lang/US-English.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/ERRVCM/lang/US-English.lang",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/ERRVCM/lang/US-English.lang",		//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/ERRVCM/lang/US-Portuguese.lang",	//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/ERRVCM/lang/US-English.lang"		//CFG_LANGUAGE_RUSSIAN
#else
	L"rom:/VCM/ERRVCM/lang/EU-English.lang",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/ERRVCM/lang/EU-English.lang",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/ERRVCM/lang/EU-French.lang",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/ERRVCM/lang/EU-German.lang",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/ERRVCM/lang/EU-Italian.lang",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/ERRVCM/lang/EU-Spanish.lang",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/ERRVCM/lang/EU-English.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/ERRVCM/lang/EU-English.lang",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/ERRVCM/lang/EU-Dutch.lang",			//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/ERRVCM/lang/EU-Portuguese.lang",	//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/ERRVCM/lang/EU-Russian.lang"		//CFG_LANGUAGE_RUSSIAN
#endif
};

const wchar_t*			g_wzTrlEmuShellErrLanguageScalePath[] = {
#if defined REGION_JP
	L"rom:/VCM/ERRVCM/lang/JP-Scale.scale",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/ERRVCM/lang/JP-Scale.scale",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/ERRVCM/lang/JP-Scale.scale",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/ERRVCM/lang/JP-Scale.scale",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/ERRVCM/lang/JP-Scale.scale",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/ERRVCM/lang/JP-Scale.scale",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/ERRVCM/lang/JP-Scale.scale",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/ERRVCM/lang/JP-Scale.scale",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/ERRVCM/lang/JP-Scale.scale",		//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/ERRVCM/lang/JP-Scale.scale",		//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/ERRVCM/lang/JP-Scale.scale"			//CFG_LANGUAGE_RUSSIAN
#elif defined REGION_US
	L"rom:/VCM/ERRVCM/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/ERRVCM/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/ERRVCM/lang/US-FR-Scale.scale",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/ERRVCM/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/ERRVCM/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/ERRVCM/lang/US-SP-Scale.scale",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/ERRVCM/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/ERRVCM/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/ERRVCM/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/ERRVCM/lang/US-PO-Scale.scale",		//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/ERRVCM/lang/US-EN-Scale.scale"		//CFG_LANGUAGE_RUSSIAN
#else
	L"rom:/VCM/ERRVCM/lang/EU-EN-Scale.scale",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/ERRVCM/lang/EU-EN-Scale.scale",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/ERRVCM/lang/EU-FR-Scale.scale",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/ERRVCM/lang/EU-GE-Scale.scale",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/ERRVCM/lang/EU-IT-Scale.scale",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/ERRVCM/lang/EU-SP-Scale.scale",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/ERRVCM/lang/EU-EN-Scale.scale",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/ERRVCM/lang/EU-EN-Scale.scale",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/ERRVCM/lang/EU-DU-Scale.scale",		//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/ERRVCM/lang/EU-PO-Scale.scale",		//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/ERRVCM/lang/EU-RU-Scale.scale"		//CFG_LANGUAGE_RUSSIAN								
#endif
};

const wchar_t*			g_wzTrlEmuShellMessageWindowLanguagePath[] = {
#if defined REGION_JP
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/Japanese.lang",			//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/Japanese.lang",			//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/Japanese.lang",			//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/Japanese.lang",			//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/Japanese.lang",			//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/Japanese.lang",			//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/Japanese.lang",			//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/Japanese.lang",			//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/Japanese.lang",			//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/Japanese.lang",			//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/Japanese.lang"			//CFG_LANGUAGE_RUSSIAN
#elif defined REGION_US
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/US-English.lang",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/US-English.lang",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/US-French.lang",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/US-English.lang",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/US-English.lang",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/US-Spanish.lang",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/US-English.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/US-English.lang",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/US-English.lang",		//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/US-Portuguese.lang",	//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/US-English.lang"		//CFG_LANGUAGE_RUSSIAN
#else
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/EU-English.lang",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/EU-English.lang",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/EU-French.lang",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/EU-German.lang",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/EU-Italian.lang",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/EU-Spanish.lang",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/EU-English.lang",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/EU-English.lang",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/EU-Dutch.lang",			//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/EU-Portuguese.lang",	//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/EU-Russian.lang"		//CFG_LANGUAGE_RUSSIAN
#endif
};

const wchar_t*			g_wzTrlEmuShellMessageWindowLanguageScalePath[] = {
#if defined REGION_JP
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/JP-Scale.scale",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/JP-Scale.scale",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/JP-Scale.scale",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/JP-Scale.scale",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/JP-Scale.scale",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/JP-Scale.scale",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/JP-Scale.scale",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/JP-Scale.scale",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/JP-Scale.scale",		//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/JP-Scale.scale",		//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/JP-Scale.scale"			//CFG_LANGUAGE_RUSSIAN
#elif defined REGION_US
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/US-FR-Scale.scale",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/US-SP-Scale.scale",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/US-EN-Scale.scale",		//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/US-PO-Scale.scale",		//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/US-EN-Scale.scale"		//CFG_LANGUAGE_RUSSIAN
#else
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/EU-EN-Scale.scale",		//CFG_LANGUAGE_JAPANESE
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/EU-EN-Scale.scale",		//CFG_LANGUAGE_ENGLISH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/EU-FR-Scale.scale",		//CFG_LANGUAGE_FRENCH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/EU-GE-Scale.scale",		//CFG_LANGUAGE_GERMAN
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/EU-IT-Scale.scale",		//CFG_LANGUAGE_ITALIAN
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/EU-SP-Scale.scale",		//CFG_LANGUAGE_SPANISH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/EU-EN-Scale.scale",		//CFG_LANGUAGE_SIMP_CHINESE
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/EU-EN-Scale.scale",		//CFG_LANGUAGE_KOREAN
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/EU-DU-Scale.scale",		//CFG_LANGUAGE_DUTCH
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/EU-PO-Scale.scale",		//CFG_LANGUAGE_PORTUGUESE
	L"rom:/VCM/HVCVCM/COMMON_WND/lang/EU-RU-Scale.scale"		//CFG_LANGUAGE_RUSSIAN								
#endif
};

#endif
