#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Colorizer.generated.h"

UCLASS()
class SOLOVYOFF_API AColorizer : public AActor
{
	GENERATED_BODY()

public:	
	AColorizer();

    UFUNCTION(BlueprintCallable, Category = "Color")
    void ColorizeNearest(TSubclassOf<AActor> ActorClass, const uint8 QtyNearest = 2);

protected:
	virtual void BeginPlay() override;
};
