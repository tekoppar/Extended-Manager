#pragma once
namespace Moon {
	typedef signed char        int8_t;
	typedef short              int16_t;
	typedef int                int32_t;
	typedef long long          int64_t;
	typedef unsigned char      uint8_t;
	typedef unsigned short     uint16_t;
	typedef unsigned int       uint32_t;
	typedef unsigned long long uint64_t;

#ifdef _WIN64
	typedef unsigned __int64  uintptr_t;
	typedef __int64          intptr_t;
#else
	typedef unsigned int uintptr_t;
	typedef int              intptr_t;
#endif

	//20
	struct VirtualInvokeData
	{
		uintptr_t methodPtr;
		void* method;
	};

	//26
	struct Il2CppType
	{
		void* data;
		unsigned int bits;
	};

	struct Il2CppClass;

	//46
	struct Il2CppClass_1
	{
		void* image;
		void* gc_desc;
		const char* name;
		const char* namespaze;
		Il2CppType byval_arg;
		Il2CppType this_arg;
		Il2CppClass* element_class;
		Il2CppClass* castClass;
		Il2CppClass* declaringType;
		Il2CppClass* parent;
		void* generic_class;
		void* typeDefinition;
		void* interopData;
		Il2CppClass* klass;
		void* fields;
		void* events;
		void* properties;
		void* methods;
		Il2CppClass** nestedTypes;
		Il2CppClass** implementedInterfaces;
		void* interfaceOffsets;
	};

	//71
	struct Il2CppClass_2
	{
		void* rgctx_data;
		Il2CppClass** typeHierarchy;
		uint32_t initializationExceptionGCHandle;
		uint32_t cctor_started;
		uint32_t cctor_finished;
		uint64_t cctor_thread;
		int32_t genericContainerIndex;
		uint32_t instance_size;
		uint32_t actualSize;
		uint32_t element_size;
		int32_t native_size;
		uint32_t static_fields_size;
		uint32_t thread_static_fields_size;
		int32_t thread_static_fields_offset;
		uint32_t flags;
		uint32_t token;
		uint16_t method_count;
		uint16_t property_count;
		uint16_t field_count;
		uint16_t event_count;
		uint16_t nested_type_count;
		uint16_t vtable_count;
		uint16_t interfaces_count;
		uint16_t interface_offsets_count;
		uint8_t typeHierarchyDepth;
		uint8_t genericRecursionDepth;
		uint8_t rank;
		uint8_t minimumAlignment;
		uint8_t naturalAligment;
		uint8_t packingSize;
		uint8_t bitflags1;
		uint8_t bitflags2;
	};

	//107
	struct Il2CppClass
	{
		Il2CppClass_1 _1;
		void* static_fields;
		Il2CppClass_2 _2;
		VirtualInvokeData vtable[255];
	};

	//426
	struct System_String_o;

	//4939
	struct UnityEngine_Object_o;

	//61550
	struct Moon_MoonTypeExtraData_o {
		int32_t IntExtraData;
	};
	struct Moon_MoonTypeExtraData_StaticFields {
	};
	struct Moon_MoonTypeExtraData_VTable {
		VirtualInvokeData _0_Equals;
		VirtualInvokeData _1_Finalize;
		VirtualInvokeData _2_GetHashCode;
		VirtualInvokeData _3_ToString;
	};
	struct Moon_MoonTypeExtraData_c {
		Il2CppClass_1 _1;
		Moon_MoonTypeExtraData_StaticFields* static_fields;
		Il2CppClass_2 _2;
		Moon_MoonTypeExtraData_VTable vtable;
	};

	//61567
	struct Moon_MoonTypeData_o {
		UnityEngine_Object_o* UnityObjectRef;
		Moon_MoonTypeExtraData_o ExtraData;
	};
	struct Moon_MoonTypeData_StaticFields {
	};
	struct Moon_MoonTypeData_VTable {
		VirtualInvokeData _0_Equals;
		VirtualInvokeData _1_Finalize;
		VirtualInvokeData _2_GetHashCode;
		VirtualInvokeData _3_ToString;
	};
	struct Moon_MoonTypeData_c {
		Il2CppClass_1 _1;
		Moon_MoonTypeData_StaticFields* static_fields;
		Il2CppClass_2 _2;
		Moon_MoonTypeData_VTable vtable;
	};

