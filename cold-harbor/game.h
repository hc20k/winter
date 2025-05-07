#pragma once

typedef _CRT_ALIGN(16) struct _SETJMP_FLOAT128 {
	__int64 LowPart;
	__int64 HighPart;
} SETJMP_FLOAT128;

namespace game {
	enum XAssetType
	{
		ASSET_TYPE_XMODELPIECES = 0x0,
		ASSET_TYPE_PHYSPRESET = 0x1,
		ASSET_TYPE_PHYSCONSTRAINTS = 0x2,
		ASSET_TYPE_DESTRUCTIBLEDEF = 0x3,
		ASSET_TYPE_XANIMPARTS = 0x4,
		ASSET_TYPE_XMODEL = 0x5,
		ASSET_TYPE_MATERIAL = 0x6,
		ASSET_TYPE_TECHNIQUE_SET = 0x7,
		ASSET_TYPE_IMAGE = 0x8,
		ASSET_TYPE_SOUND = 0x9,
		ASSET_TYPE_SOUND_PATCH = 0xA,
		ASSET_TYPE_CLIPMAP = 0xB,
		ASSET_TYPE_CLIPMAP_PVS = 0xC,
		ASSET_TYPE_COMWORLD = 0xD,
		ASSET_TYPE_GAMEWORLD_SP = 0xE,
		ASSET_TYPE_GAMEWORLD_MP = 0xF,
		ASSET_TYPE_MAP_ENTS = 0x10,
		ASSET_TYPE_GFXWORLD = 0x11,
		ASSET_TYPE_LIGHT_DEF = 0x12,
		ASSET_TYPE_UI_MAP = 0x13,
		ASSET_TYPE_FONT = 0x14,
		ASSET_TYPE_FONTICON = 0x15,
		ASSET_TYPE_MENULIST = 0x16,
		ASSET_TYPE_MENU = 0x17,
		ASSET_TYPE_LOCALIZE_ENTRY = 0x18,
		ASSET_TYPE_WEAPON = 0x19,
		ASSET_TYPE_WEAPONDEF = 0x1A,
		ASSET_TYPE_WEAPON_VARIANT = 0x1B,
		ASSET_TYPE_WEAPON_FULL = 0x1C,
		ASSET_TYPE_ATTACHMENT = 0x1D,
		ASSET_TYPE_ATTACHMENT_UNIQUE = 0x1E,
		ASSET_TYPE_WEAPON_CAMO = 0x1F,
		ASSET_TYPE_SNDDRIVER_GLOBALS = 0x20,
		ASSET_TYPE_FX = 0x21,
		ASSET_TYPE_IMPACT_FX = 0x22,
		ASSET_TYPE_AITYPE = 0x23,
		ASSET_TYPE_MPTYPE = 0x24,
		ASSET_TYPE_MPBODY = 0x25,
		ASSET_TYPE_MPHEAD = 0x26,
		ASSET_TYPE_CHARACTER = 0x27,
		ASSET_TYPE_XMODELALIAS = 0x28,
		ASSET_TYPE_RAWFILE = 0x29,
		ASSET_TYPE_STRINGTABLE = 0x2A,
		ASSET_TYPE_LEADERBOARD = 0x2B,
		ASSET_TYPE_XGLOBALS = 0x2C,
		ASSET_TYPE_DDL = 0x2D,
		ASSET_TYPE_GLASSES = 0x2E,
		ASSET_TYPE_EMBLEMSET = 0x2F,
		ASSET_TYPE_SCRIPTPARSETREE = 0x30,
		ASSET_TYPE_KEYVALUEPAIRS = 0x31,
		ASSET_TYPE_VEHICLEDEF = 0x32,
		ASSET_TYPE_MEMORYBLOCK = 0x33,
		ASSET_TYPE_ADDON_MAP_ENTS = 0x34,
		ASSET_TYPE_TRACER = 0x35,
		ASSET_TYPE_SKINNEDVERTS = 0x36,
		ASSET_TYPE_QDB = 0x37,
		ASSET_TYPE_SLUG = 0x38,
		ASSET_TYPE_FOOTSTEP_TABLE = 0x39,
		ASSET_TYPE_FOOTSTEPFX_TABLE = 0x3A,
		ASSET_TYPE_ZBARRIER = 0x3B,
		ASSET_TYPE_COUNT = 0x3C,
		ASSET_TYPE_STRING = 0x3C,
		ASSET_TYPE_ASSETLIST = 0x3D,
		ASSET_TYPE_REPORT = 0x3E,
		ASSET_TYPE_DEPEND = 0x3F,
		ASSET_TYPE_FULL_COUNT = 0x40,
	};

