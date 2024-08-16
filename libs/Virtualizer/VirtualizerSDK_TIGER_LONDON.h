/******************************************************************************
 Header: VirtualizerSDK_TIGER_LONDON.h
 Description: Definition of CustomVM macros

 Author/s: Oreans Technologies
 (c) 2015 Oreans Technologies

 --- File generated automatically from Oreans VM Generator (27/1/2015) ---
******************************************************************************/


// ****************************************************************************
// Declaration of Custom VM macros
// ****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

#if defined(PLATFORM_X32)

	void __stdcall VIRTUALIZER_TIGER_LONDON_START_ASM32();
	void __stdcall VIRTUALIZER_TIGER_LONDON_END_ASM32();

#define VIRTUALIZER_TIGER_LONDON_START VIRTUALIZER_TIGER_LONDON_START_ASM32();
#define VIRTUALIZER_TIGER_LONDON_END VIRTUALIZER_TIGER_LONDON_END_ASM32();

#endif

#if defined(PLATFORM_X64)

	void __stdcall VIRTUALIZER_TIGER_LONDON_START_ASM64();
	void __stdcall VIRTUALIZER_TIGER_LONDON_END_ASM64();

#define VIRTUALIZER_TIGER_LONDON_START VIRTUALIZER_TIGER_LONDON_START_ASM64();
#define VIRTUALIZER_TIGER_LONDON_END VIRTUALIZER_TIGER_LONDON_END_ASM64();

#endif

#ifdef __cplusplus
}
#endif

