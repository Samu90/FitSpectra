// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIsamueletorellidIDesktopdITOFPETdIdefV3dIsodio_cpp_ACLiC_dict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "/Users/samueletorelli/Desktop/TOFPET/defV3/./sodio.cpp"

// Header files passed via #pragma extra_include

namespace {
  void TriggerDictionaryInitialization_sodio_cpp_ACLiC_dict_Impl() {
    static const char* headers[] = {
"./sodio.cpp",
0
    };
    static const char* includePaths[] = {
"/Users/samueletorelli/Documents/root/build/include",
"/Users/samueletorelli/Documents/root/build/etc",
"/Users/samueletorelli/Documents/root/build/etc/cling",
"/Users/samueletorelli/Documents/root/build/include",
"/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.14.sdk/usr/include",
"/Users/samueletorelli/Documents/root/build/include",
"/Users/samueletorelli/Desktop/TOFPET/defV3/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "sodio_cpp_ACLiC_dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "sodio_cpp_ACLiC_dict dictionary payload"

#ifndef __ACLIC__
  #define __ACLIC__ 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "./sodio.cpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Analysis", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("sodio_cpp_ACLiC_dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_sodio_cpp_ACLiC_dict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_sodio_cpp_ACLiC_dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_sodio_cpp_ACLiC_dict() {
  TriggerDictionaryInitialization_sodio_cpp_ACLiC_dict_Impl();
}
