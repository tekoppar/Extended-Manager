#pragma once
namespace Moon {
    typedef unsigned int size_t;
    typedef signed char int8_t;
    typedef unsigned char uint8_t;
    typedef signed short int16_t;
    typedef unsigned short uint16_t;
    typedef signed int int32_t;
    typedef unsigned int uint32_t;
    typedef signed long long int64_t;
    typedef unsigned long long uint64_t;
    typedef unsigned long uintptr_t;

    //14
    typedef struct Il2CppClass Il2CppClass;
    typedef struct Il2CppType Il2CppType;
    typedef struct EventInfo EventInfo;
    typedef struct MethodInfo MethodInfo;
    typedef struct FieldInfo FieldInfo;
    typedef struct PropertyInfo PropertyInfo;
    typedef struct Il2CppAssembly Il2CppAssembly;
    typedef struct Il2CppArray Il2CppArray;
    typedef struct Il2CppDelegate Il2CppDelegate;
    //typedef struct Il2CppDomain Il2CppDomain;
    typedef struct Il2CppImage Il2CppImage;
    typedef struct Il2CppException Il2CppException;
    typedef struct Il2CppProfiler Il2CppProfiler;
    typedef struct Il2CppObject Il2CppObject;
    typedef struct Il2CppReflectionMethod Il2CppReflectionMethod;
    typedef struct Il2CppReflectionType Il2CppReflectionType;
    typedef struct Il2CppString Il2CppString;
    typedef struct Il2CppThread Il2CppThread;
    typedef struct Il2CppAsyncResult Il2CppAsyncResult;
    typedef struct Il2CppManagedMemorySnapshot Il2CppManagedMemorySnapshot;
    typedef struct Il2CppCustomAttrInfo Il2CppCustomAttrInfo;

    //122
    typedef void (*Il2CppMethodPointer)();

    //128
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

    //167
    typedef int32_t TypeIndex;
    typedef int32_t ParameterIndex;
    typedef int32_t GenericContainerIndex;
    typedef int32_t RGCTXIndex;
    typedef int32_t TypeDefinitionIndex;
    typedef int32_t CustomAttributeIndex;
    typedef int32_t MethodIndex;
    typedef int32_t StringIndex;
    typedef int32_t FieldIndex;
    typedef int32_t EventIndex;
    typedef int32_t PropertyIndex;
    typedef int32_t NestedTypeIndex;
    typedef int32_t InterfacesIndex;
    typedef int32_t VTableIndex;
    typedef int32_t GenericParameterIndex;

    //243
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

    //310
    typedef struct Il2CppMethodDefinition
    {
        StringIndex nameIndex;
        TypeDefinitionIndex declaringType;
        TypeIndex returnType;
        ParameterIndex parameterStart;
        GenericContainerIndex genericContainerIndex;
        MethodIndex methodIndex;
        MethodIndex invokerIndex;
        MethodIndex reversePInvokeWrapperIndex;
        RGCTXIndex rgctxStartIndex;
        int32_t rgctxCount;
        uint32_t token;
        uint16_t flags;
        uint16_t iflags;
        uint16_t slot;
        uint16_t parameterCount;
    } Il2CppMethodDefinition;

    //367
    typedef struct Il2CppAssemblyNameDefinition
    {
        StringIndex nameIndex;
        StringIndex cultureIndex;
        StringIndex hashValueIndex;
        StringIndex publicKeyIndex;
        uint32_t hash_alg;
        int32_t hash_len;
        uint32_t flags;
        int32_t major;
        int32_t minor;
        int32_t build;
        int32_t revision;
        uint8_t public_key_token[8];
    } Il2CppAssemblyNameDefinition;

    //505
    typedef struct Il2CppArrayType
    {
        const Il2CppType* etype;
        uint8_t rank;
        uint8_t numsizes;
        uint8_t numlobounds;
        int* sizes;
        int* lobounds;
    } Il2CppArrayType;

    //514
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

    //533
    typedef struct Il2CppGenericContainer
    {
        int32_t ownerIndex;
        int32_t type_argc;
        int32_t is_method;
        GenericParameterIndex genericParameterStart;
    } Il2CppGenericContainer;
    typedef struct Il2CppGenericClass
    {
        TypeDefinitionIndex typeDefinitionIndex;
        Il2CppGenericContext context;
        Il2CppClass* cached_class;
    } Il2CppGenericClass;

    typedef struct Il2CppGenericMethod
    {
        const MethodInfo* methodDefinition;
        Il2CppGenericContext context;
    } Il2CppGenericMethod;

    //551
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


    //584
    typedef struct Il2CppGuid Il2CppGuid;
    typedef struct Il2CppAppDomain Il2CppAppDomain;
    typedef struct Il2CppAppDomainSetup Il2CppAppDomainSetup;
    typedef struct Il2CppAppContext Il2CppAppContext;

