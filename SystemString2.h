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

    typedef struct Il2CppClass Il2CppClass;
    typedef struct EventInfo EventInfo;
    typedef struct MethodInfo MethodInfo;
    typedef struct FieldInfo FieldInfo;
    typedef struct PropertyInfo PropertyInfo;
    typedef struct Il2CppAssembly Il2CppAssembly;
    typedef struct Il2CppArray Il2CppArray;
    typedef struct Il2CppDelegate Il2CppDelegate;
    typedef struct Il2CppDomain Il2CppDomain;
    typedef struct Il2CppImage Il2CppImage;
    typedef struct Il2CppException Il2CppException;
    typedef struct Il2CppProfiler Il2CppProfiler;
    typedef struct Il2CppObject Il2CppObject;
    typedef struct Il2CppReflectionMethod Il2CppReflectionMethod;
    typedef struct Il2CppReflectionType Il2CppReflectionType;
    typedef struct Il2CppString Il2CppString;
    typedef struct Il2CppThread Il2CppThread;
    typedef struct Il2CppAsyncResult Il2CppAsyncResult;
    typedef struct Il2CppCustomAttrInfo Il2CppCustomAttrInfo;

    typedef enum Il2CppTypeEnum
    {
        IL2CPP_TYPE_END = 0x00,
        IL2CPP_TYPE_VOID = 0x01,
        IL2CPP_TYPE_BOOLEAN = 0x02,
        IL2CPP_TYPE_CHAR = 0x03,
        IL2CPP_TYPE_I1 = 0x04,
        IL2CPP_TYPE_U1 = 0x05,
        IL2CPP_TYPE_I2 = 0x06,
        IL2CPP_TYPE_U2 = 0x07,
        IL2CPP_TYPE_I4 = 0x08,
        IL2CPP_TYPE_U4 = 0x09,
        IL2CPP_TYPE_I8 = 0x0a,
        IL2CPP_TYPE_U8 = 0x0b,
        IL2CPP_TYPE_R4 = 0x0c,
        IL2CPP_TYPE_R8 = 0x0d,
        IL2CPP_TYPE_STRING = 0x0e,
        IL2CPP_TYPE_PTR = 0x0f,
        IL2CPP_TYPE_BYREF = 0x10,
        IL2CPP_TYPE_VALUETYPE = 0x11,
        IL2CPP_TYPE_CLASS = 0x12,
        IL2CPP_TYPE_VAR = 0x13,
        IL2CPP_TYPE_ARRAY = 0x14,
        IL2CPP_TYPE_GENERICINST = 0x15,
        IL2CPP_TYPE_TYPEDBYREF = 0x16,
        IL2CPP_TYPE_I = 0x18,
        IL2CPP_TYPE_U = 0x19,
        IL2CPP_TYPE_FNPTR = 0x1b,
        IL2CPP_TYPE_OBJECT = 0x1c,
        IL2CPP_TYPE_SZARRAY = 0x1d,
        IL2CPP_TYPE_MVAR = 0x1e,
        IL2CPP_TYPE_CMOD_REQD = 0x1f,
        IL2CPP_TYPE_CMOD_OPT = 0x20,
        IL2CPP_TYPE_INTERNAL = 0x21,
        IL2CPP_TYPE_MODIFIER = 0x40,
        IL2CPP_TYPE_SENTINEL = 0x41,
        IL2CPP_TYPE_PINNED = 0x45,
        IL2CPP_TYPE_ENUM = 0x55
    } Il2CppTypeEnum;
    typedef int32_t TypeIndex;
    typedef int32_t TypeDefinitionIndex;
    typedef int32_t FieldIndex;
    typedef int32_t DefaultValueIndex;
    typedef int32_t DefaultValueDataIndex;
    typedef int32_t CustomAttributeIndex;
    typedef int32_t ParameterIndex;
    typedef int32_t MethodIndex;
    typedef int32_t GenericMethodIndex;
    typedef int32_t PropertyIndex;
    typedef int32_t EventIndex;
    typedef int32_t GenericContainerIndex;
    typedef int32_t GenericParameterIndex;
    typedef int16_t GenericParameterConstraintIndex;
    typedef int32_t NestedTypeIndex;
    typedef int32_t InterfacesIndex;
    typedef int32_t VTableIndex;
    typedef int32_t InterfaceOffsetIndex;
    typedef int32_t RGCTXIndex;
    typedef int32_t StringIndex;
    typedef int32_t StringLiteralIndex;
    typedef int32_t GenericInstIndex;
    typedef int32_t ImageIndex;
    typedef int32_t AssemblyIndex;
    typedef int32_t InteropDataIndex;
    const TypeIndex kTypeIndexInvalid = -1;
    const TypeDefinitionIndex kTypeDefinitionIndexInvalid = -1;
    const DefaultValueDataIndex kDefaultValueIndexNull = -1;
    const CustomAttributeIndex kCustomAttributeIndexInvalid = -1;
    const EventIndex kEventIndexInvalid = -1;
    const FieldIndex kFieldIndexInvalid = -1;
    const MethodIndex kMethodIndexInvalid = -1;
    const PropertyIndex kPropertyIndexInvalid = -1;
    const GenericContainerIndex kGenericContainerIndexInvalid = -1;
    const GenericParameterIndex kGenericParameterIndexInvalid = -1;
    const RGCTXIndex kRGCTXIndexInvalid = -1;
    const StringLiteralIndex kStringLiteralIndexInvalid = -1;
    const InteropDataIndex kInteropDataIndexInvalid = -1;
    typedef uint32_t EncodedMethodIndex;

    typedef struct Il2CppTypeDefinition
    {
        StringIndex nameIndex;
        StringIndex namespaceIndex;
        TypeIndex byvalTypeIndex;
        TypeIndex byrefTypeIndex;
        TypeIndex declaringTypeIndex;
        TypeIndex parentIndex;
        TypeIndex elementTypeIndex;
        RGCTXIndex rgctxStartIndex;
        int32_t rgctxCount;
        GenericContainerIndex genericContainerIndex;
        uint32_t flags;
        FieldIndex fieldStart;
        MethodIndex methodStart;
        EventIndex eventStart;
        PropertyIndex propertyStart;
        NestedTypeIndex nestedTypesStart;
        InterfacesIndex interfacesStart;
        VTableIndex vtableStart;
        InterfacesIndex interfaceOffsetsStart;
        uint16_t method_count;
        uint16_t property_count;
        uint16_t field_count;
        uint16_t event_count;
        uint16_t nested_type_count;
        uint16_t vtable_count;
        uint16_t interfaces_count;
        uint16_t interface_offsets_count;
        uint32_t bitfield;
        uint32_t token;
    } Il2CppTypeDefinition;


    typedef enum
    {
        IL2CPP_PROFILE_NONE = 0,
        IL2CPP_PROFILE_APPDOMAIN_EVENTS = 1 << 0,
        IL2CPP_PROFILE_ASSEMBLY_EVENTS = 1 << 1,
        IL2CPP_PROFILE_MODULE_EVENTS = 1 << 2,
        IL2CPP_PROFILE_CLASS_EVENTS = 1 << 3,
        IL2CPP_PROFILE_JIT_COMPILATION = 1 << 4,
        IL2CPP_PROFILE_INLINING = 1 << 5,
        IL2CPP_PROFILE_EXCEPTIONS = 1 << 6,
        IL2CPP_PROFILE_ALLOCATIONS = 1 << 7,
        IL2CPP_PROFILE_GC = 1 << 8,
        IL2CPP_PROFILE_THREADS = 1 << 9,
        IL2CPP_PROFILE_REMOTING = 1 << 10,
        IL2CPP_PROFILE_TRANSITIONS = 1 << 11,
        IL2CPP_PROFILE_ENTER_LEAVE = 1 << 12,
        IL2CPP_PROFILE_COVERAGE = 1 << 13,
        IL2CPP_PROFILE_INS_COVERAGE = 1 << 14,
        IL2CPP_PROFILE_STATISTICAL = 1 << 15,
        IL2CPP_PROFILE_METHOD_EVENTS = 1 << 16,
        IL2CPP_PROFILE_MONITOR_EVENTS = 1 << 17,
        IL2CPP_PROFILE_IOMAP_EVENTS = 1 << 18,
        IL2CPP_PROFILE_GC_MOVES = 1 << 19,
        IL2CPP_PROFILE_FILEIO = 1 << 20
    } Il2CppProfileFlags;
    typedef enum
    {
        IL2CPP_PROFILE_FILEIO_WRITE = 0,
        IL2CPP_PROFILE_FILEIO_READ
    } Il2CppProfileFileIOKind;
    typedef enum
    {
        IL2CPP_GC_EVENT_START,
        IL2CPP_GC_EVENT_MARK_START,
        IL2CPP_GC_EVENT_MARK_END,
        IL2CPP_GC_EVENT_RECLAIM_START,
        IL2CPP_GC_EVENT_RECLAIM_END,
        IL2CPP_GC_EVENT_END,
        IL2CPP_GC_EVENT_PRE_STOP_WORLD,
        IL2CPP_GC_EVENT_POST_STOP_WORLD,
        IL2CPP_GC_EVENT_PRE_START_WORLD,
        IL2CPP_GC_EVENT_POST_START_WORLD
    } Il2CppGCEvent;
    typedef enum
    {
        IL2CPP_STAT_NEW_OBJECT_COUNT,
        IL2CPP_STAT_INITIALIZED_CLASS_COUNT,
        IL2CPP_STAT_METHOD_COUNT,
        IL2CPP_STAT_CLASS_STATIC_DATA_SIZE,
        IL2CPP_STAT_GENERIC_INSTANCE_COUNT,
        IL2CPP_STAT_GENERIC_CLASS_COUNT,
        IL2CPP_STAT_INFLATED_METHOD_COUNT,
        IL2CPP_STAT_INFLATED_TYPE_COUNT,
    } Il2CppStat;
    typedef enum
    {
        IL2CPP_UNHANDLED_POLICY_LEGACY,
        IL2CPP_UNHANDLED_POLICY_CURRENT
    } Il2CppRuntimeUnhandledExceptionPolicy;
    typedef struct Il2CppStackFrameInfo
    {
        const MethodInfo* method;
    } Il2CppStackFrameInfo;


    typedef enum Il2CppRGCTXDataType
    {
        IL2CPP_RGCTX_DATA_INVALID,
        IL2CPP_RGCTX_DATA_TYPE,
        IL2CPP_RGCTX_DATA_CLASS,
        IL2CPP_RGCTX_DATA_METHOD,
        IL2CPP_RGCTX_DATA_ARRAY,
    } Il2CppRGCTXDataType;

    typedef union Il2CppRGCTXData
    {
        void* rgctxDataDummy;
        const MethodInfo* method;
        const Il2CppType* type;
        Il2CppClass* klass;
    } Il2CppRGCTXData;


    typedef uint16_t Il2CppChar;
    typedef char Il2CppNativeChar;
    typedef void (*il2cpp_register_object_callback)(Il2CppObject** arr, int size, void* userdata);
    typedef void (*il2cpp_WorldChangedCallback)();
    typedef void (*Il2CppFrameWalkFunc) (const Il2CppStackFrameInfo* info, void* user_data);
    typedef void (*Il2CppProfileFunc) (Il2CppProfiler* prof);
    typedef void (*Il2CppProfileMethodFunc) (Il2CppProfiler* prof, const MethodInfo* method);
    typedef void (*Il2CppProfileAllocFunc) (Il2CppProfiler* prof, Il2CppObject* obj, Il2CppClass* klass);
    typedef void (*Il2CppProfileGCFunc) (Il2CppProfiler* prof, Il2CppGCEvent event, int generation);
    typedef void (*Il2CppProfileGCResizeFunc) (Il2CppProfiler* prof, int64_t new_size);
    typedef void (*Il2CppProfileFileIOFunc) (Il2CppProfiler* prof, Il2CppProfileFileIOKind kind, int count);
    typedef void (*Il2CppProfileThreadFunc) (Il2CppProfiler* prof, unsigned long tid);
    typedef const Il2CppNativeChar* (*Il2CppSetFindPlugInCallback)(const Il2CppNativeChar*);
    typedef void (*Il2CppLogCallback)(const char*);
    typedef struct Il2CppManagedMemorySnapshot Il2CppManagedMemorySnapshot;
    typedef void (*Il2CppMethodPointer)();
    typedef uintptr_t il2cpp_array_size_t;
    typedef uint32_t Il2CppMethodSlot;
    const uint32_t kInvalidIl2CppMethodSlot = 65535;
    const int ipv6AddressSize = 16;
    typedef int32_t il2cpp_hresult_t;


    typedef struct Il2CppGuid Il2CppGuid;
    typedef struct Il2CppAppDomain Il2CppAppDomain;
    typedef struct Il2CppAppDomainSetup Il2CppAppDomainSetup;
    typedef struct Il2CppAppContext Il2CppAppContext;
    typedef struct Il2CppNameToTypeDefinitionIndexHashTable Il2CppNameToTypeDefinitionIndexHashTable;
    typedef struct VirtualInvokeData
    {
        Il2CppMethodPointer methodPtr;
        const MethodInfo* method;
    } VirtualInvokeData;


    struct MoonTypeExtraData {
        int32_t IntExtraData;
    };
    struct MoonTypeExtraData__Boxed {
        struct MoonTypeExtraData__Class* klass;
        struct MonitorData* monitor;
        struct MoonTypeExtraData fields;
    };
    struct MoonTypeData {
        struct Object_1* UnityObjectRef;
        struct MoonTypeExtraData ExtraData;
    };
    struct MoonTypeData__Boxed {
        struct MoonTypeData__Class* klass;
        struct MonitorData* monitor;
        struct MoonTypeData fields;
    };


    typedef void (*PInvokeMarshalToNativeFunc)(void* managedStructure, void* marshaledStructure);
    typedef void (*PInvokeMarshalFromNativeFunc)(void* marshaledStructure, void* managedStructure);
    typedef void (*PInvokeMarshalCleanupFunc)(void* marshaledStructure);
    typedef struct Il2CppIUnknown* (*CreateCCWFunc)(Il2CppObject* obj);
    typedef struct Il2CppInteropData
    {
        Il2CppMethodPointer delegatePInvokeWrapperFunction;
        PInvokeMarshalToNativeFunc pinvokeMarshalToNativeFunction;
        PInvokeMarshalFromNativeFunc pinvokeMarshalFromNativeFunction;
        PInvokeMarshalCleanupFunc pinvokeMarshalCleanupFunction;
        CreateCCWFunc createCCWFunction;
        const Il2CppGuid* guid;
        const Il2CppType* type;
    } Il2CppInteropData;

    typedef struct Il2CppGenericInst
    {
        uint32_t type_argc;
        const Il2CppType** type_argv;
    } Il2CppGenericInst;

    typedef struct Il2CppGenericContext
    {
        const Il2CppGenericInst* class_inst;
        const Il2CppGenericInst* method_inst;
    } Il2CppGenericContext;

    typedef struct Il2CppGenericClass
    {
        TypeDefinitionIndex typeDefinitionIndex;
        Il2CppGenericContext context;
        Il2CppClass* cached_class;
    } Il2CppGenericClass;

    typedef struct Il2CppArrayType
    {
        const Il2CppType* etype;
        uint8_t rank;
        uint8_t numsizes;
        uint8_t numlobounds;
        int* sizes;
        int* lobounds;
    } Il2CppArrayType;

    typedef struct Il2CppType
    {
        union
        {
            void* dummy;
            TypeDefinitionIndex klassIndex;
            const Il2CppType* type;
            Il2CppArrayType* array;
            GenericParameterIndex genericParameterIndex;
            Il2CppGenericClass* generic_class;
        } data;
        unsigned int attrs : 16;
        Il2CppTypeEnum type : 8;
        unsigned int num_mods : 6;
        unsigned int byref : 1;
        unsigned int pinned : 1;
    } Il2CppType;

    typedef struct Il2CppRuntimeInterfaceOffsetPair
    {
        Il2CppClass* interfaceType;
        int32_t offset;
    } Il2CppRuntimeInterfaceOffsetPair;

    typedef struct Il2CppClass_0 {
        const Il2CppImage* image;
        void* gc_desc;
        const char* name;
        const char* namespaze;
        Il2CppType byval_arg;
        Il2CppType this_arg;
        Il2CppClass* element_class;
        Il2CppClass* castClass;
        Il2CppClass* declaringType;
        Il2CppClass* parent;
        Il2CppGenericClass* generic_class;
        const Il2CppTypeDefinition* typeDefinition;
        const Il2CppInteropData* interopData;
        Il2CppClass* klass;
        FieldInfo* fields;
        const EventInfo* events;
        const PropertyInfo* properties;
        const MethodInfo** methods;
        Il2CppClass** nestedTypes;
        Il2CppClass** implementedInterfaces;
    } Il2CppClass_0;

    typedef struct Il2CppClass_1 {
        Il2CppClass** typeHierarchy;
        uint32_t initializationExceptionGCHandle;
        uint32_t cctor_started;
        uint32_t cctor_finished;
#ifdef IS_32BIT
        uint32_t cctor_thread__padding;
        uint32_t cctor_thread;
        uint32_t cctor_thread__hi;
#else
        __declspec(align(8)) uint64_t cctor_thread;
#endif
        GenericContainerIndex genericContainerIndex;
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
        uint8_t packingSize;
        uint8_t initialized_and_no_error : 1;
        uint8_t valuetype : 1;
        uint8_t initialized : 1;
        uint8_t enumtype : 1;
        uint8_t is_generic : 1;
        uint8_t has_references : 1;
        uint8_t init_pending : 1;
        uint8_t size_inited : 1;
        uint8_t has_finalize : 1;
        uint8_t has_cctor : 1;
        uint8_t is_blittable : 1;
        uint8_t is_import_or_windows_runtime : 1;
        uint8_t is_vtable_initialized : 1;
        uint8_t has_initialization_error : 1;
    } Il2CppClass_1;


    struct __declspec(align(8)) MoonString__Fields {
        struct String* m_staticValue;
        struct MoonTypeData m_data;
        bool m_isInitialized;
        bool m_isStatic;
        bool m_canResolve;
        struct IMoonTypeResolver* m_resolver;
        struct IMoonType_1_System_String_* m_cachedProxyType;
    };
    struct MoonString {
        struct MoonString__Class* klass;
        struct MonitorData* monitor;
        struct MoonString__Fields fields;
    };
    struct MoonString__VTable {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData Resolve;
        VirtualInvokeData SafeResolve;
        VirtualInvokeData TryResolve;
        VirtualInvokeData get_IsStaticValue;
        VirtualInvokeData GetTypeData;
        VirtualInvokeData CanResolve;
        VirtualInvokeData get_IsCrossSceneReference;
    };
    struct MoonString__StaticFields {
    };
    struct MoonString__Class {
        struct Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct MoonString__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        struct Il2CppClass_1 _1;
        struct MoonString__VTable vtable;
    };
    struct MoonTypeData__VTable {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };
    struct MoonTypeData__StaticFields {
    };
    struct MoonTypeData__Class {
        struct Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct MoonTypeData__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        struct Il2CppClass_1 _1;
        struct MoonTypeData__VTable vtable;
    };
}