#include "Colorizer.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"

AColorizer::AColorizer()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AColorizer::BeginPlay()
{
	Super::BeginPlay();
}

void AColorizer::ColorizeNearest(TSubclassOf<AActor> ActorClass, const uint8 QtyNearest)
{
    TArray<AActor*> Founds;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ActorClass, Founds);

    const FVector NearestTo = GetActorLocation();

    TMap<float, AStaticMeshActor*> Map;
    for (AActor* Actor: Founds)
    {
        AStaticMeshActor* StaticMesh = Cast<AStaticMeshActor>(Actor);
        if (StaticMesh)
        {
            const FVector Location = Actor->GetActorLocation();
            const float Distance = FVector::Distance(Location, NearestTo);
            Map.Add(Distance, StaticMesh);    
        }
    }

    Map.KeySort([](float A, float B) {
        return A < B; 
    });

    uint32 Counter = 0;
    for (auto& Element: Map)
    {
        if (Counter == QtyNearest)
            break;

        AStaticMeshActor* StaticMeshActor = Element.Value;
        UStaticMeshComponent* StaticMeshComponent = StaticMeshActor->GetStaticMeshComponent();
        UMaterialInterface* Material = StaticMeshComponent->GetMaterial(0);
        UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, NULL);
        DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FVector(1,0,0));
        StaticMeshComponent->SetMaterial(0, DynamicMaterial);    

        ++Counter;
    }
}