	enum XZoneFlags
	{
		DB_ZONE_NULL = 0,
		DB_ZONE_CODE = 1,		// 0x1,
		DB_ZONE_CODE_LOC = 1 << 1,	// 0x2,

		DB_ZONE_DEV = 1 << 2,	// 0x4, (IN SP: DB_ZONE_DEV == DB_ZONE_DEV_LOC )
		// DB_ZONE_DEV_LOC			= 1 << 2,	// 0x4,

		DB_ZONE_PATCH = 1 << 3,	// 0x8,
		DB_ZONE_PATCH_LOC = 1 << 4,	// 0x10,
		DB_ZONE_MOD = 1 << 5,	// 0x20,
		DB_ZONE_MOD_LOC = 1 << 6,	// 0x40,
		DB_ZONE_COMMON = 1 << 8,	// 0x100,
		DB_ZONE_COMMON_LOC = 1 << 8,	// 0x100,

#if 0
		// These values need to be validated
		DB_ZONE_FFOTD = 1 << 9,	// 0x200,
		DB_ZONE_FFOTD_LOC = 1 << 10,	// 0x400,
		DB_ZONE_LEVELCOMMON = 1 << 11,	// 0x800,
		DB_ZONE_LEVELCOMMON_LOC = 1 << 12,	// 0x1000,
		DB_ZONE_LEVEL = 1 << 13,	// 0x2000,
		DB_ZONE_LEVEL_LOC = 1 << 14,	// 0x4000,
		DB_ZONE_LEVELOVERLAY = 1 << 15,	// 0x8000,
		DB_ZONE_LEVELOVERLAY_LOC = 1 << 16,	// 0x10000,
#endif

		DB_ZONE_GUMP = 1 << 17,	// 0x20000,
		DB_ZONE_GUMP_LOC = 1 << 18,	// 0x40000,

#if 0
		// These values need to be validated
		DB_ZONE_LOW_MARKER = 1 << 19,	// 0x80000,
		DB_ZONE_MYCHANGES_LOC = 1 << 20,	// 0x100000,
		DB_ZONE_MYCHANGES = 1 << 21,	// 0x200000,

		// Probably not used in SP
		DB_ZONE_UI_VIEWER_LOC = 1 << 22,	// 0x400000,
		DB_ZONE_UI_VIEWER = 1 << 23,	// 0x800000,

		DB_ZONE_FRONTEND_LOC = 1 << 24,	// 0x1000000,
		DB_ZONE_FRONTEND = 1 << 25,	// 0x2000000,
#endif

		DB_ZONE_PATCH_UI = 1 << 26, // 0x4000000,
		DB_ZONE_PATCH_UI_LOC = 1 << 27, // 0x8000000,

#if 0
		// These values need to be validated
		DB_ZONE_HIGH_MARKER = 1 << 26,	// 0x4000000,
		DB_ZONE_LOAD = 1 << 27,	// 0x8000000,
#endif

		DB_FLAG_NULL = 0,
		DB_FLAG_RSTREAM = 1 << 30,	// 0x40000000,
		DB_FLAG_STRICTFREE = 1 << 31,	// 0x80000000,
	};

	struct XZoneInfo
	{
		const char *name;
		uint32_t allocFlags;
		uint32_t freeFlags;
	};

	struct XBlock
	{
		unsigned __int8 *data;
		unsigned int size;
	};

