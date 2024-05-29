#pragma once
//#define MAKEDLL 1

#ifdef MAKEDLL
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif