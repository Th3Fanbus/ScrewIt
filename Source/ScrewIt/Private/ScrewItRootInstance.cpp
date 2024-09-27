/* SPDX-License-Identifier: MPL-2.0 */

#include "ScrewItRootInstance.h"

#include "Containers/EnumAsByte.h"
#include "Reflection/ClassGenerator.h"
#include "Registry/ModContentRegistry.h"
#include "Resources/FGBuildingDescriptor.h"
#include "Buildables/FGBuildableGeneratorFuel.h"
#include "FGCustomizationRecipe.h"
#include "FGRecipe.h"
#include "FGRecipeManager.h"
#include "FGSchematic.h"
#include "Logging/LogMacros.h"
#include "Logging/StructuredLog.h"
#include "UObject/UObjectGlobals.h"
#include "Algo/Accumulate.h"
#include "Algo/AllOf.h"
#include "Algo/AnyOf.h"
#include "Algo/ForEach.h"
#include "Algo/Reverse.h"
#include "Algo/Transform.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/AssetManager.h"

#define TH3_PROJECTION_THIS(FuncName) \
	[this](auto&&... Args) -> decltype(auto) \
	{ \
		return FuncName(Forward<decltype(Args)>(Args)...); \
	}


void UScrewItRootInstance::ScrewOneTapeData(const TSubclassOf<UFGTapeData>& TapeDataClass)
{
	if (!TapeDataClass) {
		UE_LOG(LogScrewIt, Error, TEXT("Got nullptr TapeDataClass"));
		return;
	}
	UFGTapeData* TapeDataCDO = TapeDataClass.GetDefaultObject();
	if (!TapeDataCDO) {
		UE_LOG(LogScrewIt, Error, TEXT("TapeDataClass %s has nullptr CDO"), *TapeDataClass->GetName());
		return;
	}
	TapeDataCDO->mTitle = ScrewCDO->mDisplayName;
	TapeDataCDO->mDescription = ScrewCDO->mDescription;
	TapeDataCDO->mSmallIcon = ScrewCDO->mPersistentBigIcon;
	TapeDataCDO->mBigIcon = ScrewCDO->mPersistentBigIcon;

	EditedCDOs.Add(TapeDataCDO);
}

void UScrewItRootInstance::ScrewOneUnlock(UFGUnlock* Unlock)
{
	if (!Unlock) {
		UE_LOG(LogScrewIt, Error, TEXT("Got nullptr Unlock"));
		return;
	}
	if (UFGUnlockTape* UnlockTape = Cast<UFGUnlockTape>(Unlock)) {
		Algo::ForEach(UnlockTape->mTapeUnlocks, TH3_PROJECTION_THIS(ScrewOneTapeData));
	}
	if (UFGUnlockArmEquipmentSlot* UnlockArm = Cast<UFGUnlockArmEquipmentSlot>(Unlock)) {

	}
	if (UFGUnlockBlueprints* UnlockBP = Cast<UFGUnlockBlueprints>(Unlock)) {

	}
	if (UFGUnlockBuildEfficiency* UnlockBuildEff = Cast<UFGUnlockBuildEfficiency>(Unlock)) {

	}
	if (UFGUnlockBuildOverclock* UnlockBuildOC = Cast<UFGUnlockBuildOverclock>(Unlock)) {

	}
	if (UFGUnlockCheckmark* UnlockCheckmark = Cast<UFGUnlockCheckmark>(Unlock)) {

	}
	if (UFGUnlockCustomizer* UnlockCustomizer = Cast<UFGUnlockCustomizer>(Unlock)) {

	}
	if (UFGUnlockEmote* UnlockEmote = Cast<UFGUnlockEmote>(Unlock)) {

	}
	if (UFGUnlockGiveItem* UnlockGiveItem = Cast<UFGUnlockGiveItem>(Unlock)) {

	}
	if (UFGUnlockInfoOnly* UnlockInfoOnly = Cast<UFGUnlockInfoOnly>(Unlock)) {
		UnlockInfoOnly->mUnlockName = ScrewCDO->mDisplayName;
		UnlockInfoOnly->mUnlockDescription = ScrewCDO->mDescription;
		UnlockInfoOnly->mUnlockIconBig = ScrewCDO->mPersistentBigIcon;
		UnlockInfoOnly->mUnlockIconSmall = ScrewCDO->mPersistentBigIcon;
		UnlockInfoOnly->mUnlockIconCategory = ScrewCDO->mPersistentBigIcon;
	}
	if (UFGUnlockInventorySlot* UnlockInventorySlot = Cast<UFGUnlockInventorySlot>(Unlock)) {

	}
	if (UFGUnlockMap* UnlockMap = Cast<UFGUnlockMap>(Unlock)) {

	}
	if (UFGUnlockRecipe* UnlockRecipe = Cast<UFGUnlockRecipe>(Unlock)) {

	}
	if (UFGUnlockScannableObject* UnlockScannableObject = Cast<UFGUnlockScannableObject>(Unlock)) {

	}
	if (UFGUnlockScannableResource* UnlockScannableResource = Cast<UFGUnlockScannableResource>(Unlock)) {

	}
	if (UFGUnlockSchematic* UnlockSchematic = Cast<UFGUnlockSchematic>(Unlock)) {

	}
}
void UScrewItRootInstance::ScrewOneBuilding(const TSubclassOf<AFGBuildable>& BuildableClass)
{
	if (!BuildableClass) {
		UE_LOG(LogScrewIt, Error, TEXT("Got nullptr BuildableClass"));
		return;
	}
	AFGBuildable* BuildableCDO = BuildableClass.GetDefaultObject();
	if (!BuildableCDO) {
		UE_LOG(LogScrewIt, Error, TEXT("BuildableClass %s has nullptr CDO"), *BuildableClass->GetName());
		return;
	}
	BuildableCDO->mDisplayName = ScrewCDO->mDisplayName;
	BuildableCDO->mDescription = ScrewCDO->mDescription;

	EditedCDOs.Add(BuildableCDO);
}

