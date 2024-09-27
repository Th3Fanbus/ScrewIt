/* SPDX-License-Identifier: MPL-2.0 */

#include "Screwer.h"
#include "ScrewIt.h"
#include "Algo/Transform.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Resources/FGItemDescriptor.h"
#include "FGItemCategory.h"
#include "FGEmote.h"
#include "FGRecipe.h"
#include "FGSchematic.h"

/* Special thanks to Archengius for this snippet of code */
static void DiscoverSubclassesOf(TSet<FTopLevelAssetPath>& out_AllClasses, UClass* BaseClass)
{
	TArray<FTopLevelAssetPath> NativeRootClassPaths;
	TArray<UClass*> NativeRootClasses;
	GetDerivedClasses(BaseClass, NativeRootClasses);
	NativeRootClasses.Add(BaseClass);

	const auto predicate = [](const UClass* RootClass) { return RootClass && RootClass->HasAnyClassFlags(CLASS_Native); };
	const auto transform = &UClass::GetClassPathName;
	Algo::TransformIf(NativeRootClasses, NativeRootClassPaths, predicate, transform);

	IAssetRegistry::Get()->GetDerivedClassNames(NativeRootClassPaths, {}, out_AllClasses);
	out_AllClasses.Append(NativeRootClassPaths);
}

void FScrewer::Screw()
{
	UE_LOG(LogScrewIt, Verbose, TEXT("Looking for '%s'..."), *BaseClass->GetName());
	TSet<FTopLevelAssetPath> AssetPaths;
	DiscoverSubclassesOf(AssetPaths, BaseClass);
	Algo::Transform(AssetPaths, SoftPaths, [](const FTopLevelAssetPath& AssetPath) { return FSoftObjectPath(AssetPath); });
	UE_LOG(LogScrewIt, Display, TEXT("Screwing %d '%s'..."), SoftPaths.Num(), *BaseClass->GetName());
	const double Begin = FPlatformTime::Seconds();
	UAssetManager::GetStreamableManager().RequestAsyncLoad(SoftPaths, [this, Begin]() {
		const double Mid = FPlatformTime::Seconds();
		UE_LOG(LogScrewIt, Display, TEXT("Took %f ms to load '%s'"), (Mid - Begin) * 1000, *BaseClass->GetName());
		for (const FSoftObjectPath& Path : SoftPaths) {
			Invoke(HandlerFunc, Path);
		}
		const double End = FPlatformTime::Seconds();
		UE_LOG(LogScrewIt, Display, TEXT("Done screwing '%s' in %f ms"), *BaseClass->GetName(), (Mid - Begin) * 1000);
	}, FStreamableManager::DefaultAsyncLoadPriority); // AsyncLoadHighPriority
}