	//149670
	struct System_String_StaticFields {
		System_String_o* Empty;
	};
	struct System_String_VTable {
		VirtualInvokeData _0_Equals;
		VirtualInvokeData _1_Finalize;
		VirtualInvokeData _2_GetHashCode;
		VirtualInvokeData _3_ToString;
		VirtualInvokeData _4_CompareTo;
		VirtualInvokeData _5_Clone;
		VirtualInvokeData _6_GetTypeCode;
		VirtualInvokeData _7_System_IConvertible_ToBoolean;
		VirtualInvokeData _8_System_IConvertible_ToChar;
		VirtualInvokeData _9_System_IConvertible_ToSByte;
		VirtualInvokeData _10_System_IConvertible_ToByte;
		VirtualInvokeData _11_System_IConvertible_ToInt16;
		VirtualInvokeData _12_System_IConvertible_ToUInt16;
		VirtualInvokeData _13_System_IConvertible_ToInt32;
		VirtualInvokeData _14_System_IConvertible_ToUInt32;
		VirtualInvokeData _15_System_IConvertible_ToInt64;
		VirtualInvokeData _16_System_IConvertible_ToUInt64;
		VirtualInvokeData _17_System_IConvertible_ToSingle;
		VirtualInvokeData _18_System_IConvertible_ToDouble;
		VirtualInvokeData _19_System_IConvertible_ToDecimal;
		VirtualInvokeData _20_System_IConvertible_ToDateTime;
		VirtualInvokeData _21_ToString;
		VirtualInvokeData _22_System_IConvertible_ToType;
		VirtualInvokeData _23_System_Collections_IEnumerable_GetEnumerator;
		VirtualInvokeData _24_CompareTo;
		VirtualInvokeData _25_System_Collections_Generic_IEnumerable_System_Char__GetEnumerator;
		VirtualInvokeData _26_Equals;
	};
	struct System_String_c {
		Il2CppClass_1 _1;
		System_String_StaticFields* static_fields;
		Il2CppClass_2 _2;
		System_String_VTable vtable;
	};
	struct System_String_o {
		System_String_c* klass;
		void* monitor;
		int32_t m_stringLength;
		uint16_t m_firstChar;
	};

	//20375
	struct Moon_IMoonType_string__o;

	//252468
	struct UnityEngine_GameObject_StaticFields {
	};
	struct UnityEngine_GameObject_VTable {
		VirtualInvokeData _0_Equals;
		VirtualInvokeData _1_Finalize;
		VirtualInvokeData _2_GetHashCode;
		VirtualInvokeData _3_ToString;
	};
	struct UnityEngine_GameObject_c {
		Il2CppClass_1 _1;
		UnityEngine_GameObject_StaticFields* static_fields;
		Il2CppClass_2 _2;
		UnityEngine_GameObject_VTable vtable;
	};
	struct UnityEngine_GameObject_o {
		UnityEngine_GameObject_c* klass;
		void* monitor;
		intptr_t Object_m_CachedPtr;
	};

	//254414
	struct UnityEngine_Object_StaticFields {
		int32_t OffsetOfInstanceIDInCPlusPlusObject;
	};
	struct UnityEngine_Object_VTable {
		VirtualInvokeData _0_Equals;
		VirtualInvokeData _1_Finalize;
		VirtualInvokeData _2_GetHashCode;
		VirtualInvokeData _3_ToString;
	};
	struct UnityEngine_Object_c {
		Il2CppClass_1 _1;
		UnityEngine_Object_StaticFields* static_fields;
		Il2CppClass_2 _2;
		UnityEngine_Object_VTable vtable;
	};
	struct UnityEngine_Object_o {
		UnityEngine_Object_c* klass;
		void* monitor;
		intptr_t m_CachedPtr;
	};

	//260292
	struct Moon_IMoonTypeResolver_StaticFields {
	};
	struct Moon_IMoonTypeResolver_VTable {
	};
	struct Moon_IMoonTypeResolver_c {
		Il2CppClass_1 _1;
		Moon_IMoonTypeResolver_StaticFields* static_fields;
		Il2CppClass_2 _2;
		Moon_IMoonTypeResolver_VTable vtable;
	};
	struct Moon_IMoonTypeResolver_o {
		Moon_IMoonTypeResolver_c* klass;
		void* monitor;
	};

	//260722
	struct Moon_MoonString_StaticFields {
	};
	struct Moon_MoonString_VTable {
		VirtualInvokeData _0_Equals;
		VirtualInvokeData _1_Finalize;
		VirtualInvokeData _2_GetHashCode;
		VirtualInvokeData _3_ToString;
		VirtualInvokeData _4_Resolve;
		VirtualInvokeData _5_SafeResolve;
		VirtualInvokeData _6_TryResolve;
		VirtualInvokeData _7_get_IsStaticValue;
		VirtualInvokeData _8_GetTypeData;
		VirtualInvokeData _9_CanResolve;
		VirtualInvokeData _10_get_IsCrossSceneReference;
	};
	struct Moon_MoonString_c {
		Il2CppClass_1 _1;
		Moon_MoonString_StaticFields* static_fields;
		Il2CppClass_2 _2;
		Moon_MoonString_VTable vtable;
	};
	struct Moon_MoonString_o {
		Moon_MoonString_c* klass;
		void* monitor;
		System_String_o* m_staticValue;
		Moon_MoonTypeData_o m_data;
		bool m_isInitialized;
		bool m_isStatic;
		bool m_canResolve;
		Moon_IMoonTypeResolver_o* m_resolver;
		Moon_IMoonType_string__o* m_cachedProxyType;
	};

	//665611
	struct Moon_IMoonType_string__StaticFields {
	};
	struct Moon_IMoonType_string__VTable {
	};
	struct Moon_IMoonType_string__c {
		Il2CppClass_1 _1;
		Moon_IMoonType_string__StaticFields* static_fields;
		Il2CppClass_2 _2;
		Moon_IMoonType_string__VTable vtable;
	};
	struct Moon_IMoonType_string__o {
		Moon_IMoonType_string__c* klass;
		void* monitor;
	};
}