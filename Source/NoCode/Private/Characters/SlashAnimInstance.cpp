// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SlashAnimInstance.h"
#include "Characters/SlashCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


void USlashAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    SlashCharacter = Cast<ASlashCharacter>(TryGetPawnOwner());
    if(SlashCharacter)
    {
        SlashCharacterMovement = SlashCharacter->GetCharacterMovement(); //캐릭터 이동
    }
    
}

void USlashAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
    Super::NativeUpdateAnimation(DeltaTime);
    if(SlashCharacterMovement)
    {      
        GroundSpeed = UKismetMathLibrary::VSizeXY(SlashCharacterMovement->Velocity);
        bIsFalling = SlashCharacterMovement->IsFalling();
        CharacterState = SlashCharacter->GetCharacterState(); //게터함수 쓰자
    }
}
