// Copyright Gujianyi


#include "AbilitySystem/Abilities/AuraSummonAbility.h"

#include "NiagaraBakerSettings.h"
#include "Kismet/KismetSystemLibrary.h"


TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();//获取召唤师的朝向
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();//获取召唤师的位置
	const float DeltaSpread = SpawnSpread / NumMinions;//将召唤的角度范围进行分段，在每段里面生成一个召唤物

	
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread / 2.f, FVector::UpVector);//获取到最左侧的角度
	TArray<FVector> SpawnLocations;
	for (int32 i = 0; i < NumMinions; i++)//遍历，在每个分段上面获取位置
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);//获取当前分段的角度
		const FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);//随机位置，加上原始位置就是偏移的位置
		SpawnLocations.Add(ChosenSpawnLocation);
		
		DrawDebugSphere(GetWorld(), ChosenSpawnLocation, 18.f, 12, FColor::Cyan, false, 3.f );
		UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Location, Location + Direction * MaxSpawnDistance, 4.f, FLinearColor::Green, 3.f );
		DrawDebugSphere(GetWorld(), Location + Direction * MinSpawnDistance, 5.f, 12, FColor::Red, false, 3.f );
		DrawDebugSphere(GetWorld(), Location + Direction * MaxSpawnDistance, 5.f, 12, FColor::Red, false, 3.f );
	}
	
	return SpawnLocations;
}