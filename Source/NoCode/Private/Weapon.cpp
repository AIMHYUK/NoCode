// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Characters/SlashCharacter.h"



void AWeapon::OnSphereOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
    
    UE_LOG(LogTemp, Warning, TEXT("overlapped"));
    ASlashCharacter* SlashCharacter = Cast<ASlashCharacter>(OtherActor);
    if(SlashCharacter)
    {
        FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
        ItemMesh->AttachToComponent(SlashCharacter->GetMesh(), TransformRules, FName("RightHandSocket"));
    }  
}

void AWeapon::OnSphereEndlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
    Super::OnSphereEndlap(OverlappedComponent,OtherActor, OtherComp, OtherBodyIndex);
}