void UScrewItRootInstance::ScrewOneVehicle(const TSubclassOf<AFGVehicle>& VehicleClass)
{
	if (!VehicleClass) {
		UE_LOG(LogScrewIt, Error, TEXT("Got nullptr VehicleClass"));
		return;
	}
	AFGVehicle* VehicleCDO = VehicleClass.GetDefaultObject();
	if (!VehicleCDO) {
		UE_LOG(LogScrewIt, Error, TEXT("VehicleClass %s has nullptr CDO"), *VehicleClass->GetName());
		return;
	}
	VehicleCDO->mDisplayName = ScrewCDO->mDisplayName;
	VehicleCDO->mDescription = ScrewCDO->mDescription;
	VehicleCDO->mActorRepresentationTexture = ScrewCDO->mPersistentBigIcon;
	VehicleCDO->mMapText = ScrewCDO->mDisplayName;

	EditedCDOs.Add(VehicleCDO);
}

void UScrewItRootInstance::ScrewOneItem(const FSoftObjectPath& Path)
{
	const TSubclassOf<UFGItemDescriptor> ItemClass = TSoftClassPtr<UFGItemDescriptor>(Path).Get();
	if (!ItemClass) {
		UE_LOG(LogScrewIt, Error, TEXT("Got nullptr ItemClass"));
		return;
	}
	UFGItemDescriptor* ItemCDO = ItemClass.GetDefaultObject();
	if (!ItemCDO) {
		UE_LOG(LogScrewIt, Error, TEXT("ItemClass %s has nullptr CDO"), *ItemClass->GetName());
		return;
	}
	ItemCDO->mDisplayName = ScrewCDO->mDisplayName;
	ItemCDO->mDescription = ScrewCDO->mDescription;
	ItemCDO->mAbbreviatedDisplayName = ScrewCDO->mAbbreviatedDisplayName;
	ItemCDO->mSmallIcon = ScrewCDO->mPersistentBigIcon;
	ItemCDO->mPersistentBigIcon = ScrewCDO->mPersistentBigIcon;
	ItemCDO->mConveyorMesh = ScrewCDO->mConveyorMesh;
	ItemCDO->mFluidColor = ScrewColor;
	ItemCDO->mGasColor = ScrewColor;
	ItemCDO->mScannerLightColor = ScrewColor;

	if (UFGBuildingDescriptor* BuildingCDO = Cast<UFGBuildingDescriptor>(ItemCDO)) {
		ScrewOneBuilding(BuildingCDO->mBuildableClass);
	}
	if (UFGVehicleDescriptor* VehicleCDO = Cast<UFGVehicleDescriptor>(ItemCDO)) {
		ScrewOneVehicle(VehicleCDO->mVehicleClass);
	}
	if (UFGCreatureDescriptor* CreatureCDO = Cast<UFGCreatureDescriptor>(ItemCDO)) {
		CreatureCDO->mSmallIconArachnophobiaMode = ScrewCDO->mPersistentBigIcon;
		CreatureCDO->mBigIconArachnophobiaMode = ScrewCDO->mPersistentBigIcon;
	}
	if (UFGResourceDescriptor* ResourceCDO = Cast<UFGResourceDescriptor>(ItemCDO)) {
		ResourceCDO->mCompassTexture = ScrewCDO->mPersistentBigIcon;
		ResourceCDO->mPingColor = ScrewColor;
	}

	EditedCDOs.Add(ItemCDO);
}

