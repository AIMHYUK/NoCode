// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SlashCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GroomComponent.h"
#include "Item.h"
#include "Weapon.h"


ASlashCharacter::ASlashCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//BirdMesh->AttachToComponent(Capsule); //동적으로 컴포넌트 추가할때

	//AutoPossessPlayer = EAutoReceiveInput::Player0; //player 0 자동빙의

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false; //컨트롤러 회전 사용X

	GetCharacterMovement()->bOrientRotationToMovement = true; //캐릭터무브먼트 - 무브번트방향으로 세팅 조정
	GetCharacterMovement()->RotationRate = FRotator(0, 400, 0); //캐릭터 자동 회전

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprintArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300;
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(SpringArm);

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh()); //Mesh는 비공개라서 Get함수 사용
	Hair->AttachmentName = FString("head"); //머리카락을 머리에 붙일 예정

	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh()); //Mesh는 비공개라서 Get함수 사용
	Eyebrows->AttachmentName = FString("head"); //머리카락을 머리에 붙일 예정

}

// Called when the game starts or when spawned
void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if(PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if(Subsystem)
		{
			Subsystem->AddMappingContext(SlashContext, 0);
		}
	}
}

// Called every frame
void ASlashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Triggered, this, &ASlashCharacter::EKeyPressed);
	}

}

void ASlashCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetController()->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0); //가로 회전방향(YAW)만 사용

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);
	// const FVector Forward = GetActorForwardVector();
	// const FVector Right = GetActorRightVector();
	// AddMovementInput(Forward, 5000 * MovementVector.Y); //W,S 매핑
	// AddMovementInput(Right, 5000 * MovementVector.X); //W,S 매핑 -> 실제 방향이 아닌 메시가 바라보는 방향으로 진행된다.
}

void ASlashCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();
	if(GetController())
	{
		AddControllerPitchInput(-LookAxisValue.Y);
		AddControllerYawInput(LookAxisValue.X);
		// AddActorLocalRotation(FRotator(LookAxisValue.Y, LookAxisValue.X, 0.f));
	}
}
void ASlashCharacter::EKeyPressed(const FInputActionValue &Value)
{
	const bool Pressed = Value.Get<bool>();
	UE_LOG(LogTemp, Warning, TEXT("equip"));
	AWeapon* OverLappingWeapon = Cast<AWeapon>(OverlappingItem);
	if(OverLappingWeapon)
	{
		OverLappingWeapon->Equip(GetMesh(),FName("RightHandSocket")); //무기의 메쉬를 오른손 소켓에 저장
	}
}