// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Initial_IntegrationCharacter.h"

#include "QuestManager.h"
#include "PlayStyleManager.h"

//#include "Interactable.h"
#include "CustomPlayerController.h"

#include "Engine.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "GameFramework/SpringArmComponent.h"


//////////////////////////////////////////////////////////////////////////
// AThird_PersonCharacter

AInitial_IntegrationCharacter::AInitial_IntegrationCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	style  = CreateDefaultSubobject<UPlayStyleManager>(FName("Style Manager"));


	//style = new *APlayStyleManager();
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AInitial_IntegrationCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AInitial_IntegrationCharacter::OnInteract);

	//PlayerInputComponent->BindAction("QuestList", IE_Pressed, this, &AInitial_IntegrationCharacter::OnQuestList);

	//PlayerInputComponent->BindAction("HistoryGUI", IE_Pressed, this, &AInitial_IntegrationCharacter::OnHistoryGUI);

	//PlayerInputComponent->BindAction("EvolutionGUI", IE_Pressed, this, &AInitial_IntegrationCharacter::OnEvolutionGUI);

	PlayerInputComponent->BindAxis("MoveForward", this, &AInitial_IntegrationCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AInitial_IntegrationCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AInitial_IntegrationCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AInitial_IntegrationCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AInitial_IntegrationCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AInitial_IntegrationCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AInitial_IntegrationCharacter::OnResetVR);
}


void AInitial_IntegrationCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AInitial_IntegrationCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AInitial_IntegrationCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AInitial_IntegrationCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AInitial_IntegrationCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AInitial_IntegrationCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AInitial_IntegrationCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

/*
void AInitial_IntegrationCharacter::OnInteract()
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Interacting!!"));
	}
}

void AInitial_IntegrationCharacter::OnQuestList()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Quest List!!"));
	}
}

void AInitial_IntegrationCharacter::OnEvolutionGUI()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Evo GUI!!"));
	}
}

void AInitial_IntegrationCharacter::OnHistoryGUI()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("History GUI!!"));
	}
}

void AInitial_IntegrationCharacter::CheckForInteracables()
{
	FHitResult hitResult;

	FVector startTrace = FollowCamera->GetComponentLocation();
	FVector endTrace = (FollowCamera->GetForwardVector() * 500) + startTrace;

	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActor(this);

	ACustomPlayerController* controller = Cast<ACustomPlayerController>(GetController());

	if (GetWorld()->LineTraceSingleByChannel(hitResult, startTrace, endTrace, ECC_Visibility, queryParams) && controller)
	{
		if (AInteractable* interactable = Cast<AInteractable>(hitResult.GetActor()))
		{
			controller->currentInteractable = interactable;
			return;
		}
	}

	if(controller)
		controller->currentInteractable = NULL;
}
*/

bool AInitial_IntegrationCharacter::AddQuest(UQuest* addQuest) 
{
	return true; 
}

bool AInitial_IntegrationCharacter::CompleteQuest(UQuest* completeQuest)
{
	return true;
}

bool AInitial_IntegrationCharacter::AbandonQuest(UQuest* abandonQuest)
{
	return true;
}

bool AInitial_IntegrationCharacter::AlreadyAccepted(UQuest* compQuest)
{
	return true;
}

// Called every frame
void AInitial_IntegrationCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//CheckForInteracables();

}