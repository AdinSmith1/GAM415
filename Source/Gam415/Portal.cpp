// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Gam415Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// creating mesh, scene capture, and arrow
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Comp");
	sceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>("Capture");
	rootArrow = CreateDefaultSubobject<UArrowComponent>("Root Arrow");

	RootComponent = boxComp;
	mesh->SetupAttachment(boxComp);
	sceneCapture->SetupAttachment(mesh);
	rootArrow->SetupAttachment(RootComponent);


	// turn off mesh collision so player can walk through portal
	mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);
	mesh->SetHiddenInSceneCapture(true);
	
	 
	// if material is valid set mesh material
	if (mat)
	{
		mesh->SetMaterial(0, mat);
	}

}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdatePortals();

}


void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGam415Character* playerChar = Cast<AGam415Character>(OtherActor);

	// check if cast to player character is valid
	if (playerChar)
	{
		// check if other portal is valid
		if (OtherPortal)
		{
			// check if already teleporting, probably so you dont get teleported multiple times while going through the portal.
			if (!playerChar->isTeleporting)
			{
				// sets isTeleporting to true, then gets location of other portal and moves the character to the location.
				playerChar->isTeleporting = true;
				FVector loc = OtherPortal->rootArrow->GetComponentLocation();
				playerChar->SetActorLocation(loc);

				// one second delay until you can teleport again
				FTimerHandle TimeHandle;
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindUFunction(this, "SetBool", playerChar);
				GetWorld()->GetTimerManager().SetTimer(TimeHandle, TimerDelegate, 1, false);


			}
		}
	}
}



// turn off isTeleporting
void APortal::SetBool(AGam415Character* playerChar)
{
	// turn off isTeleporting if cast to playerChar is valid
	if (playerChar)
	{
		playerChar->isTeleporting = false;
	}
}

// updates portal visual
void APortal::UpdatePortals()
{
	// get location of portal one I think
	FVector Location = this->GetActorLocation() - OtherPortal->GetActorLocation();
	// get player camera location and rotation
	FVector camLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentLocation();
	FRotator camRotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentRotation();
	FVector CombinedLocation = camLocation + Location;

	// sets location of scene capture
	sceneCapture->SetWorldLocationAndRotation(CombinedLocation, camRotation);
}

