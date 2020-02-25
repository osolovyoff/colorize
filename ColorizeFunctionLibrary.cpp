#include "ColorizeFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void UColorizeFunctionLibrary::ColorizeNearest(const FVector& NearestTo, UWorld* World, TSubclassOf<AActor> ActorClass, const uint8 QtyNearest)
{
    TArray<AActor*> Founds;
    UGameplayStatics::GetAllActorsOfClass(World, ActorClass, Founds);

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
        DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FVector(255,0,0));
        StaticMeshComponent->SetMaterial(0, DynamicMaterial);

        ++Counter;
    }
}
