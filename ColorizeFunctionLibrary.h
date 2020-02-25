#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ColorizeFunctionLibrary.generated.h"

UCLASS()
class SOLOVYOFF_API UColorizeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Colour")
    static void ColorizeNearest(const FVector& NearestTo, UWorld* World, TSubclassOf<AActor> ActorClass, const uint8 QtyNearest = 2);
};