    //590
    typedef struct Il2CppNameToTypeDefinitionIndexHashTable Il2CppNameToTypeDefinitionIndexHashTable;
    typedef struct VirtualInvokeData
    {
        Il2CppMethodPointer methodPtr;
        const MethodInfo* method;
    } VirtualInvokeData;

    //701
    typedef struct FieldInfo
    {
        const char* name;
        const Il2CppType* type;
        Il2CppClass* parent;
        int32_t offset;
        uint32_t token;
    } FieldInfo;

    typedef struct PropertyInfo
    {
        Il2CppClass* parent;
        const char* name;
        const MethodInfo* get;
        const MethodInfo* set;
        uint32_t attrs;
        uint32_t token;
    } PropertyInfo;

    typedef struct EventInfo
    {
        const char* name;
        const Il2CppType* eventType;
        Il2CppClass* parent;
        const MethodInfo* add;
        const MethodInfo* remove;
        const MethodInfo* raise;
        uint32_t token;
    } EventInfo;

    //728
    typedef struct ParameterInfo
    {
        const char* name;
        int32_t position;
        uint32_t token;
        const Il2CppType* parameter_type;
    } ParameterInfo;

    //735
    typedef void* (*InvokerMethod)(Il2CppMethodPointer, const MethodInfo*, void*, void**);

    //812
    typedef union Il2CppRGCTXData
    {
        void* rgctxDataDummy;
        const MethodInfo* method;
        const Il2CppType* type;
        Il2CppClass* klass;
    } Il2CppRGCTXData;

    typedef struct MethodInfo
    {
        Il2CppMethodPointer methodPointer;
        InvokerMethod invoker_method;
        const char* name;
        Il2CppClass* klass;
        const Il2CppType* return_type;
        const ParameterInfo* parameters;
        union
        {
            const Il2CppRGCTXData* rgctx_data;
            const Il2CppMethodDefinition* methodDefinition;
        };
        union
        {
            const Il2CppGenericMethod* genericMethod;
            const Il2CppGenericContainer* genericContainer;
        };
        uint32_t token;
        uint16_t flags;
        uint16_t iflags;
        uint16_t slot;
        uint8_t parameters_count;
        uint8_t is_generic : 1;
        uint8_t is_inflated : 1;
        uint8_t wrapper_type : 1;
        uint8_t is_marshaled_from_native : 1;
    } MethodInfo;

    //847
    typedef struct Il2CppRuntimeInterfaceOffsetPair
    {
        Il2CppClass* interfaceType;
        int32_t offset;
    } Il2CppRuntimeInterfaceOffsetPair;

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

    typedef struct Il2CppClass
    {
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
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        void* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass** typeHierarchy;
        uint32_t initializationExceptionGCHandle;
        uint32_t cctor_started;
        uint32_t cctor_finished;
        __declspec(align(8)) uint64_t cctor_thread;
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
        VirtualInvokeData vtable[32];
    } Il2CppClass;

    //1026
    typedef struct Il2CppDomain
    {
        Il2CppAppDomain* domain;
        Il2CppAppDomainSetup* setup;
        Il2CppAppContext* default_context;
        const char* friendly_name;
        uint32_t domain_id;
        void* agent_info;
    } Il2CppDomain;

    typedef struct Il2CppAssemblyName
    {
        const char* name;
        const char* culture;
        const char* hash_value;
        const char* public_key;
        uint32_t hash_alg;
        int32_t hash_len;
        uint32_t flags;
        int32_t major;
        int32_t minor;
        int32_t build;
        int32_t revision;
        uint8_t public_key_token[8];
    } Il2CppAssemblyName;

    //1050
    typedef struct Il2CppImage
    {
        const char* name;
        const char* nameNoExt;
        Il2CppAssembly* assembly;
        TypeDefinitionIndex typeStart;
        uint32_t typeCount;
        TypeDefinitionIndex exportedTypeStart;
        uint32_t exportedTypeCount;
        CustomAttributeIndex customAttributeStart;
        uint32_t customAttributeCount;
        MethodIndex entryPointIndex;
        Il2CppNameToTypeDefinitionIndexHashTable* nameToClassHashTable;
        uint32_t token;
        uint8_t dynamic;
    } Il2CppImage;

    //1067
    typedef struct Il2CppAssembly
    {
        Il2CppImage* image;
        uint32_t token;
        int32_t referencedAssemblyStart;
        int32_t referencedAssemblyCount;
        Il2CppAssemblyName aname;
    } Il2CppAssembly;

    //1196
    struct Il2CppObject {
        struct Il2CppClass* klass;
        struct MonitorData* monitor;
    };
}