	struct __declspec(align(128)) DB_LOAD_STREAM
	{
		unsigned __int8 decompressedData[32768];
		unsigned __int8 checksum[32];
		unsigned __int8 *compressedData;
		int compressedDataAvail;
		int decompressedDataAvail;
		int decompressedDataOffset;
		bool busy;
	};

	struct DBDecompressCmd_t
	{
		int which;
		DB_LOAD_STREAM *stream;
		unsigned __int8 *ioBuffer;
		unsigned __int8 iv[8];
	};

	struct __declspec(align(128)) DB_LoadData
	{
		int f;
		const char *filename;
		XBlock *blocks;
		int flags;
		void (__cdecl *interrupt)();
		int allocType;
		unsigned __int64 readOffset;
		unsigned __int64 endOffset;
		unsigned __int8 *ioBuffer;
		int ioBufferOffset;
		unsigned __int8 *compressData;
		int tail;
		int head;
		DBDecompressCmd_t cmd[4];
		DB_LOAD_STREAM stream[4];
		int next_buffer;
		int locks[4];
		bool loadPending[4];
		bool abort;
		int requiredVersion;
		int lastError;
		int startTime;
	};

	struct z_stream_s
	{
		unsigned __int8 *next_in;
		unsigned int avail_in;
		unsigned int total_in;
		unsigned __int8 *next_out;
		unsigned int avail_out;
		unsigned int total_out;
		char *msg;
		void *state;
		unsigned __int8 *(__cdecl *zalloc)(unsigned __int8 *, unsigned int, unsigned int);
		void (__cdecl *zfree)(unsigned __int8 *, unsigned __int8 *);
		unsigned __int8 *opaque;
		int data_type;
		unsigned int adler;
	};

	typedef float vec3_t[3];
	typedef float vec4_t[4];





	struct DObjAnimMat
	{
		float quat[4];
		float trans[3];
		float transWeight;
	};
	struct __declspec(align(16)) XSurface
	{
		char unknownData1[0x10];
		char tileMode;
		char vertListCount;
		unsigned __int16 flags;
		unsigned __int16 vertCount;
		unsigned __int16 triCount;
		unsigned __int16 baseVertIndex;
		unsigned __int16 *triIndices;							//Loaded Last, size = ((triCount << 1) + triCount) << 1
		//XSurfaceVertexInfo vertInfo;
		//unknownXModelStruct1Internal2 unkInternal2;		//if flags & 1 then use option2 else use verts0
		//D3DVertexBuffer vertexBuffer;
		//union
		//{
		//	XRigidVertList *vertList;
		//	XRigidVertList *vertListEA;
		//};
		//D3DIndexBuffer indexBuffer;
		//int partBits[5];
	};
	struct ScriptString
	{
	};
	struct XModel
	{
		const char *name;
		char numBones;
		char numRootBones;
		char numsurfs;
		char lodRampType;
		union
		{
			ScriptString * boneNames;
			ScriptString * localBoneNames;
		};
		union
		{
			char * parentList;  //size = numBones - numRootBones
			char * localParentList;  //size = numBones - numRootBones
		};
		union
		{
			unsigned short * quats;		//size = (numBones - numRootBones) << 3
			unsigned short * localQuats;	//size = (numBones - numRootBones) << 3
		};
		union
		{
			float * trans;							//size = (numBones - numRootBones) << 4
			float * localTrans;							//size = (numBones - numRootBones) << 4
		};
		char *partClassification;		//size = numBones
		DObjAnimMat *baseMat;					//size = numBones << 5
		XSurface *surfs;	//count = numsurfs
	};


	struct WeaponDef
	{
		const char *szOverlayName;
		XModel *gunXModel;//**
		XModel *handXModel;
		const char *szModeName;
	};
	struct WeaponVariantDef
	{
		char* name;
		int iVariantCount;
		WeaponDef *weapDef;
		const char *szDisplayName;
		const char *szAltWeaponName;
		const char *szAttachmentUnique;
		//.....
	};






