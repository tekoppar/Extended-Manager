// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// IL2CPP application initializer

#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "il2cpp-init.h"
#include "helpers.h"

// IL2CPP APIs
#define DO_API(r, n, p) r (*n) p
#ifdef _WOTW_PATCH_THREE
#include "il2cpp-api-functions.h"
#endif

#ifdef _WOTW_PATCH_TWO
#include "../appdata_1_2/il2cpp-api-functions.h"
#endif
#undef DO_API

// Application-specific functions
#define DO_APP_FUNC(a, r, n, p) r (*n) p
#define DO_APP_FUNC_METHODINFO(a, n) struct MethodInfo ** n
namespace app
{
#ifdef _WOTW_PATCH_THREE
#include "il2cpp-functions1.h"
#include "il2cpp-functions2.h"
#include "il2cpp-functions3.h"
#include "il2cpp-functions4.h"
#include "il2cpp-functions5.h"
#include "il2cpp-functions6.h"
#include "il2cpp-functions7.h"
#endif

#ifdef _WOTW_PATCH_TWO
#include "../appdata_1_2/Functions/il2cpp-functions1.h"
#include "../appdata_1_2/Functions/il2cpp-functions2.h"
#include "../appdata_1_2/Functions/il2cpp-functions3.h"
#include "../appdata_1_2/Functions/il2cpp-functions4.h"
#include "../appdata_1_2/Functions/il2cpp-functions5.h"
#endif
}
#undef DO_APP_FUNC
#undef DO_APP_FUNC_METHODINFO

// TypeInfo pointers
#define DO_TYPEDEF(a, n) n ## __Class** n ## __TypeInfo
namespace app
{
#ifdef _WOTW_PATCH_THREE
#include "il2cpp-types-ptr.h"
#endif

#ifdef _WOTW_PATCH_TWO
#include "../appdata_1_2/il2cpp-types-ptr.h"
#endif
}
#undef DO_TYPEDEF

// IL2CPP application initializer
void init_il2cpp()
{
	// Get base address of IL2CPP module
	uintptr_t baseAddress = il2cppi_get_base_address();

	using namespace app;

	// Define IL2CPP API function addresses
#define DO_API(r, n, p) n = (r (*) p)(baseAddress + n ## _ptr)
#ifdef _WOTW_PATCH_THREE
#include "il2cpp-api-functions.h"
#endif

#ifdef _WOTW_PATCH_TWO
#include "../appdata_1_2/il2cpp-api-functions.h"
#endif
#undef DO_API

// Define function addresses
#define DO_APP_FUNC(a, r, n, p) n = (r (*) p)(baseAddress + a)
#define DO_APP_FUNC_METHODINFO(a, n) n = (struct MethodInfo **)(baseAddress + a)
#ifdef _WOTW_PATCH_THREE
#include "il2cpp-functions1.h"
#include "il2cpp-functions2.h"
#include "il2cpp-functions3.h"
#include "il2cpp-functions4.h"
#include "il2cpp-functions5.h"
#include "il2cpp-functions6.h"
#include "il2cpp-functions7.h"
#endif

#ifdef _WOTW_PATCH_TWO
#include "../appdata_1_2/Functions/il2cpp-functions1.h"
#include "../appdata_1_2/Functions/il2cpp-functions2.h"
#include "../appdata_1_2/Functions/il2cpp-functions3.h"
#include "../appdata_1_2/Functions/il2cpp-functions4.h"
#include "../appdata_1_2/Functions/il2cpp-functions5.h"
#endif
#undef DO_APP_FUNC
#undef DO_APP_FUNC_METHODINFO

// Define TypeInfo variables
#define DO_TYPEDEF(a, n) n ## __TypeInfo = (n ## __Class**) (baseAddress + a);
#ifdef _WOTW_PATCH_THREE
#include "il2cpp-types-ptr.h"
#endif

#ifdef _WOTW_PATCH_TWO
#include "../appdata_1_2/il2cpp-types-ptr.h"
#endif
#undef DO_TYPEDEF
}