/* SPDX-License-Identifier: MPL-2.0 */

#pragma once

#include "CoreMinimal.h"
#include "ScrewIt.h"
#include "Screwer.h"
#include "Module/GameInstanceModule.h"
#include "Resources/FGTapeData.h"
#include "Resources/FGItemDescriptor.h"
#include "Resources/FGBuildingDescriptor.h"
#include "Resources/FGResourceDescriptor.h"
#include "Resources/FGVehicleDescriptor.h"
#include "Creature/FGCreatureDescriptor.h"
#include "FGResourceSinkSettings.h"
#include "FGItemCategory.h"
#include "FGEmote.h"
#include "FGRecipe.h"
#include "FGSchematic.h"
#include "FGVehicle.h"
#include "FGUnlockTape.h"
#include "Unlocks/FGUnlock.h"
#include "Unlocks/FGUnlockArmEquipmentSlot.h"
#include "Unlocks/FGUnlockBlueprints.h"
#include "Unlocks/FGUnlockBuildEfficiency.h"
#include "Unlocks/FGUnlockBuildOverclock.h"
#include "Unlocks/FGUnlockCheckmark.h"
#include "Unlocks/FGUnlockCustomizer.h"
#include "Unlocks/FGUnlockEmote.h"
#include "Unlocks/FGUnlockGiveItem.h"
#include "Unlocks/FGUnlockInfoOnly.h"
#include "Unlocks/FGUnlockInventorySlot.h"
#include "Unlocks/FGUnlockMap.h"
#include "Unlocks/FGUnlockRecipe.h"
#include "Unlocks/FGUnlockScannableObject.h"
#include "Unlocks/FGUnlockScannableResource.h"
#include "Unlocks/FGUnlockSchematic.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

#include "ScrewItRootInstance.generated.h"

UCLASS(Abstract)
class SCREWIT_API UScrewItRootInstance : public UGameInstanceModule
{
	GENERATED_BODY()
private:
	/* Marked as UPROPERTY because it holds CDO edits */
	UPROPERTY()
	TSet<UObject*> EditedCDOs;

	UPROPERTY(Transient)
	const UFGItemDescriptor* ScrewCDO;

	/* Blue screw color */
	const FColor ScrewColor = FColor(0, 102, 255);

	TArray<TSharedRef<FScrewer>> Screwers;
protected:
	template<typename T>
	void RegisterScrewerType(const TFunction<void(const FSoftObjectPath&)> HandlerFunc)
	{
		Screwers.Add(MakeShared<FScrewer>(T::StaticClass(), HandlerFunc));
	}

	void ScrewOneBuilding(const TSubclassOf<AFGBuildable>& BuildableClass);
	void ScrewOneVehicle(const TSubclassOf<AFGVehicle>& VehicleClass);
	void ScrewOneTapeData(const TSubclassOf<UFGTapeData>& TapeDataClass);

	void ScrewOneUnlock(UFGUnlock* Unlock);

	void ScrewOneItem(const FSoftObjectPath& Path);
	void ScrewOneRecipe(const FSoftObjectPath& Path);
	void ScrewOneCategory(const FSoftObjectPath& Path);
	void ScrewOneSchematic(const FSoftObjectPath& Path);
	void ScrewOneEmote(const FSoftObjectPath& Path);
public:
	virtual void DispatchLifecycleEvent(ELifecyclePhase Phase) override;

	UPROPERTY(EditDefaultsOnly, Category = "Mod Configuration")
	const TSubclassOf<UFGItemDescriptor> NuclearWasteClass;
	UPROPERTY(EditDefaultsOnly, Category = "Mod Configuration")
	const TSubclassOf<UFGItemDescriptor> ScrewClass;
	UPROPERTY(EditDefaultsOnly, Category = "Mod Configuration")
	FSlateBrush ScrewBrushIcon;
};