	struct D3DBaseTexture
	{
		void* a1;
		char pad[0x30];
		//char pad[0x34];
	};
	struct GfxImage
	{
		D3DBaseTexture basemap;//size = 0x34    52
		char mapType;//							53
		char unknown3;//						54
		char unknown4;//						55
		char unknown5;//						56
		int size;//								60
		unsigned __int16 width;//				62
		unsigned __int16 height;//				64
		unsigned __int16 depth;//				66
		char levelCount;//						67
		char streaming;//						68
		unsigned int baseSize;//				72
		char *pixels;//							76 (pointer = 4 else char itself = 2)
		char unknownData2[0x7C];//				200
		char streamedPartCount;//				201
		const char *name;//						205
		unsigned int hash;//					209
	};
	//palceholder
	struct D3DPixelShader
	{

	};
	struct D3DVertexShader
	{

	};

	struct RawFile
	{
		const char *Name;
		int Length;
		const char *Buffer;
	};

	union XAssetHeader
	{
		// 	XModelPieces *xmodelPieces;
		// 	PhysPreset *physPreset;
		// 	PhysConstraints *physConstraints;
		// 	DestructibleDef *destructibleDef;
		// 	XAnimParts *parts;
		XModel *model;
		void *material;
		// 	MaterialPixelShader *pixelShader;
		// 	MaterialVertexShader *vertexShader;
		// 	MaterialTechniqueSet *techniqueSet;
		GfxImage *image;
		// 	SndBank *sound;
		// 	SndPatch *soundPatch;
		// 	clipMap_t *clipMap;
		// 	ComWorld *comWorld;
		// 	GameWorldSp *gameWorldSp;
		// 	GameWorldMp *gameWorldMp;
		// 	MapEnts *mapEnts;
		// 	GfxWorld *gfxWorld;
		// 	GfxLightDef *lightDef;
		//Font_s *font;
		// 	FontIcon *fontIcon;
		// 	MenuList *menuList;
		// 	menuDef_t *menu;
		//LocalizeEntry *localize;
		WeaponVariantDef *weapon;
		// 	WeaponAttachment *attachment;
		// 	WeaponAttachmentUnique *attachmentUnique;
		// 	WeaponCamo *weaponCamo;
		// 	SndDriverGlobals *sndDriverGlobals;
		// 	FxEffectDef *fx;
		// 	FxImpactTable *impactFx;
		RawFile *rawfile;
		// 	StringTable *stringTable;
		// 	LeaderboardDef *leaderboardDef;
		// 	XGlobals *xGlobals;
		// 	ddlRoot_t *ddlRoot;
		// 	Glasses *glasses;
		// 	//TextureList *textureList;
		// 	void *textureList;
		// 	EmblemSet *emblemSet;
		// 	ScriptParseTree *scriptParseTree;
		// 	KeyValuePairs *keyValuePairs;
		// 	VehicleDef *vehicleDef;
		// 	MemoryBlock *memoryBlock;
		// 	AddonMapEnts *addonMapEnts;
		// 	TracerDef *tracerDef;
		// 	SkinnedVertsDef *skinnedVertsDef;
		// 	Qdb *qdb;
		// 	Slug *slug;
		// 	FootstepTableDef *footstepTableDef;
		// 	FootstepFXTableDef *footstepFXTableDef;
		// 	ZBarrierDef *zbarrierDef;
		void *data;
	};

	struct StringTableCell
	{
		const char* string;
		int hash;
	};

	struct StringTable
	{
		const char* name;
		int columnCount;
		int rowCount;
		StringTableCell* values;
	};


	namespace hks
	{
		struct lua_State;
		struct HashTable;
		struct cclosure;

		struct GenericChunkHeader
		{
			unsigned __int64 m_flags;
		};

		struct ChunkHeader : GenericChunkHeader
		{
			ChunkHeader* m_next;
		};

		struct UserData : ChunkHeader
		{
			unsigned __int64 m_envAndSizeOffsetHighBits;
			unsigned __int64 m_metaAndSizeOffsetLowBits;
			char m_data[8];
		};