void UScrewItRootInstance::ScrewOneRecipe(const FSoftObjectPath& Path)
{
	const TSubclassOf<UFGRecipe> RecipeClass = TSoftClassPtr<UFGRecipe>(Path).Get();
	if (!RecipeClass) {
		UE_LOG(LogScrewIt, Error, TEXT("Got nullptr RecipeClass"));
		return;
	}
	UFGRecipe* RecipeCDO = RecipeClass.GetDefaultObject();
	if (!RecipeCDO) {
		UE_LOG(LogScrewIt, Error, TEXT("RecipeClass %s has nullptr CDO"), *RecipeClass->GetName());
		return;
	}
	if (RecipeCDO->mDisplayNameOverride) {
		RecipeCDO->mDisplayName = ScrewCDO->mDisplayName;
	}

	EditedCDOs.Add(RecipeCDO);
}

void UScrewItRootInstance::ScrewOneCategory(const FSoftObjectPath& Path)
{
	const TSubclassOf<UFGCategory> CategoryClass = TSoftClassPtr<UFGCategory>(Path).Get();
	if (!CategoryClass) {
		UE_LOG(LogScrewIt, Error, TEXT("Got nullptr CategoryClass"));
		return;
	}
	UFGCategory* CategoryCDO = CategoryClass.GetDefaultObject();
	if (!CategoryCDO) {
		UE_LOG(LogScrewIt, Error, TEXT("CategoryClass %s has nullptr CDO"), *CategoryClass->GetName());
		return;
	}
	CategoryCDO->mDisplayName = ScrewCDO->mDisplayName;
	CategoryCDO->mCategoryIcon = ScrewBrushIcon;

	EditedCDOs.Add(CategoryCDO);
}

void UScrewItRootInstance::ScrewOneSchematic(const FSoftObjectPath& Path)
{
	const TSubclassOf<UFGSchematic> SchematicClass = TSoftClassPtr<UFGSchematic>(Path).Get();
	if (!SchematicClass) {
		UE_LOG(LogScrewIt, Error, TEXT("Got nullptr SchematicClass"));
		return;
	}
	UFGSchematic* SchematicCDO = SchematicClass.GetDefaultObject();
	if (!SchematicCDO) {
		UE_LOG(LogScrewIt, Error, TEXT("SchematicClass %s has nullptr CDO"), *SchematicClass->GetName());
		return;
	}
	SchematicCDO->mDisplayName = ScrewCDO->mDisplayName;
	SchematicCDO->mDescription = ScrewCDO->mDescription;
	SchematicCDO->mSchematicIcon = ScrewBrushIcon;
	SchematicCDO->mSmallSchematicIcon = ScrewCDO->mPersistentBigIcon;

	Algo::ForEach(SchematicCDO->mUnlocks, TH3_PROJECTION_THIS(ScrewOneUnlock));

	EditedCDOs.Add(SchematicCDO);
}

void UScrewItRootInstance::ScrewOneEmote(const FSoftObjectPath& Path)
{
	const TSubclassOf<UFGEmote> EmoteClass = TSoftClassPtr<UFGEmote>(Path).Get();
	if (!EmoteClass) {
		UE_LOG(LogScrewIt, Error, TEXT("Got nullptr EmoteClass"));
		return;
	}
	UFGEmote* EmoteCDO = EmoteClass.GetDefaultObject();
	if (!EmoteCDO) {
		UE_LOG(LogScrewIt, Error, TEXT("EmoteClass %s has nullptr CDO"), *EmoteClass->GetName());
		return;
	}
	EmoteCDO->mEmoteName = ScrewCDO->mDisplayName;
	EmoteCDO->mEmoteIcon = ScrewCDO->mPersistentBigIcon;

	EditedCDOs.Add(EmoteCDO);
}

void UScrewItRootInstance::DispatchLifecycleEvent(ELifecyclePhase Phase)
{
	Super::DispatchLifecycleEvent(Phase);

	ScrewCDO = ScrewClass.GetDefaultObject();
	if (!ScrewCDO) {
		UE_LOG(LogScrewIt, Error, TEXT("Screw class CDO is nullptr, bailing out"));
		return;
	}

	if (Phase == ELifecyclePhase::CONSTRUCTION) {
		RegisterScrewerType<UFGItemDescriptor>(TH3_PROJECTION_THIS(ScrewOneItem));
		RegisterScrewerType<UFGRecipe>(TH3_PROJECTION_THIS(ScrewOneRecipe));
		RegisterScrewerType<UFGCategory>(TH3_PROJECTION_THIS(ScrewOneCategory));
		RegisterScrewerType<UFGSchematic>(TH3_PROJECTION_THIS(ScrewOneSchematic));
		RegisterScrewerType<UFGEmote>(TH3_PROJECTION_THIS(ScrewOneEmote));

		/* Screw main menu early */
		ScrewOneItem(FSoftObjectPath(NuclearWasteClass));
	}
	if (Phase == ELifecyclePhase::POST_INITIALIZATION) {
		UE_LOG(LogScrewIt, Display, TEXT("Screwing up..."));
		for (TSharedRef<FScrewer>& Screwer : Screwers) {
			Screwer->Screw();
		}
	}
}