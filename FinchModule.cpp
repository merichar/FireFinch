// #include generic factory stuff here
#include <mozilla/ModuleUtils.h>
#include "Finch.h"
#include "mozilla-config.h"

/** NEW Code? (Gecko > 2.0) **/


#include "nsIModule.h"

NS_GENERIC_FACTORY_CONSTRUCTOR(Finch)

NS_DEFINE_NAMED_CID(FINCH_CID);
 static const mozilla::Module::CIDEntry kFinchCIDs[] = {
     { &kFINCH_CID, false, NULL, FinchConstructor },
     { NULL }
 };

static const mozilla::Module::ContractIDEntry kFinchContracts[] = {
     { FINCH_CONTRACTID , &kFINCH_CID },
     { NULL }
};

static const mozilla::Module::CategoryEntry kFinchCategories[] = {
    { "finch",  FINCH_CONTRACTID , FINCH_CONTRACTID },
    { NULL }
};

static const mozilla::Module kFinchModule = {
    mozilla::Module::kVersion,
    kFinchCIDs,
    kFinchContracts,
    kFinchCategories
 };

NSMODULE_DEFN(nsSampleModule) = &kFinchModule;

NS_IMPL_MOZILLA192_NSGETMODULE(&kFinchModule)

/** OLD Code (Gecko < 2.0) **/

#if 0

NS_GENERIC_FACTORY_CONSTRUCTOR(Finch)

static nsModuleComponentInfo components[] =
{
  {
    FINCH_CLASSNAME, 
    FINCH_CID,
    FINCH_CONTRACTID,
    FinchConstructor,
  }
};

NS_IMPL_NSGETMODULE("FinchModule", components)

#endif