		struct InternString
		{
			unsigned __int64 m_flags;
			unsigned __int64 m_lengthbits;
			unsigned int m_hash;
			char m_data[30];
		};

		union HksValue
		{
			cclosure* cClosure;
			void* closure;
			UserData* userData;
			HashTable* table;
			void* tstruct;
			InternString* str;
			void* thread;
			void* ptr;
			float number;
			long long i64;
			unsigned long long ui64;
			unsigned int native;
			bool boolean;
		};

		enum HksObjectType
		{
			TANY = 0xFFFFFFFE,
			TNONE = 0xFFFFFFFF,
			TNIL = 0x0,
			TBOOLEAN = 0x1,
			TLIGHTUSERDATA = 0x2,
			TNUMBER = 0x3,
			TSTRING = 0x4,
			TTABLE = 0x5,
			TFUNCTION = 0x6,  // idk
			TUSERDATA = 0x7,
			TTHREAD = 0x8,
			TIFUNCTION = 0x9, // Lua function
			TCFUNCTION = 0xA, // C function
			TUI64 = 0xB,
			TSTRUCT = 0xC,
			NUM_TYPE_OBJECTS = 0xE,
		};

		struct HksObject
		{
			HksObjectType t;
			HksValue v;
		};

		const struct hksInstruction
		{
			unsigned int code;
		};

		struct ActivationRecord
		{
			HksObject* m_base;
			const hksInstruction* m_returnAddress;
			__int16 m_tailCallDepth;
			__int16 m_numVarargs;
			int m_numExpectedReturns;
		};

		struct CallStack
		{
			ActivationRecord* m_records;
			ActivationRecord* m_lastrecord;
			ActivationRecord* m_current;
			const hksInstruction* m_current_lua_pc;
			const hksInstruction* m_hook_return_addr;
			int m_hook_level;
		};

		struct ApiStack
		{
			HksObject* top;
			HksObject* base;
			HksObject* alloc_top;
			HksObject* bottom;
		};

		struct UpValue : ChunkHeader
		{
			HksObject m_storage;
			HksObject* loc;
			UpValue* m_next;
		};

		struct CallSite
		{
			_SETJMP_FLOAT128 m_jumpBuffer[16];
			CallSite* m_prev;
		};

		enum Status
		{
			NEW = 0x1,
			RUNNING = 0x2,
			YIELDED = 0x3,
			DEAD_ERROR = 0x4,
		};

		enum HksError
		{
			HKS_NO_ERROR = 0x0,
			HKS_ERRSYNTAX = 0xFFFFFFFC,
			HKS_ERRFILE = 0xFFFFFFFB,
			HKS_ERRRUN = 0xFFFFFF9C,
			HKS_ERRMEM = 0xFFFFFF38,
			HKS_ERRERR = 0xFFFFFED4,
			HKS_THROWING_ERROR = 0xFFFFFE0C,
			HKS_GC_YIELD = 0x1,
		};

		struct lua_Debug
		{
			int event;
			const char* name;
			const char* namewhat;
			const char* what;
			const char* source;
			int currentline;
			int nups;
			int nparams;
			int ishksfunc;
			int linedefined;
			int lastlinedefined;
			char short_src[512];
			int callstack_level;
			int is_tail_call;
		};

		using lua_function = int(__fastcall*)(lua_State*);

		struct luaL_Reg
		{
			const char* name;
			lua_function function;
		};

		struct Node
		{
			HksObject m_key;
			HksObject m_value;
		};

		struct Metatable
		{
		};

		struct HashTable : ChunkHeader
		{
			Metatable* m_meta;
			unsigned int m_version;
			unsigned int m_mask;
			Node* m_hashPart;
			HksObject* m_arrayPart;
			unsigned int m_arraySize;
			Node* m_freeNode;
		};

		struct cclosure : ChunkHeader
		{
			lua_function m_function;
			HashTable* m_env;
			__int16 m_numUpvalues;
			__int16 m_flags;
			InternString* m_name;
			HksObject m_upvalues[1];
		};

