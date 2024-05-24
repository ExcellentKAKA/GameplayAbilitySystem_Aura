// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define CUSTOM_DEPTH_RED 250

//ECollisionChannel::ECC_GameTraceChannel1在Editor上创建了新Channel，对应着ECC_GameTraceChannel1, ECC_GameTraceChannel2...
#define ECC_Projectile ECollisionChannel::ECC_GameTraceChannel1
#define ECC_Target ECollisionChannel::ECC_GameTraceChannel2
#define ECC_ExcludePlayer ECollisionChannel::ECC_GameTraceChannel3