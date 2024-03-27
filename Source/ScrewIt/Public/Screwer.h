/* SPDX-License-Identifier: MPL-2.0 */

#pragma once

#include "CoreMinimal.h"

class SCREWIT_API FScrewer final
{
protected:
	UClass* BaseClass;
	TArray<FSoftObjectPath> SoftPaths;
	const TFunction<void(const FSoftObjectPath&)> HandlerFunc;
public:
	FScrewer(UClass* InBaseClass, const TFunction<void(const FSoftObjectPath&)> InHandlerFunc) : BaseClass(InBaseClass), HandlerFunc(InHandlerFunc)
	{
	}
	void Screw();
};
