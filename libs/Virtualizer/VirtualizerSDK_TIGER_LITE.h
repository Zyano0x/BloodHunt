/******************************************************************************
 Header: VirtualizerSDK_TIGER_LITE.h
 Description: Definition of CustomVM macros

 Author/s: Oreans Technologies 
 (c) 2019 Oreans Technologies

 --- File generated automatically from Oreans VM Generator (29/10/2019) ---
******************************************************************************/


// ****************************************************************************
// Declaration of Custom VM macros
// ****************************************************************************

#ifdef __cplusplus
 extern "C" {
#endif

#if defined(PLATFORM_X32)

void __stdcall VIRTUALIZER_TIGER_LITE_START_ASM32();
void __stdcall VIRTUALIZER_TIGER_LITE_END_ASM32();

#define VIRTUALIZER_TIGER_LITE_START VIRTUALIZER_TIGER_LITE_START_ASM32();
#define VIRTUALIZER_TIGER_LITE_END VIRTUALIZER_TIGER_LITE_END_ASM32();

#endif

#if defined(PLATFORM_X64)

void __stdcall VIRTUALIZER_TIGER_LITE_START_ASM64();
void __stdcall VIRTUALIZER_TIGER_LITE_END_ASM64();

#define VIRTUALIZER_TIGER_LITE_START VIRTUALIZER_TIGER_LITE_START_ASM64();
#define VIRTUALIZER_TIGER_LITE_END VIRTUALIZER_TIGER_LITE_END_ASM64();

#endif

#ifdef __cplusplus
}
#endif