		enum HksCompilerSettings_BytecodeSharingFormat
		{
			BYTECODE_DEFAULT = 0x0,
			BYTECODE_INPLACE = 0x1,
			BYTECODE_REFERENCED = 0x2,
		};

		enum HksCompilerSettings_IntLiteralOptions
		{
			INT_LITERALS_NONE = 0x0,
			INT_LITERALS_LUD = 0x1,
			INT_LITERALS_32BIT = 0x1,
			INT_LITERALS_UI64 = 0x2,
			INT_LITERALS_64BIT = 0x2,
			INT_LITERALS_ALL = 0x3,
		};

		struct HksCompilerSettings
		{
			int m_emitStructCode;
			const char** m_stripNames;
			int m_emitGlobalMemoization;
			int _m_isHksGlobalMemoTestingMode;
			HksCompilerSettings_BytecodeSharingFormat m_bytecodeSharingFormat;
			HksCompilerSettings_IntLiteralOptions m_enableIntLiterals;
			int(__fastcall* m_debugMap)(const char*, int);
		};

		enum HksBytecodeSharingMode
		{
			HKS_BYTECODE_SHARING_OFF = 0x0,
			HKS_BYTECODE_SHARING_ON = 0x1,
			HKS_BYTECODE_SHARING_SECURE = 0x2,
		};

		struct HksGcWeights
		{
			int m_removeString;
			int m_finalizeUserdataNoMM;
			int m_finalizeUserdataGcMM;
			int m_cleanCoroutine;
			int m_removeWeak;
			int m_markObject;
			int m_traverseString;
			int m_traverseUserdata;
			int m_traverseCoroutine;
			int m_traverseWeakTable;
			int m_freeChunk;
			int m_sweepTraverse;
		};

		struct GarbageCollector_Stack
		{
			void* m_storage;
			unsigned int m_numEntries;
			unsigned int m_numAllocated;
		};

		struct ProtoList
		{
			void** m_protoList;
			unsigned __int16 m_protoSize;
			unsigned __int16 m_protoAllocSize;
		};

		struct GarbageCollector
		{
			int m_target;
			int m_stepsLeft;
			int m_stepLimit;
			HksGcWeights m_costs;
			int m_unit;
			_SETJMP_FLOAT128(*m_jumpPoint)[16];
			lua_State* m_mainState;
			lua_State* m_finalizerState;
			void* m_memory;
			int m_phase;
			GarbageCollector_Stack m_resumeStack;
			GarbageCollector_Stack m_greyStack;
			GarbageCollector_Stack m_remarkStack;
			GarbageCollector_Stack m_weakStack;
			int m_finalizing;
			HksObject m_safeTableValue;
			lua_State* m_startOfStateStackList;
			lua_State* m_endOfStateStackList;
			lua_State* m_currentState;
			HksObject m_safeValue;
			void* m_compiler;
			void* m_bytecodeReader;
			void* m_bytecodeWriter;
			int m_pauseMultiplier;
			int m_stepMultiplier;
			bool m_stopped;
			int(__fastcall* m_gcPolicy)(lua_State*);
			unsigned __int64 m_pauseTriggerMemoryUsage;
			int m_stepTriggerCountdown;
			unsigned int m_stringTableIndex;
			unsigned int m_stringTableSize;
			UserData* m_lastBlackUD;
			UserData* m_activeUD;
		};

		enum MemoryManager_ChunkColor
		{
			RED = 0x0,
			BLACK = 0x1,
		};

		struct ChunkList
		{
			ChunkHeader m_prevToStart;
		};

		enum Hks_DeleteCheckingMode
		{
			HKS_DELETE_CHECKING_OFF = 0x0,
			HKS_DELETE_CHECKING_ACCURATE = 0x1,
			HKS_DELETE_CHECKING_SAFE = 0x2,
		};

