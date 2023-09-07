

#include "FuckingPlatform.h"

	AFuckingPlatform::AFuckingPlatform()
	{		
		PrimaryActorTick.bCanEverTick = true;

		SetMobility(EComponentMobility::Movable);
	}




	void AFuckingPlatform::BeginPlay()
	{


	}

	void AFuckingPlatform::Tick(float DeltaTime)
	{
		Super::Tick(DeltaTime);


		SetActorLocation(GetActorLocation() += FVector{ 10 * DeltaTime , 0 ,0 });



	}
