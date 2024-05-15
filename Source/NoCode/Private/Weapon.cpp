// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Characters/SlashCharacter.h"

void AWeapon::Equip(USceneComponent *InParent, FName InSocketName)
{
    FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
    ItemMesh->AttachToComponent(InParent, TransformRules, InSocketName);
    ItemState = EItemState::EIS_Equipped;
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
    
}

void AWeapon::OnSphereEndlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
    Super::OnSphereEndlap(OverlappedComponent,OtherActor, OtherComp, OtherBodyIndex);
}