		struct MemoryManager
		{
			void* (__fastcall* m_allocator)(void*, void*, unsigned __int64, unsigned __int64);
			void* m_allocatorUd;
			MemoryManager_ChunkColor m_chunkColor;
			unsigned __int64 m_used;
			unsigned __int64 m_highwatermark;
			ChunkList m_allocationList;
			ChunkList m_sweepList;
			ChunkHeader* m_lastKeptChunk;
			lua_State* m_state;
			ChunkList m_deletedList;
			int m_deleteMode;
			Hks_DeleteCheckingMode m_deleteCheckingMode;
		};

		struct StaticStringCache
		{
			HksObject m_objects[41];
		};

		enum HksBytecodeEndianness
		{
			HKS_BYTECODE_DEFAULT_ENDIAN = 0x0,
			HKS_BYTECODE_BIG_ENDIAN = 0x1,
			HKS_BYTECODE_LITTLE_ENDIAN = 0x2,
		};

		struct RuntimeProfileData_Stats
		{
			unsigned __int64 hksTime;
			unsigned __int64 callbackTime;
			unsigned __int64 gcTime;
			unsigned __int64 cFinalizerTime;
			unsigned __int64 compilerTime;
			unsigned int hkssTimeSamples;
			unsigned int callbackTimeSamples;
			unsigned int gcTimeSamples;
			unsigned int compilerTimeSamples;
			unsigned int num_newuserdata;
			unsigned int num_tablerehash;
			unsigned int num_pushstring;
			unsigned int num_pushcfunction;
			unsigned int num_newtables;
		};

		struct RuntimeProfileData
		{
			__int64 stackDepth;
			__int64 callbackDepth;
			unsigned __int64 lastTimer;
			RuntimeProfileData_Stats frameStats;
			unsigned __int64 gcStartTime;
			unsigned __int64 finalizerStartTime;
			unsigned __int64 compilerStartTime;
			unsigned __int64 compilerStartGCTime;
			unsigned __int64 compilerStartGCFinalizerTime;
			unsigned __int64 compilerCallbackStartTime;
			__int64 compilerDepth;
			void* outFile;
			lua_State* rootState;
		};

		typedef int32_t hksBool;
		typedef char hksChar;
		typedef uint8_t hksByte;
		typedef int16_t hksShort16;
		typedef uint16_t hksUshort16;
		typedef float HksNumber;
		typedef int32_t hksInt32;
		typedef uint32_t hksUint32;
		typedef int64_t hksInt64;
		typedef uint64_t hksUint64;
		typedef size_t hksSize;
		typedef int32_t ErrorCode;
		typedef hksInt32(*lua_CFunction)(void*);
		typedef void (*HksLogFunc)(struct lua_State*, const char*, ...);
		typedef void (*HksEmergencyGCFailFunc)(struct lua_State*, size_t);

		struct HksGlobal
		{
			MemoryManager m_memory;
			GarbageCollector m_collector;
			StringTable m_stringTable;
			__int64 padding3;
			HksBytecodeSharingMode m_bytecodeSharingMode;
			int padding;
			HksObject m_registry;
			ChunkList m_userDataList;
			lua_State* m_root;
			StaticStringCache m_staticStringCache;
			void* m_debugger;
			void* m_profiler;
			RuntimeProfileData m_runProfilerData;
			HksCompilerSettings m_compilerSettings;
			int(*m_panicFunction)(lua_State*);
			void* m_luaplusObjectList;
			int m_heapAssertionFrequency;
			int m_heapAssertionCount;
			void (*m_logFunction)(lua_State*, const char*, ...);
			void (*m_emergencyGCFailFunction)(lua_State*, size_t);
			HksBytecodeEndianness m_bytecodeDumpEndianness;
			int padding2;
		};

		struct lua_State : ChunkHeader
		{
			HksGlobal* m_global;
			CallStack m_callStack;
			ApiStack m_apistack;
			UpValue* pending;
			HksObject globals;
			HksObject m_cEnv;
			CallSite* m_callsites;
			int m_numberOfCCalls;
			void* m_context;
			InternString* m_name;
			lua_State* m_nextState;
			lua_State* m_nextStateStack;
			Status m_status;
			HksError m_error;
		};
	}
}