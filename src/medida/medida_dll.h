#ifndef MEDIDA_DLL_H_
#define MEDIDA_DLL_H_

#ifdef MEDIDA_VS_EXPORTS
#	define DLLEXPORT __declspec(dllexport)
#else
#	define DLLEXPORT __declspec(dllimport)
#endif // MEDIDA_VS_EXPORTS
#endif // !MEDIDA_DLL_H_
